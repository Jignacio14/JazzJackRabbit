#include "./audio_engine.h"

#include "../../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int CHUNK_SIZE = 4096;
const static int SOUNDS_COUNT_TRIGGER_FOR_CLEANUP = 50;
const static int BACKGROUND_MUSIC_VOLUME =
    globalConfigs.getBackgroundMusicVolumeGame();

AudioEngine::AudioEngine()
    : sdl(SDL_INIT_AUDIO), sdlMixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                                    MIX_DEFAULT_CHANNELS, CHUNK_SIZE),
      audioLoader(this->sdlMixer), music(nullptr) {
  this->sdlMixer.SetMusicVolume(BACKGROUND_MUSIC_VOLUME);
}

void AudioEngine::preloadAudios() { this->audioLoader.preloadAudios(); }

void AudioEngine::removeFinishedAudios() {
  this->sounds.remove_if([](const std::unique_ptr<SoundEffect> &soundEffect) {
    return !soundEffect->isAlive();
  });
}

void AudioEngine::playMusic(SDL2pp::Music &musicTrack) {
  if (this->music != nullptr) {
    this->stopPlayingBackgroundMusic();
  }

  this->music = std::make_unique<Music>(this->sdlMixer, musicTrack);
  this->music->startPlayback();
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

void AudioEngine::playGameOverSound() {
  this->playSound(this->audioLoader.getGameOverSound());
}

void AudioEngine::playJazzDeathSound() {
  this->playSound(this->audioLoader.getJazzDeathSound());
}

void AudioEngine::playJazzhurtSound() {
  this->playSound(this->audioLoader.getJazzHurtSound());
}

void AudioEngine::playSpazDeathSound() {
  this->playSound(this->audioLoader.getSpazDeathSound());
}

void AudioEngine::playSpazHurtSound() {
  this->playSound(this->audioLoader.getSpazHurtSound());
}

void AudioEngine::playLoriDeathSound() {
  this->playSound(this->audioLoader.getLoriDeathSound());
}

void AudioEngine::playLorihurtSound() {
  this->playSound(this->audioLoader.getLoriHurtSound());
}

void AudioEngine::playCarrotusBackgroundMusic() {
  this->playMusic(this->audioLoader.getCarrotusBackgroundMusic());
}

void AudioEngine::playBeachWorldBackgroundMusic() {
  this->playMusic(this->audioLoader.getBeachWorldBackgroundMusic());
}

void AudioEngine::stopPlayingBackgroundMusic() {
  if (this->music == nullptr) {
    return;
  }

  this->music->stopPlayback();
}

AudioEngine::~AudioEngine() {}
