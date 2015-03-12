#ifndef DEFS_H
#define DEFS_H

#define _BLINNPHONG

typedef enum {down=0, up=1} DIRECTION;

#define CRED 0
#define CGREEN 1
#define CBLUE 2


struct VECTOR3D
{
    double x;
    double y;
    double z;
} ;

struct VIEWPORT
{
    int xvmin;
    int yvmin;
    int xvmax;
    int yvmax;
};

struct PIXEL
{
    int i;
    int j;
};


struct SPHERE_INTERSECTION
{
    double lambda_in;
    double lambda_out;
    VECTOR3D normal;
    VECTOR3D point;
    bool valid;
};

struct SPHERE
{
    VECTOR3D center;
    double radius;
    double kd_rgb[3];
    double ks_rgb[3];
    double ka_rgb[3];
    double shininess;
    bool mirror;
};

struct RAY
{
    VECTOR3D origin;
    VECTOR3D direction;
};

struct BASIS
{
    VECTOR3D u;
    VECTOR3D v;
    VECTOR3D n;
};

#endif