#include "./audio_engine.h"

const static int CHANNELS = 2;
const static int CHUNK_SIZE = 4096;

const static int SOUNDS_COUNT_TRIGGER_FOR_CLEANUP = 50;

AudioEngine::AudioEngine()
    : sdl(SDL_INIT_AUDIO), sdlMixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                                    MIX_DEFAULT_CHANNELS, CHUNK_SIZE),
      audioLoader(this->sdlMixer), jumpSoundDuration(300),
      groundHitSoundDuration(250), gun1ShotSoundDuration(200),
      gun2ShotSoundDuration(400), bulletImpactSoundDuration(350),
      coinCollectedSoundDuration(475), diamondCollectedSoundDuration(460),
      carrotCollectedSoundDuration(300), ammoCollectedSoundDuration(300),
      gameOverSoundDuration(2100), jazzDeathSoundDuration(1600),
      jazzHurtSoundDuration(450), spazDeathSoundDuration(2500),
      spazHurtSoundDuration(450), loriDeathSoundDuration(900),
      loriHurtSoundDuration(600) {}

void AudioEngine::preloadAudios() { this->audioLoader.preloadAudios(); }

void AudioEngine::removeFinishedAudios() {
  this->sounds.remove_if([](const std::unique_ptr<SoundEffect> &soundEffect) {
    return !soundEffect->isAlive();
  });
}

void AudioEngine::playSound(SDL2pp::Chunk &soundChunk, uint32_t &duration) {
  std::unique_ptr<SoundEffect> sound =
      std::make_unique<SoundEffect>(this->sdlMixer, soundChunk, duration);

  this->sounds.push_back(std::move(sound));

  this->sounds.back()->play();

  if (this->sounds.size() % SOUNDS_COUNT_TRIGGER_FOR_CLEANUP == 0) {
    this->removeFinishedAudios();
  }
}

void AudioEngine::playJumpSound() {
  this->playSound(this->audioLoader.getJumpSound(), this->jumpSoundDuration);
}

void AudioEngine::playGroundHitSound() {
  this->playSound(this->audioLoader.getGroundHitSound(),
                  this->groundHitSoundDuration);
}

void AudioEngine::playGun1ShotSound() {
  this->playSound(this->audioLoader.getGun1ShotSound(),
                  this->gun1ShotSoundDuration);
}

void AudioEngine::playGun2ShotSound() {
  this->playSound(this->audioLoader.getGun2ShotSound(),
                  this->gun2ShotSoundDuration);
}

void AudioEngine::playBulletImpactSound() {
  this->playSound(this->audioLoader.getBulletImpactSound(),
                  this->bulletImpactSoundDuration);
}

void AudioEngine::playCoinCollectedSound() {
  this->playSound(this->audioLoader.getCoinCollectedSound(),
                  this->coinCollectedSoundDuration);
}

void AudioEngine::playDiamondCollectedSound() {
  this->playSound(this->audioLoader.getDiamondCollectedSound(),
                  this->diamondCollectedSoundDuration);
}

void AudioEngine::playCarrotCollectedSound() {
  this->playSound(this->audioLoader.getCarrotCollectedSound(),
                  this->carrotCollectedSoundDuration);
}

void AudioEngine::playAmmoCollectedSound() {
  this->playSound(this->audioLoader.getAmmoCollectedSound(),
                  this->ammoCollectedSoundDuration);
}

void AudioEngine::playGameOverSound() {
  this->playSound(this->audioLoader.getGameOverSound(),
                  this->gameOverSoundDuration);
}

void AudioEngine::playJazzDeathSound() {
  this->playSound(this->audioLoader.getJazzDeathSound(),
                  this->jazzDeathSoundDuration);
}

void AudioEngine::playJazzhurtSound() {
  this->playSound(this->audioLoader.getJazzHurtSound(),
                  this->jazzHurtSoundDuration);
}

void AudioEngine::playSpazDeathSound() {
  this->playSound(this->audioLoader.getSpazDeathSound(),
                  this->spazDeathSoundDuration);
}

void AudioEngine::playSpazHurtSound() {
  this->playSound(this->audioLoader.getSpazHurtSound(),
                  this->spazHurtSoundDuration);
}

void AudioEngine::playLoriDeathSound() {
  this->playSound(this->audioLoader.getLoriDeathSound(),
                  this->loriDeathSoundDuration);
}

void AudioEngine::playLorihurtSound() {
  this->playSound(this->audioLoader.getLoriHurtSound(),
                  this->loriHurtSoundDuration);
}

AudioEngine::~AudioEngine() {}
