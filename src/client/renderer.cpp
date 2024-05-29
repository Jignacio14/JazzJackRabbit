
#include "renderer.h"
#include "StopIteration.h"
#include <chrono>
#include <cmath>
#include <thread>

Renderer::Renderer(int id, Socket &socket)
    : client_id(id), keep_running(true), rate(RATE),
      client(std::move(socket) id) {}

double Renderer::now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(
             std::chrono::high_resolution_clock::now().time_since_epoch())
      .count();
}

void Renderer::run() {

  while (keep_running) {
    double t1 = now();
    try {
      // Game logic. Debe tirar un StopIteration. Así está en el código de
      // python. Alternativa: pasar por referencia keep_running al método
      // correspondiente y que se detenga así el loop, sin utilizar excepciones
      // para el workflow.

      // Quizas deberia poner aca client.start y que el client lance los hilos
      // en dicho metodo

    } catch (const StopIteration &) {
      break;
    }
    double t2 = now();
    double rest = rate - (t2 - t1);
    if (rest < 0) {
      double behind = -rest;
      rest = rate - fmod(behind, rate);
      double lost = behind + rest;
      // cppcheck-suppress unreadVariable
      t1 += lost;
      // it += std::floor(lost / rate); Creo que it no se usa para nada.

    } else {
      std::this_thread::sleep_for(std::chrono::duration<double>(rest));
      // cppcheck-suppress unreadVariable
      t1 += rate;
      // it++;
    }
  }
}
