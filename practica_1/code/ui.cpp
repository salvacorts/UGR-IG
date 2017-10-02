#include "./include/ui.h"

UI::UI(_piramide& p, _cubo& c) {
  this->piramide = &p;
  this->cubo = &c;
}

void UI::Muestra(TipoObjeto objeto, Visualizacion viMode) {
  const float r = 1.0; const float r2 = 0.0;
  const float g = 0.0; const float g2 = 1.0;
  const float b = 0.0; const float b2 = 0.0;
  const int grosor = 1;

  _triangulos3D* figura;

  if (objeto == Cubo) {
    figura = this->cubo;
  } else {
    figura = this->piramide;
  }

  switch (viMode) {
    case Puntos:
      figura->draw_puntos(r, g, b, grosor);
      break;
    case Aristas:
      figura->draw_aristas(r, g, b, grosor);
      break;
    case Solido:
      figura->draw_solido(r, g, b);
      break;
    case Ajedrez:
      figura->draw_solido_ajedrez(r, g, b, r2, g2, b2);
      break;
  }
}
