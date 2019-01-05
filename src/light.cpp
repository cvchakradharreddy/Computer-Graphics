//
//  light.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#include "light.h"

Light::Light(void){
    this->origin << 0,0,0;
}

Light::Light(Vector3d origin, double intensity, Vector3d color){
    this->origin = origin;
    this->intensity = intensity;
    this->color = color;
}

void Light::set_origin(Vector3d origin){
    this->origin = origin;
}

Vector3d Light::get_origin(void){
    return this->origin;
}

void Light::set_intensity(double intensity){
    this->intensity = intensity;
}

double Light::get_intensity(void){
    return this->intensity;
}

void Light::set_color(Vector3d color){
    this->color = color;
}

Vector3d Light::get_color(void){
    return this->color;
}


