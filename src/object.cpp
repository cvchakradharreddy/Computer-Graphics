//
//  object.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/24/18.
//

#include <stdio.h>

#include "object.h"

Object::Object() {
    //nothing
}

Object::Object(Vector3d color, Material material_properties) {
    this->color = color;
    this->material_properties = material_properties;
}

Object::~Object(){};
