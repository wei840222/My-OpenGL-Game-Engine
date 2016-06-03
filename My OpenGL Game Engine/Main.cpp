#include <iostream>
#include <GL/glut.h>
#include "header.h"

using namespace std;

int old_x = 0, old_y = 0;
GLfloat spin_x = 0, spin_y = 0;

Point P1(0, 0, 0), P2(0, 40, 0), P3(20, 20, 20), P4(0, 0, 40);
Vector T1(100, 0, 0), T2(-100, 0, 0);
hermiteCurves cubeHC(P1, P2, T1, T2);
bezierCurves cubeBC(P1, P2, P3, P4);
catmullRomSpline cubeCC(P1, P2, P3, P4);
float t = 0;
bool go = true;

////////////////初始化////////////////
void Initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -50, 50);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 1);
}

////////////////命令列資訊////////////////
void Showdata() {
	system("CLS");
	printf("hermiteCurves:\nX: %f Y: %f Z: %f\n", cubeHC.parameter(t).x, cubeHC.parameter(t).y, cubeHC.parameter(t).z);
	printf("bezierCurves:\nX: %f Y: %f Z: %f\n", cubeBC.parameter(t).x, cubeBC.parameter(t).y, cubeBC.parameter(t).z);
	printf("catmullRomSpline:\nX: %f Y: %f Z: %f\n", cubeCC.parameter(t).x, cubeCC.parameter(t).y, cubeCC.parameter(t).z);
}

////////////////描繪畫面////////////////
void Display() {
	//清理顏色緩衝區
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//保存當前模型視圖矩陣
	glPushMatrix();
	//畫面旋轉
	glTranslatef(-0.5, 0, 0);
	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);

	//hermiteCurves方塊
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(cubeHC.parameter(t).x, cubeHC.parameter(t).y, cubeHC.parameter(t).z);
	glutSolidCube(1);
	glPopMatrix();

	//bezierCurves方塊
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(cubeBC.parameter(t).x, cubeBC.parameter(t).y, cubeBC.parameter(t).z);
	glutSolidCube(1);
	glPopMatrix();

	//catmullRomSpline方塊
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(cubeCC.parameter(t).x, cubeCC.parameter(t).y, cubeCC.parameter(t).z);
	glutSolidCube(1);
	glPopMatrix();

	//彈出堆棧
	glPopMatrix();
	//顯示命令列資料
	Showdata();
	//交換緩衝區
	glutSwapBuffers();
	//代入參數
	if (go) {
		t += 0.01;
		if (t > 1)
			go = false;
	}
	else {
		t -= 0.01;
		if (t < 0)
			go = true;
	}
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
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		glutPostRedisplay();
		break;
	}
}

int main() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);						//開啟深度測試
	glutInitWindowSize(800, 600);					//視窗長寬
	glutInitWindowPosition(400, 300);				//視窗左上角的位置
	glutCreateWindow("My OpenGL Projects");			//建立視窗並打上標題

	Initialize();
	glutMouseFunc(MouseClick);						//滑鼠按下
	glutMotionFunc(MouseMotion);					//滑鼠拖曳
	glutSpecialFunc(SpecialKeyPress);				//處理按鍵
	glutDisplayFunc(Display);						//負責描繪
	glutIdleFunc(Display);							//負責動畫
	glutMainLoop();									//進入主迴圈
	return 0;
}