#ifndef AUDIO_LOADER_H
#define AUDIO_LOADER_H

#include <SDL2pp/SDL2pp.hh>

class AudioLoader {
private:
  SDL2pp::Mixer &sdlMixer;

  SDL2pp::Chunk jumpSound;
  SDL2pp::Chunk gun1ShotSound;

public:
  explicit AudioLoader(SDL2pp::Mixer &sdlMixer);

  void preloadAudios();

  SDL2pp::Chunk &getJumpSound();
  SDL2pp::Chunk &getGun1ShotSound();
};

#endif // AUDIO_LOADER_H