#include <GL/freeglut.h>
#include <math.h>

int width = 640;
int height = 640;



void display()
{
	glViewport(0, 0, width, height);

	glClearColor(0.5, 0.5, 0.5, 0.0); //select color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // put selected color in background

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // setting for matrix 

	//void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near(front), GLdouble far(back))
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 100.0); // (x,y,z)  x-coordinate, y-coordinate, z-coordinate

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  // setting for matrix 



	double rad = 1;
	// code should put in (glBegin ~ glEnd)
	glBegin(GL_TRIANGLES); // glBegin(mode)  it has a lots of mode
	for (int i = 0; i < 360; i++)
	{

		if (i < 90) {

			double angle = i * 3.141592 / 180; // pi/180 = 1 degree

			double r = cos(angle);
			double g = sin(angle);
			double x = rad * cos(angle);
			double y = rad * sin(angle);

			double z = i + 1;
			double nextangle = z * 3.141592 / 180; // pi/180 = 1 degree
			double i = rad * cos(nextangle);
			double j = rad * sin(nextangle);

			glColor3f(r, g, 0.0);
			glVertex2f(0, 0);
			glColor3f(r, g, 0.0);
			glVertex2f(x, y);
			glColor3f(r, g, 0.0);
			glVertex2f(i, j);

		}

		else if (i >= 90 && i < 180) {

			double angle = i * 3.141592 / 180; // pi/180 = 1 degree

			double g = sin(angle);
			double b = fabs(cos(angle));
			double x = rad * cos(angle);
			double y = rad * sin(angle);

			double z = i + 1;
			double nextangle = z * 3.141592 / 180; // pi/180 = 1 degree
			double i = rad * cos(nextangle);
			double j = rad * sin(nextangle);

			glColor3f(0, g, b);
			glVertex2f(0, 0);
			glColor3f(0, g, b);
			glVertex2f(x, y);
			glColor3f(0, g, b);
			glVertex2f(i, j);

		}

		else if (i >= 180 && i < 270) {

			double angle = i * 3.141592 / 180; // pi/180 = 1 degree

			double g = fabs(sin(angle));
			double b = fabs(cos(angle));
			double x = rad * cos(angle);
			double y = rad * sin(angle);

			double z = i + 1;
			double nextangle = z * 3.141592 / 180; // pi/180 = 1 degree
			double i = rad * cos(nextangle);
			double j = rad * sin(nextangle);

			glColor3f(0, g, b);
			glVertex2f(0, 0);
			glColor3f(0, g, b);
			glVertex2f(x, y);
			glColor3f(0, g, b);
			glVertex2f(i, j);

		}
		else if (i >= 270 && i < 360) {

			double angle = i * 3.141592 / 180; // pi/180 = 1 degree

			double r = cos(angle);
			double g = fabs(sin(angle));
			double x = rad * cos(angle);
			double y = rad * sin(angle);

			double z = i + 1;
			double nextangle = z * 3.141592 / 180; // pi/180 = 1 degree
			double i = rad * cos(nextangle);
			double j = rad * sin(nextangle);

			glColor3f(r, g, 0);
			glVertex2f(0, 0);
			glColor3f(r, g, 0);
			glVertex2f(x, y);
			glColor3f(r, g, 0);
			glVertex2f(i, j);
		}

	}
	glEnd();


	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // glut initialization
	glutInitWindowSize(width, height);  // size for this program
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //decide what kind of mode

	glutCreateWindow("Hello world");//name of program
	glutDisplayFunc(display);		//execute function(display)
	glutMainLoop();					//(infinite loop)
	return 0;
}