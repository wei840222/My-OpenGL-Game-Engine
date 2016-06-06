#include <iostream>  
#include <GL/glut.h>  
#include "header.h"  

using namespace std;

//視窗設定
const int windowSizeW = 600, windowSizeH = 600;
const char windowName[] = "My OpenGL Game Engine";

//滑鼠拖曳畫面旋轉
int mouseClick_x = 0, mouseClick_y = 0, mouseMotion_x = 0, mouseMotion_y = 0;

//動畫控制(毫秒)
bool animationPlay = true;
int animationDelay = 5;
float t = 0;

//繪圖物件
Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);
Point o(0, 0, 0);
Vector x(150, 0, 0), y(0, 150, 0), z(0, 0, 150);
Line X(o, x), Y(o, y), Z(o, z);

//拋物體運動
Point start(0, 50, 0);
Vector speed(0, 0, 0);
Vector acceleration(0, 0, 0);


void Display() {
	//清除顏色緩衝區
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	//處理畫面旋轉
	glRotatef(mouseMotion_y, 1.0, 0.0, 0.0);
	glRotatef(mouseMotion_x, 0.0, 1.0, 0.0);

	//X Y Z軸
	glLineWidth(2);
	X.draw(red); Y.draw(green); Z.draw(blue);

	//斜坡
	glLineWidth(1);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 50, 0);
	glVertex3f(85, 0, 0);
	glEnd();

	//摩擦力下滑運動
	glColor3f(0, 0, 0);
	glPushMatrix();
	AccelerationMoving(start, speed, Friction(30), t);
	glutSolidCube(5);
	glPopMatrix();

	glPopMatrix();
	//交換緩衝區
	glutSwapBuffers();
}

void AnimationTimer(int id) {
	if (animationPlay) {
		t < 50 ? t+=0.01 : t = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(animationDelay, AnimationTimer, 1);
}

void MouseClick(int button, int state, int x, int y) {
	mouseClick_x = x;
	mouseClick_y = y;
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	mouseMotion_x = x - mouseClick_x;
	mouseMotion_y = y - mouseClick_y;
	glutPostRedisplay();
}

void SpecialKeyPress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		glutPostRedisplay();
		break;
	}
}

void GLInitialize() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 200, -50, 200, -50, 200);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 1);
}

int main() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowSizeW, windowSizeH);
	glutCreateWindow(windowName);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutSpecialFunc(SpecialKeyPress);
	glutDisplayFunc(Display);
	glutTimerFunc(animationDelay, AnimationTimer, 1);

	GLInitialize();
	glutMainLoop();
	return 0;
}