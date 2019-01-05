//
//  sphere.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#ifndef sphere_h
#define sphere_h

#include <Eigen/Core>
#include "ray.h"
#include "material.h"
#include "object.h"
using namespace Eigen;

class Sphere: public Object{
public:
    double radius;
    Vector3d center;
    
    Sphere();
    Sphere(double radius, Vector3d center, Vector3d color, Material material_properties);
    
    void set_radius(double radius);
    void set_center(Vector3d center);
    void set_color(Vector3d color);
    void set_material_properties(Material material_properties);
    bool intersect(Ray &ray);
};

#endif /* sphere_h */
