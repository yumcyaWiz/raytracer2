#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <memory>
#include "vec3.h"
#include "hit.h"
#include "object.h"
class Objects {
    public:
        std::vector<std::shared_ptr<Object>> objects;


        Objects() {};


        void add(Object* obj) {
            objects.push_back(std::shared_ptr<Object>(obj));
        };
        bool intersect(const Ray& ray, Hit& res) {
            bool hit = false;
            res.t = ray.tmax;
            for(auto itr = objects.begin(); itr != objects.end(); itr++) {
                Hit res2;
                if((*itr)->intersect(ray, res2)) {
                    hit = true;
                    if(res2.t < res.t) {
                        res = res2;
                    }
                }
            }
            return hit;
        };
};
#endif
