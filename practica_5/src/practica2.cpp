//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <unistd.h>
#include "ui.h" // De aqui se hereda objetos.h

int ANCHO, ALTO;
int vista_multiple = 0;
float factorPlanta = 1.0;
float factorAlzado = 1.0;
float factorPerfil = 1.0;

// tamaño de los ejes
const int AXIS_SIZE = 5000;
GLint rendermode;

// Objeto a dibujar
_brazoRobot brazoRobot;
_revolucion* revolucion;
_objetoPLY* objetoPLY;
_piramide piramide;
_cubo cubo;


_triangulos3D* figura1;
_triangulos3D* figura2;
_triangulos3D* escena;
bool figura1_color_original = true;
bool figura2_color_original = true;
int objetosEscena;


TipoObjeto objeto = Piramide;
Visualizacion viMode = Aristas;
bool enEscena = false;
bool circulos = false;
bool tapas = false;

UI ui(piramide, cubo, brazoRobot);

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width, Window_height, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50, UI_window_pos_y=50, UI_window_width=500, UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(-Window_width, Window_width, -Window_height, Window_height, Front_plane, Back_plane);

  glViewport(0, 0, ANCHO, ALTO);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer() {
  // posicion del observador
  change_projection();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis() {
  glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1,0,0);
    glVertex3f(-AXIS_SIZE,0,0);
    glVertex3f(AXIS_SIZE,0,0);

    // eje Y, color verde
    glColor3f(0,1,0);
    glVertex3f(0,-AXIS_SIZE,0);
    glVertex3f(0,AXIS_SIZE,0);

    // eje Z, color azul
    glColor3f(0,0,1);
    glVertex3f(0,0,-AXIS_SIZE);
    glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************
void draw_objects() {
  ui.Muestra(objeto, viMode, escena, objetosEscena, circulos, tapas, enEscena);

  if (rendermode == GL_SELECT) {
		glLoadName(2);
  }
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void) {
  clear_window();

  if (vista_multiple == 0) {
    change_observer();
    draw_axis();
    draw_objects();

  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-Window_width, Window_width, -Window_height, Window_height, Front_plane, Back_plane);
    glViewport((GLint) ANCHO/2, 0, (GLint) ANCHO/2, (GLint) ALTO/2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-Observer_distance);
    glRotatef(Observer_angle_x,1,0,0);
    glRotatef(Observer_angle_y,0,1,0);

    draw_axis();
    draw_objects();


    ////////////////// Planta //////////////////
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -100, 100);
    glScalef(factorPlanta, factorPlanta, -1.0);
    glViewport(0, 0, (GLint) ANCHO/2, (GLint) ALTO/2);

    gluLookAt(0,1,0, 0,0,0, 0,0,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw_axis();
    draw_objects();


    ////////////////// Alzado //////////////////
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -100, 100);
    glScalef(factorPlanta, factorPlanta, 1.0);
    glViewport(0, (GLint) ALTO/2, (GLint) ANCHO/2, (GLint) ALTO/2);

    gluLookAt(0,0,1, 0,0,0, 0,1,0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw_axis();
    draw_objects();


    ////////////////// Perfil //////////////////
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -100, 100);
    glScalef(factorPlanta, factorPlanta, 1.0);
    glViewport((GLint) ANCHO/2, (GLint) ALTO/2, (GLint) ANCHO/2, (GLint) ALTO/2);

    gluLookAt(1,0,0, 0,0,0, 0,1,0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw_axis();
    draw_objects();
  }

  glutSwapBuffers();
}

void procesar_hits(GLint hits, GLuint *names) {

  // cout << "Hits: " << hits << endl;
  //
	// for (int i = 0; i < hits; i++) {
	// 	cout << "Numero: " << names[i * 4] << endl;
  //
	// 	cout << "Min Z: " << names[i * 4 + 1] << endl;
	// 	cout << "Max Z: " << names[i * 4 + 2] << endl;
	// 	cout << "Nombre en la pila: " << names[i * 4 + 3] << endl;
  // }

	if (hits > 0) {
		if (names[0+3] == 1) {
      std::cout << "/* a */" << '\n';
			if (figura1_color_original) {
				figura1->set_color(0, 1, 0);
				figura1_color_original = false;
			} else {
				figura1->set_color(1, 0, 0);
				figura1_color_original = true;
			}
		} else if (names[0+3] == 2) {
      std::cout << "/* b */" << '\n';
			if (figura2_color_original) {
				figura1->set_color(0, 1, 0);
				figura2_color_original = false;
			} else {
				figura1->set_color(1, 0, 0);
				figura2_color_original = true;
			}
		}
	}
}

void pick(int x, int y) {
  cout << "PICK x=" << x << ",y=" << y << endl;

	GLuint selectBuf[100]={0};
	GLint viewport[4], hits=0;

	// Declarar buffer de selección
	glSelectBuffer(100, selectBuf);

	// Obtener los parámetros del viewport
	glGetIntegerv (GL_VIEWPORT, viewport);

	// Pasar OpenGL a modo selección
	rendermode = GL_SELECT;
	glRenderMode (GL_SELECT);
	glInitNames();
	glPushName(0);

	// Fijar la transformación de proyección para la selección
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix (x,(viewport[3] - y),5.0, 5.0, viewport);
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

	// Dibujar la escena
	draw_scene();

	// Pasar OpenGL a modo render
	hits = glRenderMode (GL_RENDER);

	// Restablecer la transformación de proyección
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

	// Procesar el contenido del buffer de selección
	procesar_hits(hits, selectBuf);

	// Dibujar la escena para actualizar cambios
  draw_scene();
}

void clickRaton(int boton, int estado, int x, int y) {
	if (boton == GLUT_LEFT_BUTTON) pick(x, y);
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1) {
  //change_projection();
  //glViewport(0,0,Ancho1,Alto1);

  ANCHO = Ancho1;
  ALTO = Alto1;
  glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y) {
  unsigned char key = toupper(Tecla1);

  if (key == 'Q') exit(0);

  if (key == 'P') {
    viMode = Puntos;
  } else if (key == 'T') {
    tapas = !tapas;
  } else if (key == '-') {
    factorPlanta = factorPlanta / 1.2;
  } else if (key == '+') {
    factorPlanta = factorPlanta * 1.2;
  } else if (key == 'J') {
    circulos = !circulos;
  } else if (key == 'L') {
    viMode = Aristas;
  } else if (key == 'F') {
    viMode = Solido;
  } else if (key == 'C') {
    viMode = Ajedrez;
  } else if (key == 'V') {
    viMode = Fade;
  } else if (key == '1') {
    objeto = Piramide;
  } else if (key == '2') {
    objeto = Cubo;
  } else if (key == '3') {
    string archivo;
    int n;

    cout << "[>] Ruta archivo de revolucion: ";
    cin >> archivo;
    cout << "[>] Numero de caras: ";
    cin >> n;
    cout << "Para quitar/poner tapas: 't'" << endl;

    if (revolucion != NULL) delete revolucion;

    revolucion = new _revolucion(archivo.c_str());
    ui.SetRevolucion(*revolucion, n, tapas);
    objeto = Revolucion;
  } else if (key == '4') {
    string archivo;

    cout << "[>] Ruta archivo: ";
    cin >> archivo;

    if (objetoPLY != NULL) delete objetoPLY;

    objetoPLY = new _objetoPLY(archivo.c_str());
    ui.SetPLY(*objetoPLY);
    objeto = PLY;
  } else if (key == '5') {
    objeto = BrazoRobot;
  } else if (key == '6') {
    if (!enEscena) {
      figura1 = new _cubo();
      figura2 = new _piramide();

      figura1->set_color(1, 0, 0);
      figura2->set_color(1, 0, 0);

      escena = new _triangulos3D[2];
      escena[0] = *figura1;
      escena[1] = *figura2;
      objetosEscena = 2;
    }

    enEscena = !enEscena;
  }

  glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************
void special_keys(int Tecla1,int x,int y) {
  switch (Tecla1){
  	case GLUT_KEY_LEFT:
      Observer_angle_y--;
      break;
  	case GLUT_KEY_RIGHT:
      Observer_angle_y++;
      break;
  	case GLUT_KEY_UP:
      Observer_angle_x--;
      break;
  	case GLUT_KEY_DOWN:
      Observer_angle_x++;
      break;
  	case GLUT_KEY_PAGE_UP:
      Observer_distance*=1.2;
      break;
  	case GLUT_KEY_PAGE_DOWN:
      Observer_distance/=1.2;
      break;
    case GLUT_KEY_F1:
      if (objeto == BrazoRobot) brazoRobot.MueveBase(5);
      break;
    case GLUT_KEY_F2:
      if (objeto == BrazoRobot) brazoRobot.MueveBase(-5);
      break;
    case GLUT_KEY_F3:
      if (objeto == BrazoRobot) brazoRobot.MueveBrazo(5);
      break;
    case GLUT_KEY_F4:
      if (objeto == BrazoRobot) brazoRobot.MueveBrazo(-5);
      break;
    case GLUT_KEY_F5:
      if (objeto == BrazoRobot) brazoRobot.MueveAntebrazo(5);
      break;
    case GLUT_KEY_F6:
      if (objeto == BrazoRobot) brazoRobot.MueveAntebrazo(-5);
      break;
    case GLUT_KEY_F7:
      if (objeto == BrazoRobot) {
        // for (float alfa = 0; alfa <= 360.0; alfa+=5) {
        //   brazoRobot.RotaHerramienta(alfa);
        //   cout << alfa << endl;
        //   glutPostRedisplay();
        //   usleep(100000);
        // }
        brazoRobot.RotaHerramienta(5);
      }
      break;
    case GLUT_KEY_F8:
      vista_multiple=1;
      break;
    case GLUT_KEY_F9:
      vista_multiple=0;
      break;
  }

  glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void) {
  // se inicalizan la ventana y los planos de corte
  Window_width=5;
  Window_height=5;
  Front_plane=10;
  Back_plane=1000;

  // se inicia la posicion del observador, en el eje z
  Observer_distance=2*Front_plane;
  Observer_angle_x=0;
  Observer_angle_y=0;

  // se indica cual sera el color para limpiar la ventana	(r,v,a,al)
  // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
  glClearColor(1,1,1,1);

  // se habilita el z-bufer
  glEnable(GL_DEPTH_TEST);
  //
  change_projection();
  //
  glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv) {
  // se llama a la inicialización de glut
  glutInit(&argc, argv);

  // se indica las caracteristicas que se desean para la visualización con OpenGL
  // Las posibilidades son:
  // GLUT_SIMPLE -> memoria de imagen simple
  // GLUT_DOUBLE -> memoria de imagen doble
  // GLUT_INDEX -> memoria de imagen con color indizado
  // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
  // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
  // GLUT_DEPTH -> memoria de profundidad o z-bufer
  // GLUT_STENCIL -> memoria de estarcido
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  // posicion de la esquina inferior izquierdad de la ventana
  glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

  // tamaño de la ventana (ancho y alto)
  glutInitWindowSize(UI_window_width,UI_window_height);

  // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
  // al bucle de eventos)
  glutCreateWindow("Practica 2");

  // asignación de la funcion llamada "dibujar" al evento de dibujo
  glutDisplayFunc(draw_scene);
  // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
  glutReshapeFunc(change_window_size);
  // asignación de la funcion llamada "tecla_normal" al evento correspondiente
  glutKeyboardFunc(normal_keys);
  // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
  glutSpecialFunc(special_keys);
  // Para el raton
  glutMouseFunc(clickRaton);

  // funcion de inicialización
  initialize();

  // inicio del bucle de eventos
  glutMainLoop();
  return 0;
}
