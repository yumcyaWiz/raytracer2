#ifndef VEC4_H
#define VEC4_H
class Vec4 {
    public:
        float x;
        float y;
        float z;
        float w;

        Vec4() { x = y = z = w = 0.0f; };
        Vec4(float _x) : x(_x), y(_x), z(_x), w(_x) {};
        Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};

        Vec4 operator+(const Vec4& v) const {
            return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        };
        Vec4 operator+(float k) const {
            return Vec4(x + k, y + k, z + k, w + k);
        };
        Vec4 operator-(const Vec4& v) const {
            return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        };
        Vec4 operator-(float k) const {
            return Vec4(x - k, y - k, z - k, w - k);
        };
        Vec4 operator*(const Vec4& v) const {
            return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
        };
        Vec4 operator*(float k) const {
            return Vec4(x * k, y * k, z * k, w * k);
        };
        Vec4 operator/(const Vec4& v) const {
            return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
        };
        Vec4 operator/(float k) const {
            return Vec4(x / k, y / k, z / k, w / k);
        };

        float operator[](int i) const {
            if(i == 0) return x;
            if(i == 1) return y;
            if(i == 2) return z;
            return w;
        };
        float &operator[](int i) {
            if(i == 0) return x;
            if(i == 1) return y;
            if(i == 2) return z;
            return w;
        };

        float length() {
            return std::sqrt(x*x + y*y + z*z + w*w);
        };
        float length2() {
            return x*x + y*y + z*z + w*w;
        };
};
Vec4 operator+(float k, const Vec4& v) {
    return Vec4(k + v.x, k + v.y, k + v.z, k + v.w);
}
Vec4 operator-(float k, const Vec4& v) {
    return Vec4(k - v.x, k - v.y, k - v.z, k - v.w);
}
Vec4 operator*(float k, const Vec4& v) {
    return Vec4(k * v.x, k * v.y, k * v.z, k * v.w);
}
Vec4 operator/(float k, const Vec4& v) {
    return Vec4(k / v.x, k / v.y, k / v.z, k / v.w);
}


float dot(const Vec4& v1, const Vec4& v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}
#endif
