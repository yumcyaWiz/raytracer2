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
    
    Point3 camPos = Point3(0, 1, 5.5);
    Vec3 camForward = normalize(Point3() - camPos);
    //Camera *cam = new ThinLensCamera(camPos, camForward, 1.0f, 1.0f, Point3(0, 0, 2.5), 5.6f);
    Camera *cam = new EquiSolidAngleFisheyeCamera(camPos, camForward, 1.0f, 0.65f);

    Objects *objs = new Objects();
    Transform t = translate(Vec3(0, -1, 0))*scale(5.0, 1.0, 5.0);
    Transform t_inv = inverse(t);
    objs->add(new Plane(&t, &t_inv, new Diffuse(0.9f), new Mono(RGB(1.0f))));
    /*
    Transform t2 = translate(Vec3(0, 0, 0))*rotateY(M_PI/2.0);
    Transform t2_inv = inverse(t2);
    objs->add(new Sphere(1.0f, &t2, &t2_inv, new Glass(1.4f), new ImageTexture("uv_test2.png"), -1.0f, 1.0f, 2*M_PI));
    */

    /*
    Transform t2 = translate(Vec3());
    Transform t2_inv = inverse(t2);
    objs->add(new Sphere(1.0f, &t2, &t2_inv, new Glass(1.4f), new Mono(RGB(1.0f)), -1.0f, 1.0f, 2*M_PI));
    */

    /*
    for(int i = 0; i < 30; i++) {
        Vec3 pos = randVec(-3.0, 3.0, 0.0, 2.0, -3.0, 3.0);
        Transform* t2 = new Transform(rotate(2*M_PI*rnd(), 2*M_PI*rnd(), 2*M_PI*rnd())*translate(pos)*scale(0.7, 1.0, 0.7));
        Transform* t2_inv = new Transform(inverse(*t2));
        Material *mat;
        Texture *tex;
        if(rnd() < 0.8) {
            mat = new Diffuse(0.9f);
            tex = new Mono(RGB(rnd(), rnd(), rnd()));
        }
        else {
            mat = new Mirror(1.0f);
            tex = new Mono(RGB(1.0f));
        }
        objs->add(new Plane(t2, t2_inv, mat, tex));
    }
    */
    
    Transform t2 = scale(1.0, 1.0, 1.0); 
    Transform t2_inv = inverse(t2);
    objs->add(new Sphere(1.0f, &t2, &t2_inv, new Mirror(1.0f), new Mono(RGB(1.0f)), -1.0f, 1.0f, 2.0*M_PI));
    for(int i = 0; i < 12; i++) {
        float x = std::cos((float)i/12.0f * 2.0f*M_PI);
        float y = std::sin((float)i/12.0f * 2.0f*M_PI);
        Transform* t = new Transform(translate(Vec3(2.5f*x, -0.5, 2.5f*y)));
        Transform* t_inv = new Transform(inverse(*t));
        objs->add(new Sphere(0.5f, t, t_inv, new Glass(1.4f), new ImageTexture("earth2.jpg"), -1.0f, 1.0f, 2*M_PI));
    }

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
