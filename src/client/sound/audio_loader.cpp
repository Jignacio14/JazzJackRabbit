#include "./audio_loader.h"

AudioLoader::AudioLoader(SDL2pp::Mixer &sdlMixer)
    : sdlMixer(sdlMixer), jumpSound("src/client/sound/files/jump.mp3"),
      groundHitSound("src/client/sound/files/ground_hit.mp3"),
      gun1ShotSound("src/client/sound/files/gun_1_shot.mp3"),
      gun2ShotSound("src/client/sound/files/gun_2_shot.mp3"),
      gunChangeSound("src/client/sound/files/gun_change.mp3"),
      bulletImpactSound("src/client/sound/files/bullet_impact.mp3"),
      coinCollectedSound("src/client/sound/files/coin_collected.mp3"),
      diamondCollectedSound("src/client/sound/files/diamond_collected.mp3"),
      carrotCollectedSound("src/client/sound/files/carrot_collected.mp3"),
      ammoCollectedSound("src/client/sound/files/ammo_collected.mp3"),
      gameOverSound("src/client/sound/files/game_over.mp3"),
      jazzDeathSound("src/client/sound/files/jazz_death.mp3"),
      jazzHurtSound("src/client/sound/files/jazz_hurt.mp3"),
      spazDeathSound("src/client/sound/files/spaz_death.mp3"),
      spazHurtSound("src/client/sound/files/spaz_hurt.mp3"),
      loriDeathSound("src/client/sound/files/lori_death.mp3"),
      loriHurtSound("src/client/sound/files/lori_hurt.mp3"),
      carrotusBackgroundMusic(
          "src/client/sound/files/carrotus_background_music.mp3"),
      beachWorldBackgroundMusic(
          "src/client/sound/files/beach_world_background_music.mp3"),
      disconnectionSound("src/client/sound/files/disconnection_sound.mp3"),
      genericEnemyMeleeShotSound("src/client/sound/files/enemy_melee_shot.mp3"),
      bubbaHurtSound("src/client/sound/files/bubba_hurt.mp3"),
      turtleGoonHurtSound("src/client/sound/files/turtle_goon_hurt.mp3"),
      schwarzenguardHurtSound("src/client/sound/files/schwarzenguard_hurt.mp3"),
      bubbaDeathSound("src/client/sound/files/bubba_death.mp3"),
      turtleGoonDeathSound("src/client/sound/files/turtle_goon_death.mp3"),
      schwarzenguardDeathSound(
          "src/client/sound/files/schwarzenguard_death.mp3") {}

void AudioLoader::preloadAudios() {}

SDL2pp::Chunk &AudioLoader::getJumpSound() { return this->jumpSound; }

SDL2pp::Chunk &AudioLoader::getGroundHitSound() { return this->groundHitSound; }

SDL2pp::Chunk &AudioLoader::getGun1ShotSound() { return this->gun1ShotSound; }

SDL2pp::Chunk &AudioLoader::getGun2ShotSound() { return this->gun2ShotSound; }

SDL2pp::Chunk &AudioLoader::getGunChangeSound() { return this->gunChangeSound; }

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

SDL2pp::Chunk &AudioLoader::getGameOverSound() { return this->gameOverSound; }

SDL2pp::Chunk &AudioLoader::getJazzDeathSound() { return this->jazzDeathSound; }

SDL2pp::Chunk &AudioLoader::getJazzHurtSound() { return this->jazzHurtSound; }

SDL2pp::Chunk &AudioLoader::getSpazDeathSound() { return this->spazDeathSound; }

SDL2pp::Chunk &AudioLoader::getSpazHurtSound() { return this->spazHurtSound; }

SDL2pp::Chunk &AudioLoader::getLoriDeathSound() { return this->loriDeathSound; }

SDL2pp::Chunk &AudioLoader::getLoriHurtSound() { return this->loriHurtSound; }

SDL2pp::Music &AudioLoader::getCarrotusBackgroundMusic() {
  return this->carrotusBackgroundMusic;
}

SDL2pp::Music &AudioLoader::getBeachWorldBackgroundMusic() {
  return this->beachWorldBackgroundMusic;
}

SDL2pp::Chunk &AudioLoader::getDisconnectionSound() {
  return this->disconnectionSound;
}

SDL2pp::Chunk &AudioLoader::getGenericEnemyMeleeShotSound() {
  return this->genericEnemyMeleeShotSound;
}

SDL2pp::Chunk &AudioLoader::getBubbaHurtSound() { return this->bubbaHurtSound; }

SDL2pp::Chunk &AudioLoader::getTurtleGoonHurtSound() {
  return this->turtleGoonHurtSound;
}

SDL2pp::Chunk &AudioLoader::getSchwarzenguardHurtSound() {
  return this->schwarzenguardHurtSound;
}

SDL2pp::Chunk &AudioLoader::getBubbaDeathSound() {
  return this->bubbaDeathSound;
}

SDL2pp::Chunk &AudioLoader::getTurtleGoonDeathSound() {
  return this->turtleGoonDeathSound;
}

SDL2pp::Chunk &AudioLoader::getSchwarzenguardDeathSound() {
  return this->schwarzenguardDeathSound;
}
