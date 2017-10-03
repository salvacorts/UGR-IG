#include "objetos.h"

enum TipoObjeto {Cubo, Piramide};

enum Visualizacion {Puntos, Aristas, Solido, Ajedrez};

class UI {
public:
  _cubo* cubo;
  _piramide* piramide;

  UI(_piramide& p, _cubo& c);
  void Muestra(TipoObjeto objeto, Visualizacion viMode, bool circulos=false);
};
