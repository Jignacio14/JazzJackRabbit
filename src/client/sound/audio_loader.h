#ifndef AUDIO_LOADER_H
#define AUDIO_LOADER_H

#include <SDL2pp/SDL2pp.hh>

class AudioLoader {
private:
  SDL2pp::Mixer &sdlMixer;

  SDL2pp::Chunk jumpSound;
  SDL2pp::Chunk groundHitSound;
  SDL2pp::Chunk gun1ShotSound;
  SDL2pp::Chunk gun2ShotSound;
  SDL2pp::Chunk gunChangeSound;
  SDL2pp::Chunk bulletImpactSound;
  SDL2pp::Chunk coinCollectedSound;
  SDL2pp::Chunk diamondCollectedSound;
  SDL2pp::Chunk carrotCollectedSound;
  SDL2pp::Chunk ammoCollectedSound;

  SDL2pp::Chunk gameOverSound;

  SDL2pp::Chunk jazzDeathSound;
  SDL2pp::Chunk jazzHurtSound;
  SDL2pp::Chunk spazDeathSound;
  SDL2pp::Chunk spazHurtSound;
  SDL2pp::Chunk loriDeathSound;
  SDL2pp::Chunk loriHurtSound;

  SDL2pp::Music carrotusBackgroundMusic;
  SDL2pp::Music beachWorldBackgroundMusic;

public:
  explicit AudioLoader(SDL2pp::Mixer &sdlMixer);

  void preloadAudios();

  SDL2pp::Chunk &getJumpSound();
  SDL2pp::Chunk &getGroundHitSound();
  SDL2pp::Chunk &getGun1ShotSound();
  SDL2pp::Chunk &getGun2ShotSound();
  SDL2pp::Chunk &getGunChangeSound();
  SDL2pp::Chunk &getBulletImpactSound();
  SDL2pp::Chunk &getCoinCollectedSound();
  SDL2pp::Chunk &getDiamondCollectedSound();
  SDL2pp::Chunk &getCarrotCollectedSound();
  SDL2pp::Chunk &getAmmoCollectedSound();

  SDL2pp::Chunk &getGameOverSound();

  SDL2pp::Chunk &getJazzDeathSound();
  SDL2pp::Chunk &getJazzHurtSound();
  SDL2pp::Chunk &getSpazDeathSound();
  SDL2pp::Chunk &getSpazHurtSound();
  SDL2pp::Chunk &getLoriDeathSound();
  SDL2pp::Chunk &getLoriHurtSound();

  SDL2pp::Music &getCarrotusBackgroundMusic();
  SDL2pp::Music &getBeachWorldBackgroundMusic();
};

#endif // AUDIO_LOADER_H