#include <iostream>
#include <GL/glut.h>
#include "header.h"

using namespace std;

int old_x = 0, old_y = 0;
GLfloat spin_x = 0, spin_y = 0;

Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);
Point O(0, 0, 0), cube(0, 20, 0);
Vector N(0, 1, 0), V(0, 40, 0);
Line L(O, V);
Plane P(O, N);

////////////////初始化////////////////
void Initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -50, 50);
	glMatrixMode(GL_MODELVIEW);
}

////////////////顯示計算結果////////////////
void ShowData() {
	system("CLS");
	cout << "cube(" << cube.x << ", " << cube.y << ", " << cube.z << ")" << endl;
	cout << "CollisionPoint(" << collisionPoint(L, P).x << ", " << collisionPoint(L, P).y << ", " << collisionPoint(L, P).z << ")" << endl;
}

////////////////描繪畫面////////////////
void Display() {
	glClearColor(1, 1, 1, 1);				//不透明黑色背景
	glClear(GL_COLOR_BUFFER_BIT);			//清理顏色緩衝區

											//畫面旋轉
	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);


	//平面
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(10, 0, 10);
	glVertex3f(-10, 0, 10);
	glVertex3f(-10, 0, -10);
	glVertex3f(10, 0, -10);
	glEnd();

	//線
	L.draw(green);

	//方塊
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, cube.y, 0);
	glutSolidCube(1);
	glPopMatrix();

	//更新畫面
	glPopMatrix();
	glFlush();
}

////////////////獲取滑鼠按下////////////////
void MouseClick(int button, int state, int x, int y) {
	old_x = x;
	old_y = y;
	glutPostRedisplay();
}

////////////////獲取滑鼠拖曳////////////////
void MouseMotion(int x, int y) {
	spin_x = x - old_x;
	spin_y = y - old_y;
	glutPostRedisplay();
}

////////////////獲取鍵盤按下////////////////
void SpecialKeyPress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (cube.y < 40)
			cube.y++;
		glutPostRedisplay();
		ShowData();
		break;
	case GLUT_KEY_DOWN:
		if (cube.y != collisionPoint(L, P).y)
			cube.y--;
		glutPostRedisplay();
		ShowData();
		break;
	}
}

int main() {
	glutInitWindowSize(800, 600);					//視窗長寬
	glutInitWindowPosition(400, 300);				//視窗左上角的位置
	glutCreateWindow("My OpenGL Projects");			//建立視窗並打上標題

	Initialize();
	ShowData();
	//下面三個與Callback函式有關
	glutMouseFunc(MouseClick);						//滑鼠按下
	glutMotionFunc(MouseMotion);					//滑鼠拖曳
	glutSpecialFunc(SpecialKeyPress);				//處理按鍵
	glutDisplayFunc(Display);						//負責描繪
	glutMainLoop();									//進入主迴圈
	return 0;
}