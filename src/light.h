//
//  light.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#ifndef light_h
#define light_h

#include <Eigen/Core>
using namespace Eigen;

class Light {
public:
    Vector3d origin;
    double intensity;
    Vector3d color;
    
    Light();
    Light(Vector3d origin, double intensity, Vector3d color);
    void set_origin(Vector3d origin);
    Vector3d get_origin(void);
    void set_intensity(double intensity);
    double get_intensity(void);
    void set_color(Vector3d color);
    Vector3d get_color(void);
};

#endif /* light_h */
