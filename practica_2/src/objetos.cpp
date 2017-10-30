#include "objetos.h"
#include <climits>

// Objeto _puntos3D //

_puntos3D::_puntos3D() {}

void _puntos3D::draw_puntos(float color[3], int grosor) {
  glPointSize(grosor);
  glColor3f(color[0], color[1], color[2]);

  glBegin(GL_POINTS);

    for (int i = 0; i < vertices.size(); ++i) {
      _vertex3f v = vertices[i];
      glVertex3f(v.x, v.y, v.z);
    }

  glEnd();
}

void _puntos3D::AddRandColors() {
  colores.resize(vertices.size());

  for (int i = 0; i < colores.size(); ++i) {
    colores[i].r = DoubRand();
    colores[i].g = DoubRand();
    colores[i].b = DoubRand();
  }
}


// Objeto _triangulos3D //

_triangulos3D::_triangulos3D() {}

void _triangulos3D::draw_color_vertices() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glShadeModel(GL_SMOOTH);
  glBegin(GL_TRIANGLES);

    for (int i = 0; i < caras.size(); ++i) {
      int v1=caras[i]._0, v2=caras[i]._1, v3=caras[i]._2;

      glColor3f(colores[v1].r, colores[v1].g, colores[v1].b);
      glVertex3f(vertices[v1].x, vertices[v1].y, vertices[v1].z);

      glColor3f(colores[v2].r, colores[v2].g, colores[v2].b);
      glVertex3f(vertices[v2].x, vertices[v2].y, vertices[v2].z);

      glColor3f(colores[v3].r, colores[v3].g, colores[v3].b);
      glVertex3f(vertices[v3].x, vertices[v3].y, vertices[v3].z);
    }

  glEnd();
  glShadeModel(GL_FLAT);
}

void _triangulos3D::draw_circulos_vertices(float radio, int resolucion, float color[3]) {
  for (int i = 0; i < vertices.size(); ++i) {
    draw_circulo(radio, vertices[i].x, vertices[i].y, vertices[i].z, resolucion, color);
  }
}

void _triangulos3D::draw_circulo(float radio, float x, float y, float z, int n, float color[3]) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(color[0], color[1], color[2]);

  glBegin(GL_POLYGON);
    for (int i = 0; i < n; ++i) {
      glVertex3f(x+radio*cosf(2.0*M_PI*i/n), y+radio*sinf(2.0*M_PI*i/n), z);
    }
  glEnd();

}

void _triangulos3D::draw_aristas(float color[3], int grosor) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPointSize(grosor);
  glColor3f(color[0], color[1], color[2]);

  glBegin(GL_TRIANGLES);
    for (int i = 0; i < caras.size(); ++i) {
      int v1=caras[i]._0, v2=caras[i]._1, v3=caras[i]._2;
      glVertex3f(vertices[v1].x, vertices[v1].y, vertices[v1].z);
      glVertex3f(vertices[v2].x, vertices[v2].y, vertices[v2].z);
      glVertex3f(vertices[v3].x, vertices[v3].y, vertices[v3].z);
    }

  glEnd();
}

void _triangulos3D::draw_solido(float color[3]) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(color[0], color[1], color[2]);

  glBegin(GL_TRIANGLES);

    for (int i = 0; i < caras.size(); ++i) {
      int v1=caras[i]._0, v2=caras[i]._1, v3=caras[i]._2;
      glVertex3f(vertices[v1].x, vertices[v1].y, vertices[v1].z);
      glVertex3f(vertices[v2].x, vertices[v2].y, vertices[v2].z);
      glVertex3f(vertices[v3].x, vertices[v3].y, vertices[v3].z);
    }

  glEnd();
}

void _triangulos3D::draw_solido_ajedrez(float color1[3], float color2[3]) {
  int r, g, b;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);

    for (int i = 0; i < caras.size(); ++i) {
      int v1=caras[i]._0, v2=caras[i]._1, v3=caras[i]._2;

      if (i % 2 == 0) {
        r = color1[0]; g = color1[1]; b = color1[2];
      } else {
        r = color2[0]; g = color2[1]; b = color2[2];
      }

      glColor3f(r, g, b);
      glVertex3f(vertices[v1].x, vertices[v1].y, vertices[v1].z);
      glVertex3f(vertices[v2].x, vertices[v2].y, vertices[v2].z);
      glVertex3f(vertices[v3].x, vertices[v3].y, vertices[v3].z);
    }

  glEnd();
}


// Objeto _cubo //
_cubo::_cubo(float tam) {
  // Vertices (da igual sentido horario o antihorario)
  vertices.resize(8);
  vertices[0]; vertices[0].x=0; vertices[0].y=0; vertices[0].z=tam;
  vertices[1]; vertices[1].x=0; vertices[1].y=0; vertices[1].z=0;
  vertices[2]; vertices[2].x=tam; vertices[2].y=0; vertices[2].z=0;
  vertices[3]; vertices[3].x=tam; vertices[3].y=0; vertices[3].z=tam;
  vertices[4]; vertices[4].x=tam; vertices[4].y=tam; vertices[4].z=tam;
  vertices[5]; vertices[5].x=0; vertices[5].y=tam; vertices[5].z=tam;
  vertices[6]; vertices[6].x=0; vertices[6].y=tam; vertices[6].z=0;
  vertices[7]; vertices[7].x=tam; vertices[7].y=tam; vertices[7].z=0;

  // Caras de dos triangulos (12 total) (los vertices tienen que ir en sentido antihorario)
  caras.resize(12);
  caras[0]; caras[0]._0=0; caras[0]._1=3; caras[0]._2=5;
  caras[1]; caras[1]._0=3; caras[1]._1=4; caras[1]._2=5;
  caras[2]; caras[2]._0=4; caras[2]._1=6; caras[2]._2=5;
  caras[3]; caras[3]._0=4; caras[3]._1=7; caras[3]._2=6;
  caras[4]; caras[4]._0=3; caras[4]._1=7; caras[4]._2=4;
  caras[5]; caras[5]._0=2; caras[5]._1=7; caras[5]._2=3;
  caras[6]; caras[6]._0=3; caras[6]._1=2; caras[6]._2=1;
  caras[7]; caras[7]._0=0; caras[7]._1=3; caras[7]._2=1;
  caras[8]; caras[8]._0=1; caras[8]._1=5; caras[8]._2=6;
  caras[9]; caras[9]._0=1; caras[9]._1=0; caras[9]._2=5;
  caras[10]; caras[10]._0=1; caras[10]._1=7; caras[10]._2=2;
  caras[11]; caras[11]._0=1; caras[11]._1=6; caras[11]._2=7;

  // Colores
  colores.resize(8);
  colores[0].r = 0.1; colores[0].g = 0.7; colores[0].b = 0.5;
  colores[1].r = 0.5; colores[1].g = 0.1; colores[1].b = 0.9;
  colores[2].r = 0.8; colores[2].g = 0.4; colores[2].b = 0.2;
  colores[3].r = 0.2; colores[3].g = 0.9; colores[3].b = 0.9;
  colores[4].r = 0.6; colores[4].g = 0.8; colores[4].b = 0.3;
  colores[5].r = 0.2; colores[5].g = 0.9; colores[5].b = 0.5;
  colores[6].r = 0.9; colores[6].g = 0.7; colores[6].b = 0.5;
  colores[7].r = 0.4; colores[7].g = 0.2; colores[7].b = 0.7;
}


// Objeto _piramide //
_piramide::_piramide(float tam, float al) {
  // vertices
  vertices.resize(5);
  vertices[0]; vertices[0].x=-tam; vertices[0].y=0; vertices[0].z=tam;
  vertices[1]; vertices[1].x=tam; vertices[1].y=0; vertices[1].z=tam;
  vertices[2]; vertices[2].x=tam; vertices[2].y=0; vertices[2].z=-tam;
  vertices[3]; vertices[3].x=-tam; vertices[3].y=0; vertices[3].z=-tam;
  vertices[4]; vertices[4].x=0; vertices[4].y=al; vertices[4].z=0;

  // Caras
  // las caras estan compuestas de tres vertices
  // los vertices se recorren en sentido antihorario
  // se buscan en el vector vertices
  caras.resize(6);
  caras[0]; caras[0]._0=0; caras[0]._1=1; caras[0]._2=4;
  caras[1]; caras[1]._0=1; caras[1]._1=2; caras[1]._2=4;
  caras[2]; caras[2]._0=2; caras[2]._1=3; caras[2]._2=4;
  caras[3]; caras[3]._0=3; caras[3]._1=0; caras[3]._2=4;
  caras[4]; caras[4]._0=3; caras[4]._1=1; caras[4]._2=0;
  caras[5]; caras[5]._0=3; caras[5]._1=2; caras[5]._2=1;

  // Colores
  colores.resize(5);
  colores[0].r = 0.1; colores[0].g = 0.7; colores[0].b = 0.5;
  colores[1].r = 0.5; colores[1].g = 0.1; colores[1].b = 0.9;
  colores[2].r = 0.8; colores[2].g = 0.4; colores[2].b = 0.2;
  colores[3].r = 0.2; colores[3].g = 0.9; colores[3].b = 0.9;
  colores[4].r = 0.6; colores[4].g = 0.8; colores[4].b = 0.3;
}


// Objeto PLY
_objetoPLY::_objetoPLY(const char archivo[]) {
  _file_ply File_ply;

  if (File_ply.open(archivo)) {
    File_ply.read(vertices, caras);
    cout << "[+] " << archivo << " readed" << endl;

    colores.resize(vertices.size());

    AddRandColors();
  }
}

// Objeto por revolucion
_revolucion::_revolucion(const char perfil[])  : _objetoPLY(perfil) {
  this->perfil = vertices;
}

void _revolucion::parametros(bool tapas, int num) {
  int pts_perfil = perfil.size();
  _vertex3f vertice_aux;
  _vertex3i cara_aux;

  // Necesario para el Get() de ambos parametros para ver si hay cambios
  this->n = num;
  this->tapas = tapas;

  vertices.resize(pts_perfil*n);
  caras.clear();  // Si no se limpia, una vez que hay tapas, ahi se quedan

  // Crea los vertices
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < pts_perfil; i++) {
      double alpha = 2.0*M_PI*j/(1.0*n);

      vertice_aux.x = perfil[i].x*cosf(alpha) + perfil[i].z*sinf(alpha);
      vertice_aux.z = perfil[i].x*sinf(alpha) + perfil[i].z*cos(alpha);
      vertice_aux.y = perfil[i].y;

      vertices[i+j*pts_perfil] = vertice_aux;
    }
  }

  // Caras:
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < pts_perfil-1; i++) {
      cara_aux._0 = i + ((j+1)%n)*pts_perfil;
      cara_aux._1 = i + 1 + ((j+1)%n)*pts_perfil;
      cara_aux._2 = i + 1 + j*pts_perfil;
      caras.push_back(cara_aux);

      cara_aux._0 = i + 1 + j*pts_perfil;
      cara_aux._0 = i + j*pts_perfil;
      cara_aux._1 = i + ((j+1)%n)*pts_perfil;
      caras.push_back(cara_aux);
    }
  }

  // TODO: Calculas el punto mas alto y el mas bajo
  if (tapas) {
    // _vertex3f pt_superior, pt_inferior;
    // int y_min = INT_MAX;
    // int y_max = INT_MIN;
    //
    // // Busca la cara mas alta y la mas baja
    // for (int i = 0; i < perfil.size(); i++) {
    //   if (perfil[i].y < y_min) {
    //     pt_inferior = perfil[i];
    //     y_min = perfil[i].y;
    //   }
    //
    //   if (perfil[i].y > y_max) {
    //     pt_superior = perfil[i];
    //     y_max = perfil[i].y;
    //   }
    // }

    // Tapa Inferior
    if (fabs(perfil[0].x) > 0.0) {
      vertice_aux.x = 0.0;
      vertice_aux.y = perfil[0].y;
      vertice_aux.z = 0.0;
      vertices.push_back(vertice_aux);

      cara_aux._0 = pts_perfil*n;

      for (int i = 0; i < n; i++) {
        cara_aux._1 = ((i+1)%n)*pts_perfil;
        cara_aux._2 = i*pts_perfil;

        caras.push_back(cara_aux);
      }
    }

    // Tapa superior
    if (fabs(perfil[pts_perfil-1].x) > 0.0) {
      vertice_aux.x = 0.0;
      vertice_aux.y = perfil[pts_perfil-1].y;
      vertice_aux.z = 0.0;
      vertices.push_back(vertice_aux);

      cara_aux._0 = pts_perfil*n+1;

      for (int i = 0; i < n; i++) {
        cara_aux._1 = (i+1)*pts_perfil-1;
        cara_aux._2 = ((i+1)%n)*pts_perfil + pts_perfil-1,

        caras.push_back(cara_aux);
      }
    }
  }

  AddRandColors();
}

_cilindro::_cilindro() {
  profile = {{0,-5,0},{2,-5,0},{2,5,0},{0,5,0}};
}
