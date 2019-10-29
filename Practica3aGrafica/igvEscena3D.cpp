#include <cstdlib>
#include <stdio.h>
#include <cmath>

#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"


// Metodos constructores 

igvEscena3D::igvEscena3D() {
    ejes = true;

    // Apartado A: insertar aqu� el c�digo para crear la malla asociada a la escena equivalente a un cubo
    GLfloat vertices[24] = {0.5, 0.5, 0.5,
                            -0.5, 0.5, 0.5,
                            -0.5, -0.5, 0.5,
                            0.5, -0.5, 0.5,
                            0.5, -0.5, -0.5,
                            0.5, 0.5, -0.5,
                            -0.5, 0.5, -0.5,
                            -0.5, -0.5, -0.5};
//    unsigned int v_triangulos[]
    GLuint triangulos[36] = {0, 1, 2,
                             0, 3, 5,
                             2, 3, 0,
                             3, 4, 5,
                             4, 6, 5,
                             6, 4, 7,
                             1, 6, 7,
                             1, 7, 2,
                             2, 3, 4,
                             0, 5, 1,
                             4, 7, 2,
                             5, 6, 1
    };
    malla = new igvMallaTriangulos(8, vertices, 12, triangulos);
}

igvEscena3D::~igvEscena3D() {

}


// Metodos publicos 

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

void igvEscena3D::visualizar(void) {
    GLfloat color_malla[] = {0, 0.25, 0};
    // crear luces
    GLfloat luz0[4] = {2.0, 2.5, 3.0, 1}; // luz puntual para visualizar el cubo

    glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aqu� si permanece fija y no se mueve con la escena
    glEnable(GL_LIGHT0);

    // crear el modelo
    glPushMatrix(); // guarda la matriz de modelado

    // se pintan los ejes
    if (ejes) pintar_ejes();


    //glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena
    glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);

    // Apartado A: la siguiente llamada hay que sustituirla por la llamada al m�todo visualizar de la malla
    malla->visualizar();

    glPopMatrix(); // restaura la matriz de modelado
}

