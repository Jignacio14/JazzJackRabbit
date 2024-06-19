#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include "../../common/thread.h"
#include <SDL2pp/SDL2pp.hh>

class SoundEffect : private Thread {
private:
  SDL2pp::Mixer &sdlMixer;
  SDL2pp::Chunk &sound;

public:
  SoundEffect(SDL2pp::Mixer &sdlMixer, SDL2pp::Chunk &sound);

  virtual void run() override;

  void play();

  bool isAlive() const;

  ~SoundEffect() override;
};

#endif // SOUND_EFFECT_H