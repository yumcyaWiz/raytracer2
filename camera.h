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

        virtual Ray getRay(float u, float v, float &w) const = 0;
};


class SimpleCamera : public Camera {
    public:
        float pinhole_distance;
        SimpleCamera(const Point3& _camPos, const Vec3& _camForward) : Camera(_camPos, _camForward), pinhole_distance(1.0f) {};

        Ray getRay(float u, float v, float &w) const {
            v = -v;
            Point3 sensorPos = camPos + u*camRight + v*camUp;
            Point3 pinholePos = camPos + pinhole_distance*camForward;
            Vec3 rayDir = normalize(pinholePos - sensorPos);
            w = std::pow(dot(camForward, rayDir), 2.0f); 
            return Ray(camPos, rayDir);
        };
};


/*
class ThinLensCamera : public Camera {
    public:
        float lens_radius;
        float lens_distance;
        float focal_length;

        ThinLensCamera(const Point3& camPos, const Vec3& camForward) : Camera(camPos, camForward), lens_radius(0.1f), lens_distance(0.1f), focal_length(1.0f) {};

        Ray getRay(float u, float v, float &w) const {
            Point3 sensorPos = camPos + u*camRight + v*camUp;
            Point3 lensPos = camPos + lens_distance*camForward + lens_radius*random_in_unitDisk(camRight, camUp);
            Vec3 sensor_to_lensPos = normalize(lensPos - sensorPos);
            return Ray(Point3f(), Vector3f());
        };
};
*/
#endif
