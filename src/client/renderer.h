
#ifndef JAZZJACKRABBIT_CONSTANTRATELOOP_H
#define JAZZJACKRABBIT_CONSTANTRATELOOP_H

#include <functional>


class ConstantRateLooper {
private:
    bool keep_running;
    double rate;
    int it;

    /*
     * Returns current time in seconds since epoch.
     */
    double now();

public:
    ConstantRateLooper(double rate);

    /*
     * It executes the game logic repeatedly, keeping a constant time rate between each iteration,
     * adjusting the wait time to compensate any possible delay.
     * */
    void run();
};


#endif //JAZZJACKRABBIT_CONSTANTRATELOOP_H
