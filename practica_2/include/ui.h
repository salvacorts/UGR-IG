#include "objetos.h"

enum TipoObjeto {Cubo, Piramide, PLY, Revolucion, Cilindro};

enum Visualizacion {Puntos, Aristas, Solido, Ajedrez, Fade};

class UI {
public:
  _revolucion* revolucion;
  _piramide* piramide;
  _objetoPLY* objeto;
  _cubo* cubo;

  UI(_piramide& p, _cubo& c);
  void SetPLY(_objetoPLY& o);
  void SetRevolucion(_revolucion& revolucion, int n, bool tapas=false);
  void Muestra(TipoObjeto objeto, Visualizacion viMode, bool circulos=false, bool tapas=false);
};
