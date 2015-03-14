#ifndef RAY_H
#define RAY_H

#include "defs.h"

void compute_ray(RAY* ray, VECTOR3D* view_point, VIEWPORT* viewport, PIXEL* pixel, BASIS* camera_frame, double dist);
void compute_shadow_ray(RAY* ray, SPHERE_INTERSECTION* intersection, VECTOR3D* light);
void compute_reflected_ray(RAY* reflected_ray, RAY* incidence_ray, SPHERE_INTERSECTION* intersection);


#endif
