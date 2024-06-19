#include "./music.h"

const static int FIRST_FREE_AVAILABLE_CHANNEL_ID = -1;
const static int FADE_IN_DELAY = 500; // In ms

Music::Music(SDL2pp::Mixer &sdlMixer, SDL2pp::Music &music)
    : sdlMixer(sdlMixer), music(music) {}

void Music::run() {
  this->sdlMixer.FadeInMusic(this->music, FIRST_FREE_AVAILABLE_CHANNEL_ID,
                             FADE_IN_DELAY);
}

void Music::startPlayback() { this->start(); }

void Music::stopPlayback() { this->sdlMixer.HaltMusic(); }

Music::~Music() { this->join(); }

bool Music::isAlive() const { return this->is_alive(); }
