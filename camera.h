#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"
class Camera {
    public:
        Vec3 camPos;
        Vec3 camForward;
        Vec3 camRight;
        Vec3 camUp;


        Camera(const Vec3& _camPos, const Vec3& _camForward) {
            camPos = _camPos;
            camForward = _camForward;
            camRight = -cross(camForward, Vec3(0, 1, 0));
            camUp = cross(camRight, camForward);
        };


        Ray getRay(float u, float v) const {
            return normalize(camForward + u*camRight + v*camUp);
        };
};
#endif
