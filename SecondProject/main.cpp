//
//  main.cpp
//
//  Created by Yonghao Yue on 2019/09/28.
//  Updated: 2020/09/23
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <unistd.h>
#else
#include <GL/freeglut.h>
#include <Windows.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "Camera.h"

double g_FrameSize_WindowSize_Scale_x = 1.0;
double g_FrameSize_WindowSize_Scale_y = 1.0;

int width = 640;
int height = 480;
int mx, my;

Camera g_Camera;

void idle()
{
#ifdef __APPLE__
  usleep( 1000.0 * 1000.0 / 60.0 ); // in microseconds
#else
  Sleep(1000.0/60.0); // in milliseconds
#endif
  glutPostRedisplay();
}

void projection_and_modelview( const Camera& in_Camera )
{
  const double fovy_deg = ( 2.0 * 180.0 / M_PI ) * atan( 0.024 * 0.5 / in_Camera.getFocalLength() );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fovy_deg, double( width ) / double( height ), 0.01 * in_Camera.getFocalLength(), 1000.0 );
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  
  const Eigen::Vector3d lookAtPoint = in_Camera.getLookAtPoint();
  gluLookAt( in_Camera.getEyePoint().x(), in_Camera.getEyePoint().y(), in_Camera.getEyePoint().z(), lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z(), in_Camera.getYVector().x(), in_Camera.getYVector().y(), in_Camera.getYVector().z() );
}

void mouseDrag(int x, int y)
{
	const int _dx = x - mx;
	mx = x; my = y;

	const double dx = double(_dx) / double(width);
	const double scale = 2.0;

	g_Camera.rotateCameraInLocalFrameFixLookAt(dx * scale);
	glutPostRedisplay();
}

void mouseDown(int x, int y)
{
	mx = x; my = y;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mouseDown(x, y);
}


void drawSquare(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_color)
{
	glBegin(GL_TRIANGLES);

	glColor3f(in_color.x(), in_color.y(), in_color.z());

	const Eigen::Vector3d p_xmym = in_center - in_arm_u - in_arm_v;
	const Eigen::Vector3d p_xpym = in_center + in_arm_u - in_arm_v;
	const Eigen::Vector3d p_xmyp = in_center - in_arm_u + in_arm_v;
	const Eigen::Vector3d p_xpyp = in_center + in_arm_u + in_arm_v;

	glVertex3f(p_xmym.x(), p_xmym.y(), p_xmym.z());
	glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());
	glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());

	glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());
	glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());
	glVertex3f(p_xpyp.x(), p_xpyp.y(), p_xpyp.z());

	glEnd();
}

void drawTriangle(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_color)
{
	glBegin(GL_TRIANGLES);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(in_color.x(), in_color.y(), in_color.z());

	const Eigen::Vector3d p_xmym = in_center - in_arm_u - in_arm_v;
	const Eigen::Vector3d p_xpym = in_center + in_arm_u - in_arm_v;
	const Eigen::Vector3d p_xmyp = in_center - in_arm_u + in_arm_v;

	glVertex3f(p_xmym.x(), p_xmym.y(), p_xmym.z());
	glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());
	glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());


	glEnd();
}



//assignment1 Box
void drawBox(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_arm_w, const Eigen::Vector3d& in_color)
{
	// X-
	drawSquare(in_center - in_arm_u, -in_arm_v, in_arm_w, in_color);
	// X+
	drawSquare(in_center + in_arm_u, in_arm_v, in_arm_w, in_color);
	// Y-
	drawSquare(in_center - in_arm_v, in_arm_u, in_arm_w, in_color);
	// Y+
	drawSquare(in_center + in_arm_v, -in_arm_u, in_arm_w, in_color);
	// Z-
	drawSquare(in_center - in_arm_w, -in_arm_u, in_arm_v, in_color);
	// Z+
	drawSquare(in_center + in_arm_w, in_arm_u, in_arm_v, in_color);
}

//assignment2 Cone

// in_center is center of polygon
// in_arm_v is height
void drawPolygon(const Eigen::Vector3d & in_center, const Eigen::Vector3d & in_arm_v, const Eigen::Vector3d & in_color)
{

	// color 
	glColor3f(in_color.x(), in_color.y(), in_color.z());

	// center = center of polygon
	const Eigen::Vector3d center = in_center;
	/* top vertex = top of cone*/
	const Eigen::Vector3d top_vertex = in_arm_v;

	// for loop
	glBegin(GL_TRIANGLES);
	const Eigen::Vector3d rad = Eigen::Vector3d{ 0.5, 0.5, 0.5 };
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		//radius times x-coordinate
		const Eigen::Vector3d x = rad * cos(angle);
		//radius times z-coordinate
		const Eigen::Vector3d z = rad * sin(angle);

		double tugi = i + 1;
		double next_angle = tugi * angle;
		//radius times x-coordinate
		const Eigen::Vector3d  next_x = rad * cos(next_angle);
		//radius times z-coordinate
		const Eigen::Vector3d next_z = rad * sin(next_angle);


		//triangles.
		//vertex
		glVertex3f(x.x(), center.y(), z.z());
		//next vertex
		glVertex3f(next_x.x(), center.y(), next_z.z());
		//center
		glVertex3f(center.x(), center.y(), center.z());

		//triangles.
		//vertex
		glVertex3f(x.x(), center.y(), z.z());
		//next vertex
		glVertex3f(next_x.x(), center.y(), next_z.z());
		//height
		glVertex3f(center.x(), top_vertex.y(), center.z());

	}
	glEnd();
}

//assignment3
void drawSphere(double r, int hor, int ver, const Eigen::Vector3d& in_color, const Eigen::Vector3d& in_trans) {
	
	// color 
	glColor3f(in_color.x(), in_color.y(), in_color.z());
	glTranslatef(in_trans.x(), in_trans.y(), in_trans.z()); 

	int i, j;
	for (i = 0; i <= hor; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / hor);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / hor);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= ver; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / ver;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);

		}
		glEnd();
	}
}


void drawFloor()
{
	glBegin(GL_TRIANGLES);
	for (int j = -20; j < 20; j++)
	{
		for (int i = -20; i < 20; i++)
		{
			int checker_bw = (i + j) % 2;
			if (checker_bw == 0)
			{
				glColor3f(0.3, 0.3, 0.3);

				glVertex3f(i * 0.5, 0.0, j * 0.5);
				glVertex3f(i * 0.5, 0.0, (j + 1) * 0.5);
				glVertex3f((i+1) * 0.5, 0.0, j * 0.5);

				glVertex3f(i * 0.5, 0.0, (j + 1) * 0.5);
				glVertex3f((i+1) * 0.5, 0.0, (j + 1) * 0.5);
				glVertex3f((i + 1) * 0.5, 0.0, j * 0.5);

			}
		}
	}
	glEnd();
}

void display()
{
  glViewport( 0, 0, width * g_FrameSize_WindowSize_Scale_x, height * g_FrameSize_WindowSize_Scale_y );
  
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  projection_and_modelview( g_Camera );
  
  glEnable( GL_DEPTH_TEST );

  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_BLEND );
  glEnable( GL_POINT_SMOOTH );
  glEnable( GL_LINE_SMOOTH );
  glEnable( GL_POLYGON_SMOOTH);
  glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
  glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
  glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
  
  drawFloor();





  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.8, 0.0);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-0.8, -0.8, 0.0);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f( 0.8, -0.8, 0.0);
  glEnd();

  //assignment1
  //drawerBox({center(x,y,z), x, y, z, color})
  drawBox({ -1.0, 0.3, -0.5 }, { 0.3, 0.0, 0.0 }, { 0.0, 0.3, 0.0 }, { 0.0, 0.0, 0.5 }, { 1.0, 0.3, 0.5 });
  
  //assignment2
  // drawPolygon(center, height, color)
  drawPolygon({ 0.0, 0.0, 0.0 }, { 0.0, 0.5, 0.0 }, { 0.5, 0.2, 0.5 });
  
  
  //drawSphere(radius, horizontal, vertical, color, translate)
  //assignment3
  drawSphere(0.5, 7, 7, { 0.1, 0.8, 0.1 }, { 1.0, 0.3, 1.0 }); 
  //assignment4
  drawSphere(0.5, 20, 20, { 0.6, 0.2, 0.1 }, {-2.0, 0.0, -0.2});

  
  glutSwapBuffers();
}

void resize( int w, int h )
{
  width = w;
  height = h;
}

int main( int argc, char* argv[] )
{
  g_Camera.setEyePoint( Eigen::Vector3d{ 0.0, 1.0, 3.0 } );
  g_Camera.lookAt( Eigen::Vector3d{ 0.0, 0.0, 0.0 }, Eigen::Vector3d{ 0.0, 1.0, 0.0} );
  
  glutInit( &argc, argv );
  glutInitWindowSize( width, height );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE );
  
  glutCreateWindow( "Hello world!!" );
  
  // With retina display, frame buffer size is twice the window size.
  // Viewport size should be set on the basis of the frame buffer size, rather than the window size.
  // g_FrameSize_WindowSize_Scale_x and g_FrameSize_WindowSize_Scale_y account for this factor.
  GLint dims[4] = {0};
  glGetIntegerv(GL_VIEWPORT, dims);
  g_FrameSize_WindowSize_Scale_x = double( dims[2] ) / double( width );
  g_FrameSize_WindowSize_Scale_y = double( dims[3] ) / double( height );
  
  glutDisplayFunc( display );
  glutIdleFunc( idle );
  glutReshapeFunc( resize );
  glutMouseFunc(mouse);
  glutMotionFunc(mouseDrag);

  glutMainLoop();
  return 0;
}
