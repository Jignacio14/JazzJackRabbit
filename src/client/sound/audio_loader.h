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
  SDL2pp::Chunk bulletImpactSound;
  SDL2pp::Chunk coinCollectedSound;
  SDL2pp::Chunk diamondCollectedSound;
  SDL2pp::Chunk carrotCollectedSound;
  SDL2pp::Chunk ammoCollectedSound;

public:
  explicit AudioLoader(SDL2pp::Mixer &sdlMixer);

  void preloadAudios();

  SDL2pp::Chunk &getJumpSound();
  SDL2pp::Chunk &getGroundHitSound();
  SDL2pp::Chunk &getGun1ShotSound();
  SDL2pp::Chunk &getGun2ShotSound();
  SDL2pp::Chunk &getBulletImpactSound();
  SDL2pp::Chunk &getCoinCollectedSound();
  SDL2pp::Chunk &getDiamondCollectedSound();
  SDL2pp::Chunk &getCarrotCollectedSound();
  SDL2pp::Chunk &getAmmoCollectedSound();
};

#endif // AUDIO_LOADER_H