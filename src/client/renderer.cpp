
#include "renderer.h"
#include "StopIteration.h"
#include <chrono>
#include <cmath>
#include <thread>

double ClientLoop::now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(
             std::chrono::high_resolution_clock::now().time_since_epoch())
      .count();
}

ClientLoop::ClientLoop(int id, double rate)
    : client_id(id), keep_running(true), rate(rate) {}

void ClientLoop::run() {

  while (keep_running) {
    double t1 = now();
    try {
      // Game logic. Debe tirar un StopIteration. Así está en el código de
      // python. Alternativa: pasar por referencia keep_running al método
      // correspondiente y que se detenga así el loop, sin utilizar excepciones
      // para el workflow.
    } catch (const StopIteration &) {
      break;
    }
    double t2 = now();
    double rest = rate - (t2 - t1);
    if (rest < 0) {
      double behind = -rest;
      rest = rate - fmod(behind, rate);
      double lost = behind + rest;
      t1 += lost;
      // it += std::floor(lost / rate); Creo que it no se usa para nada.

    } else {
      std::this_thread::sleep_for(std::chrono::duration<double>(rest));
      t1 += rate;
      // it++;
    }
  }
}
