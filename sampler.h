#ifndef SAMPLER_H
#define SAMPLER_H
#include <random>
#include "vec3.h"
std::random_device rnd_dev;
std::mt19937 mt(rnd_dev());
std::uniform_real_distribution<float> rand_dist(0, 1);
inline float rnd() {
    return rand_dist(mt);
}


inline Vec3 randVec() {
    return Vec3(2.0*rnd() - 1.0, 2.0*rnd() - 1.0, 2.0*rnd() - 1.0);
}
inline Vec3 randVec(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
    return Vec3(xmin + rnd()*(xmax - xmin), ymin + rnd()*(ymax - ymin), zmin + rnd()*(zmax - zmin));
}

inline Vec3 random_in_unitSphere() {
    Vec3 v;
    do {
        v = randVec();
    }
    while(v.length2() > 1.0);
    return v;
}
#endif
