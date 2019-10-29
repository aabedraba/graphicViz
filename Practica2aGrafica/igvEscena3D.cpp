#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores -----------------------------------

igvEscena3D::igvEscena3D() { ejes = true; rotation = 1; scaled = false; }

igvEscena3D::~igvEscena3D() {}


// Metodos publicos ----------------------------------------

void pintar_ejes(void) {
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glBegin(GL_LINES);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glBegin(GL_LINES);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

void tube() {
    static GLUquadric *quad = gluNewQuadric();

    GLfloat color_tube[] = {0, 0, 0.5};
    glMaterialfv(GL_FRONT, GL_EMISSION, color_tube);
    gluCylinder(quad, 0.25, 0.25, 1, 15, 15);
}


void igvEscena3D::visualizar(int scene) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

    // lights
    GLfloat light0[] = {10, 8, 9, 1}; // point light source
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);

    glPushMatrix(); // store the model matrices

    // se pintan los ejes
    if (ejes) pintar_ejes();

    // Scene selection based on menu option (int scene)
    if (scene == SceneA) renderSceneA();
    else if (scene == SceneB) renderSceneB();

    glPopMatrix(); // restore the modelview matrix
    glutSwapBuffers(); // it is used, instead of glFlush(), to avoid flickering
}

void igvEscena3D::renderSceneA() {
    GLfloat color_piece[] = {0, 0.25, 0};
    GLfloat color_black[] = {0, 0, 0};

    // Practica 2a. Parte A.

    // Cube
    glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

    float translation = 1.5;
    int rows = 3, columns = 3, depth = 3;
    for (int i = 0; i < depth; ++i) {
        glPushMatrix();
        glTranslated(i * translation, 0, 0);
        glutSolidCube(1);
        for (int j = 0; j < rows; ++j) {
            glPushMatrix();
            glTranslated(0, j * translation, 0);
            glutSolidCube(1);
            for (int k = 0; k < columns; ++k) {
                glPushMatrix();
                glTranslated(0, 0, k * translation);
                glutSolidCube(1);
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
}

void igvEscena3D::renderSceneB() {
    GLfloat color_black[] = { 0,0,0 };

    //A
    renderSceneA();

    glPushMatrix();
    glTranslated(3, 3, 3);
    glRotated(rotation*90, 0, 0, 1);
    glRotated(270, 1, 0, 0);
    if(scaled)
        glScaled(1, 1, 3);
    tube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3, 3, 0);
    glRotated(rotation*90, 0, 0, 1);
    glRotated(270, 1, 0, 0);
    if(scaled)
        glScaled(1, 1, 3);
    tube();
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, color_black);
}

void igvEscena3D::rotate(){
    rotation+=1;
}

void igvEscena3D::scale(){
    if (scaled)
        scaled = false;
    else
        scaled = true;
}