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

  void playJumpSound();
  void playGroundHitSound();
  void playGun1ShotSound();
  void playGun2ShotSound();
  void playBulletImpactSound();
  void playCoinCollectedSound();
  void playDiamondCollectedSound();
  void playCarrotCollectedSound();
  void playAmmoCollectedSound();
};

#endif // AUDIO_ENGINE_H