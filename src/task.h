//
//  task.h
//  Assignment1
//
//  Created by Venkata Chakradhar Reddy Challa on 9/19/18.
//

#ifndef task_h
#define task_h

#include <stdio.h>
#include <iostream>
#include <list>

#include "light.h"
#include "sphere.h"
#include "common.h"
#include "shading.h"
#include "projection.h"
#include "mesh.h"

using namespace std;

class Task {
public:
    static void task1(void);
    static void task2(void);
    static void task3(void);
    static void task4(void);
    static void task5(void);
    
private:
    static void randomSpheresAndLights(Projection projectionType, string filename);
    static void multipleSpheresAndLights(Projection projectionType, string filename);
};

#endif /* task_h */
