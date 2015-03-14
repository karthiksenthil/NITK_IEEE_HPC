#ifndef SHADING_H
#define SHADING_H

#include "defs.h"

double lambertian_shading(SPHERE_INTERSECTION *intersection, VECTOR3D* light, double kd, double ka, double intensity, double amb_intensity);
double blinnphong_shading(SPHERE_INTERSECTION *intersection, VECTOR3D* light, VECTOR3D* viewpoint, double kd, double ks, double ka, double p, double intensity, double amb_intensity);
double shadow(double ka, double amb_intensity) ;
void set_rgb_array(double* rgb_array, double cred, double cgreen, double cblue);

#endif
