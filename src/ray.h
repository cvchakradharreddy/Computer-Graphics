//
//  ray.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#ifndef ray_h
#define ray_h

#include <Eigen/Core>
using namespace Eigen;

class Ray {
public:
    Vector3d origin;
    Vector3d direction;
    Vector3d intersection_point;
    Vector3d normal;
    
    Ray();
    Ray(Vector3d origin, Vector3d direction);
    void set_origin(Vector3d origin);
    void set_direction(Vector3d direction);
    void set_intersection_point(Vector3d point);
    Vector3d get_intersection_point(void);
    void set_normal(Vector3d normal);
    Vector3d get_normal(void);
};

#endif /* ray_h */
