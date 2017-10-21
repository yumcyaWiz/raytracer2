#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "point3.h"
#include "ray.h"
#include "sampler.h"
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


class ThinLensCamera : public Camera {
    public:
        float lens_radius;
        float lens_distance;
        float focus_distance;

        ThinLensCamera(const Point3& camPos, const Vec3& camForward, float lens_radius, float lens_distance, float focus_distance) : Camera(camPos, camForward), lens_radius(lens_radius), lens_distance(lens_distance), focus_distance(focus_distance) {};

        Ray getRay(float u, float v, float &w) const {
            v = -v;
            Point3 sensorPos = camPos + u*camRight + v*camUp;
            Point3 lensCenterPos = camPos + lens_distance*camForward;
            Point3 lensPos = camPos + lens_distance*camForward + lens_radius*random_in_unitDisk(camRight, camUp);

            float object_distance = focus_distance - lens_distance;
            Vec3 sensor_to_lensCenter = normalize(lensCenterPos - sensorPos);
            float sensor_object_distance = (lens_distance + object_distance)/dot(camForward, sensor_to_lensCenter);
            Point3 objectPos = sensorPos + sensor_object_distance*sensor_to_lensCenter; 

            Vec3 sensor_to_lensPos = normalize(lensPos - sensorPos);
            float sensor_lens_distance = (lensPos - sensorPos).length();
            w = std::pow(dot(camForward, sensor_to_lensPos), 2.0f)/std::pow(sensor_lens_distance, 2.0f);

            Vec3 rayDir = normalize(objectPos - lensPos);
            return Ray(lensPos, rayDir);
        };
};
#endif
