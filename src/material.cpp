//
//  material.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/22/18.
//

#include "material.h"

Material::Material(void) {
    this->Kd = 0.5;
    this->Ks = 0.5;
}

Material::Material(double Kd, double Ks) {
    this->Kd = Kd;
    this->Ks = Ks;
}
