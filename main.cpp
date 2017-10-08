#include <iostream>
#include <unistd.h>
#include <cmath>
#include "vec2.h"
#include "vec3.h"
#include "point3.h"
#include "mat4.h"
#include "transform.h"
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
    
    Point3 camPos = Point3(0, 3, -5);
    Vec3 camForward = normalize(Point3() - camPos);
    Camera *cam = new Camera(camPos, camForward);

    Objects *objs = new Objects();
    Transform t = translate(Vec3(0, -1, 0))*scale(5.0, 1.0, 5.0);
    Transform t_inv = inverse(t);
    objs->add(new Plane(&t, &t_inv, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(0.9f)), new Mono(RGB(0.1f)), 5.0f)));
    /*
    for(int i = 0; i < 20; i++) {
        Vec3 pos = randVec(-2.0, 2.0, 0.0, 2.0, -2.0, 2.0);
        Transform* t2 = new Transform(rotate(2*M_PI*rnd(), 2*M_PI*rnd(), 2*M_PI*rnd())*translate(pos));
        Transform* t2_inv = new Transform(inverse(*t2));
        objs->add(new Plane(t2, t2_inv, new Diffuse(0.9f), new Mono(RGB(rnd(), rnd(), rnd()))));
    }
    */
    
    Transform t2 = translate(Vec3()); 
    Transform t2_inv = inverse(t2);
    objs->add(new Sphere(1.0f, &t2, &t2_inv, new Mirror(0.9f), new Mono(RGB(1.0f))));
    for(int i = 0; i < 12; i++) {
        float x = std::cos((float)i/12.0f * 2.0f*M_PI);
        float y = std::sin((float)i/12.0f * 2.0f*M_PI);
        Transform* t = new Transform(translate(3.0f*Vec3(x, 0, y)));
        Transform* t_inv = new Transform(inverse(*t));
        objs->add(new Sphere(0.5f, t, t_inv, new Glass(1.4f), new Mono(RGB((x + 1.0f)/2.0f, (y + 1.0f)/2.0f, 1.0f))));
    }

    Sky *sky = new simpleSky(1.0f);

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
