#include "./sound_effect.h"
#include <exception>

const static int FIRST_FREE_AVAILABLE_CHANNEL_ID = -1;

SoundEffect::SoundEffect(SDL2pp::Mixer &sdlMixer, SDL2pp::Chunk &sound)
    : sdlMixer(sdlMixer), sound(sound) {}

void SoundEffect::run() {
  try {
    this->sdlMixer.PlayChannel(FIRST_FREE_AVAILABLE_CHANNEL_ID, this->sound);
  } catch (...) { /* There may no be a free channel available */
  }
}

void SoundEffect::play() { this->start(); }

SoundEffect::~SoundEffect() { this->join(); }

bool SoundEffect::isAlive() const { return this->is_alive(); }
