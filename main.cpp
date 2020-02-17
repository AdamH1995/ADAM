//
//  main.cpp
//  Homework 1
//
//  Created by Adam P Hayes on 1/27/20.
//  Copyright © 2020 WIU. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <iostream>

const int MAP_SIZE=16;
int currentFrame=0;

//Original character bitmap
int bitMap[MAP_SIZE][MAP_SIZE]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,1,0,4,4,0,1,1,1,0,0,0},
    {0,0,1,1,1,1,0,4,4,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
    {0,0,0,0,1,1,2,2,2,2,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,3,1,1,1,1,3,0,0,0,0,0},
    {0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0},
    {0,0,3,3,0,0,0,0,0,0,0,0,3,3,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
//Character bitmap of jump animation
int jump[3][MAP_SIZE][MAP_SIZE]={
    {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,1,0,4,4,0,1,1,1,0,0,0},
    {0,0,1,1,1,1,0,4,4,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0},
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
    {0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,1,0,4,4,0,1,1,1,0,0,0},
    {0,0,1,1,1,1,0,4,4,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
    {0,0,0,0,1,1,2,2,2,2,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,3,1,1,1,1,3,0,0,0,0,0},
    {0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0},
    {0,0,0,0,3,3,0,0,0,0,3,3,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    },
    {
    {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,1,0,4,4,0,1,1,1,0,0,0},
    {0,0,1,1,1,1,0,4,4,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
    {0,0,0,0,1,1,2,2,2,2,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,3,1,1,1,1,3,0,0,0,0,0},
    {0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0},
    {0,0,0,0,3,3,0,0,0,0,3,3,3,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    }
};
//Timer function to switch between frames of character animation
void timerFunction(int x){
    glutPostRedisplay();
    glutTimerFunc(16, timerFunction, 1);
    currentFrame++;
    
}

void display(){
    
    //Want to clear the screan after the last characted is drawn
    //glClear(GL_COLOR_BUFFER_BIT );
    //Reset to original x,y coordinates to start drawing character again
    glPopMatrix();
    glPushMatrix();
    
    //Character drawing, loops through x and y values and checks the number placed in each
    glTranslatef(-1.0625f, 1.0625f, 0.0f);
        for(int x=0; x<MAP_SIZE; x++){
            glTranslatef(0.125f, 0.0f, 0.0f);
            for(int y=0; y<MAP_SIZE; y++){
                glTranslatef(0.0f, -0.125f, 0.0f);
                //yellow-green
                if(jump[currentFrame][y][x]==1){
                    glColor3f(1.0f, 0.8667f, 0.0117f);
                    glutSolidCube(0.125);
                }
                //red
                else if(jump[currentFrame][y][x]==2){
                    glColor3f(1.0f, 0.0196f, 0.0196f);
                    glutSolidCube(0.125);
                }
                //blue
                else if(jump[currentFrame][y][x]==3){
                    glColor3f(0.1098f, 0.0313f, 0.541f);
                    glutSolidCube(0.125);
                }
                //black
                else if (jump[currentFrame][y][x]){
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glutSolidCube(0.125);
                }
                //white
                else{
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glutSolidCube(0.125);
                }
            }
        glTranslatef(0.0f, 2.0f, 0.0);
    }
    glFlush();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv); //
    glutCreateWindow("Not Mike Wazowski.");
    glutDisplayFunc(display);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutTimerFunc(16, timerFunction, 1);
    glutMainLoop();
    return 0;
}
