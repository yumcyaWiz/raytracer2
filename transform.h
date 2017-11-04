#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vec3.h"
#include "mat4.h"
#include "ray.h"
#include "hit.h"
class Transform {
    public:
        Mat4 mat;
        Mat4 mat_inv;

        Transform() : mat(Mat4()), mat_inv(Mat4()) {};
        Transform(const Mat4& _mat, const Mat4& _mat_inv) : mat(_mat), mat_inv(_mat_inv) {};
        Transform(const Transform& t) : mat(t.mat), mat_inv(t.mat_inv) {};

        Transform operator*(const Transform& t) const {
            return Transform(mat*t.mat, t.mat_inv*mat_inv);
        };
        Vec3 operator()(const Vec3& v) const {
            return Vec3(mat.m[0][0]*v.x + mat.m[0][1]*v.y + mat.m[0][2]*v.z,
                    mat.m[1][0]*v.x + mat.m[1][1]*v.y + mat.m[1][2]*v.z,
                    mat.m[2][0]*v.x + mat.m[2][1]*v.y + mat.m[2][2]*v.z);
        };
        Point3 operator()(const Point3& p) const {
            float xp = mat.m[0][0]*p.x + mat.m[0][1]*p.y + mat.m[0][2]*p.z + mat.m[0][3];
            float yp = mat.m[1][0]*p.x + mat.m[1][1]*p.y + mat.m[1][2]*p.z + mat.m[1][3];
            float zp = mat.m[2][0]*p.x + mat.m[2][1]*p.y + mat.m[2][2]*p.z + mat.m[2][3];
            float wp = mat.m[3][0]*p.x + mat.m[3][1]*p.y + mat.m[3][2]*p.z + mat.m[3][3];
            if(wp == 1) return Point3(xp, yp, zp);
            else return Point3(xp/wp, yp/wp, zp/wp);
        };
        Normal operator()(const Normal& n) const {
            return Normal(mat_inv.m[0][0]*n.x + mat_inv.m[1][0]*n.y + mat_inv.m[2][0]*n.z,
                    mat_inv.m[0][1]*n.x + mat_inv.m[1][1]*n.y + mat_inv.m[2][1]*n.z,
                    mat_inv.m[0][2]*n.x + mat_inv.m[1][2]*n.y + mat_inv.m[2][2]*n.z);
        };
        Ray operator()(const Ray& r) const {
            return Ray((*this)(r.origin), (*this)(r.direction));
        };
        Hit operator()(const Hit& res) const {
            return Hit(res.t, (*this)(res.ray), (*this)(res.hitPos), res.u, res.v, (*this)(res.dpdu), (*this)(res.dpdv), normalize((*this)(res.hitNormal)), res.hitObj, res.inside); 
        };
};


Transform translate(const Vec3& v) {
    Mat4 m(1, 0, 0, v.x,
            0, 1, 0, v.y,
            0, 0, 1, v.z,
            0, 0, 0, 1);
    Mat4 m_inv(1, 0, 0, -v.x,
            0, 1, 0, -v.y,
            0, 0, 1, -v.z,
            0, 0, 0, 1);
    return Transform(m, m_inv);
}

Transform scale(float sx, float sy, float sz) {
    Mat4 m(sx, 0, 0, 0,
            0, sy, 0, 0,
            0, 0, sz, 0,
            0, 0, 0, 1);
    Mat4 m_inv(1/sx, 0, 0, 0,
            0, 1/sy, 0, 0,
            0, 0, 1/sz, 0,
            0, 0, 0, 1);
    return Transform(m, m_inv);
}

Transform rotateX(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Mat4 m(1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1);
    return Transform(m, transpose(m));
}
Transform rotateY(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Mat4 m(c, 0, s, 0,
            0, 1, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1);
    return Transform(m, transpose(m));
}
Transform rotateZ(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Mat4 m(c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    return Transform(m, transpose(m));
}
Transform rotate(float thetaX, float thetaY, float thetaZ) {
    return rotateX(thetaX)*rotateY(thetaY)*rotateZ(thetaZ);
}

Transform inverse(const Transform& t) {
    return Transform(t.mat_inv, t.mat);
}
#endif
