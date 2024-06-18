#include "./audio_engine.h"

const static int CHANNELS = 2;
const static int CHUNK_SIZE = 4096;

AudioEngine::AudioEngine()
    : sdl(SDL_INIT_AUDIO),
      sdlMixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE),
      audioLoader(this->sdlMixer) {}

void AudioEngine::preloadAudios() { this->audioLoader.preloadAudios(); }

SDL2pp::Chunk &AudioEngine::getSound() { return this->audioLoader.getSound(); }

SDL2pp::Mixer &AudioEngine::getSdlMixerReference() {
  return std::ref(this->sdlMixer);
}
