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
#include "util.h"


int main(int argc, char** argv) {
    int width;
    int height;
    int samples;
    bool png_output = false;
    bool normal_output = false;

    int opt;
    while((opt = getopt(argc, argv, "w:h:s:on")) != -1) {
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
            case 'n':
                normal_output = true;
                break;
        }
    }


    Image *img = new Image(width, height);
    
    Point3 camPos = Point3(0, 3, 11);
    Vec3 camForward = normalize(Point3() - camPos);
    //Camera *cam = new PinholeCamera(camPos, camForward, 1.5f, 1.5f);
    Camera *cam = new ThinLensCamera(camPos, camForward, 3.0f, 1.5f, Point3(0, 0, 0), 12.0f);
    //Camera *cam = new EquidistantFisheyeCamera(camPos, camForward, 1.0f, 1.0f);

    Objects *objs = new Objects();
    Transform t = translate(Vec3(0, -1, 0))*scale(10.0, 1.0, 10.0);
    Transform t_inv = inverse(t);
    objs->add(new Plane(&t, &t_inv, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(1.0f)), new Mono(RGB(0.1f)), 5.0f)));
    Transform t2 = translate(Vec3(-5, -1, 0));
    Transform t2_inv = inverse(t2);
    objs->add(new Paraboloid(&t2, &t2_inv, new Diffuse(0.9f), new ImageTexture("uv_test.png"), 3.0f, 1.0f, 0.0f, 1.5f, 2*M_PI));
    Transform t3 = translate(Vec3(-2.5, -1, 0));
    Transform t3_inv = inverse(t3);
    objs->add(new Cone(&t3, &t3_inv, new Diffuse(0.9f), new ImageTexture("uv_test.png"), 1.0f, 1.0f, 2*M_PI));
    Transform t4 = translate(Vec3(0, -1, 0));
    Transform t4_inv = inverse(t4);
    objs->add(new Disk(&t4, &t4_inv, new Diffuse(0.9f), new ImageTexture("uv_test.png"), 1.0f, 1.0f, 0.2f, 2*M_PI));
    Transform t5 = translate(Vec3(2.5, 0, 0));
    Transform t5_inv = inverse(t5);
    objs->add(new Cylinder(&t5, &t5_inv, new Diffuse(0.9f), new ImageTexture("uv_test.png"), 1.0f, -1.0f, 1.0f, 2*M_PI));
    Transform t6 = translate(Vec3(5, 0, 0));
    Transform t6_inv = inverse(t6);
    objs->add(new Sphere(&t6, &t6_inv, new Diffuse(0.9f), new ImageTexture("uv_test.png"), 1.0f, -1.0f, 1.0f, 2*M_PI));

    Sky *sky = new IBL("PaperMill_E_3k.hdr");

    Render render(cam, objs, sky, img, samples);
    if(normal_output) {
        render.render_normal();
        render.output();
        return 0;
    }
    render.render();
    if(png_output) {
        render.png_output();
    }
    else {
        render.output();
    }

    return 0;
}
