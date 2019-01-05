//
//  object.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/24/18.
//

#ifndef object_h
#define object_h

#include "material.h"
#include "ray.h"

#include <Eigen/Core>
using namespace Eigen;

class Object {
public:
    Vector3d color;
    Material material_properties;
    
    Object();
    Object(Vector3d color, Material material_properties);
    virtual ~Object();
    virtual bool intersect(Ray &ray) = 0;
};

#endif /* object_h */
