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
        float sensitivity;

        Camera(const Point3& _camPos, const Vec3& _camForward, float sensitivity) : camPos(_camPos), camForward(_camForward), camRight(-cross(camForward, Vec3(0, 1, 0))), camUp(cross(camRight, camForward)), sensitivity(sensitivity) {};

        virtual bool getRay(float u, float v, Ray& ray, float &w) const = 0;
};


class PinholeCamera : public Camera {
    public:
        float focal_length;

        PinholeCamera(const Point3& _camPos, const Vec3& _camForward, float sensitivity, float focal_length) : Camera(_camPos, _camForward, sensitivity), focal_length(focal_length) {};

        bool getRay(float u, float v, Ray& ray, float &w) const {
            v = -v;
            Point3 sensorPos = camPos + u*camRight + v*camUp;
            Point3 pinholePos = camPos + focal_length*camForward;
            Vec3 rayDir = normalize(pinholePos - sensorPos);
            w = sensitivity * std::pow(dot(camForward, rayDir), 4.0f);
            ray = Ray(camPos, rayDir);
            return true;
        };
};


class OrthogonalCamera : public Camera {
    public:
        float sizeU;
        float sizeV;

        OrthogonalCamera(const Point3& camPos, const Vec3& camForward, float sensitivity, float sizeU, float sizeV) : Camera(camPos, camForward, sensitivity), sizeU(sizeU), sizeV(sizeV) {};

        bool getRay(float u, float v, Ray& ray, float &w) const {
            Point3 sensorPos = camPos + sizeU*u*camRight + sizeV*v*camUp;
            w = sensitivity;
            ray = Ray(sensorPos, camForward);
            return true;
        };
};


class ThinLensCamera : public Camera {
    public:
        float lens_distance;
        Point3 focus_point;
        float Fnumber;
        float lens_radius;
        float object_distance;
        float focal_length;
        Point3 lensCenterPos;

        ThinLensCamera(const Point3& camPos, const Vec3& camForward, float sensitivity, float lens_distance, const Point3& focus_point, float Fnumber) : Camera(camPos, camForward, sensitivity), lens_distance(lens_distance), focus_point(focus_point), Fnumber(Fnumber) {
            object_distance = distance(focus_point, camPos) - lens_distance;
            focal_length = 1.0f/(1.0f/lens_distance + 1.0f/object_distance);
            lens_radius = 0.5f*focal_length/Fnumber;
            lensCenterPos = camPos + lens_distance*camForward;
        };

        bool getRay(float u, float v, Ray& ray, float &w) const {
            v = -v;
            Point3 sensorPos = camPos + u*camRight + v*camUp;
            Point3 lensPos = camPos + lens_distance*camForward + lens_radius*random_in_unitDisk(camRight, camUp);

            Vec3 sensor_to_lensCenter = normalize(lensCenterPos - sensorPos);
            float sensor_object_distance = (lens_distance + object_distance)/dot(camForward, sensor_to_lensCenter);
            Point3 objectPos = sensorPos + sensor_object_distance*sensor_to_lensCenter; 

            Vec3 sensor_to_lensPos = normalize(lensPos - sensorPos);
            float sensor_lens_distance2 = (lensPos - sensorPos).length2();
            w = sensitivity * std::pow(dot(camForward, sensor_to_lensPos), 2.0f)/sensor_lens_distance2;

            Vec3 rayDir = normalize(objectPos - lensPos);
            ray = Ray(lensPos, rayDir);
            return true;
        };
};


class FisheyeCamera : public Camera {
    public:
        float focal_length;

        FisheyeCamera(const Point3& camPos, const Vec3& camForward, float sensitivity, float focal_length) : Camera(camPos, camForward, sensitivity), focal_length(focal_length) {};
};


class OrthogonalFisheyeCamera : public FisheyeCamera {
    public:
        OrthogonalFisheyeCamera(const Point3& camPos, const Vec3& camForward, float sensitivity, float focal_length) : FisheyeCamera(camPos, camForward, sensitivity, focal_length) {};

        bool getRay(float u, float v, Ray& ray, float &w) const {
            /*
            float x = u;
            float y = v;
            if(x*x + y*y > focal_length)
                return false;
            float z = std::sqrt(focal_length - (x*x + y*y));
            
            w = sensitivity;

            Vec3 rayDir = normalize(camRight*x + camUp*y + camForward*z);
            ray = Ray(camPos + focal_length*rayDir, rayDir);
            return true;
            */
            float r = std::sqrt(u*u + v*v);
            if(std::abs(r/focal_length) > 1) return false;
            float theta = std::asin(r/focal_length);
            float phi = std::atan2(v, u);
            if(phi < 0) phi += 2*M_PI;

            float x = std::cos(phi)*std::sin(theta);
            float y = std::sin(phi)*std::sin(theta);
            float z = std::cos(theta);
            w = sensitivity;
            Vec3 rayDir = normalize(x*camRight + y*camUp + z*camForward);
            ray = Ray(camPos + focal_length*rayDir, rayDir);
            return true;
        };
};


class EquidistantFisheyeCamera : public FisheyeCamera {
    public:
        EquidistantFisheyeCamera(const Point3& camPos, const Vec3& camForward, float sensitivity, float focal_length) : FisheyeCamera(camPos, camForward, sensitivity, focal_length) {};

        bool getRay(float u, float v, Ray& ray, float &w) const {
            float r = std::sqrt(u*u + v*v);
            float theta = r/focal_length;
            if(std::abs(theta) > M_PI/2) return false;
            float phi = std::atan2(v, u);
            if(phi < 0) phi += 2*M_PI;

            float x = std::cos(phi)*std::sin(theta);
            float y = std::sin(phi)*std::sin(theta);
            float z = std::cos(theta);
            w = sensitivity * std::pow(dot(normalize(Point3(x, y, z) - Point3(u, v, 0)), Vec3(0, 0, 1)), 4.0f);
            Vec3 rayDir = normalize(x*camRight + y*camUp + z*camForward);
            ray = Ray(camPos + focal_length*rayDir, rayDir);
            return true;
        };
};


class StereoFisheyeCamera : public FisheyeCamera {
    public:
        StereoFisheyeCamera(const Point3& camPos, const Vec3& camForward, float sensitivity, float focal_length) : FisheyeCamera(camPos, camForward, sensitivity, focal_length) {};

        bool getRay(float u, float v, Ray& ray, float &w) const {
            float r = std::sqrt(u*u + v*v);
            float theta = 2*std::atan(r/(2*focal_length));
            if(std::abs(theta) > M_PI/2) return false;
            float phi = std::atan2(v, u);
            if(phi < 0) phi += 2*M_PI;

            float x = std::cos(phi)*std::sin(theta);
            float y = std::sin(phi)*std::sin(theta);
            float z = std::cos(theta);
            w = sensitivity * std::pow(dot(normalize(Point3(x, y, z) - Point3(u, v, 0)), Vec3(0, 0, 1)), 4.0f);
            Vec3 rayDir = normalize(x*camRight + y*camUp + z*camForward);
            ray = Ray(camPos + focal_length*rayDir, rayDir);
            return true;
        };
};


class EquiSolidAngleFisheyeCamera : public FisheyeCamera {
    public:
        EquiSolidAngleFisheyeCamera(const Point3& camPos, const Vec3& camForward, float sensitivity, float focal_length) : FisheyeCamera(camPos, camForward, sensitivity, focal_length) {};

        bool getRay(float u, float v, Ray& ray, float &w) const {
            float r = std::sqrt(u*u + v*v);
            if(std::abs(r/(2*focal_length)) > 1) return false;
            float theta = 2*std::asin(r/(2*focal_length));
            if(std::abs(theta) > M_PI/2) return false;
            float phi = std::atan2(v, u);
            if(phi < 0) phi += 2*M_PI;

            float x = std::cos(phi)*std::sin(theta);
            float y = std::sin(phi)*std::sin(theta);
            float z = std::cos(theta);
            w = sensitivity * std::pow(dot(normalize(Point3(x, y, z) - Point3(u, v, 0)), Vec3(0, 0, 1)), 4.0f);
            Vec3 rayDir = normalize(x*camRight + y*camUp + z*camForward);
            ray = Ray(camPos + focal_length*rayDir, rayDir);
            return true;
        };
};
#endif
