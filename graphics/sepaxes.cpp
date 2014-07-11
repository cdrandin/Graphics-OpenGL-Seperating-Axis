/*
*	Name:	Matthew Nguyen
*  Email: masayuflame@gmail.com
*	Class:	CPSC 486 Game Programming
*	Asgt:	2 Seperating Axes
*	Due:	December 3rd, 2013
*	
*	Purpose: Seperating axes, this program draws 5 squares on screen and moves them around.
*			 If the objects collide, reflect their movement.
*/

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>

#include "ray3.h"
#include "square.h"
#include "vector.h"
#include "getopt.h"
#include "Windows.h"
/* OpenGL */
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*Globals*/
char *windowName = "Seperating Axes";
int height = 600;
int width = 600;

square polygon[5];

using namespace std;

float movespeedred = 0.005;
float movespeedblue = 0.003;
float movespeedgreen = 0.004;
float movespeedyellow = 0.008;
float movespeedwhite = 0.009;
float xtranslation = 0;
float xtranslation2 = 0;
float ytranslation = 0;
float ytranslation2 = 0;
float ytranslation3 = 0;

bool verbose = false;

void usage( std::string msg )
{
 std::cerr << msg << std::endl;
 std::cerr << "usage: psurfviewer [-v -h]" << std::endl;
 std::cerr << "         or" << std::endl;
 std::cerr << "    psurfviewer [--verbose --help]" << std::endl;
}

int whichSide(square &s, ray3 &r)
{
	int positive = 0, negative = 0;
	for (int i = 0; i < 4; i++)
	{
		double t = r.Direction.dotProduct(s.verticieslist[i] - r.Origin);

		if (t > 0)
		{
			positive ++;
		}
		else if (t < 0)
		{	
			negative ++;
		}

		if(positive && negative) 
		{
			return 0;
		}
	}

	return (positive?+1:-1);
}

// function to test the intersection of 2 squares
bool testIntersection2D(square &a, square &b)
{
	for (int i = 0; i < 4; i++)
	{
		if (whichSide(b, a.edgenormals[i]) > 0)
		{
			return false;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (whichSide(a, b.edgenormals[i]) > 0)
		{
			return false;
		}
	}

	return true;
}

// function to calculate the numbers to make the objects move
void animate(int value)
{	
	// handle animations of the cubes
	// each square has their own movespeed.color
	// 2 squares have x axis movement
	// 3 squares have y axis movement
	xtranslation += movespeedgreen;
	if (xtranslation < -0.95 || xtranslation > 0.95)
		movespeedgreen *= -1;

	xtranslation2 += movespeedblue;
	if (xtranslation2 < -0.95 || xtranslation2 > 0.95)
		movespeedblue *= -1;

	ytranslation += movespeedred;
	if (ytranslation < -0.95 || ytranslation > 0.95)
		movespeedred *= -1;
	
	ytranslation2 += movespeedyellow;
	if(ytranslation2 < -0.95 || ytranslation2 > 0.95)
		movespeedyellow *= -1;

	ytranslation3 += movespeedwhite;
	if(ytranslation3 < -0.95 || ytranslation3 > 0.95)
		movespeedwhite *= -1;

	float size = 0.05;

	// check for collisions
	// polygon 1 Red
	Vec3 verticies1[4];
	verticies1[0] = (Vec3(-0.5-size, ytranslation+size, 0));
	verticies1[1] = (Vec3(-0.5+size, ytranslation+size, 0));
	verticies1[2] = (Vec3(-0.5+size, ytranslation-size, 0));
	verticies1[3] = (Vec3(-0.5-size, ytranslation-size, 0));

	// polygon 2 Green
	Vec3 verticies2[4];
	verticies2[0] = (Vec3(xtranslation-size, 0.5+size, 0));
	verticies2[1] = (Vec3(xtranslation+size, 0.5+size, 0));
	verticies2[2] = (Vec3(xtranslation+size, 0.5-size, 0));
	verticies2[3] = (Vec3(xtranslation-size, 0.5-size, 0));

	// polygon 3 Blue
	Vec3 verticies3[4];
	verticies3[0] = (Vec3(xtranslation2-size, -0.5+size, 0));
	verticies3[1] = (Vec3(xtranslation2+size, -0.5+size, 0));
	verticies3[2] = (Vec3(xtranslation2+size, -0.5-size, 0));
	verticies3[3] = (Vec3(xtranslation2-size, -0.5-size, 0));

	// polygon 4 Yellow
	Vec3 verticies4[4];
	verticies4[0] = (Vec3(0.5-size, ytranslation2+size, 0));
	verticies4[1] = (Vec3(0.5+size, ytranslation2+size, 0));
	verticies4[2] = (Vec3(0.5+size, ytranslation2-size, 0));
	verticies4[3] = (Vec3(0.5-size, ytranslation2-size, 0));

	// polygon 5 White
	Vec3 verticies5[4];
	verticies5[0] = (Vec3(-size, ytranslation3+size, 0));
	verticies5[1] = (Vec3(+size, ytranslation3+size, 0));
	verticies5[2] = (Vec3(+size, ytranslation3-size, 0));
	verticies5[3] = (Vec3(-size, ytranslation3-size, 0));

	// red
	polygon[0] = square(verticies1);

	// green
	polygon[1] = square(verticies2);

	// blue
	polygon[2] = square(verticies3);

	// yellow
	polygon[3] = square(verticies4);

	// white
	polygon[4] = square(verticies5);

	bool collide[6] = {false, false, false, false, false, false};

	collide[0] = testIntersection2D(polygon[0], polygon[1]);
	collide[1] = testIntersection2D(polygon[0], polygon[2]);
	collide[2] = testIntersection2D(polygon[1], polygon[3]);
	collide[3] = testIntersection2D(polygon[3], polygon[2]);
	collide[4] = testIntersection2D(polygon[1], polygon[4]);
	collide[5] = testIntersection2D(polygon[2], polygon[4]);

	// check collision for red and green
	if(collide[0])
	{
		movespeedred *= -1;
		movespeedgreen *= -1;
		cout<<"Red and Green"<<endl;
	}
	// check collision for red and blue
	if(collide[1])
	{
		movespeedred *= -1;
		movespeedblue *= -1;
		if (verbose)
			cout<<"Red and Blue"<<endl;
	}
	// check collision for green and yellow
  if(collide[2])
	{
		movespeedgreen *= -1;
		movespeedyellow *= -1;
		if (verbose)
			cout<<"Green and Yellow"<<endl;
	}
	// check collision for blue and yellow
	if(collide[3])
	{
		movespeedyellow *= -1;
		movespeedblue *= -1;
		if (verbose)
			cout<<"Blue and Yellow"<<endl;
	}
	// check collision for white and green
	if(collide[4])
	{
		movespeedwhite *= -1;
		movespeedgreen *= -1;
		if (verbose)
			cout<<"White and Green"<<endl;
	}
	// check collision for white and blue
	if(collide[5])
	{
		movespeedwhite *= -1;
		movespeedblue *= -1;
		if (verbose)
			cout<<"White and Blue"<<endl;
	}

	glutPostRedisplay();
	glutTimerFunc( 16, animate, 0);

}

// display initialization
void displayInit()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glFrontFace( GL_CCW );
	glLoadIdentity();
}

// function to draw each individual polygon
void drawSquare(square &s)
{
	// drawing representation polygons
	glPushMatrix();
	glBegin(GL_QUADS);
	for(int i = 0; i < 4; i++)
	{
		glVertex2f(s.verticieslist[i][0], s.verticieslist[i][1]);
	}
	glEnd();
	glPopMatrix();
	
}

// Display the scene
void display()
{
	displayInit();
	
	/*
	// Draw edge lines to focal point when using seperating axis
	for(int j=0;j<5;++j)
	{
		for(int i=0;i<(int)polygon->edgenormals.size();++i)
		{
			glBegin(GL_LINES);
			glColor3d(1.0,0.0,0.0);
			glVertex3f(polygon[j].edgenormals.at(i).Origin[0],
					  polygon[j].edgenormals.at(i).Origin[1],
					  polygon[j].edgenormals.at(i).Origin[2]);

			glVertex3f(polygon[j].edgenormals.at(i).Direction[0],
					  polygon[j].edgenormals.at(i).Direction[1],
					  polygon[j].edgenormals.at(i).Direction[2]);
			glEnd();
		}
	}
	*/

	// draw the 5 squares
	for (int i = 0; i < 5; i++)
	{
		// setting the colors of the 5 squares
		// red, green, blue, yellow, white
		if(i == 0)
			glColor3f(1,0,0);
		else if(i == 1)
			glColor3f(0,1,0);
		else if(i == 2)
			glColor3f(0,0,1);
		else if(i == 3)
			glColor3f(1,1,0);
		else
			glColor3f(1,1,1);

		// draw each square
		drawSquare(polygon[i]);
	}

	gluLookAt( 0.0, 0.0, -1.0, 
			   0.0, 0.0, 0.0, 
			   0.0, 1.0, 0.0 );

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

// handles reshape of the window
void reshape( int w, int h )
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -1.0, 1.0, -1.0, 1.0, -10.0, 10.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

// main function
int main(int argc, char*argv[])
{

	int ch;
	struct option longopts[] = 
	{
		{ "verbose", required_argument, NULL, 'v' },
		{ "help", required_argument, NULL, 'h' },
		{ NULL, 0, NULL, 0 }
	};

	// init
	glutInit(&argc, argv);

	while( (ch = getopt_long(argc, argv, "vh", longopts, NULL)) != -1 )
	{
		switch( ch )
		{
		case 'v':
			// Turn on debugging
			verbose = true;
			break;
		case 'h':
			usage( std::string( "Hope this helps..." ) );
			break;
		default:
			/* do nothing */
			fprintf( stderr, "Ignoring unknown option: %c\n", ch );
			break;
		} 
	}
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width,height);
	glutCreateWindow(windowName);

	// handles animation, 60 frames per sec
	glutTimerFunc( 16, animate, 0);

	// handles window reshape
	glutReshapeFunc(reshape);

	// display scene contents
	glutDisplayFunc(display);
	
	glutMainLoop();

	// terminate program
	return 0;
}