//
//  mesh.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/23/18.
//

#include "mesh.h"

Mesh::Mesh(void){
    this->color = Vector3d(0.0,0.0,0.0);
}

Mesh::Mesh(int no_of_vertices, int no_of_faces, vector<Vector3d> vertices, vector<Vector3i> faces, Vector3d color, Material material_properties) {
    this->no_of_vertices = no_of_vertices;
    this->no_of_faces = no_of_faces;
    this->vertices = vertices;
    this->faces = faces;
    this->color = color;
    this->material_properties = material_properties;
}

bool Mesh::intersect(Ray &ray) {
    bool rayInteresectMesh = false;
    double nearTriangleDist = std::numeric_limits<double>::max();
    Vector3d nearestv0v1;
    Vector3d nearestv0v2;
    for (auto const& triangleIndices: this->faces) {
        Vector3d v0 = vertices.at(triangleIndices(0));
        Vector3d v1 = vertices.at(triangleIndices(1));
        Vector3d v2 = vertices.at(triangleIndices(2));
        double u, v;
        double t = std::numeric_limits<float>::max();
        if(isRayTriangleInteresect(ray, v0, v1, v2, t, u, v) && t < nearTriangleDist) {
            nearTriangleDist = t;
            rayInteresectMesh = true;
            nearestv0v1 = v1 - v0;
            nearestv0v2 = v2 - v0;
        }
    }
    
    if(rayInteresectMesh){
        ray.set_intersection_point(ray.origin + ray.direction * nearTriangleDist);
        ray.set_normal(nearestv0v1.cross(nearestv0v2).normalized());
    }
    
    return rayInteresectMesh;
}

bool Mesh::isRayTriangleInteresect(Ray &ray, Vector3d v0, Vector3d v1, Vector3d v2, double &t, double &u, double &v) {
    Vector3d v0v1 = v1 - v0;
    Vector3d v0v2 = v2 - v0;
    Vector3d pvec = ray.direction.cross(v0v2);
    double det = v0v1.dot(pvec);
    
    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < 1e-8) {
        return false;
    }
    
    double detInv = 1 / det;
    
    Vector3d tvec = ray.origin - v0;
    u = tvec.dot(pvec) * detInv;
    if (u < 0 || u > 1) return false;
    
    Vector3d qvec = tvec.cross(v0v1);
    v = ray.direction.dot(qvec) * detInv;
    if (v < 0 || u + v > 1) return false;
    
    t = v0v2.dot(qvec) * detInv;
    
    return true;
    
}
