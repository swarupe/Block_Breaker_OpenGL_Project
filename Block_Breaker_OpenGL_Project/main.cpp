#define _USE_MATH_DEFINES
#include <cmath>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include<iostream>
#include"stdafx.h"
#include<stdlib.h>
#include<time.h>
using namespace std;


bool check_collision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) //Function for checking collision
{
	if (Ay + Ah < By) return false; //if A is more to the lft than B
	else if (Ay > By + Bh) return false; //if A is more to rgt than B
	else if (Ax + Aw < Bx) return false; //if A is higher than B
	else if (Ax > Bx + Bw) return false; //if A is lower than B

	return true; //There is a collision because none of above returned false
}

void initialize()	//To set the initial co-ordinates of the objects on the screen
{
	if (level2_flag == false) {
		for (int n = 0, x = 23, y = 450; n < 14; n++, x += 65)
		{
			if (x > 453)
			{
				x = 23;
				y -= 25;
			}
			b[n].x = x;
			b[n].y = y;
			b[n].w = 60;
			b[n].h = 20;
			b[n].alive = true;
		}
		color1[0] = 0.419608;
		color1[1] = 0.137255;
		color1[2] = 0.556863;
		color2[0] = 0.196078;
		color2[1] = 0.8;
		color2[2] = 0.6;


		ball.ballx = 300;
		ball.bally = 50;
		ball.radius = 15;
		ball.velx = 0.50;
		ball.vely = 0.50;
	}
	else
	{
		for (int n = 0; n < 14; n++)
			b[n].alive = false;
		for (int n = 0; n < 21; n++)
			a[n].alive = true;
		for (int n = 0, x = 23, y = 450; n < 21; n++, x += 65)
		{
			if (x > 453)
			{
				x = 23;
				y -= 25;
			}
			a[n].x = x;
			a[n].y = y;
			a[n].w = 60;
			a[n].h = 20;
			a[n].alive = true;
		}
		color1[0] = 0.0;
		color1[1] = 0.0;
		color1[2] = 1.0;
		color2[0] = 0.0;
		color2[1] = 0.0;
		color2[2] = 0.0;

		ball.ballx = 300;
		ball.bally = 50;
		ball.radius = 15;
		ball.velx = 0.70;
		ball.vely = 0.70;
	}
	paddle.myx = 300;
	paddle.myy = 0;
	paddle.width = 80;
	paddle.height = 20;
	paddle.lft = false;
	paddle.rgt = false;

	ball.color[0] = 1.8;
	ball.color[1] = 0.0;
	ball.color[2] = 0.196078;

	paddle.color[0] = 0.0;
	paddle.color[1] = 1.0;
	paddle.color[2] = 0.0;
}

void reshape()		//Modify the co-ordinates according to the key-presses and collisions etc...
{
	if (paddle.myx<0)
		paddle.myx = 0;
	if (paddle.myx + paddle.width>500)
		paddle.myx = 420;
	if (paddle.lft == true)
		paddle.myx = paddle.myx - 0.2;
	if (paddle.rgt == true)
		paddle.myx = paddle.myx + 0.2;

	ball.ballx += 0.2*ball.velx;
	ball.bally += 0.2*ball.vely;

	for (int n = 0; n<45; n++)
	{
		if (b[n].alive == true)
		{
			if (check_collision(ball.ballx, ball.bally, ball.radius, ball.radius, b[n].x, b[n].y, b[n].w, b[n].h) == true)
			{
				ball.vely = -ball.vely;
				b[n].alive = false;
				ball.down = true;
				ball.up = false;
				hitCount++;
				lastCurrentTime = currentTime;
				currentTime = clock();
				float deltaT = difftime(currentTime, lastCurrentTime) / 1000.0;
				float deltaTSqDiv2 = (deltaT * deltaT) * 0.5;
				break;
			}
		}
	}

	if (ball.ballx<10)
	{
		ball.velx = -ball.velx;
		ball.right = true;
		ball.left = false;
	}
	if (ball.ballx + ball.radius>500)
	{
		ball.right = false;
		ball.left = true;
		ball.velx = -ball.velx;
	}
	if (ball.bally + ball.radius>500)
		ball.vely = -ball.vely;
	else if (ball.bally<0)
		exit(0);

	if (check_collision(ball.ballx, ball.bally - 13, ball.radius, ball.radius, paddle.myx, paddle.myy, paddle.width, paddle.height) == true)
	{
		ball.vely = -ball.vely;
		ball.up = true;
		ball.down = false;
	}
	if (hitCount == 14) {
		level2_flag = true;
		initialize();
		myinit();
		glutDisplayFunc(display_level2);
	}
	draw();
}

void level2_reshape() {
	if (paddle.myx<0)
		paddle.myx = 0;
	if (paddle.myx + paddle.width>500)
		paddle.myx = 420;
	if (paddle.lft == true)
		paddle.myx = paddle.myx - 0.2;
	if (paddle.rgt == true)
		paddle.myx = paddle.myx + 0.2;

	ball.ballx += 0.2*ball.velx;
	ball.bally += 0.2*ball.vely;

	for (int n = 0; n<45; n++)
	{
		if (a[n].alive == true)
		{
			if (check_collision(ball.ballx, ball.bally, ball.radius, ball.radius, a[n].x, a[n].y, a[n].w, a[n].h) == true)
			{
				ball.vely = -ball.vely;
				a[n].alive = false;
				ball.down = true;
				ball.up = false;
				hitCount++;
				lastCurrentTime = currentTime;
				currentTime = clock();
				float deltaT = difftime(currentTime, lastCurrentTime) / 1000.0;
				float deltaTSqDiv2 = (deltaT * deltaT) * 0.5;
				break;
			}
		}
	}
	if (ball.ballx<10)
	{
		ball.velx = -ball.velx;
		ball.right = true;
		ball.left = false;
	}
	if (ball.ballx + ball.radius>500)
	{
		ball.right = false;
		ball.left = true;
		ball.velx = -ball.velx;
	}
	if (ball.bally + ball.radius>500)
		ball.vely = -ball.vely;
	else if (ball.bally<0)
		exit(0);

	if (check_collision(ball.ballx, ball.bally - 13, ball.radius, ball.radius, paddle.myx, paddle.myy, paddle.width, paddle.height) == true)
	{
		ball.vely = -ball.vely;
		ball.up = true;
		ball.down = false;
	}
	draw();
}


void specialUp(int key, int x, int y)
{
	switch (key)
	{
	case (GLUT_KEY_LEFT): paddle.lft = false; break;
	case (GLUT_KEY_RIGHT): paddle.rgt = false; break;
	}
}

void specialDown(int key, int x, int y)
{
	switch (key)
	{
	case (GLUT_KEY_LEFT): paddle.lft = true; break;
	case (GLUT_KEY_RIGHT): paddle.rgt = true; break;
	}
}

void myinit()
{
	glViewport(0, 0, 500, 500);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void draw()		//Render the objects on the screen using the latest updated co-ordinates 
{
	if (level2_flag == false) {
		for (int i = 0; i < 45; i++)
		{
			if (b[i].alive == true)
			{
				if (i % 2 == 0) glColor3fv(color1);
				else glColor3fv(color2);
				glBegin(GL_POLYGON);
				glVertex2f(b[i].x, b[i].y);
				glVertex2f(b[i].x + b[i].w, b[i].y);
				glVertex2f(b[i].x + b[i].w, b[i].y + b[i].h);
				glVertex2f(b[i].x, b[i].y + b[i].h);
				glEnd();
			}
		}
		string level1 = "LEVEL 1 ";
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(0.0 + 10.0, 0.0 + 480.0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char *)level1.c_str());
	}

	else if (level2_flag == true)
	{
		for (int i = 0; i < 45; i++)
		{
			if (a[i].alive == true)
			{
				if (i % 2 == 0) glColor3fv(color1);
				else glColor3fv(color2);
				glBegin(GL_POLYGON);
				glVertex2f(a[i].x, a[i].y);
				glVertex2f(a[i].x + a[i].w, a[i].y);
				glVertex2f(a[i].x + a[i].w, a[i].y + a[i].h);
				glVertex2f(a[i].x, a[i].y + a[i].h);
				glEnd();
			}
		}
		string level2 = "LEVEL 2 ";
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(0.0 + 10.0, 0.0 + 480.0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char *)level2.c_str());
	}

	glColor3fv(paddle.color);
	glBegin(GL_POLYGON);
	glVertex2f(paddle.myx, paddle.myy);
	glVertex2f(paddle.myx + paddle.width, paddle.myy);
	glVertex2f(paddle.myx + paddle.width, paddle.myy + paddle.height);
	glVertex2f(paddle.myx, paddle.myy + paddle.height);
	glEnd();

	//# of triangles used to draw circle

	glColor3fv(ball.color);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(ball.ballx, ball.bally); // center of circle
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			ball.ballx + (ball.radius * cos(i *  twicePi / triangleAmount)),
			ball.bally + (ball.radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();

	//to display score
	string playerScore = "SCORE: ";
	char buffer[33];
	_itoa_s(hitCount, buffer, 10);
	playerScore += buffer;

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(0.0 + 380.0, 0.0 + 480.0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char *)playerScore.c_str());

	glutPostRedisplay();
	glutSwapBuffers();

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glDisable(GL_DEPTH_TEST);
	draw();
	glFlush();
	reshape();
}

void display_level2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glDisable(GL_DEPTH_TEST);
	draw();
	glFlush();
	level2_reshape();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) 		//27 corresponds to the esc key
	{
		temp_velx = ball.velx;
		temp_vely = ball.vely;
		balltemp_l = ball.left;
		balltemp_r = ball.right;
		balltemp_u = ball.up;
		balltemp_d = ball.down;

		ball.velx = 0;
		ball.vely = 0;	//To stop the ball from moving
		glutCreateMenu(main_menu);
		glutAddMenuEntry("Continue", CONTINUE);
		glutAddMenuEntry("Quit Game", QUIT);

		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
}

void main_menu(int opt)
{
	switch (opt)
	{
	case CONTINUE:
		revert();
		break;
	case QUIT: exit(0);
	}
}

void revert()
{
	ball.velx = temp_velx;
	ball.vely = temp_vely;

	ball.left = balltemp_l;
	ball.right = balltemp_r;
	ball.up = balltemp_u;
	ball.down = balltemp_d;
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Block Breaker");
	initialize();
	myinit();
	glutDisplayFunc(display);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	glutKeyboardFunc(keyboard);
	reshape();
	glutMainLoop();
	return 0;
}

