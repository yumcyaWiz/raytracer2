#include <iostream>
#include "vec2.h"
#include "vec3.h"
#include "mat4.h"
#include "image.h"
#include "camera.h"
#include "objects.h"
#include "render.h"
#include "sky.h"


int main() {
    Image *img = new Image(512, 512);
    
    Vec3 camPos = Vec3(0, 1, -3);
    Vec3 camForward = normalize(-camPos);
    Camera *cam = new Camera(camPos, camForward);

    Objects *objs = new Objects();
    objs->add(new Plane(Vec3(0, -1, 0), Vec3(0, 1, 0), Vec2(5.0f), new Diffuse(0.9f), new Mono(RGB(1.0f))));
    objs->add(new Sphere(Vec3(0, 0, 0), 1.0f, new Glass(1.4f), new Mono(RGB(1.0f)))); 

    Render render(cam, objs, new testSky(), img, 10);
    render.render();

    return 0;
}
