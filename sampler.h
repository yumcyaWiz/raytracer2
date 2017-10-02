#ifndef SAMPLER_H
#define SAMPLER_H
#include <random>
std::random_device rnd_dev;
std::mt19937 mt(rnd_dev());
std::uniform_real_distribution<float> rand_dist(0, 1);
inline float rnd() {
    return rand_dist(mt);
}
#endif
