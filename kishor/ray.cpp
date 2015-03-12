#include "ray.h"
#include "vectors.h"


void compute_ray(RAY* ray, VECTOR3D* view_point, VIEWPORT* viewport, PIXEL* pixel, BASIS* camera_frame, double dist)
{
    float u, v;
    VECTOR3D v1, v2, v3, v4, dir;

    u = (double)(viewport->xvmin) + (double)(pixel->i) + 0.5 ;  
    v = (double)(viewport->yvmin) + (double)(pixel->j) + 0.5 ;  
    
    vec_scale(-dist, &v1, &camera_frame->n);
    vec_scale(u, &v2, &camera_frame->u);
    vec_scale(v, &v3, &camera_frame->v);
    
    ray->origin.x = view_point->x;  
    ray->origin.y = view_point->y;
    ray->origin.z = view_point->z;
    
    vec_add(&v4, &v1, &v2);
    vec_add(&dir, &v4, &v3);
    normalize_vector(&dir);
    
    ray->direction.x = dir.x;
    ray->direction.y = dir.y;
    ray->direction.z = dir.z;
}


void compute_reflected_ray(RAY* reflected_ray, RAY* incidence_ray, SPHERE_INTERSECTION* intersection)
{
    
    double dp1;
    VECTOR3D scaled_normal, reflected_direction;
    
    // calculate dot-product between surface normal and the direction of the incidence ray:
    dp1 = dotproduct(&intersection->normal, &incidence_ray->direction);
    // scale surface normal by 2*dp1:
    dp1 = 2*dp1;
    vec_scale(dp1, &scaled_normal, &intersection->normal);
    
    vec_sub(&reflected_direction, &incidence_ray->direction, &scaled_normal);
    
    reflected_ray->origin.x = intersection->point.x;  
    reflected_ray->origin.y = intersection->point.y;
    reflected_ray->origin.z = intersection->point.z;
    
    reflected_ray->direction.x = reflected_direction.x;
    reflected_ray->direction.y = reflected_direction.y;
    reflected_ray->direction.z = reflected_direction.z;
}


void compute_shadow_ray(RAY* ray, SPHERE_INTERSECTION* intersection, VECTOR3D* light) {

    VECTOR3D dir;
    
    // intersection point is the origin of shadow ray
    ray->origin.x = intersection->point.x;
    ray->origin.y = intersection->point.y;
    ray->origin.z = intersection->point.z;
    
    // ray direction is from the intersection point towards the light:
    vec_sub(&dir, light, &intersection->point);
    normalize_vector(&dir);
    
    ray->direction.x = dir.x;
    ray->direction.y = dir.y;
    ray->direction.z = dir.z;
}
