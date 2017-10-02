#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "rgb.h"
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
            if(i < 0 || i >= width || j < 0 || j >= height) {
                std::cerr << "Invalid access" << std::endl;
                exit(1);
            }
            return data[j + width*i];
        };
        void set(int i, int j, const RGB& col) {
            if(i < 0 || i >= width || j < 0 || j >= height) {
                std::cerr << "Invalid access" << std::endl;
                exit(1);
            }
            data[j + width*i] = col;
        };
        void ppm_output(std::string filename) {
            std::ofstream file(filename);
            file << "P3" << std::endl;
            file << width << " " << height << std::endl;
            file << "255" << std::endl;

            for(int j = 0; j < height; j++) {
                for(int i = 0; i < width; i++) {
                    RGB col = clamp(this->get(i, j), RGB(0), RGB(255));
                    file << (int)col.r << " " << (int)col.g << " " << (int)col.b << std::endl;
                }
            }

            file.close();
        };
};
#endif
