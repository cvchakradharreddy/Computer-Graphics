//
//  mesh.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/23/18.
//

#ifndef mesh_h
#define mesh_h


#include <vector>
#include <Eigen/Dense>

#include "ray.h"
#include "material.h"
#include "object.h"

using namespace std;
using namespace Eigen;

class Mesh: public Object{
public:
    int no_of_vertices;
    int no_of_faces;
    vector<Vector3d> vertices;
    vector<Vector3i> faces;
    
    Mesh(void);
    Mesh(int no_of_vertices, int no_of_faces, vector<Vector3d> vertices, vector<Vector3i> faces, Vector3d color, Material material_properties);
    bool intersect(Ray &ray);
    
private:
    bool isRayTriangleInteresect(Ray &ray, Vector3d v0, Vector3d v1, Vector3d v2, double &t, double &u, double &v);
};

#endif /* mesh_h */
