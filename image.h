#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "rgb.h"
#include "util.h"
class Image {
    public:
        int width;
        int height;
        RGB *data;

        Image(int _width, int _height) : width(_width), height(_height) {
            data = new RGB[width*height];
        };
        ~Image() {
            delete[] data;
        };

        RGB get(int i, int j) const {
            if(i < 0 || i >= height || j < 0 || j >= width) {
                std::cerr << "Invalid access" << std::endl;
                std::exit(1);
            }
            return data[j + width*i];
        };
        void set(int i, int j, const RGB& col) {
            if(i < 0 || i >= height || j < 0 || j >= width) {
                std::cerr << "Invalid access" << std::endl;
                std::exit(1);
            }
            data[j + width*i] = col;
        };


        void ppm_output(std::string filename) {
            std::ofstream file(filename);
            file << "P3" << std::endl;
            file << width << " " << height << std::endl;
            file << "255" << std::endl;

            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    RGB col = clamp(this->get(i, j), RGB(0), RGB(1));
                    file << (int)(255.f*col.r) << " " << (int)(255.f*col.g) << " " << (int)(255.f*col.b) << std::endl;
                }
            }

            file.close();
        };
        void ppm_output() {
            this->ppm_output(ctime_string() + ".ppm");
        };

        void divide(float n) {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    this->set(i, j, this->get(i, j)/n);
                }
            }
        };
        void gamma_correlation() {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    this->set(i, j, pow(this->get(i, j), 1.0f/2.2f));
                }
            }
        };
};
#endif
