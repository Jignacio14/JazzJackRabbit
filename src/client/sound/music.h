#ifndef JJR2_MUSIC_H
#define JJR2_MUSIC_H

#include "../../common/thread.h"
#include <SDL2pp/SDL2pp.hh>

class Music : private Thread {
private:
  SDL2pp::Mixer &sdlMixer;
  SDL2pp::Music &music;

public:
  Music(SDL2pp::Mixer &sdlMixer, SDL2pp::Music &music);

  virtual void run() override;

  void startPlayback();

  void stopPlayback();

  bool isAlive() const;

  ~Music() override;
};

#endif // JJR2_MUSIC_H