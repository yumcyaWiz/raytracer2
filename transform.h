#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vec3.h"
#include "mat4.h"
#include "ray.h"
class Transform {
    public:
        Mat4 mat;
        Mat4 mat_inv;

        Transform(const Mat4& _mat, const Mat4& _mat_inv) : mat(_mat), mat_inv(_mat_inv) {};

        Vec3 operator()(const Vec3& v) const {
            Vec4 v4 = mat*Vec4(v.x, v.y, v.z, 1.0f);
            return 1.0/v4.w * Vec3(v4.x, v4.y, v4.z);
        };
        Ray operator()(const Ray& r) const {
            return Ray((*this)(r.origin), (*this)(r.direction));
        };
};


Transform scale(float sx, float sy, float sz) {
    Mat4 m(sx, 0, 0, 0,
            0, sy, 0, 0,
            0, 0, sz, 0,
            0, 0, 0, 1.0f);
    Mat4 m_inv(1.0f/sx, 0, 0, 0,
            0, 1.0f/sy, 0, 0,
            0, 0, 1.0f/sz, 0,
            0, 0, 0, 1.0f);
    return Transform(m, m_inv);
}

Transform rotateX(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Mat4 m(1.0f, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1.0f);
    return Transform(m, transpose(m));
}
Transform rotateY(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Mat4 m(c, 0, s, 0,
            0, 1.0f, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1.0f);
    return Transform(m, transpose(m));
}
Transform rotateZ(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Mat4 m(c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1.0f, 0,
            0, 0, 0, 1.0f);
    return Transform(m, transpose(m));
}
#endif
