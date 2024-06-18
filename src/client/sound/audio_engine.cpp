#include "./audio_engine.h"

const static int CHANNELS = 2;
const static int CHUNK_SIZE = 4096;

const static int SOUNDS_COUNT_TRIGGER_FOR_CLEANUP = 50;

AudioEngine::AudioEngine()
    : sdl(SDL_INIT_AUDIO),
      sdlMixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE),
      audioLoader(this->sdlMixer) {}

void AudioEngine::preloadAudios() { this->audioLoader.preloadAudios(); }

/*SDL2pp::Chunk &AudioEngine::getSound() { return this->audioLoader.getSound();
}

SDL2pp::Mixer &AudioEngine::getSdlMixerReference() {
  return std::ref(this->sdlMixer);
}*/

void AudioEngine::removeFinishedAudios() {
  this->sounds.remove_if([](const std::unique_ptr<SoundEffect> &soundEffect) {
    return !soundEffect->isAlive();
  });
}

void AudioEngine::playSound(SDL2pp::Chunk &soundChunk) {
  std::unique_ptr<SoundEffect> sound =
      std::make_unique<SoundEffect>(this->sdlMixer, soundChunk);

  this->sounds.push_back(std::move(sound));

  this->sounds.back()->play();

  if (this->sounds.size() % SOUNDS_COUNT_TRIGGER_FOR_CLEANUP == 0) {
    this->removeFinishedAudios();
  }
}

void AudioEngine::playJumpSound() {
  this->playSound(this->audioLoader.getJumpSound());
}

void AudioEngine::playGroundHitSound() {
  this->playSound(this->audioLoader.getGroundHitSound());
}

void AudioEngine::playGun1ShotSound() {
  this->playSound(this->audioLoader.getGun1ShotSound());
}

void AudioEngine::playGun2ShotSound() {
  this->playSound(this->audioLoader.getGun2ShotSound());
}

void AudioEngine::playBulletImpactSound() {
  this->playSound(this->audioLoader.getBulletImpactSound());
}

void AudioEngine::playCoinCollectedSound() {
  this->playSound(this->audioLoader.getCoinCollectedSound());
}

void AudioEngine::playDiamondCollectedSound() {
  this->playSound(this->audioLoader.getDiamondCollectedSound());
}

void AudioEngine::playCarrotCollectedSound() {
  this->playSound(this->audioLoader.getCarrotCollectedSound());
}

void AudioEngine::playAmmoCollectedSound() {
  this->playSound(this->audioLoader.getAmmoCollectedSound());
}
