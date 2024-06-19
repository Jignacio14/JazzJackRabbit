#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "./audio_loader.h"
#include "./music.h"
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
  bool isBackgroundMusicActivated;

  // cppcheck-suppress unusedStructMember
  std::list<std::unique_ptr<SoundEffect>> sounds;

  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Music> music;

  void removeFinishedAudios();

  void playSound(SDL2pp::Chunk &soundChunk);
  void playMusic(SDL2pp::Music &musicTrack);

public:
  AudioEngine();

  void preloadAudios();

  void playJumpSound();
  void playGroundHitSound();
  void playGun1ShotSound();
  void playGun2ShotSound();
  void playGunChangeSound();
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

  void playCarrotusBackgroundMusic();
  void playBeachWorldBackgroundMusic();

  void stopPlayingBackgroundMusic();

  ~AudioEngine();
};

#endif // AUDIO_ENGINE_H