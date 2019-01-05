//
//  ray.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#include "ray.h"

Ray::Ray(void) {
    this->origin << 0, 0, 0;
    this->direction << 0, 0, -1;
}

Ray::Ray(Vector3d origin, Vector3d direction) {
    this->origin = origin;
    this->direction = direction;
}
void Ray::set_origin(Vector3d origin) {
    this->origin = origin;
}

void Ray::set_direction(Vector3d direction) {
    this->direction = direction;
}

void Ray::set_intersection_point(Vector3d point) {
    this->intersection_point = point;
}

Vector3d Ray::get_intersection_point (void) {
    return this->intersection_point;
}

void Ray::set_normal(Vector3d normal) {
    this->normal = normal;
}

Vector3d Ray::get_normal (void) {
    return this->normal;
}
