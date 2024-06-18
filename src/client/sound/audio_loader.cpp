#include "./audio_loader.h"

AudioLoader::AudioLoader(SDL2pp::Mixer &sdlMixer)
    : sdlMixer(sdlMixer), jumpSound("src/client/sound/files/jump.mp3"),
      gun1ShotSound("src/client/sound/files/gun_1_shot.mp3") {}

void AudioLoader::preloadAudios() {}

SDL2pp::Chunk &AudioLoader::getJumpSound() { return this->jumpSound; }

SDL2pp::Chunk &AudioLoader::getGun1ShotSound() { return this->gun1ShotSound; }
