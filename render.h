#ifndef RENDER_H
#define RENDER_H
class Render {
    public:
        Image *img;


        Render(Image& _img) : img(&_img) {};


        void render() {
            Camera cam(Vec3(0, 0, 0), Vec3(0, 0, 1));
            Sphere sphere(Vec3(0, 0, 3), 1.0f, 0.0f, 3.28f, 0.0f, 3.14f);

            for(int i = 0; i < img->width; i++) {
                for(int j = 0; j < img->height; j++) {
                    float u = (2.0f*i - img->width)/img->height;
                    float v = (2.0f*j - img->height)/img->height;
                    Ray ray = cam.getRay(u, v);
                    Hit res;
                    if(sphere.intersect(ray, res)) {
                        RGB mat = RGB((res.hitNormal + 1.0)/2.0);
                        img->set(i, j, mat);
                    }
                    else {
                        img->set(i, j, RGB(0));
                    }
                }
            }
            img->ppm_output("output.ppm");
        };
};
#endif
