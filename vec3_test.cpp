#include "vec3.hpp"


int main(void) {
    Vec3 v1(1, 0, 0);
    Vec3 v2(0, 1, 0);
    v1.cross(v2).print();
}
