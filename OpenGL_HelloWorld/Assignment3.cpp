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
	glClear(GL_COLOR_BUFFER_BIT); // buffer

	glShadeModel(GL_FLAT); // shade



	// code should put in (glBegin ~ glEnd)
	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(-1.0, -0.7, 0.0); // v0
	glVertex3f(-0.6, 0.3, 0.0); // v1
	glColor3f(1.0, 1.0, 0.0); // Yellow
	glVertex3f(0.0, 0.0, 0.0); // v2
	glColor3f(1.0, 0.0, 1.0); //Magenta
	glVertex3f(0.4, 0.5, 0.0); // v3
	glColor3f(0.0, 1.0, 1.0); //Cyan
	glVertex3f(0.7, -1.0, 0.0); // v4
	glColor3f(0.0, 0.0, 1.0); //Blue)
	glVertex3f(1.0, 0.1, 0.0); // v5

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