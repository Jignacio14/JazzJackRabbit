#include "./audio_loader.h"

AudioLoader::AudioLoader(SDL2pp::Mixer &sdlMixer)
    : sdlMixer(sdlMixer), jumpSound("src/client/sound/files/jump.mp3"),
      groundHitSound("src/client/sound/files/ground_hit.mp3"),
      gun1ShotSound("src/client/sound/files/gun_1_shot.mp3"),
      gun2ShotSound("src/client/sound/files/gun_2_shot.mp3"),
      bulletImpactSound("src/client/sound/files/bullet_impact.mp3"),
      coinCollectedSound("src/client/sound/files/coin_collected.mp3"),
      diamondCollectedSound("src/client/sound/files/diamond_collected.mp3"),
      carrotCollectedSound("src/client/sound/files/carrot_collected.mp3"),
      ammoCollectedSound("src/client/sound/files/ammo_collected.mp3") {}

void AudioLoader::preloadAudios() {}

SDL2pp::Chunk &AudioLoader::getJumpSound() { return this->jumpSound; }

SDL2pp::Chunk &AudioLoader::getGroundHitSound() { return this->groundHitSound; }

SDL2pp::Chunk &AudioLoader::getGun1ShotSound() { return this->gun1ShotSound; }

SDL2pp::Chunk &AudioLoader::getGun2ShotSound() { return this->gun2ShotSound; }

SDL2pp::Chunk &AudioLoader::getBulletImpactSound() {
  return this->bulletImpactSound;
}

SDL2pp::Chunk &AudioLoader::getCoinCollectedSound() {
  return this->coinCollectedSound;
}

SDL2pp::Chunk &AudioLoader::getDiamondCollectedSound() {
  return this->diamondCollectedSound;
}

SDL2pp::Chunk &AudioLoader::getCarrotCollectedSound() {
  return this->carrotCollectedSound;
}

SDL2pp::Chunk &AudioLoader::getAmmoCollectedSound() {
  return this->ammoCollectedSound;
}
