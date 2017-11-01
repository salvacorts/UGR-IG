//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include "file_ply_stl.h"
#include <stdlib.h>
#include <cmath>

using namespace std;

//*************************************************************************
// clase punto
//*************************************************************************
class _puntos3D {
public:
  vector<_vertex3f> vertices;
  vector<_vertex3f> colores;

  _puntos3D();
  void 	draw_puntos(float color[3], int grosor);

protected:
  void AddRandColors();

  inline double DoubRand() {
    return 1/((double) (rand()%10));
  }
};

//*************************************************************************
// clase triángulo
//*************************************************************************
class _triangulos3D : public _puntos3D {
private:
  void draw_circulo(float radio, float x, float y, float z, int n, float color[3]);

public:
  vector<_vertex3i> caras;

	_triangulos3D();
  void draw_color_vertices();
  void draw_circulos_vertices(float radio, int resolucion, float color[3]);
  void draw_aristas(float color[3], int grosor);
  void draw_solido(float color[3]);
  void draw_solido_ajedrez(float color1[3], float color2[3]);
};


//*************************************************************************
// clase cubo
//*************************************************************************
class _cubo : public _triangulos3D {
public:
	_cubo(float tam=1);
};


//*************************************************************************
// clase piramide
//*************************************************************************
class _piramide : public _triangulos3D {
public:
	_piramide(float tam=1, float al=1.75);
};

//*************************************************************************
// clase Objeto PLY
//*************************************************************************
class _objetoPLY : public _triangulos3D {
public:
  _objetoPLY(const char archivo[]);
};

//*************************************************************************
// clase Objeto Por Revolucion
//*************************************************************************
class _revolucion : public _objetoPLY {
private:
  vector<_vertex3f> perfil;
  bool tapas = false;
  int n = 10;
public:
  _revolucion(const char ferfil[]);
  void parametros(bool tapas, int num);

  inline bool getTapas() {
    return tapas;
  }

  inline int getNumCaras() {
    return n;
  }
};

class _brazoRobot : public _triangulos3D {
private:
  _cubo base;
  _cubo brazo;
  _cubo antebrazo;

  float alfaBase = 0;
  float alfaBrazo = 0;
  float alfaAntebrazo = 0;

  void DrawBase();
  void DrawBrazo();
  void DrawAntebrazo();

public:
  void Draw();
  void MueveBase(float alfa);
  void MueveBrazo(float alfa);
  void MueveAntebrazo(float alfa);
};
