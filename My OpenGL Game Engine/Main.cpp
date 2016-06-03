#include <iostream>
#include <GL/glut.h>
#include "header.h"

using namespace std;

int old_x = 0, old_y = 0, spin_x = 0, spin_y = 0;

bool animationPlay = true;
int animationDelay = 20;
float t = 0;

Point O(0, 0, 0), Q1(50, 0, 0), Q2(0, 50, 0);
Vector X(1, 0, 0), Y(0, 1, 0), Z(0, 0, 1);

Quaternion q1(X, 90), q2(Z, 90);

void CommandIO() {
	//命令列資訊
	system("CLS");
}

void Display() {
	////描繪畫面
	//清理顏色緩衝區
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//保存當前模型視圖矩陣
	glPushMatrix();
	//畫面旋轉
	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);

	//四分數旋轉
	Quaternion q3 = slerp(t, q1, q2);
	q3.apply();
	//茶壺
	glColor3f(0.2, 0.7, 0.1);
	glutWireTeapot(50);

	//彈出堆棧
	glPopMatrix();

	//交換緩衝區
	glutSwapBuffers();
}

void AnimationTimer(int id) {
	//動畫
	if (animationPlay) {
		t += 0.01;
		if (t > 1)
			animationPlay = false;
	}
	else {
		t -= 0.01;
		if (t < 0)
			animationPlay = true;
	}
	glutTimerFunc(animationDelay, AnimationTimer, 1);
}

void MouseClick(int button, int state, int x, int y) {
	////獲取滑鼠按下
	old_x = x;
	old_y = y;
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	////獲取滑鼠拖曳
	spin_x = x - old_x;
	spin_y = y - old_y;
	glutPostRedisplay();
}

void SpecialKeyPress(int key, int x, int y) {
	//獲取鍵盤按下
	switch (key) {
	case GLUT_KEY_UP:
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		glutPostRedisplay();
		break;
	}
}

void Initialize() {
	//圖形初始化
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);							//開啟深度測試
	glutInitWindowSize(600, 600);						//視窗長寬
	glutInitWindowPosition(600, 50);					//視窗左上角的位置
	glutCreateWindow("My OpenGL Projects");				//建立視窗並打上標題
	glOrtho(-100, 100, -100, 100, -100, 100);			//畫面範圍
	glClearColor(1, 1, 1, 1);							//背景色
	glutMouseFunc(MouseClick);							//滑鼠按下
	glutMotionFunc(MouseMotion);						//滑鼠拖曳
	glutSpecialFunc(SpecialKeyPress);					//處理按鍵
	glutDisplayFunc(Display);							//負責描繪
	glutIdleFunc(Display);								//負責動畫
	glutTimerFunc(animationDelay, AnimationTimer, 1);	//動畫延遲時間
}

int main() {
	CommandIO();		//顯示命令列資料
	Initialize();		//圖形初始化
	glutMainLoop();		//進入主迴圈
	return 0;
}