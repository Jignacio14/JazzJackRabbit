#include "./audio_loader.h"

AudioLoader::AudioLoader(SDL2pp::Mixer &sdlMixer)
    : sdlMixer(sdlMixer), sound("src/client/sound/files/test2.mp3") {}

void AudioLoader::preloadAudios() {}

SDL2pp::Chunk &AudioLoader::getSound() { return this->sound; }
