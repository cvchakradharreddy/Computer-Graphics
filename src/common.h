//
//  common.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#ifndef common_h
#define common_h

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <ctime>
#include <vector>
#include <cmath>

#include "light.h"
#include "sphere.h"
#include "shading.h"
#include "projection.h"
#include "material.h"
#include "mesh.h"

using namespace std;

class Common {
    public:
    static list<Light> generateLightSources(int n);
    static list<Sphere> generateSpheres(int n);
    static void computeIntersection(list<Sphere> spheres, Ray &ray, double &r, double &g, double &b, double &a, list<Light> lightSources, Shading shadingType);
    static void initiateRayTracer(list<Light> lightSources, list<Sphere> spheres, MatrixXd &R, MatrixXd &G, MatrixXd &B, MatrixXd &A, Shading shadingType, Projection projectionType);
    static Vector3d multiplyTwoVectors (Vector3d vector1, Vector3d vector2);
    
    static void initiateRayTracerForObjects(list<Light> lightSources, list<Object*> objects, MatrixXd &R, MatrixXd &G, MatrixXd &B, MatrixXd &A, Shading shadingType, Projection projectionType, bool enableShadow);
    static bool loadMeshFromFile(int &no_of_vertices, int &no_of_faces, vector<Vector3d> &vertices, vector<Vector3i> &faces, string filename);
    static void computeRayIntesectionObjects(Ray &ray, list<Object*> objects, double &r, double &g, double &b, double &a, list<Light> lightSources, Shading shadingType, bool enableShadow);
    static bool doesRayIntesectTriangle(Ray &ray, Vector3d &triangle, double &nearTriangle, Vector3d &uv);
    static bool doesShadowIntersect(list<Object*> objects, Ray ray);
};
#endif /* common_h */
