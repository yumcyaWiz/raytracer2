#ifndef SAMPLER_H
#define SAMPLER_H
#include <random>
#include "vec3.h"

/*
#include "sobol/sobol.cpp"
*/

std::random_device rnd_dev;
std::mt19937 mt(rnd_dev());
std::uniform_real_distribution<float> rand_dist(0, 1);
inline float rnd() {
    return rand_dist(mt);
}
inline float rnd2() {
    return 2.0f*rnd() - 1.0f;
}


std::uniform_int_distribution<> randint_dist(0, 10000);
inline int rndint() {
    return randint_dist(mt);
}


inline Vec3 randVec() {
    return Vec3(rnd2(), rnd2(), rnd2());
}
inline Vec3 randVec(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
    return Vec3(xmin + rnd()*(xmax - xmin), ymin + rnd()*(ymax - ymin), zmin + rnd()*(zmax - zmin));
}


inline Vec3 random_in_unitSphere() {
    Vec3 v;
    do {
        v = randVec();
    }
    while(v.length2() > 1.0f);
    return v;
}
inline Vec3 random_in_unitHemisphere(const Vec3& right, const Vec3& forward, const Vec3& up) {
    float x, y, z;
    Vec3 v;
    do {
        x = rnd2();
        y = rnd();
        z = rnd2();
        v = x*right + y*up + z*forward;
    }
    while(v.length2() > 1.0f);
    return v;
};

inline Vec3 random_in_unitDisk(const Vec3& right, const Vec3& up) {
    Vec3 v;
    do {
        v = rnd2()*right + rnd2()*up;
    }
    while(v.length2() > 1.0);
    return v;
}

inline Vec3 random_in_unitAstroid(const Vec3& right, const Vec3& up) {
    Vec3 v;
    float x;
    float y;
    do {
        x = rnd2();
        y = rnd2();
        v = x*right + y*up;
    }
    while(std::pow(x, 2.0f/3.0f) + std::pow(y, 2.0f/3.0f) > 1.0f);
    return v;
}


/*
int sobol2_seed[2] = {rndint(), rndint()};
inline void sobol2(float quasi[]) {
    i4_sobol(2, sobol2_seed, quasi);
}
*/
#endif
