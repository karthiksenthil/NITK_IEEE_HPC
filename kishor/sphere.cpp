#include "sphere.h"
#include "math.h"
#include "vectors.h"


bool sphere_intersection (RAY *ray, SPHERE *sphere, SPHERE_INTERSECTION* intersection) {

    double discriminant;
    double A, B, C;
    double lambda1, lambda2;
    VECTOR3D temp;
    
    A = dotproduct(&ray->direction, &ray->direction);
    
    vec_sub(&temp, &ray->origin, &sphere->center);
    B = 2 * dotproduct(&temp, &ray->direction);
    
    vec_sub(&temp, &ray->origin, &sphere->center);
    C = dotproduct(&temp, &temp) - (sphere->radius * sphere->radius);
    
    discriminant = B*B - 4*A*C;
    
    if (discriminant >= 0) {
        lambda1 = (-B + sqrt(discriminant)) / (2*A);
        lambda2 = (-B - sqrt(discriminant)) / (2*A);
        
        // is the object visible from the eye (lambda1,2>0)
        if (lambda1>=0 && lambda2>=0) {
            if (lambda1 == lambda2) {
                intersection->lambda_in = intersection->lambda_out = lambda1;
            }
            else if (lambda1 < lambda2) {
                intersection->lambda_in  = lambda1;
                intersection->lambda_out = lambda2;
            }
            else {
                intersection->lambda_in  = lambda2;
                intersection->lambda_out = lambda1;
            }
            intersection->valid = true;
            return true;
        }
        else {
            intersection->valid = false;
            return false;
        }
    }
    else {
        intersection->valid = false;
        return false;
    }

}


// Calculate normal vector in the point of intersection:
void intersection_normal(SPHERE *sphere, SPHERE_INTERSECTION* intersection, RAY* ray) {
    
    double lambda, scale;
    VECTOR3D v1, v2, point, normal;
    
    lambda = intersection->lambda_in;
    
    vec_scale(lambda, &v1, &ray->direction);
    vec_add(&point, &v1, &ray->origin);
    
    intersection->point.x = point.x;
    intersection->point.y = point.y;
    intersection->point.z = point.z;
    
    vec_sub(&v2, &point, &sphere->center);
    
    scale = 1.0 / sphere->radius;
    vec_scale(scale, &normal, &v2);
    
    normalize_vector(&normal);

    intersection->normal.x = normal.x;
    intersection->normal.y = normal.y;
    intersection->normal.z = normal.z;
    
}

void copy_intersection_struct(SPHERE_INTERSECTION* is1, SPHERE_INTERSECTION* is2) {
    is1->lambda_in = is2->lambda_in;
    is1->lambda_out = is2->lambda_out;
    
    is1->normal.x = is2->normal.x;
    is1->normal.y = is2->normal.y;
    is1->normal.z = is2->normal.z;
    
    is1->point.x = is2->point.x;
    is1->point.y = is2->point.y;
    is1->point.z = is2->point.z;
    
    is1->valid = is2->valid;

}
