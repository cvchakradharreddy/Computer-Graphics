//
//  common.cpp
//  Assignment1_bin
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#include "common.h"

list<Light> Common::generateLightSources(int n){
    list<Light> lightSources;
    for(int i = 0; i < n; ++i) {
        double random_x = (rand() % 9) - 4; //assigns random value between -4 and 4
        double random_y = (rand() % 9) - 4; //assigns random value between -4 and 4
        double random_z = 10;
        double light_intensity = 1.0; //Assuming intensity to be 1
        Light lightSource(Vector3d(random_x, random_y, random_z), light_intensity, Vector3d(1.0,1.0,1.0));
        lightSources.push_back(lightSource);
        cout << "Generated light source" << i+1 << "  origin (" << random_x << "," << random_y << "," << random_z << ")" << endl;
    }
    return lightSources;
}

list<Sphere> Common::generateSpheres(int n) {
    list<Sphere> spheres;
    for (int i = 0; i < n; ++i) {
        double random_radius = (rand() % 10)/ 10.0 + 1.0 ; //assigns random value between 1.0 and 2.0
        double random_x = (rand() % 9) - 4; //assigns random value between -4 and 4
        double random_y = (rand() % 9) - 4; //assigns random value between -4 and 4
        double random_z = (rand() % 5); //assigns random value between 0 and 4
        Sphere sphere;
        sphere.set_radius(random_radius);
        sphere.set_center(Vector3d(random_x,random_y,random_z));
        sphere.set_color(Vector3d(0.0, 0.0, 0.0));
        spheres.push_back(sphere);
        cout << "Generated sphere" << i+1 << " center (" << random_x << "," << random_y << "," << random_z << ")" << endl;
    }
    
    return spheres;
}

void Common::computeIntersection(list<Sphere> spheres, Ray &ray, double &r, double &g, double &b, double &a, list<Light> lightSources, Shading shadingType) {
    for (auto sphere = spheres.begin(); sphere != spheres.end(); ++sphere) {
        if(sphere->intersect(ray)) {
            Vector3d ray_intersection = ray.get_intersection_point();
            // Compute normal at the intersection point
            Vector3d ray_normal = ray.get_normal();
            
            Vector3d diffuse_shading(0.0, 0.0, 0.0);
            Vector3d specular_shading(0.0, 0.0, 0.0);
            Vector3d ambient_shading(0.0, 0.0, 0.0);
            Vector3d total_shading(0.0, 0.0, 0.0);
            
            // Simple diffuse model
            for (auto light = lightSources.begin(); light != lightSources.end(); ++light) {
                Vector3d l = light->get_origin() - ray_intersection;
                if(shadingType == Shading::Lambertian || shadingType == Shading::Blinn_Phong || shadingType == Shading::All) {
                    double d = l.normalized().transpose() * ray_normal;
                    
                    // Clamp to zero
                    d = max(d,0.);
                    
                    //Apply light intensity and add to previous light source shading value
                    double diff = (light->get_intensity() * d);
                    
                    // Assuming diffuse coefficient (Kd) to be the same as sphere surface color
                    Vector3d shade_color = sphere->color == Vector3d(0,0,0) ? light-> color : multiplyTwoVectors(sphere->color, light->color);
                    
                    // Multiply with diffuse coefficient Kd
                    shade_color = shade_color * sphere->material_properties.Kd;
                    
                    //Add to previous light source shading value
                    diffuse_shading = (shade_color * diff) + diffuse_shading;
                }
                
                if(shadingType == Shading::Specular || shadingType == Shading::Blinn_Phong || shadingType == Shading::All) {
                    Vector3d v = ray.origin - ray_intersection;
                    Vector3d h = (v + l).normalized();
                    double s = h.transpose() * ray_normal;
                    
                    // Clamp to zero and The power, or Phong exponent is assumed to be 2
                    s = pow(max(s, 0.), 5);
                    
                    //Apply light intensity
                    double spec = (light->get_intensity() * s);
                    
                    // Assuming specular coefficient (Ks) to be 0.5
                    Vector3d shade_color = sphere->color == Vector3d(0,0,0) ? light-> color : multiplyTwoVectors(sphere->color, light->color);
                    
                    shade_color = shade_color * sphere->material_properties.Ks;
                    
                    //Add to previous light source shading value
                    specular_shading = (shade_color * spec) + specular_shading;
                }
            }
            
            if(shadingType == Shading::Ambient || shadingType == Shading::All) {
                // Assuming ambient coefficient (Ka) to be 0.2 and ambient light intensity to be 0.1
                Vector3d ambient_color(1.0, 1.0, 1.0); //Ambient color
                Vector3d Ka = multiplyTwoVectors(sphere->color, ambient_color);
                const double ambient_light_intensity = 0.4;
                
                ambient_shading = Ka * ambient_light_intensity;
            }
            
            switch (shadingType) {
                case Shading::Specular:
                    total_shading = specular_shading;
                    break;
                case Shading::Ambient:
                    total_shading = ambient_shading;
                    break;
                case Shading::Blinn_Phong:
                    total_shading = diffuse_shading + specular_shading;
                    break;
                case Shading::All:
                    total_shading = diffuse_shading + specular_shading + ambient_shading;
                    break;
                case Shading::Lambertian:
                default:
                    total_shading = diffuse_shading;
                    break;
            }
            
            // Apply total shading to pixel
            r = total_shading(0);
            g = total_shading(1);
            b = total_shading(2);
            
            // Disable the alpha mask for this pixel
            a = 1;
        }
    }
}

void Common::initiateRayTracer(list<Light> lightSources, list<Sphere> spheres, MatrixXd &R, MatrixXd &G, MatrixXd &B, MatrixXd &A, Shading shadingType, Projection projectionType)
{
    // The camera is orthographic, pointing in the direction -z and covering the unit square (-1,1) in x and y
    Vector3d origin(-5,5,10);
    double imagePlane_width = 10;
    double imagePlane_height = 10;
    Vector3d x_displacement(imagePlane_width/R.cols(),0,0);
    Vector3d y_displacement(0,-imagePlane_height/R.rows(),0);
    
    for (unsigned i=0;i<R.cols();i++)
    {
        for (unsigned j=0;j<R.rows();j++)
        {
            // Prepare the ray
            Ray ray;
            Vector3d w(0,0,1);
            switch (projectionType) {
                case Projection::Perspective:
                {
                    const double d = 2.0;
                    Vector3d e(-5, 5, 0);
                    Vector3d ray_direction = -w*d + double(i)*x_displacement + double(j)*y_displacement + e;
                    ray.set_origin(Vector3d(0,0,10));
                    ray.set_direction(ray_direction.normalized());
                    break;
                }
                case Projection::Orthographic:
                default:
                {
                    ray.set_origin(origin + double(i)*x_displacement + double(j)*y_displacement);
                    ray.set_direction(-w);
                    break;
                }
            }
            
            //Compute intersection
            computeIntersection(spheres, ray, R(i,j), G(i,j), B(i,j), A(i,j), lightSources, shadingType);
        }
    }
}

Vector3d Common::multiplyTwoVectors (Vector3d vector1, Vector3d vector2) {
    Vector3d result;
    result(0) = vector1(0) * vector2(0);
    result(1) = vector1(1) * vector2(1);
    result(2) = vector1(2) * vector2(2);
    
    return result;
}

bool Common::loadMeshFromFile(int &no_of_vertices, int &no_of_faces, vector<Vector3d> &vertices, vector<Vector3i> &faces, string filename) {
    
    ifstream file;
    file.open ("../../data/"+filename);
    if (!file.is_open()) {
        cout << "Try checking file presence one level above in directory" << endl;
        file.open ("../data/"+filename);
        if(!file.is_open()){
            cout << "Oops! no file found!" << endl;
            return false;
        }
    }
    
    std::string eachLine;
    int lineNumber = 0;
    // Get each line
    while (std::getline (file, eachLine)) {
        // Use std::stringstream to isolate words using operator >>
        std::stringstream wordStream (eachLine);
        
        std::string eachWord;
        int wordNumber = 0;
        
        if(lineNumber == 0) {
            while (wordStream >> eachWord) {
                if(eachWord != "OFF") {
                    std::cout << "Not a OFF file" << endl;
                    return false;
                }
                wordNumber++;
            }
        } else if(lineNumber == 1){
            while (wordStream >> eachWord) {
                if(wordNumber == 0){
                    no_of_vertices = stoi(eachWord);
                } else if(wordNumber == 1) {
                    no_of_faces = stoi(eachWord);
                }
                wordNumber++;
            }
            
        } else if(lineNumber > 1 && lineNumber < no_of_vertices + 2){
            Vector3d vertex = Vector3d::Zero();
            while (wordStream >> eachWord) {
                if (wordNumber <= 3) {
                    if(filename == "bunny.off"){
                        vertex(wordNumber) = stod(eachWord) * 20;
                    } else if(filename == "bumpy_cube"){
                        vertex(wordNumber) = stod(eachWord) * 0.5;
                    } else {
                        vertex(wordNumber) = stod(eachWord);
                    }
                }
                wordNumber++;
            }
            vertices.push_back(vertex);
        } else {
            Vector3i face = Vector3i::Zero();
            int i = 0;
            while (wordStream >> eachWord) {
                if (wordNumber > 0 && wordNumber <= 3) {
                    face(i) = stoi(eachWord);
                    i++;
                }
                wordNumber++;
            }
            faces.push_back(face);
        }
        lineNumber++;
    }
    file.close ();
    return true;
}

void Common::initiateRayTracerForObjects(list<Light> lightSources, list<Object*> objects, MatrixXd &R, MatrixXd &G, MatrixXd &B, MatrixXd &A, Shading shadingType, Projection projectionType, bool enableShadow) {
    Vector3d origin(-5,5,10);
    double imagePlane_width = 10;
    double imagePlane_height = 10;
    Vector3d x_displacement(imagePlane_width/R.cols(),0,0);
    Vector3d y_displacement(0,-imagePlane_height/R.rows(),0);
    int progress = 0;
    int previousProgress = -1;
    for (unsigned i=0;i<R.cols();i++)
    {
        for (unsigned j=0;j<R.rows();j++)
        {
            // Prepare the ray
            Ray ray;
            Vector3d w(0,0,1);
            switch (projectionType) {
                case Projection::Perspective:
                {
                    const double d = 2.0;
                    Vector3d e(-5, 5, 0);
                    Vector3d ray_direction = -w*d + double(i)*x_displacement + double(j)*y_displacement + e;
                    ray.set_origin(Vector3d(0,0,10));
                    ray.set_direction(ray_direction.normalized());
                    break;
                }
                case Projection::Orthographic:
                default:
                {
                    ray.set_origin(origin + double(i)*x_displacement + double(j)*y_displacement);
                    ray.set_direction(-w);
                    break;
                }
            }
            
            //Compute intersection
            Common::computeRayIntesectionObjects(ray, objects, R(i,j), G(i,j), B(i,j), A(i,j), lightSources, shadingType, enableShadow);
        }
        progress = ((i+1)*100)/(R.cols());
        if(progress != previousProgress) {
            cout << progress << "% completed" << endl;
            previousProgress = progress;
        }
    }
}

bool Common::doesShadowIntersect(list<Object*> objects, Ray ray){
    bool doesInteresectionHappen = false;
    for(auto const& object: objects){
        if(object->intersect(ray)){
            doesInteresectionHappen = true;
        }
    }
    return doesInteresectionHappen;
}

void Common::computeRayIntesectionObjects(Ray &ray, list<Object*> objects, double &r, double &g, double &b, double &a, list<Light> lightSources, Shading shadingType, bool enableShadow) {
    Vector3d nearest_ray_intersection;
    Vector3d nearest_ray_normal;
    Object* nearest_object;
    
    bool doesInteresectionHappen = false;
    double nearest_ray_intersection_distance = std::numeric_limits<double>::max();
    for(auto const& object: objects){
        if(object->intersect(ray) && (ray.get_intersection_point() - ray.origin).norm() < nearest_ray_intersection_distance){
            nearest_ray_intersection = ray.get_intersection_point();
            nearest_ray_intersection_distance = (nearest_ray_intersection - ray.origin).norm();
            nearest_object = object;
            nearest_ray_normal = ray.get_normal();
            doesInteresectionHappen = true;
        }
    }
   
    if(doesInteresectionHappen){
        Vector3d ray_intersection = nearest_ray_intersection;
        // Compute normal at the intersection point
        Vector3d ray_normal = nearest_ray_normal;
        
        Vector3d diffuse_shading(0.0, 0.0, 0.0);
        Vector3d specular_shading(0.0, 0.0, 0.0);
        Vector3d ambient_shading(0.0, 0.0, 0.0);
        Vector3d total_shading(0.0, 0.0, 0.0);
        
        // Simple diffuse model
        for (auto light = lightSources.begin(); light != lightSources.end(); ++light) {
            bool noShadow = true;
            Vector3d l = light->get_origin() - ray_intersection;
            Vector3d lightDir = l.normalized();
            Ray shadowRay(ray_intersection+lightDir*0.001, lightDir);
            if(enableShadow){
               noShadow = !doesShadowIntersect(objects, shadowRay);
            }
            if(shadingType == Shading::Lambertian || shadingType == Shading::Blinn_Phong || shadingType == Shading::All) {
                double d = l.normalized().transpose() * ray_normal;
                
                // Clamp to zero
                d = max(d,0.);
                
                //Apply light intensity and add to previous light source shading value
                double diff = (light->get_intensity() * d);
                
                // Assuming diffuse coefficient (Kd) to be the same as sphere surface color
                Vector3d shade_color = nearest_object->color == Vector3d(0,0,0) ? light->color : multiplyTwoVectors(nearest_object->color, light->color);
                
                // Multiply with diffuse coefficient Kd
                shade_color = shade_color * nearest_object->material_properties.Kd;
                
                //Add to previous light source shading value
                diffuse_shading = noShadow * (shade_color * diff) + diffuse_shading;
            }
            
            if(shadingType == Shading::Specular || shadingType == Shading::Blinn_Phong || shadingType == Shading::All) {
                Vector3d v = ray.origin - ray_intersection;
                Vector3d h = (v + l).normalized();
                double s = h.transpose() * ray_normal;
                
                // Clamp to zero and The power, or Phong exponent is assumed to be 2
                s = pow(max(s, 0.), 5);
                
                //Apply light intensity
                double spec = (light->get_intensity() * s);
                
                // Assuming specular coefficient (Ks) to be 0.5
                Vector3d shade_color = nearest_object->color == Vector3d(0,0,0) ? light-> color : multiplyTwoVectors(nearest_object->color, light->color);
                
                shade_color = shade_color * nearest_object->material_properties.Ks;
                
                //Add to previous light source shading value
                specular_shading = noShadow * (shade_color * spec) + specular_shading;
            }
        }
        
        if(shadingType == Shading::Ambient || shadingType == Shading::All) {
            // Assuming ambient coefficient (Ka) to be 0.2 and ambient light intensity to be 0.1
            Vector3d ambient_color(1.0, 1.0, 1.0); //Ambient color
            Vector3d Ka = multiplyTwoVectors(nearest_object->color, ambient_color);
            const double ambient_light_intensity = 0.2;
            
            ambient_shading = Ka * ambient_light_intensity;
        }
        
        switch (shadingType) {
            case Shading::Specular:
                total_shading = specular_shading;
                break;
            case Shading::Ambient:
                total_shading = ambient_shading;
                break;
            case Shading::Blinn_Phong:
                total_shading = diffuse_shading + specular_shading;
                break;
            case Shading::All:
                total_shading = diffuse_shading + specular_shading + ambient_shading;
                break;
            case Shading::Lambertian:
            default:
                total_shading = diffuse_shading;
                break;
        }
        
        // Apply total shading to pixel
        r = total_shading(0);
        g = total_shading(1);
        b = total_shading(2);
        
        // Disable the alpha mask for this pixel
        a = 1;
    }
}
