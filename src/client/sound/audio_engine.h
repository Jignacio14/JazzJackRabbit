#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "./audio_loader.h"
#include <SDL2pp/SDL2pp.hh>

class AudioEngine {
private:
  SDL2pp::SDL sdl;
  SDL2pp::Mixer sdlMixer;
  AudioLoader audioLoader;

public:
  AudioEngine();

  void preloadAudios();

  SDL2pp::Mixer &getSdlMixerReference();

  SDL2pp::Chunk &getSound();
};

#endif // AUDIO_ENGINE_H