#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include "defs.h"
#include "vectors.h"
#include "sphere.h"
#include "shading.h"
#include "ray.h"

#define NSPHERES 3
#define FOCALDIST 1500
#define RADIUS 150

int wd;                   /* GLUT window handle */
int VIEWPLANE;
int WINDOW;


BASIS camera_frame;
VECTOR3D view_point;
VECTOR3D light;
SPHERE sphere[NSPHERES];
VIEWPORT viewport;
DIRECTION direction[NSPHERES];

double focalDist;
double color;
double lightIntensity, ambLightIntensity;

/* init function */
void init()
{
    viewport.xvmin = -VIEWPLANE;
    viewport.yvmin = -VIEWPLANE;
    viewport.xvmax = VIEWPLANE;
    viewport.yvmax = VIEWPLANE;
    
    camera_frame.u.x = 1.0;
    camera_frame.u.y = 0.0;
    camera_frame.u.z = 0.0;
    
    camera_frame.v.x = 0.0;
    camera_frame.v.y = 1.0;
    camera_frame.v.z = 0.0;
    
    camera_frame.n.x = 0.0;
    camera_frame.n.y = 0.0;
    camera_frame.n.z = 1.0;
    
    view_point.x = (viewport.xvmax - viewport.xvmin) / 2.0 ;
    view_point.y = (viewport.yvmax - viewport.yvmin) / 2.0 ;
    view_point.z = 0.0;
    
    
    light.x = view_point.x - 1300;
    light.y = view_point.y + 1300 ;
    light.z = view_point.z - 300;
    
    
    ambLightIntensity = 1.0;
    lightIntensity = 1.0;
    
    focalDist = FOCALDIST;
    
    // first sphere
    sphere[0].radius = RADIUS/1.5;
    sphere[0].center.x  = view_point.x - (RADIUS+30);
    sphere[0].center.y  = view_point.y ;
    sphere[0].center.z  = view_point.z - focalDist - (2*RADIUS+20);
    
    set_rgb_array(sphere[0].kd_rgb, 0.0, 0.0, 0.8);
    set_rgb_array(sphere[0].ks_rgb, 1.0, 1.0, 1.0);
    set_rgb_array(sphere[0].ka_rgb, 0.0, 0.0, 0.2);
    sphere[0].shininess = 100.0;
    sphere[0].mirror = false;


    // second sphere
    sphere[1].radius = RADIUS/1.2;
    sphere[1].center.x  = view_point.x + 0;
    sphere[1].center.y  = view_point.y + 50;
    sphere[1].center.z  = view_point.z - focalDist - (3*RADIUS+20);

    set_rgb_array(sphere[1].kd_rgb, 0.0, 0.5, 0.0);
    set_rgb_array(sphere[1].ks_rgb, 1.0, 1.0, 1.0);
    set_rgb_array(sphere[1].ka_rgb, 0.0, 0.2, 0.0);
    sphere[1].shininess = 10.0;
    sphere[1].mirror = false;
    
    
    //third sphere
    sphere[2].radius = RADIUS;
    sphere[2].center.x  = view_point.x + (2*RADIUS+30);
    sphere[2].center.y  = view_point.y + 100;
    sphere[2].center.z  = view_point.z - focalDist - (4*RADIUS+20);

    set_rgb_array(sphere[2].kd_rgb, 1.0, 0.0, 0.0);
    set_rgb_array(sphere[2].ks_rgb, 1.0, 1.0, 1.0);
    set_rgb_array(sphere[2].ka_rgb, 0.2, 0.0, 0.0);
    sphere[2].shininess = 100.0;
    sphere[2].mirror = false;
   
   // set clearing (background) color to white:
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // specify that ortgogonal 2D projection is to be used to 
    // map context of 2D world coordinats to the screen. We use the 
    // world-coordinate rectangle of the same aspect ratio as the display window
    // so ther is no distortion:
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WINDOW, 0.0, WINDOW);
}
/* Draw the window - this is where all the GL actions are */
void
display(void)
{
  /* clear the screen to white */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  /* clear pixels */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Ray Tracing! */
  for (int i=0; i<(viewport.xvmax - viewport.xvmin); i++)
    {
        for (int j=0; j<(viewport.yvmax - viewport.yvmin); j++)
        {
            int intersection_object = -1; // none
            int reflected_intersection_object = -1; // none
            double current_lambda = 0x7fefffffffffffff; // maximum positive double
            double current_reflected_lambda = 0x7fefffffffffffff; // maximum positive double

            RAY ray, shadow_ray, reflected_ray;
            PIXEL pixel;
            SPHERE_INTERSECTION intersection, current_intersection, shadow_ray_intersection, reflected_ray_intersection, current_reflected_intersection;

            double red, green, blue;
            double theta, reflected_theta;

            bool bShadow = false;

            pixel.i = i;
            pixel.j = j;
            
            // compute ray:
            compute_ray(&ray, &view_point, &viewport, &pixel, &camera_frame, focalDist);
            
            // check if ray hits an object:
            for (int k=0; k<NSPHERES; k++)
            {
                if (sphere_intersection(&ray, &sphere[k], &intersection))
                {
                    // intersection between ray and object
                    intersection_normal(&sphere[k], &intersection, &ray);

                    if (intersection.lambda_in<current_lambda)
                    {
                        current_lambda=intersection.lambda_in;
                        intersection_object=k;
                        copy_intersection_struct(&current_intersection, &intersection);
                    }
                }
            }
            
            // Calculate pixel color:
            if (intersection_object > -1)
            {
                compute_shadow_ray(&shadow_ray, &intersection, &light);
                theta = dotproduct(&(shadow_ray.direction), &(intersection.normal));
                for (int l=0; l<NSPHERES; l++)
                {
                    if (l!=intersection_object)
                    {
                        if (sphere_intersection(&shadow_ray, &sphere[l], &shadow_ray_intersection) && (theta>0.0))
                            bShadow=true;
                    }
                }
                if (bShadow)
                {   // if in shadow, add only ambient light to the surface color
                    red = shadow(sphere[intersection_object].ka_rgb[CRED], ambLightIntensity);
                    green = shadow(sphere[intersection_object].ka_rgb[CGREEN], ambLightIntensity);
                    blue = shadow(sphere[intersection_object].ka_rgb[CBLUE], ambLightIntensity);
                }
                else
                {
                    // intersection not in shadow:
                    red = blinnphong_shading(&current_intersection, &light, &view_point,
                        sphere[intersection_object].kd_rgb[CRED], sphere[intersection_object].ks_rgb[CRED], sphere[intersection_object].ka_rgb[CRED], sphere[intersection_object].shininess,
                        lightIntensity, ambLightIntensity);
                    green = blinnphong_shading(&current_intersection, &light, &view_point,
                        sphere[intersection_object].kd_rgb[CGREEN], sphere[intersection_object].ks_rgb[CGREEN], sphere[intersection_object].ka_rgb[CGREEN], sphere[intersection_object].shininess,
                        lightIntensity, ambLightIntensity);
                    blue = blinnphong_shading(&current_intersection, &light, &view_point,
                        sphere[intersection_object].kd_rgb[CBLUE], sphere[intersection_object].ks_rgb[CBLUE], sphere[intersection_object].ka_rgb[CBLUE], sphere[intersection_object].shininess,
                        lightIntensity, ambLightIntensity);
                }
                glColor3f(red, green, blue);
                glBegin(GL_POINTS);
                glVertex2i(i, j);
                glEnd();
                intersection_object = -1;
                bShadow = false;
            }

            else
            {
                // draw the pixel with the background color 
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2i(i, j);
                glEnd();
                intersection_object = -1;
                bShadow = false;
            }
            current_lambda = 0x7fefffffffffffff;
            current_reflected_lambda = 0x7fefffffffffffff;
        }
    }

  glFlush();
  glutSwapBuffers();
}

/* Called when window is resized,
   also when window is first created,
   before the first call to display(). */
void
reshape(int w, int h)
{
  /* tell OpenGL to use the whole window for drawing */
  glViewport(0, 0, WINDOW, WINDOW);

  /* do an orthographic parallel projection with the coordinate
     system set to first quadrant, limited by screen/window size */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, WINDOW, 0.0, WINDOW);
}

int
main(int argc, char *argv[])
{
  VIEWPLANE = atoi(argv[1]);
  WINDOW = 2 * VIEWPLANE;
  /* perform initialization NOT OpenGL/GLUT dependent,
     as we haven't created a GLUT window yet */
  struct timeval tim;
  gettimeofday(&tim, NULL);
  double t1 = tim.tv_sec + (tim.tv_usec/1000000.0);
  init();

  /* initialize GLUT, let it extract command-line 
     GLUT options that you may provide 
     - NOTE THE '&' BEFORE argc */
  glutInit(&argc, argv);

  /* specify the display to be single 
     buffered and color as RGB values */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  /* set the initial window size */
  glutInitWindowSize(WINDOW, WINDOW);

  /* create the window and store the handle to it */
  wd = glutCreateWindow("Ray Tracer" /* title */ );

  /* --- register callbacks with GLUT --- */

  /* register function to handle window resizes */
  glutReshapeFunc(reshape);

  /* register function that draws in the window */
  glutDisplayFunc(display);
  glutDestroyWindow(wd);
  gettimeofday(&tim,NULL);
  double t2 = tim.tv_sec + (tim.tv_usec/1000000.0);
  
  printf("%.6lf\n", t2-t1); 
  
  /* start the GLUT main loop */
  glutMainLoop();

  return 0;
}
