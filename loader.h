#ifndef LOADER_H
#define LOADER_H
#include <iostream>
#include <fstream>
#include <string>
#include "objects.h"
class Loader {
    public:
        Loader() {};

        bool loadFile(std::string filename, Objects& objs) const {
            std::ifstream file(filename);
        };
};
#endif
