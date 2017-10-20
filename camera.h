#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "point3.h"
#include "ray.h"
class Camera {
    public:
        Point3 camPos;
        Vec3 camForward;
        Vec3 camRight;
        Vec3 camUp;

        Camera(const Point3& _camPos, const Vec3& _camForward) : camPos(_camPos), camForward(_camForward), camRight(-cross(camForward, Vec3(0, 1, 0))), camUp(cross(camRight, camForward)) {};

        virtual Ray getRay(float u, float v) const = 0;
};


class SimpleCamera : public Camera {
    public:
        SimpleCamera(const Point3& _camPos, const Vec3& _camForward) : Camera(_camPos, _camForward) {};


        Ray getRay(float u, float v) const {
            return Ray(camPos, normalize(camForward + u*camRight + v*camUp));
        };
};
#endif
