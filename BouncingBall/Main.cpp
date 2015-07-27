#include <stdlib.h>  
#include <glut.h>
#include <stdio.h>
#include <string>
using namespace std;

int const wallwidth = 10;
int const wallheight = 100;
int random;
double arrowXpos =  0;
double arrowYpos = -1;
double sphereX = arrowXpos;
double sphereY = arrowYpos;
double sphereZ = 1;
double zoom = -7;
double dx = .3;
double dy = .3;
int score = 0;
bool repeat = false;
int rounds = 0;
double scoreX;
double scoreY;
double scoreZ;
bool gameStart;
int angle = 0;
bool eCamera; 

int score1;
int score2;
int score3;

bool start;
bool gameOver;

int dxC = 1;
int dyC = 1;

double R, G, B;

void keyboard();
void randomColors();
void Sphere();
void drawEndWall();
void drawLeftWall();
void drawRightWall();
void drawTopWall();
void drawBottomWall();
void drawSphere();
void drawShootingStation();
void anim();
void print(int, int, char*);
void resetInitialPositions();
void calculateScore();

double leftRandomR[10][100];
double leftRandomG[10][100];
double leftRandomB[10][100];

double rightRandomR[10][100];
double rightRandomG[10][100];
double rightRandomB[10][100];

double topRandomR[10][100];
double topRandomG[10][100];
double topRandomB[10][100];

double bottomRandomR[10][100];
double bottomRandomG[10][100];
double bottomRandomB[10][100];

void randomColors() {

	random = rand() % 4 + 1;
	switch (random) {
	case 1: R = 1; G = .4; B = 0.4; break; //affect el score by +10
	case 2: R = 0.6; G = .2; B = 1; break; //affect el score by +50
	case 3: R = 0.7; G = 1; B = .4; break; //affect el score -10
	case 4: R = 0.4; G = .7; B = .8; break; //affect el score +100
	}
}

void randomWallColors() {
	for (int i = 0; i < 10 ; i++){
		for (int j = 1; j < 100; j++) {
			randomColors();
			leftRandomR[i][j] = R;
			leftRandomG[i][j] = G;
			leftRandomB[i][j] = B;
			randomColors();
			rightRandomR[i][j] = R;
			rightRandomG[i][j] = G;
			rightRandomB[i][j] = B;
			randomColors();
			topRandomR[i][j] = R;
			topRandomG[i][j] = G;
			topRandomB[i][j] = B;
			randomColors();
			bottomRandomR[i][j] = R;
			bottomRandomG[i][j] = G;
			bottomRandomB[i][j] = B;
		}
	}
}

void resetInitialPositions() {
	sphereX = arrowXpos;
	sphereY = arrowYpos;
	dx = .3;
	dy = .3;
	sphereZ = 1;
	zoom = -7;
	angle = 0;
}

void displayWire(void)
{	
	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	gluPerspective(60, 640/480, 0.1, 107);
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(0, 0, zoom, 0, 0, 107, 0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

	if (gameStart == false) {
		glPushMatrix();
		glTranslated(4, 2, zoom + 7);
		glLineWidth(10);
		glColor3d(1.0, 1, 1);
		char * stC[100];
		sprintf((char *)stC, "To move the shooting arrow, use the arrow keys on the keyboard. ");
		print(0, 0, (char *)stC);
		glPopMatrix();

		glPushMatrix();
		glTranslated(4, 1, zoom + 7);
		glLineWidth(10);
		glColor3d(1.0, 1, 1);
		char * stC1[100];
		sprintf((char *)stC1, "To fire, press 'f'");
		print(0, 0, (char *)stC1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(4, 0, zoom + 7);
		glLineWidth(10);
		glColor3d(1.0, 1, 1);
		char * stC2[100];
		sprintf((char *)stC2, "To repeat round, press 'r'");
		print(0, 0, (char *)stC2);
		glPopMatrix();


		glPushMatrix();
		glTranslated(4, -1, zoom + 7);
		glColor3d(1.0, 1, 1);
		char * stC3[100];
		sprintf((char *)stC3, "To go to next round, press 'n'");
		print(0, 0, (char *)stC3);
		glPopMatrix();

		glPushMatrix();
		glTranslated(4, -2, zoom + 7);
		glColor3d(1.0, 1, 1);
		char * stC4[100];
		sprintf((char *)stC4, "For Enhanced Camera mode, press 'e'");
		print(0, 0, (char *)stC4);
		glPopMatrix();

		glPushMatrix();
		glTranslated(4, -3, zoom + 7);
		glColor3d(1.0, 1, 1);
		char * stC5[100];
		sprintf((char *)stC5, "For Simple Camera mode, press 's'");
		print(0, 0, (char *)stC5);
		glPopMatrix();
	}

	if (gameOver == true) {
		glPushMatrix();
		glTranslated(4, 4, zoom + 10);
		glColor3d(0.0, 0, 0);
		char * stC[100];
		sprintf((char *)stC, "Final Score: %i", score1+score2+score3);
		print(0, 0, (char *)stC);
		glPopMatrix();


		glPushMatrix();
		glTranslated(1, 0, zoom + 10);
		glColor3d(1, 1, 1);
		char * stC1[100];
		sprintf((char *)stC1, "Game Over");
		print(0, 0, (char *)stC1);
		glPopMatrix();

	}

		//displays score
	if (gameOver == false) {
		glPushMatrix();
		glTranslated(4, 4, zoom + 10);
		glColor3d(0.0, 0, 0);
		char * stC[100];
		sprintf((char *)stC, "Score: %i", score);
		print(0, 0, (char *)stC);
		glPopMatrix();

		glPushMatrix();
		glTranslated(1, 4, zoom + 10);
		glColor3d(0.0, 0, 0);
		char * stC1[100];
		if (eCamera == false)
		sprintf((char *)stC1, "Camera Mode: Simple");
		else 
		sprintf((char *)stC1, "Camera Mode: Enahanced");
		print(0, 0, (char *)stC1);
		glPopMatrix();
	}

	glPushMatrix();
	glRotated(angle, 0, 0, 1);
	drawRightWall();
	drawEndWall();
	drawLeftWall();
	drawTopWall();
	drawBottomWall();
	drawSphere();
	drawShootingStation();
	glPopMatrix();

	glFlush();
}

void keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT && start == false && arrowXpos <= 3.8 && rounds<3) {
		arrowXpos = arrowXpos + 0.2;
		sphereX += 0.2;
	}
	if (key == GLUT_KEY_RIGHT &&  start == false && arrowXpos > -3.8 && rounds<3) {
		arrowXpos = arrowXpos - 0.2;
		sphereX -= 0.2;
	}
	if (key == GLUT_KEY_UP && start == false && arrowYpos < 3.8 && rounds<3) {
		arrowYpos = arrowYpos + 0.2;
		sphereY += 0.2;
	}
	if (key == GLUT_KEY_DOWN && start == false && arrowYpos > -3.8 && rounds<3) {
		arrowYpos = arrowYpos - 0.2;
		sphereY -=0.2;
	}
	glutPostRedisplay();
}

void charKeyboard(unsigned char key, int x, int y) {
	if (key == 'f' && start == false && rounds < 3) {
		gameStart = true;
		start = true;
		repeat = false;
		rounds++;
		
	}
	if (key == 'r') {
		resetInitialPositions();
		repeat = true;
		start = true;
	}
	if (key == 'n' && rounds<3) {
		start = false;
		repeat = false;
		arrowXpos = 0;
		arrowYpos = -1;
		if (rounds == 1) {
			score1 = score;
		}
		if (rounds == 2) {
			score2 = score;
		}
		if (rounds == 3) {
			score3 = score;
		}
		score = 0;
		resetInitialPositions();
	}

	if (key == 'e') {
		eCamera = true;
	}
	if (key == 's') {
		eCamera = false;
	}
}

void drawEndWall() {

	//End Wall
	for (int i = -5; i < 5; i++){
		for (int j = -5; j < 5; j++){
			glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslated(i, j, 100);
			glutSolidCube(1);
			glPopMatrix();

		}
	}
}

void drawRightWall() {
	for (int i = -5; i < 5; i++){
		for (int j = 1; j < 100; j++){
			glColor3d(rightRandomR[i+5][j], rightRandomG[i+5][j], rightRandomB[i+5][j]);
			glPushMatrix();
			//glColor3f(1, 1, 0);
			glTranslated(-5, i, j);
			glutSolidCube(1);
			glPopMatrix();
		}
	}
}

void drawLeftWall() {
	for (int i = -5; i < 5; i++){
		for (int j = 1; j < 100; j++){
			glColor3d(leftRandomR[i + 5][j], leftRandomG[i + 5][j], leftRandomB[i + 5][j]);
			//glColor3d(0,0,1);			
			glPushMatrix();
			glTranslated(5, i, j);
			glutSolidCube(1);
			glPopMatrix();

		}
	}
}

void drawBottomWall() {
	for (int i = -5; i < 5; i++){
		for (int j = 1; j < 100; j++){
			glColor3d(bottomRandomR[i + 5][j], bottomRandomG[i + 5][j], bottomRandomB[i + 5][j]);
			glPushMatrix();
			glTranslated(i, -5, j);
			glutSolidCube(1);
			glPopMatrix();
		}
	}
}

void drawTopWall() {
	for (int i = -5; i < 5; i++){
		for (int j = 1; j < 100; j++){
			glColor3d(topRandomR[i + 5][j], topRandomG[i + 5][j], topRandomB[i + 5][j]);
			glPushMatrix();
			glTranslated(i, 5, j);
			glutSolidCube(1);
			glPopMatrix();
		}
	}
}

void drawSphere() {
	glPushMatrix();
	glColor3d(0, 1, 1);
	glTranslated(sphereX, sphereY, sphereZ);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();
}

void drawShootingStation() {
	glPushMatrix();
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3d(0, 0, 0);
	glVertex3d(0, -2, 1);
	glVertex3d(arrowXpos, arrowYpos, 1);
	glEnd();
	glPushMatrix();
	glTranslated(arrowXpos, arrowYpos, 1);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();
	glPopMatrix();
}

void print(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void calculateScore() {
	//x =-4 right wall
	//x =+4 left wall
	//y = +4 top wall
	//y = -4 bottom wall

	if (scoreY == +4) { //topwall
		for (int i = -5; i < 5; i++) {
			for (int j = 1; j < 100; j++) {
				if ((scoreX >= i) && (scoreX < i + 1) && (scoreZ >=j) && (scoreZ < j+1)) {
					if ((topRandomR[i+5][j] == 1) && (topRandomB[i+5][j] == 0.4) && (topRandomG[i+5][j] = 0.4)) {
						score += 10;
					}
					else {
						if ((topRandomR[i+5][j] == 0.6) && (topRandomB[i+5][j] == 1) && (topRandomG[i+5][j] = 0.2)) {
							score += 50;
						}
						else {
							if ((topRandomR[i+5][j] == 0.7) && (topRandomB[i+5][j] == 0.4) && (topRandomG[i+5][j] = 1)) {
								score -= 10;
							}
							else {
								if ((topRandomR[i+5][j] == 0.4) && (topRandomB[i+5][j] == 0.8) && (topRandomG[i+5][j] = 0.7)) {
									score += 100;
								}
							}
						}
					}
				}
			}
		}
	}

	if (scoreY == -4) {
		for (int i = -5; i < 5; i++) {
			for (int j = 1; j < 100; j++) {
				if (scoreX >= i && scoreX < i + 1 && scoreZ >= j && scoreZ < j + 1) {
					if ((bottomRandomR[i + 5][j] == 1) && (bottomRandomB[i + 5][j] == 0.4) && (bottomRandomG[i + 5][j] = 0.4)) {
						score += 10;
					}
					else {
						if ((bottomRandomR[i + 5][j] == 0.6) && (bottomRandomB[i + 5][j] == 1) && (bottomRandomG[i + 5][j] = 0.2)) {
							score += 50;
						}
						else {
							if ((bottomRandomR[i + 5][j] == 0.7) && (bottomRandomB[i + 5][j] == 0.4) && (bottomRandomG[i + 5][j] = 1)) {
								score -= 10;
							}
							else {
								if ((bottomRandomR[i + 5][j] == 0.4) && (bottomRandomB[i + 5][j] == 0.8) && (bottomRandomG[i + 5][j] = 0.7)) {
									score += 100;
								}
							}
						}
					}
				}
			}
		}
	}


	if (scoreX == -4) {
		for (int i = -5; i < 5; i++) {
			for (int j = 1; j < 100; j++) {
				if (scoreY >= i && scoreY < i + 1 && scoreZ >= j && scoreZ < j + 1) {
					if ((rightRandomR[i + 5][j] == 1) && (rightRandomB[i + 5][j] == 0.4) && (rightRandomG[i + 5][j] = 0.4)) {
						score += 10;
					}
					else {
						if ((rightRandomR[i + 5][j] == 0.6) && (rightRandomB[i + 5][j] == 1) && (rightRandomG[i + 5][j] = 0.2)) {
							score += 50;
						}
						else {
							if ((rightRandomR[i + 5][j] == 0.7) && (rightRandomB[i + 5][j] == 0.4) && (rightRandomG[i + 5][j] = 1)) {
								score -= 10;
							}
							else {
								if ((rightRandomR[i + 5][j] == 0.4) && (rightRandomB[i + 5][j] == 0.8) && (rightRandomG[i + 5][j] = 0.7)) {
									score += 100;
								}
							}
						}
					}
				}
			}
		}
	}


	if (scoreX == 4) {
		for (int i = -5; i < 5; i++) {
			for (int j = 1; j < 100; j++) {
				if (scoreY >= i && scoreY < i + 1 && scoreZ >= j && scoreZ < j + 1) {
					if ((leftRandomR[i][j] == 1) && (leftRandomB[i][j] == 0.4) && (leftRandomG[i][j] = 0.4)) {
						score += 10;
					}
					else {
						if ((leftRandomR[i][j] == 0.6) && (leftRandomB[i][j] == 1) && (leftRandomG[i][j] = 0.2)) {
							score += 50;
						}
						else {
							if ((leftRandomR[i][j] == 0.7) && (leftRandomB[i][j] == 0.4) && (leftRandomG[i][j] = 1)) {
								score -= 10;
							}
							else {
								if ((leftRandomR[i][j] == 0.4) && (leftRandomB[i][j] == 0.8) && (leftRandomG[i][j] = 0.7)) {
									score += 100;
								}
							}
						}
					}
				}
			}
		}
	}
}

void anim() {

	if (start == true && sphereZ <= 99.2) {
		sphereZ += 0.8;

		if (eCamera == true) {
			angle += 1;
		}

		

		if (arrowXpos != 0) {
			sphereX += dx;
			sphereY += dy;
		}

		zoom += 0.5;

			scoreX = sphereX;
			scoreY = sphereY;
			scoreZ = sphereZ;
			//printf("%f,  %f    ", sphereX, sphereY);
			/*printf("%f   ", scoreZ);*/
			calculateScore();

		if (sphereX >= 4 || sphereX <= -4) {
			dx *= -1;
		}

	
		if (sphereY <= -4 || sphereY >=4) {
			dy *= -1;
		}
		
	}

	if (rounds == 3 && sphereZ >=99.2) {
		start = true;
		gameOver = true;
	}
	
	if (repeat == true)
		for (int i = 0; i < 9000000; i++);

	if (repeat == false)
		for (int i = 0; i < 1000; i++);

	glutPostRedisplay();
}
 
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	random = rand() % 4 + 1;
	randomWallColors();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 150);
	glutCreateWindow("Bouncing Ball");
	glutDisplayFunc(displayWire);
	glEnable(GL_DEPTH_TEST); 
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glViewport(0, 0, 640, 480);
	glutKeyboardFunc(charKeyboard);
	glutSpecialFunc(keyboard);
	glutIdleFunc(anim);
	glutMainLoop();
}