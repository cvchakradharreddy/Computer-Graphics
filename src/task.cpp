//
//  task.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#include "task.h"

// Image writing library
#define STB_IMAGE_WRITE_IMPLEMENTATION // Do not include this line twice in your project!
#include "stb_image_write.h"
#include "utils.h"

void Task::task1(void) {
    cout << "Task 1: Ray tracer - Multiple spheres with orthographic projection and Lambertian shading" << endl;
    
    randomSpheresAndLights(Projection::Orthographic, "task1.png");
}

void Task::task2() {
    cout << "Task 2: Ray tracer - Multiple spheres with orthographic projection, diffuse, specular  and ambient shading" << endl;
    
    multipleSpheresAndLights(Projection::Orthographic, "task2.png");
}

void Task::task3(void) {
    cout << "Task 3: Ray tracer - Multiple spheres with perspective projection, diffuese, specular and ambient shading" << endl;
    randomSpheresAndLights(Projection::Perspective, "task3_1.png");
    multipleSpheresAndLights(Projection::Perspective, "task3_2.png");
}

void Task::task4(void) {
    cout << "Task 4: Ray tracer - Loads bunny and bumpy cube from .off files to the previous scene" << endl;
    list<Object*> objects;
    //Prepare lights at particular general locations
    list<Light> lightSources;
    Light light1 = Light(Vector3d(-2,2,9), 1.0, Vector3d(1.0, 1.0, 1.0));
    Light light2 = Light(Vector3d(2,-2,9), 1.0, Vector3d(1.0, 1.0, 1.0));
    lightSources.push_back(light1);
    lightSources.push_back(light2);
    
    
    Material purely_diffuse = Material(1.0,0.0);
    Material purely_specular = Material(0.0,1.0);
    
    Sphere sphere1 = Sphere(1.5, Vector3d(-2, 0, 5), Vector3d(1.0,0.0,0.0),purely_diffuse);
    Sphere sphere2 = Sphere(1.5, Vector3d(2, 0, 7), Vector3d(0.0,1.0,0.0), purely_specular);
    
    objects.push_back(&sphere1);
    objects.push_back(&sphere2);
    
    Mesh mesh1;
    mesh1.color = Vector3d(0.0, 0.0, 1.0);
    if(Common::loadMeshFromFile(mesh1.no_of_vertices, mesh1.no_of_faces, mesh1.vertices, mesh1.faces, "bunny.off")) {
       objects.push_back(&mesh1);
    }
    Mesh mesh2;
    mesh2.color = Vector3d(0.0, 1.0, 1.0);
    if(Common::loadMeshFromFile(mesh2.no_of_vertices, mesh2.no_of_faces, mesh2.vertices, mesh2.faces, "bumpy_cube.off")) {
        objects.push_back(&mesh2);
    }

    MatrixXd R = MatrixXd::Zero(800,800); // Store the color
    MatrixXd G = MatrixXd::Zero(800,800);
    MatrixXd B = MatrixXd::Zero(800,800);
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask
    
    Common::initiateRayTracerForObjects(lightSources, objects, R, G, B, A, Shading::All, Projection::Orthographic, false);
    
    // Save to png
    const string filename("task4.png");
    write_matrix_to_png(R,G,B,A,filename);
}

void Task::task5(void) {
    cout << "Task 5: Ray tracer - Add shadows to the previous scene and add a surface to see shadows" << endl;
    list<Object*> objects;
    //Prepare lights at particular general locations
    list<Light> lightSources;
    Light light1 = Light(Vector3d(-2,2,9), 1.0, Vector3d(1.0, 1.0, 1.0));
    Light light2 = Light(Vector3d(2,-2,9), 1.0, Vector3d(1.0, 1.0, 1.0));
    lightSources.push_back(light1);
    lightSources.push_back(light2);
    
    
    Material purely_diffuse = Material(1.0,0.0);
    Material purely_specular = Material(0.0,1.0);
    
    Sphere sphere1 = Sphere(1.5, Vector3d(-2, 0, 5), Vector3d(1.0,0.0,0.0),purely_diffuse);
    Sphere sphere2 = Sphere(1.5, Vector3d(2, 0, 7), Vector3d(0.0,1.0,0.0), purely_specular);
    
    objects.push_back(&sphere1);
    objects.push_back(&sphere2);
    
    Mesh mesh1;
    mesh1.color = Vector3d(0.0, 0.0, 1.0);
    if(Common::loadMeshFromFile(mesh1.no_of_vertices, mesh1.no_of_faces, mesh1.vertices, mesh1.faces, "bunny.off")) {
        objects.push_back(&mesh1);
    }
    Mesh mesh2;
    mesh2.color = Vector3d(0.0, 1.0, 1.0);
    if(Common::loadMeshFromFile(mesh2.no_of_vertices, mesh2.no_of_faces, mesh2.vertices, mesh2.faces, "bumpy_cube.off")) {
        objects.push_back(&mesh2);
    }
    
    Mesh mesh3;
    mesh3.color = Vector3d(0, 0, 0);
    if(Common::loadMeshFromFile(mesh3.no_of_vertices, mesh3.no_of_faces, mesh3.vertices, mesh3.faces, "plane.off")) {
        objects.push_back(&mesh3);
    }
    
    MatrixXd R = MatrixXd::Zero(800,800); // Store the color
    MatrixXd G = MatrixXd::Zero(800,800);
    MatrixXd B = MatrixXd::Zero(800,800);
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask
    
    Common::initiateRayTracerForObjects(lightSources, objects, R, G, B, A, Shading::All, Projection::Orthographic, true);
    
    // Save to png
    const string filename("task5.png");
    write_matrix_to_png(R,G,B,A,filename);
}


list<Light> randomLightSources;
list<Sphere> randomSpheres;

void Task::randomSpheresAndLights(Projection projectionType, string file) {
    //Prepare lights
    randomLightSources = randomLightSources.empty() ? Common::generateLightSources(1) : randomLightSources;
    
    // Prepare spheres
    randomSpheres = randomSpheres.empty() ? Common::generateSpheres(5) : randomSpheres;
    
    MatrixXd R = MatrixXd::Zero(800,800); // Store the color
    MatrixXd G = MatrixXd::Zero(800,800);
    MatrixXd B = MatrixXd::Zero(800,800);
    
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask
    Common::initiateRayTracer(randomLightSources, randomSpheres, R, G, B, A, Shading::Lambertian, projectionType);
    
    // Save to png
    const string filename(file);
    write_matrix_to_png(R,G,B,A,filename);
}

void Task::multipleSpheresAndLights(Projection projectionType, string file) {
    
    //Prepare lights at particular general locations
    list<Light> lightSources;
    Light light1 = Light(Vector3d(-2,2,9), 1.0, Vector3d(1.0, 1.0, 1.0));
    Light light2 = Light(Vector3d(2,-2,9), 1.0, Vector3d(1.0, 1.0, 1.0));
    lightSources.push_back(light1);
    lightSources.push_back(light2);
    
    // Prepare spheres at particular general locations
    list<Sphere> spheres1;
    list<Sphere> spheres2;
    
    Material purely_diffuse = Material(1.0,0.0);
    Material purely_specular = Material(0.0,1.0);
    
    Sphere sphere1 = Sphere(1.5, Vector3d(-2, 0, 5), Vector3d(1.0,0.0,0.0),purely_diffuse);
    Sphere sphere2 = Sphere(1.5, Vector3d(2, 0, 7), Vector3d(0.0,1.0,0.0), purely_specular);
    
    spheres1.push_back(sphere1);
    spheres2.push_back(sphere2);
    MatrixXd R = MatrixXd::Zero(800,800); // Store the color
    MatrixXd G = MatrixXd::Zero(800,800);
    MatrixXd B = MatrixXd::Zero(800,800);
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask
    
    Common::initiateRayTracer(lightSources, spheres1, R, G, B, A, Shading::All, projectionType);
    Common::initiateRayTracer(lightSources, spheres2, R, G, B, A, Shading::All, projectionType);
    
    // Save to png
    const string filename(file);
    write_matrix_to_png(R,G,B,A,filename);
}

