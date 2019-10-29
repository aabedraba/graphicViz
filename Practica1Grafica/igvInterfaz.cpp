#include <cstdlib>

#include "igvInterfaz.h"

// los callbacks deben ser estaticos y se requiere este objeto para acceder desde
// ellos a las variables de la clase
extern igvInterfaz interfaz;

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz ():
        ejes(true),
        circulo(true){
}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::configura_entorno(int argc, char** argv,
                                    int _ancho_ventana, int _alto_ventana,
                                    int _pos_X, int _pos_Y,
                                    string _titulo){
    // inicializaci?n de las variables de la interfaz
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicializaci?n de la ventana de visualizaci?n
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana,_alto_ventana);
    glutInitWindowPosition(_pos_X,_pos_Y);
    glutCreateWindow(_titulo.c_str());

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana

}

void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'e':
            if (interfaz.ejes) interfaz.ejes = false;
            else interfaz.ejes = true;
            break;
        case 'c':
            if(interfaz.circulo) interfaz.circulo = false;
            else interfaz.circulo = true;
            break;
        case 27: // tecla de escape para SALIR
            exit(1);
            break;
    }
    glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
    // dimensiona el viewport al nuevo ancho y alto de la ventana
    glViewport(0,0,(GLsizei) w,(GLsizei) h);

    // guardamos valores nuevos de la ventana de visualizacion
    interfaz.set_ancho_ventana(w);
    interfaz.set_alto_ventana(h);

    // establece el tipo de proyeccion a utilizar
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1,1,-1,1,-1,200);

    // se define la camara de vision
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void igvInterfaz::set_glutDisplayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
    glPushMatrix(); // guarda la matriz de modelado

    // Apartado A: pintar los ejes
    if (interfaz.ejes){
        int tam_eje = 200;
        //x
        glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(tam_eje, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(-tam_eje, 0, 0);
        glEnd();

        //y
        glBegin(GL_LINES);
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, tam_eje, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, -tam_eje, 0);
        glEnd();

        //z
        glBegin(GL_LINES);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 000, tam_eje);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 000, -tam_eje);
        glEnd();
    }
    // Apartado B: visualizar primitiva cubo en modo alambre
    float tam_lado = 1;
    glBegin(GL_LINES);
    glColor3f(0, 0, 0); //negro

    glVertex3f(0, 0, 0);
    glVertex3f(tam_lado, 0, 0);

    glVertex3f(tam_lado, 0, 0);
    glVertex3f(tam_lado, tam_lado, 0);

    glVertex3f(tam_lado, tam_lado, 0);
    glVertex3f(0, tam_lado, 0);

    glVertex3f(0, tam_lado, 0);
    glVertex3f(0, 0, 0);

    // --

    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, tam_lado);

    glVertex3f(0, 0, tam_lado);
    glVertex3f(0, tam_lado, tam_lado);

    glVertex3f(0, tam_lado, tam_lado);
    glVertex3f(0, tam_lado, 0);

    // --

    glVertex3f(tam_lado, tam_lado, 0);
    glVertex3f(tam_lado, tam_lado, tam_lado);

    glVertex3f(tam_lado, tam_lado, tam_lado);
    glVertex3f(0, tam_lado, tam_lado);

    glVertex3f(tam_lado, 0, 0);
    glVertex3f(tam_lado, tam_lado, 0);

    // --

    glVertex3f(tam_lado, 0, 0);
    glVertex3f(tam_lado, 0, tam_lado);

    glVertex3f(tam_lado, 0, tam_lado);
    glVertex3f(0, 0, tam_lado);

    // --

    glVertex3f(tam_lado, 0, tam_lado);
    glVertex3f(tam_lado, tam_lado, tam_lado);

    glEnd();

    // apartado D: cubo hecho con l?neas
    float relleno = 0.125; //distancia entre el cubo interior y exterior
    tam_lado = 0.75;
    glBegin(GL_LINES);
    glColor3f(1, 1, 0); //amarillo
    glLineWidth(2);

    glVertex3f(relleno,relleno, relleno);
    glVertex3f(relleno+tam_lado, relleno, relleno);

    glVertex3f(relleno,relleno, relleno);
    glVertex3f(relleno+tam_lado, relleno, relleno);

    glVertex3f(relleno+tam_lado, relleno, relleno);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno);

    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno);
    glVertex3f(relleno, relleno+tam_lado, relleno);

    glVertex3f(relleno, relleno+tam_lado, relleno);
    glVertex3f(relleno, relleno, relleno);

    // --

    glVertex3f(relleno, relleno, relleno);
    glVertex3f(relleno, relleno, relleno+tam_lado);

    glVertex3f(relleno, relleno, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno, relleno+tam_lado);

    glVertex3f(relleno+tam_lado, relleno, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno, relleno);

    glVertex3f(relleno+tam_lado, relleno, relleno);
    glVertex3f(relleno, relleno, relleno);

    // --

    glVertex3f(relleno, relleno, relleno+tam_lado);
    glVertex3f(relleno, relleno+tam_lado, relleno+tam_lado);

    glVertex3f(relleno, relleno+tam_lado, relleno+tam_lado);
    glVertex3f(relleno, relleno+tam_lado, relleno);

    // --

    glVertex3f(relleno+tam_lado, relleno, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);

    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);
    glVertex3f(relleno, relleno+tam_lado, relleno+tam_lado);

    // --

    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno);

    glEnd();

    // apartado E: cubo hecho con tri?ngulos
    relleno = 0.25;
    tam_lado = 0.5;

    glBegin(GL_TRIANGLES);
    glColor3f(1,1,0); //amarillo
    glVertex3f(relleno, relleno, relleno);
    glVertex3f(relleno+tam_lado, relleno, relleno);
    glVertex3f(relleno, relleno+tam_lado, relleno);

    glColor3f(1,0,0); //rojo
    glVertex3f(relleno+tam_lado, relleno, relleno);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno);
    glVertex3f(relleno, relleno+tam_lado, relleno);

    glColor3f(0,1,0); //lima
    glVertex3f(relleno+tam_lado, relleno, relleno);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);

    glColor3f(1,0,1); //magenta
    glVertex3f(relleno+tam_lado, relleno, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno, relleno);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);

    glColor3f(1,0,0); //rojo
    glVertex3f(relleno, relleno, relleno);
    glVertex3f(relleno, relleno, relleno+tam_lado);
    glVertex3f(relleno, relleno+tam_lado, relleno+tam_lado);

    glColor3f(0,100,0); //dark green
    glVertex3f(relleno, relleno, relleno);
    glVertex3f(relleno, relleno+tam_lado, relleno);
    glVertex3f(relleno, relleno+tam_lado, relleno+tam_lado);

    glColor3f(0,0,128); //navy
    glVertex3f(relleno, relleno+tam_lado, relleno);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);

    glColor3f(1,0,0); //red
    glVertex3f(relleno, relleno+tam_lado, relleno);
    glVertex3f(relleno, relleno+tam_lado, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);

    glColor3f(1,1,0); //yellow
    glVertex3f(relleno, relleno, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);

    glColor3f(0,0,128);//navy
    glVertex3f(relleno, relleno, relleno+tam_lado);
    glVertex3f(relleno, relleno+tam_lado, relleno+tam_lado);
    glVertex3f(relleno+tam_lado, relleno+tam_lado, relleno+tam_lado);
    glEnd();

    // apartado F: c?rculo hecho con tri?ngulos
    if(interfaz.circulo){
        int num_tri = 33;
        double lado = (((float)360/num_tri)*M_PI)/180; //pasamos a radianes
        double lado_acumulado = lado;

        double orig = 0.5;
        float color = 1;
        double x1=1, y1=orig ,x2=0, y2=0;

        float rg=0.97;
        for (int i=0; i<num_tri; i++){
            glBegin(GL_TRIANGLES);
            color *=rg;
            glColor3f(0,color,0);
            glVertex3f(orig,orig,1);
            glVertex3f(x1, y1, 1);
            x2 = orig*cos(lado_acumulado)+orig;
            y2 = orig*sin(lado_acumulado)+orig;
            glVertex3f(x2,y2,1);
            x1 = x2;
            y1 = y2;
            lado_acumulado+=lado;
            glEnd();
        }
    }


    glPopMatrix (); // restaura la matriz de modelado
    glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(set_glutKeyboardFunc);
    glutReshapeFunc(set_glutReshapeFunc);
    glutDisplayFunc(set_glutDisplayFunc);
}
