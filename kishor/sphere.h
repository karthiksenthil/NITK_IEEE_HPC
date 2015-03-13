#ifndef SPHERE_H
#define SPHERE_H

#include "defs.h"


bool sphere_intersection (RAY *ray, SPHERE *sphere, SPHERE_INTERSECTION* intersection);
void intersection_normal(SPHERE *sphere, SPHERE_INTERSECTION* intersection, RAY* ray);
void copy_intersection_struct(SPHERE_INTERSECTION* is1, SPHERE_INTERSECTION* is2);


#endif
