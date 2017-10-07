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
    objs->add(new Sphere(Vec3(0, -10001, 0), 10000.0f, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(0.9f)), new Mono(RGB(0.1f)), 0.1f)));
    objs->add(new Sphere(Vec3(0, 0, 0), 1.0f, new Diffuse(0.9f), new Mono(RGB(1.0f, 0.5f, 0.0f))));

    Sky *sky = new simpleSky();

    Render render(cam, objs, sky, img, 10);
    render.render();

    return 0;
}
