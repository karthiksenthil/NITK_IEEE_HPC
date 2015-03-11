#include "shading.h"
#include "vectors.h"
#include "math.h"


double lambertian_shading(SPHERE_INTERSECTION *intersection, VECTOR3D* light, double kd, double ka, double intensity, double amb_intensity) {
    
    double color;
    
    VECTOR3D l;
    
    // compute vector l 
    vec_sub(&l, light, &intersection->point);
    normalize_vector(&l);
    
    // compute the intensity:
    color = kd * intensity * dotproduct(&l, &intersection->normal) + ka * amb_intensity;
    
    if (color > 0.0) {
        return color;
    }
    else {
        return 0.0;
    }
}


double blinnphong_shading(SPHERE_INTERSECTION *intersection, VECTOR3D* light, VECTOR3D* viewpoint, double kd, double ks, double ka, double p, double intensity, double amb_intensity) {
    
    double color_diffuse = 0.0; 
    double color_specular = 0.0;
    
    VECTOR3D l;
    VECTOR3D h;
    VECTOR3D v;
    
    
    // compute vector v :
    vec_sub(&v, viewpoint, &intersection->point);
    normalize_vector(&v);
    
    // compute vector l :
    vec_sub(&l, light, &intersection->point);
    normalize_vector(&l);
    
    // compute vector h:
    vec_add(&h, &v, &l);
    normalize_vector(&h);
    
    
    // compute the diffuse intensity:
    color_diffuse = kd * intensity * dotproduct(&l, &intersection->normal) ;
    if (color_diffuse < 0.0) color_diffuse = 0.0;
    
    // compute the specular intensity:
    color_specular = ks * intensity * pow (dotproduct(&h, &intersection->normal), p);
    if (color_specular < 0.0) color_specular = 0.0;
    
    return (color_diffuse + color_specular + (ka * amb_intensity)); 
}
 

double shadow(double ka, double amb_intensity) {
    
    return (ka * amb_intensity);    
}


void set_rgb_array(double* rgb_array, double cred, double cgreen, double cblue) {
    rgb_array[CRED] = cred;
    rgb_array[CGREEN] = cgreen;
    rgb_array[CBLUE] = cblue;
}
