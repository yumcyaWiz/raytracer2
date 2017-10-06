#include <iostream>
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
    objs->add(new Sphere(Vec3(0, -101.0f, 0), 100.0f, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(0.1f)), new Mono(RGB(1.0f)), 0.1f)));
    objs->add(new Sphere(Vec3(0, 0, 0), 1.0f, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(0.1f)), new Mono(RGB(1.0f)), 0.1f)));

    Render render(cam, objs, new testSky(), img, 10);
    render.render();

    return 0;
}
