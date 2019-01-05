//
//  sphere.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/18/18.
//

#include "sphere.h"

Sphere::Sphere(void) {
    this->radius = 1;
    this->center << 0,0,0;
}

Sphere::Sphere(double radius, Vector3d center, Vector3d color, Material material_properties) {
    this->radius = radius;
    this->center = center;
    this->color = color;
    this->material_properties = material_properties;
}

void Sphere::set_radius(double radius) {
    this->radius = radius;
}

void Sphere::set_center(Vector3d center) {
    this->center = center;
}

void Sphere::set_color(Vector3d color) {
    this->color = color;
}

void Sphere::set_material_properties(Material material_properties) {
    this->material_properties = material_properties;
}

bool Sphere::intersect(Ray &ray) {
    float t0, t1; // solutions for t if the ray intersects
    
    // geometric solution
    Vector3d L = center - ray.origin;
    float tca = L.dot(ray.direction);
    if (tca < 0) return false;
    float d2 = L.dot(L) - tca * tca;
    if (d2 > radius*radius) return false;
    float thc = sqrt(radius*radius - d2);
    t0 = tca - thc;
    t1 = tca + thc;
    
    if (t0 > t1) std::swap(t0, t1);
    
    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return false; // both t0 and t1 are negative
    }
    
    float t = t0;
    
    ray.set_intersection_point(ray.origin + ray.direction * t);
    ray.set_normal((ray.intersection_point - center).normalized());
    return true;
}
