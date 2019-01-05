//
//  material.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/22/18.
//

#ifndef material_h
#define material_h

class Material {
    public:
    double Kd; // diffuse coefficient
    double Ks; // specular coefficient
    
    Material(void);
    Material(double Kd, double Ks);
};

#endif /* material_h */
