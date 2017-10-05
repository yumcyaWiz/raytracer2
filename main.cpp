#include <iostream>
#include "image.h"
#include "camera.h"
#include "objects.h"
#include "render.h"
#include "sky.h"


int main() {
    Image *img = new Image(512, 512);
    Camera *cam = new Camera(Vec3(0, 0, 0), Vec3(0, 0, 1));

    Objects *objs = new Objects;
    objs->add(new Sphere(Vec3(0, -10001.0f, 0), 10000.0f, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(1.0f)), new Mono(RGB(0.1f)), 1.0f)));
    objs->add(new Sphere(Vec3(0, 0, 3), 1.0f, new Diffuse(0.9f), new TextTexture()));

    Render render(cam, objs, new testSky(), img, 100);
    render.render();

    return 0;
}
