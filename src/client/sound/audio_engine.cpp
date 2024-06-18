#include "./audio_engine.h"

const static int CHANNELS = 2;
const static int CHUNK_SIZE = 4096;

const static int SOUNDS_COUNT_TRIGGER_FOR_CLEANUP = 50;

AudioEngine::AudioEngine()
    : sdl(SDL_INIT_AUDIO),
      sdlMixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE),
      audioLoader(this->sdlMixer) {}

void AudioEngine::preloadAudios() { this->audioLoader.preloadAudios(); }

SDL2pp::Chunk &AudioEngine::getSound() { return this->audioLoader.getSound(); }

SDL2pp::Mixer &AudioEngine::getSdlMixerReference() {
  return std::ref(this->sdlMixer);
}

void AudioEngine::removeFinishedAudios() {
  this->sounds.remove_if([](const std::unique_ptr<SoundEffect> &soundEffect) {
    return !soundEffect->isAlive();
  });
}

void AudioEngine::playSound() {
  std::unique_ptr<SoundEffect> sound = std::make_unique<SoundEffect>(
      this->sdlMixer, this->audioLoader.getSound());

  this->sounds.push_back(std::move(sound));

  this->sounds.back()->play();

  if (this->sounds.size() % SOUNDS_COUNT_TRIGGER_FOR_CLEANUP == 0) {
    this->removeFinishedAudios();
  }
}
