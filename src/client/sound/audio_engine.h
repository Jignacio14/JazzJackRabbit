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

  // cppcheck-suppress unusedStructMember
  uint32_t jumpSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t groundHitSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t gun1ShotSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t gun2ShotSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t bulletImpactSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t coinCollectedSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t diamondCollectedSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t carrotCollectedSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t ammoCollectedSoundDuration;

  // cppcheck-suppress unusedStructMember
  uint32_t gameOverSoundDuration;

  // cppcheck-suppress unusedStructMember
  uint32_t jazzDeathSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t jazzHurtSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t spazDeathSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t spazHurtSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t loriDeathSoundDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t loriHurtSoundDuration;

  void removeFinishedAudios();

  void playSound(SDL2pp::Chunk &sound, uint32_t &duration);

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

  void playGameOverSound();

  void playJazzDeathSound();
  void playJazzhurtSound();
  void playSpazDeathSound();
  void playSpazHurtSound();
  void playLoriDeathSound();
  void playLorihurtSound();

  ~AudioEngine();
};

#endif // AUDIO_ENGINE_H