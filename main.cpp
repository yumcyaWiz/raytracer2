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
    
    Point3 camPos = Point3(0, 1, 3);
    Vec3 camForward = normalize(Point3() - camPos);
    Camera *cam = new PinholeCamera(camPos, camForward, 1.0f, 1.0f);
    //Camera *cam = new ThinLensCamera(camPos, camForward, 5.0f, 1.5f, Point3(0, 0, 0), 8.0f);
    //Camera *cam = new EquidistantFisheyeCamera(camPos, camForward, 1.0f, 1.0f);

    Objects *objs = new Objects();
    Transform t = translate(Vec3(0, -1, 0))*scale(3.0, 1.0, 3.0);
    Transform t_inv = inverse(t);
    objs->add(new Plane(&t, &t_inv, new Diffuse(0.9f), new Checkerboard(new Mono(RGB(1.0f)), new Mono(RGB(0.1f)), 5.0f)));
    Transform t2 = translate(Vec3(0, 0, 0));
    Transform t2_inv = inverse(t2);
    //objs->add(new Box(&t2, &t2_inv, new Glass(1.4f), new Mono(RGB(1.0f)), Point3(-0.5, -0.5, -0.5), Point3(0.5, 0.5, 0.5)));
    objs->add(new Disk(&t2, &t2_inv, new Diffuse(0.9f), new Mono(RGB(1.0f)), 0.0f, 1.4f, 1.2f, 2*M_PI));
    Transform t3 = translate(Vec3(0, 0, 0));
    Transform t3_inv = inverse(t3);
    objs->add(new Sphere(&t3, &t3_inv, new Diffuse(1.0f), new ImageTexture("earth.jpg"), 1.0f, -1.0f, 1.0f, 2*M_PI));

    /*
    Transform t2 = translate(Vec3(-3, 0, 0))*rotateZ(M_PI/2)*scale(3.0, 1.0, 3.0);
    Transform t2_inv = inverse(t2);
    objs->add(new Plane(&t2, &t2_inv, new Diffuse(1.0f), new Mono(RGB(1.0f, 0.0f, 0.0f))));
    Transform t3 = translate(Vec3(3, 0, 0))*rotateZ(M_PI/2)*scale(3.0, 1.0, 3.0);
    Transform t3_inv = inverse(t3);
    objs->add(new Plane(&t3, &t3_inv, new Diffuse(1.0f), new Mono(RGB(0.0f, 1.0f, 0.0f))));
    Transform t4 = translate(Vec3(0, 3, 0))*scale(3.0, 1.0, 3.0);
    Transform t4_inv = inverse(t4);
    objs->add(new Plane(&t4, &t4_inv, new Diffuse(1.0f), new Mono(RGB(1.0f))));
    Transform t5 = translate(Vec3(0, 3, 0));
    Transform t5_inv = inverse(t5);
    objs->add(new Sphere(1.0f, &t5, &t5_inv, new Emissive(), new Mono(RGB(5.0f)), -1.0f, 1.0f, 2*M_PI));
    Transform t6 = translate(Vec3(0, 1.5, -3))*rotateX(M_PI/2)*scale(3.0, 3.0, 3.0);
    Transform t6_inv = inverse(t6);
    objs->add(new Plane(&t6, &t6_inv, new Diffuse(1.0f), new Mono(RGB(1.0f))));
    Transform t7 = translate(Vec3(0, 0, 0));
    Transform t7_inv = inverse(t7);
    objs->add(new Sphere(1.0f, &t7, &t7_inv, new Glass(1.4f), new Mono(RGB(0.0f, 0.0f, 1.0f)), -1.0f, 1.0f, 2*M_PI));
    */

    /*
    Transform t2 = translate(Vec3());
    Transform t2_inv = inverse(t2);
    objs->add(new Sphere(1.0f, &t2, &t2_inv, new Mirror(1.0f), new Mono(RGB(1.0f)), -1.0f, 1.0f, 2*M_PI));
    Transform t2 = translate(Vec3(0, -1, 0));
    Transform t2_inv = inverse(t2);
    objs->add(new Box(&t2, &t2_inv, new Diffuse(0.9f), new Mono(RGB(1.0f)), Point3(0, 0, 0), Point3(1, 1, 1)));
    */

    /*
    for(int i = 0; i < 12; i++) {
        float phi = (float)i/12.0 * 2*M_PI;
        float x = 2.0*std::cos(phi) - 0.7*0.5;
        float y = 2.0*std::sin(phi);
        Transform t2 = translate(Vec3(x, -1, y));
        Transform t2_inv = inverse(t2);
        objs->add(new Box(new Transform(t2), new Transform(t2_inv), new Mirror(1.0f), new Mono(hsv2rgb(phi * 180/M_PI, 1.0f, 1.0f)), Point3(0, 0, 0), Point3(0.7, 0.7, 0.7)));
    }
    */

    /*
    Transform t2 = translate(Vec3(0, 0, 0))*rotateY(M_PI/2.0);
    Transform t2_inv = inverse(t2);
    objs->add(new Sphere(1.0f, &t2, &t2_inv, new Glass(1.4f), new ImageTexture("uv_test2.png"), -1.0f, 1.0f, 2*M_PI));
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
    
    /*
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
    */

    Sky *sky = new IBL("PaperMill_E_3k.hdr");
    //Sky *sky = new simpleSky(0.5f);

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
