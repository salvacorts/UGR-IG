#include "objetos.h"

class UI {
public:
  _brazoRobot* brazoRobot;
  _revolucion* revolucion;
  _piramide* piramide;
  _objetoPLY* objeto;
  _cubo* cubo;
  _triangulos3D **escena;
  int objetosEscena;

  UI(_piramide& p, _cubo& c, _brazoRobot& b);
  void SetEscena(_triangulos3D* escena[], int objetosEscena);
  void SetPLY(_objetoPLY& o);
  void SetRevolucion(_revolucion& revolucion, int n, bool tapas=false);
  void Muestra(TipoObjeto objeto, Visualizacion viMode, _triangulos3D* escena[], int objetosEscena, bool circulos, bool tapas, bool enEscena);
};
