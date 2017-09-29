#include "./include/ui.h"

UI::UI(_piramide& p, _cubo& c) {
  this->piramide = &p;
  this->cubo = &c;
}

void UI::Muestra(TipoObjeto objeto, Visualizacion viMode) {
  const float r = 0.0;
  const float g = 0.0;
  const float b = 0.0;
  const int grosor = 1;

  _triangulos3D* figura;

  if (objeto == TipoObjeto::cubo) {
    figura = this->cubo;
  } else {
    figura = this->piramide;
  }

  switch (viMode) {
    case Visualizacion::puntos:
      figura->draw_puntos(r, g, b, grosor);
      break;
    case Visualizacion::aristas:
      figura->draw_aristas(r, g, b, grosor);
      break;
    case Visualizacion::solido:
      figura->draw_solido(r, g, b);
    case Visualizacion::ajedrez:
      figura->draw_solido_ajedrez(r, g, b, r, g, b);
  }
}
