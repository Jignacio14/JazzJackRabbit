#include "./audio_loader.h"

static const char JUMP_SOUND_PATH[] = "src/client/sound/files/jump.mp3";
static const char GROUND_HIT_SOUND_PATH[] =
    "src/client/sound/files/ground_hit.mp3";
static const char GUN_1_SHOT_SOUND_PATH[] =
    "src/client/sound/files/gun_1_shot.mp3";
static const char GUN_2_SHOT_SOUND_PATH[] =
    "src/client/sound/files/gun_2_shot.mp3";
static const char GUN_CHANGE_SOUND_PATH[] =
    "src/client/sound/files/gun_change.mp3";
static const char BULLET_IMPACT_SOUND_PATH[] =
    "src/client/sound/files/bullet_impact.mp3";
static const char COIN_COLLECTED_SOUND_PATH[] =
    "src/client/sound/files/coin_collected.mp3";
static const char DIAMOND_COLLECTED_SOUND_PATH[] =
    "src/client/sound/files/diamond_collected.mp3";
static const char CARROT_COLLECTED_SOUND_PATH[] =
    "src/client/sound/files/carrot_collected.mp3";
static const char AMMO_COLLECTED_SOUND_PATH[] =
    "src/client/sound/files/ammo_collected.mp3";
static const char GAME_OVER_SOUND_PATH[] =
    "src/client/sound/files/game_over.mp3";
static const char JAZZ_DEATH_SOUND_PATH[] =
    "src/client/sound/files/jazz_death.mp3";
static const char JAZZ_HURT_SOUND_PATH[] =
    "src/client/sound/files/jazz_hurt.mp3";
static const char SPAZ_DEATH_SOUND_PATH[] =
    "src/client/sound/files/spaz_death.mp3";
static const char SPAZ_HURT_SOUND_PATH[] =
    "src/client/sound/files/spaz_hurt.mp3";
static const char LORI_DEATH_SOUND_PATH[] =
    "src/client/sound/files/lori_death.mp3";
static const char LORI_HURT_SOUND_PATH[] =
    "src/client/sound/files/lori_hurt.mp3";
static const char CARROTUS_BACKGROUND_MUSIC_PATH[] =
    "src/client/sound/files/carrotus_background_music.mp3";
static const char BEACH_WORLD_BACKGROUND_MUSIC_PATH[] =
    "src/client/sound/files/beach_world_background_music.mp3";
static const char DISCONNECTION_SOUND_PATH[] =
    "src/client/sound/files/disconnection_sound.mp3";
static const char GENERIC_ENEMY_MELEE_SHOT_SOUND_PATH[] =
    "src/client/sound/files/enemy_melee_shot.mp3";
static const char BUBBA_HURT_SOUND_PATH[] =
    "src/client/sound/files/bubba_hurt.mp3";
static const char TURTLE_GOON_HURT_SOUND_PATH[] =
    "src/client/sound/files/turtle_goon_hurt.mp3";
static const char SCHWARZENGUARD_HURT_SOUND_PATH[] =
    "src/client/sound/files/schwarzenguard_hurt.mp3";
static const char BUBBA_DEATH_SOUND_PATH[] =
    "src/client/sound/files/bubba_death.mp3";
static const char TURTLE_GOON_DEATH_SOUND_PATH[] =
    "src/client/sound/files/turtle_goon_death.mp3";
static const char SCHWARZENGUARD_DEATH_SOUND_PATH[] =
    "src/client/sound/files/schwarzenguard_death.mp3";

AudioLoader::AudioLoader(SDL2pp::Mixer &sdlMixer)
    : sdlMixer(sdlMixer), jumpSound(JUMP_SOUND_PATH),
      groundHitSound(GROUND_HIT_SOUND_PATH),
      gun1ShotSound(GUN_1_SHOT_SOUND_PATH),
      gun2ShotSound(GUN_2_SHOT_SOUND_PATH),
      gunChangeSound(GUN_CHANGE_SOUND_PATH),
      bulletImpactSound(BULLET_IMPACT_SOUND_PATH),
      coinCollectedSound(COIN_COLLECTED_SOUND_PATH),
      diamondCollectedSound(DIAMOND_COLLECTED_SOUND_PATH),
      carrotCollectedSound(CARROT_COLLECTED_SOUND_PATH),
      ammoCollectedSound(AMMO_COLLECTED_SOUND_PATH),
      gameOverSound(GAME_OVER_SOUND_PATH),
      jazzDeathSound(JAZZ_DEATH_SOUND_PATH),
      jazzHurtSound(JAZZ_HURT_SOUND_PATH),
      spazDeathSound(SPAZ_DEATH_SOUND_PATH),
      spazHurtSound(SPAZ_HURT_SOUND_PATH),
      loriDeathSound(LORI_DEATH_SOUND_PATH),
      loriHurtSound(LORI_HURT_SOUND_PATH),
      carrotusBackgroundMusic(CARROTUS_BACKGROUND_MUSIC_PATH),
      beachWorldBackgroundMusic(BEACH_WORLD_BACKGROUND_MUSIC_PATH),
      disconnectionSound(DISCONNECTION_SOUND_PATH),
      genericEnemyMeleeShotSound(GENERIC_ENEMY_MELEE_SHOT_SOUND_PATH),
      bubbaHurtSound(BUBBA_HURT_SOUND_PATH),
      turtleGoonHurtSound(TURTLE_GOON_HURT_SOUND_PATH),
      schwarzenguardHurtSound(SCHWARZENGUARD_HURT_SOUND_PATH),
      bubbaDeathSound(BUBBA_DEATH_SOUND_PATH),
      turtleGoonDeathSound(TURTLE_GOON_DEATH_SOUND_PATH),
      schwarzenguardDeathSound(SCHWARZENGUARD_DEATH_SOUND_PATH) {}

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
