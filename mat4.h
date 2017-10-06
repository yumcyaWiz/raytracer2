#ifndef MAT4_H
#define MAT4_H
#include "vec4.h"
class Mat4 {
    public:
        float m[4][4];

        Mat4() {
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == j)
                        m[i][j] = 1.0f;
                    else
                        m[i][j] = 0.0f;
                }
            }
        };
        Mat4(float _m[4][4]) {
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    m[i][j] = _m[i][j];
                }
            }
        };
        Mat4(float t00, float t01, float t02, float t03, float t10, float t11, float t12, float t13, float t20, float t21, float t22, float t23, float t30, float t31, float t32, float t33) {
            m[0][0] = t00;
            m[0][1] = t01;
            m[0][2] = t02;
            m[0][3] = t03;
            m[1][0] = t10;
            m[1][1] = t11;
            m[1][2] = t12;
            m[1][3] = t13;
            m[2][0] = t20;
            m[2][1] = t21;
            m[2][2] = t22;
            m[2][3] = t23;
            m[3][0] = t30;
            m[3][1] = t31;
            m[3][2] = t32;
            m[3][3] = t33;
        };


        Mat4 operator+(const Mat4& mat) {
            float ret[4][4];
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    ret[i][j] = m[i][j] + mat.m[i][j];
                }
            }
            return Mat4(ret);
        };
        Mat4 operator-(const Mat4& mat) {
            float ret[4][4];
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    ret[i][j] = m[i][j] - mat.m[i][j];
                }
            }
            return Mat4(ret);
        };
        Mat4 operator*(const Mat4& mat) {
            float ret[4][4];
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    float sum = 0.0f;
                    for(int k = 0; k < 4; k++) {
                        sum += m[i][k] * mat.m[k][j];
                    }
                    ret[i][j] = sum;
                }
            }
            return Mat4(ret);
        };
        Mat4 operator*(float k) {
            float ret[4][4];
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    ret[i][j] = k*m[i][j];
                }
            }
            return Mat4(ret);
        };
        Vec4 operator*(const Vec4& v) {
            Vec4 ret;
            for(int i = 0; i < 4; i++) {
                float sum = 0.0f;
                for(int j = 0; j < 4; j++) {
                    sum += m[i][j] * v[j];
                }
                ret[i] = sum;
            }
            return ret;
        };
};
Mat4 operator*(float k, const Mat4& m) {
    float ret[4][4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            ret[i][j] = k*m.m[i][j];
        }
    }
    return Mat4(ret);
}


Mat4 transpose(const Mat4& m) {
    return Mat4(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0], m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1], m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2], m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
}
float det(const Mat4& m) {
    return m.m[0][3]*m.m[1][2]*m.m[2][1]*m.m[3][0] - m.m[0][2]*m.m[1][3]*m.m[2][1]*m.m[3][0] - m.m[0][3]*m.m[1][1]*m.m[2][2]*m.m[3][0] + m.m[0][1]*m.m[1][3]*m.m[2][2]*m.m[3][0] +
            m.m[0][2]*m.m[1][1]*m.m[2][3]*m.m[3][0] - m.m[0][1]*m.m[1][2]*m.m[2][3]*m.m[3][0] - m.m[0][3]*m.m[1][2]*m.m[2][0]*m.m[3][1] + m.m[0][2]*m.m[1][3]*m.m[2][0]*m.m[3][1] +
            m.m[0][3]*m.m[1][0]*m.m[2][2]*m.m[3][1] - m.m[0][0]*m.m[1][3]*m.m[2][2]*m.m[3][1] - m.m[0][2]*m.m[1][0]*m.m[2][3]*m.m[3][1] + m.m[0][0]*m.m[1][2]*m.m[2][3]*m.m[3][1] +
            m.m[0][3]*m.m[1][1]*m.m[2][0]*m.m[3][2] - m.m[0][1]*m.m[1][3]*m.m[2][0]*m.m[3][2] - m.m[0][3]*m.m[1][0]*m.m[2][1]*m.m[3][2] + m.m[0][0]*m.m[1][3]*m.m[2][1]*m.m[3][2] +
            m.m[0][1]*m.m[1][0]*m.m[2][3]*m.m[3][2] - m.m[0][0]*m.m[1][1]*m.m[2][3]*m.m[3][2] - m.m[0][2]*m.m[1][1]*m.m[2][0]*m.m[3][3] + m.m[0][1]*m.m[1][2]*m.m[2][0]*m.m[3][3] +
            m.m[0][2]*m.m[1][0]*m.m[2][1]*m.m[3][3] - m.m[0][0]*m.m[1][2]*m.m[2][1]*m.m[3][3] - m.m[0][1]*m.m[1][0]*m.m[2][2]*m.m[3][3] + m.m[0][0]*m.m[1][1]*m.m[2][2]*m.m[3][3];
}
Mat4 inverse(const Mat4& m) {
    return 1.0f/det(m) * Mat4();
}
#endif
