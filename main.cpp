#include <iostream>
#include <unistd.h>
#include "vec2.h"
#include "vec3.h"
#include "mat4.h"
#include "image.h"
#include "camera.h"
#include "objects.h"
#include "render.h"
#include "sky.h"


int main(int argc, char** argv) {
    int width;
    int height;
    int samples;
    bool png_output = false;

    int opt;
    while((opt = getopt(argc, argv, "w:h:s:o")) != -1) {
        switch(opt) {
            case 'w':
                width = std::stoi(optarg);
                break;
            case 'h':
                height = std::stoi(optarg);
                break;
            case 's':
                samples = std::stoi(optarg);
                break;
            case 'o':
                png_output = true;
                break;
        }
    }


    Image *img = new Image(width, height);
    
    Vec3 camPos = Vec3(0, 1, -4);
    Vec3 camForward = normalize(-camPos);
    Camera *cam = new Camera(camPos, camForward);

    Objects *objs = new Objects();
    objs->add(new Sphere(Vec3(0, -10001, 0), 10000.0f, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(0.9f)), new Mono(RGB(0.1f)), 0.1f)));
    objs->add(new Sphere(Vec3(2, 0, 0), 1.0f, new Diffuse(0.9f), new Mono(RGB(0.5f, 0.5f, 1.0f))));
    objs->add(new Sphere(Vec3(-2, 0, 0), 1.0f, new Glass(1.4f), new Mono(RGB(1.0f))));

    Sky *sky = new simpleSky();

    Render render(cam, objs, sky, img, samples);
    render.render();
    if(png_output) {
        render.png_output();
    }
    else {
        render.output();
    }

    return 0;
}
