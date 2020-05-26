#define GL_SILENCE_DEPRECATION
#define PI 3.14159265
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <math.h>


// camera movement states: rotations
bool lookUp;
bool lookDown;
bool lookLeft;
bool lookRight;
// camera movement states: translation
bool walkForward;
bool walkBackward;
bool strafeLeft;
bool strafeRight;
// camera state in the model
float xCameraLocation;
float yCameraLocation;
float zCameraLocation;
float yRotationAngle;
float zRotationAngle;
float xRotationAngle;

float forwardMovement = 1.0f;

GLfloat points[10][3];
GLint angle = 0;
float x = 90;
float innerRadius = 0.4;
float centerHeight = 0.618304 / 2.0;
GLfloat starCenter[3] = { 0.0,0.0,centerHeight };
GLfloat starCenter2[3] = { 0.0,0.0,-centerHeight / 2 };
int currentFrame = 0;
const int MAP_SIZE = 16;


//Bitmap of character created in first part of project
int jump[3][MAP_SIZE][MAP_SIZE] = {
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,4,4,4,4,1,1,0,0,0,0},
	{0,0,0,1,1,1,4,5,5,4,1,1,1,0,0,0},
	{0,0,1,1,1,1,4,5,5,4,1,1,1,1,0,0},
	{0,0,1,1,1,1,4,4,4,4,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
	{0,0,0,0,1,1,2,2,2,2,1,1,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,3,3,3,1,1,1,1,3,3,3,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	},
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,4,4,4,4,1,1,0,0,0,0},
	{0,0,0,1,1,1,4,5,5,4,1,1,1,0,0,0},
	{0,0,1,1,1,1,4,5,5,4,1,1,1,1,0,0},
	{0,0,1,1,1,1,4,4,4,4,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
	{0,0,0,0,1,1,2,2,2,2,1,1,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,3,1,1,1,1,3,0,0,0,0,0},
	{0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0},
	{0,0,0,0,3,3,0,0,0,0,3,3,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	},
	{
	{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,4,4,4,4,1,1,0,0,0,0},
	{0,0,0,1,1,1,4,5,5,4,1,1,1,0,0,0},
	{0,0,1,1,1,1,4,5,5,4,1,1,1,1,0,0},
	{0,0,1,1,1,1,4,4,4,4,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
	{0,0,0,0,1,1,2,2,2,2,1,1,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,3,1,1,1,1,3,0,0,0,0,0},
	{0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0},
	{0,0,0,0,3,3,0,0,0,0,3,3,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	}
};

void init() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glPolygonMode(GL_BACK, GL_LINE);

	glPolygonMode(GL_FRONT, GL_FILL);

	
	lookUp = false;
	lookDown = false;
	lookLeft = false;
	lookRight = false;
	walkForward = false;
	walkBackward = false;
	strafeLeft = false;
	strafeRight = false;
	
	yRotationAngle = 0;
	xRotationAngle = 0;
	zRotationAngle = 0;

	//glEnable(GL_CULL_FACE);
}

void createStar(){
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) { //Outer pentagon is even since the centerpoint is not part of the array
			points[i][0] = (cos(x * PI / 180));
			points[i][1] = (sin(x * PI / 180));
			points[i][2] = 0;
		}
		else {//Inner pentagon is scaled down
			points[i][0] = (cos(x * PI / 180) * innerRadius);
			points[i][1] = (sin(x * PI / 180) * innerRadius);
			points[i][2] = 0;
		}
		x += 36; //Each time we make a new vertice increment 36 degrees to next vertice
	}
	glRotatef(angle, 0, 1, 0); // change back to angle
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	//front half
		
	//Vertex 1
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter);
	glVertex3fv(points[0]);
	glVertex3fv(points[1]);
		
	//Vertex 2
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter);
	glVertex3fv(points[1]);
	glVertex3fv(points[2]);

	//Vertex 3
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter);
	glVertex3fv(points[2]);
	glVertex3fv(points[3]);

	//Vertex 4
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter);
	glVertex3fv(points[3]);
	glVertex3fv(points[4]);


	//Vertex 5
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter);
	glVertex3fv(points[4]);
	glVertex3fv(points[5]);

	//Vertex 6
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter);
	glVertex3fv(points[5]);
	glVertex3fv(points[6]);
	
	//Vertex 7
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter);
	glVertex3fv(points[6]);
	glVertex3fv(points[7]);

	//Vertex 8
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter);
	glVertex3fv(points[7]);
	glVertex3fv(points[8]);

		
	//Vertex 9
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter);
	glVertex3fv(points[8]);
	glVertex3fv(points[9]);

	//Vertex 10
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter);
	glVertex3fv(points[9]);
	glVertex3fv(points[0]);
	
	//back half

	//Vertex 1
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter2);
	glVertex3fv(points[9]);
	glVertex3fv(points[8]);

	//Vertex 2
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter2);
	glVertex3fv(points[8]);
	glVertex3fv(points[7]);

	//Vertex 3
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter2);
	glVertex3fv(points[7]);
	glVertex3fv(points[6]);

	//Vertex 4
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter2);
	glVertex3fv(points[6]);
	glVertex3fv(points[5]);

	//Vertex 5
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter2);
	glVertex3fv(points[5]);
	glVertex3fv(points[4]);

	//Vertex 6
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter2);
	glVertex3fv(points[4]);
	glVertex3fv(points[3]);

	//Vertex 7
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter2);
	glVertex3fv(points[3]);
	glVertex3fv(points[2]);

	//Vertex 8
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter2);
	glVertex3fv(points[2]);
	glVertex3fv(points[1]);

	//Vertex 9
	glColor3f(0.6, 0.8, 0.2);
	glVertex3fv(starCenter2);
	glVertex3fv(points[1]);
	glVertex3fv(points[0]);

	//Vertex 10
	glColor3f(0.2, 0.6, 0.8);
	glVertex3fv(starCenter2);
	glVertex3fv(points[0]);
	glVertex3fv(points[9]);

	glEnd();
}

void drawCharacter() {
	//Reset to original x,y coordinates to start drawing character again
	glPushMatrix();
	glTranslatef(-1.0625f, 1.0625f, 0.0f);
	//Character drawing, loops through x and y values and checks the number placed in each
	for (int x = 0; x < MAP_SIZE; x++) {
		glTranslatef(0.125f, 0.0f, 0.0f);
		for (int y = 0; y < MAP_SIZE; y++) {
			glTranslatef(0.0f, -0.125f, 0.0f);
			//yellow-green
			if (jump[currentFrame][y][x] == 1) {
				glColor3f(1.0f, 0.8667f, 0.0117f);
				glutSolidCube(0.125);
			}
			//red
			else if (jump[currentFrame][y][x] == 2) {
				glColor3f(1.0f, 0.0196f, 0.0196f);
				glutSolidCube(0.125);
			}
			//blue
			else if (jump[currentFrame][y][x] == 3) {
				glColor3f(0.1098f, 0.0313f, 0.541f);
				glutSolidCube(0.125);
			}
			//black
			else if (jump[currentFrame][y][x] == 4) {
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidCube(0.125);
			}
			//white
			else if (jump[currentFrame][y][x] == 5) {
				glColor3f(0.0f, 0.0f, 0.0f);
			}
			else {
				continue;
			}
		}
		glTranslatef(0.0f, 2.0f, 0.0);
	}
	glPopMatrix();
}
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -3);
	//glScalef(scale, scale, scale);
	//glTranslatef(x, y, z);
	glRotatef(angle, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3ub(250, 223, 173);
	glBegin(GL_QUADS);
	for (int i = -100;i <= 100;i += 10)
		for (int j = -100;j <= 100;j += 10)
		{
			glVertex3f(j + 10.0, 0.0, i);
			glVertex3f(j, 0, i);
			glVertex3f(j, 0, i + 10);
			glVertex3f(j + 10, 0, i + 10);
		}
	glEnd();
	
	glScalef(0.3, 0.3, 0.3);
	
	glTranslatef(0, 5, 0);
	createStar();

	glTranslatef(1, 0, -1);
	createStar();

	glTranslatef(-2, 0, -1);
	createStar();

	glTranslatef(-3, 0, 3);
	createStar();

	glTranslatef(-4, 0, -1);
	createStar();

	glLoadIdentity();
	glScalef(0.2, 0.2, 0.2);
	glTranslatef(0, .85, -10);
	drawCharacter();

	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)w / (GLfloat)h, 1, 20);

}

void timerFunction(int id) {
	switch (id) {
	case 0:
		angle++;
		angle %= 360;
		glutTimerFunc(80, timerFunction, 0);
		glutPostRedisplay();
		currentFrame++;
		if (currentFrame == 3)
			currentFrame = 0;
		break;
	default:
		break;
	}
}
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		xRotationAngle++;
		break;
	case GLUT_KEY_DOWN:
		xRotationAngle--;
		break;
	case GLUT_KEY_LEFT:
		yRotationAngle--;
		break;
	case GLUT_KEY_RIGHT:
		yRotationAngle++;
		break;
	default:
		break;
	}
	// Refresh the Window
	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	// horizontal and vertical movement
	float VM = 0; //(sin(xRotationAngle*PI / 180.0)*forwardMovement);
	float HM = (cos(xRotationAngle*PI / 180.0)*forwardMovement);

	// change in x, y, z due to this movement and camera angle
	float dX = sin(yRotationAngle*PI / 180.0) * HM;
	float dZ = -cos(yRotationAngle * PI / 180.0) * HM;
	float dY = VM;
	// a and d require y component of movement as well
	float dXSide = 0;
	float dZSide = 0;
	float dYSide = 0;

	float nextX = xCameraLocation + dX;
	float nextZ = xCameraLocation + dZ;


	switch (key)
	{
	case 'w':
		if ((nextX >= -5 && nextX <= 5) && (nextZ >= -5 && nextZ <= 5)) {
			break;
		}
		xCameraLocation += dX;
		yCameraLocation += dY;
		zCameraLocation += dZ;
		break;
	case 's':
		xCameraLocation -= dX;
		yCameraLocation -= dY;
		zCameraLocation -= dZ;
		break;
	case 'a':
		dXSide = sin((yRotationAngle - 90)*PI / 180.0) * 1;
		dZSide = -cos((yRotationAngle - 90) * PI / 180.0) * 1;
		dYSide = 0;
		xCameraLocation += dXSide;
		yCameraLocation += dYSide;
		zCameraLocation += dZSide;
		break;
	case 'd':
		dXSide = sin((yRotationAngle + 90)*PI / 180.0) * 1;
		dZSide = -cos((yRotationAngle + 90) * PI / 180.0) * 1;
		dYSide = 0;
		xCameraLocation += dXSide;
		yCameraLocation += dYSide;
		zCameraLocation += dZSide;
		break;
		// exit on escape key
	case 27:
		exit(0);
		break;
	default:
		break;
	}

}


int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(750, 750);
	glutCreateWindow("AllStar");
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutDisplayFunc(display);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboardFunc);
	glutTimerFunc(40, timerFunction, 0);
	//glutTimerFunc(100, timerFunction, 1);
	glutMainLoop();
	return 0;
}
