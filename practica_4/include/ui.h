#include "objetos.h"

class UI {
public:
  _brazoRobot* brazoRobot;
  _revolucion* revolucion;
  _piramide* piramide;
  _objetoPLY* objeto;
  _cubo* cubo;

  UI(_piramide& p, _cubo& c, _brazoRobot& b);
  void SetPLY(_objetoPLY& o);
  void SetRevolucion(_revolucion& revolucion, int n, bool tapas=false);
  void Muestra(TipoObjeto objeto, Visualizacion viMode, Iluminacion ilum, bool circulos=false, bool tapas=false);
};
