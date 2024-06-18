#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "./audio_loader.h"
#include "./sound_effect.h"
#include <SDL2pp/SDL2pp.hh>
#include <list>
#include <memory>

class AudioEngine {
private:
  SDL2pp::SDL sdl;
  SDL2pp::Mixer sdlMixer;
  AudioLoader audioLoader;

  // cppcheck-suppress unusedStructMember
  std::list<std::unique_ptr<SoundEffect>> sounds;

  void removeFinishedAudios();

  void playSound(SDL2pp::Chunk &sound);

public:
  AudioEngine();

  void preloadAudios();

  // SDL2pp::Mixer &getSdlMixerReference();

  // SDL2pp::Chunk &getSound();

  void playJumpSound();
  void playGun1ShotSound();
};

#endif // AUDIO_ENGINE_H