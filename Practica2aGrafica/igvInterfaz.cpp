#include <cstdlib>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
// ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() : menuSelection(escena.SceneA) {}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::configura_entorno(int argc, char **argv,
                                    int _ancho_ventana, int _alto_ventana,
                                    int _pos_X, int _pos_Y,
                                    string _titulo) {
    // inicialización de las variables de la interfaz
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicialización de la ventana de visualización
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());

    create_menu();

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

    glEnable(GL_LIGHTING); // activa la iluminacion de la escena
    glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion
}

void igvInterfaz::create_menu() {
    int menu_id = glutCreateMenu(menuHandle);
    glutAddMenuEntry(interfaz.escena.SceneA_Name, interfaz.escena.SceneA);
    glutAddMenuEntry(interfaz.escena.SceneB_Name, interfaz.escena.SceneB);


    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'e': // activa/desactiva la visualizacion de los ejes
            interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);

            break;

            // A realizar: Añade el código para aplicar la rotación y el escalado del tubo en la parte B
        case 'r':
            interfaz.escena.rotate();
            break;
        case 's':
            interfaz.escena.scale();
            break;

        case 27: // tecla de escape para SALIR
            exit(1);
    }
    glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
    // dimensiona el viewport al nuevo ancho y alto de la ventana
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    // guardamos valores nuevos de la ventana de visualizacion
    interfaz.set_ancho_ventana(w);
    interfaz.set_alto_ventana(h);

    // establece el tipo de proyeccion a utilizar
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 5, 200);

    // se define la camara de vision
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(1.5, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // vista en perspectiva
    //gluLookAt(1.5,0,0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // vista en planta desde el eje X positivo
}

void igvInterfaz::set_glutDisplayFunc() {
    interfaz.escena.visualizar(interfaz.menuSelection);
}

void igvInterfaz::menuHandle(int value) {
    interfaz.menuSelection = value;
    glutPostRedisplay(); // renew the content of the window
}

void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(set_glutKeyboardFunc);
    glutReshapeFunc(set_glutReshapeFunc);
    glutDisplayFunc(set_glutDisplayFunc);
}
