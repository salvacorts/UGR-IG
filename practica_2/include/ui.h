#include "objetos.h"

enum TipoObjeto {Cubo, Piramide, PLY};

enum Visualizacion {Puntos, Aristas, Solido, Ajedrez, Fade};

class UI {
public:
  _cubo* cubo;
  _piramide* piramide;
  _objetoPLY* objeto;

  UI(_piramide& p, _cubo& c);
  void SetPLY(_objetoPLY& o);
  void Muestra(TipoObjeto objeto, Visualizacion viMode, bool circulos=false);
};
