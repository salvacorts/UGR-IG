#include "objetos.h"

enum TipoObjeto {cubo, piramide};

enum Visualizacion {puntos, aristas, solido, ajedrez};

class UI {
public:
  _cubo* cubo;
  _piramide* piramide;

  UI(_piramide& p, _cubo& c);
  void Muestra(TipoObjeto objeto, Visualizacion viMode);
};
