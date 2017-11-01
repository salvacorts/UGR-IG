#include "ui.h"

UI::UI(_piramide& p, _cubo& c, _brazoRobot& b) {
  this->brazoRobot = &b;
  this->piramide = &p;
  this->cubo = &c;
}

void UI::SetPLY(_objetoPLY& o) {
  this->objeto = &o;
}

void UI::SetRevolucion(_revolucion& revolucion, int n, bool tapas) {
  this->revolucion = &revolucion;
  this->revolucion->parametros(tapas, n);
}

void UI::Muestra(TipoObjeto objeto, Visualizacion viMode, bool circulos, bool tapas) {
  float color1[] = {1.0, 0.0, 0.0};
  float color2[] = {0.0, 1.0, 0.0};
  float color3[] = {0.0, 0.0, 1.0};
  const int grosor = 1;

  _triangulos3D* figura;

  if (circulos) figura->draw_circulos_vertices(0.1, 8, color3);

  if (objeto == PLY && this->objeto != NULL) {
    figura = this->objeto;
  } else if (objeto == Revolucion) {
    figura = this->revolucion;

    if (this->revolucion->getTapas() != tapas) {
      this->revolucion->parametros(tapas, this->revolucion->getNumCaras());
    }
  } else if (objeto == BrazoRobot) {
    figura = this->brazoRobot;

    this->brazoRobot->Draw();
    return; // No tiene sentido hacer el switch
  } else if (objeto == Cubo) {
    figura = this->cubo;
  } else {
    figura = this->piramide;
  }

  switch (viMode) {
    case Puntos:
      figura->draw_puntos(color1, grosor);
      break;
    case Aristas:
      figura->draw_aristas(color1, grosor);
      break;
    case Solido:
      figura->draw_solido(color1);
      break;
    case Ajedrez:
      figura->draw_solido_ajedrez(color1, color2);
      break;
    case Fade:
      figura->draw_color_vertices();
      break;
  }
}
