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

void UI::Muestra(TipoObjeto objeto, Visualizacion viMode, Iluminacion ilu, bool circulos, bool tapas) {
  float color1[] = {1.0, 0.0, 0.0};
  float color2[] = {0.0, 1.0, 0.0};
  float color3[] = {0.0, 0.0, 1.0};
  const int grosor = 1;

  _triangulos3D* figura;

  if (objeto == PLY && this->objeto != NULL) {
    figura = this->objeto;
  } else if (objeto == Revolucion) {
    figura = this->revolucion;

    if (this->revolucion->getTapas() != tapas) {
      this->revolucion->parametros(tapas, this->revolucion->getNumCaras());
    }
  } else if (objeto == BrazoRobot) {
    figura = this->brazoRobot;

    this->brazoRobot->Draw(viMode);
    return; // No tiene sentido hacer el switch
  } else if (objeto == Cubo) {
    figura = this->cubo;
  } else {
    figura = this->piramide;
  }

  if (viMode == Puntos) {
    figura->draw_puntos(color1, grosor);
  } else if (viMode == Aristas) {
    figura->draw_aristas(color1, grosor);
  } else if (viMode == Solido) {
    figura->draw_solido(color1);
  } else if (viMode == Ajedrez) {
    figura->draw_solido_ajedrez(color1, color2);
  } else if (viMode == Fade) {
    figura->draw_color_vertices();
  } else if (viMode == Light || viMode == LightMoving) {
    figura->ambiente_difusa = {0.24725, 0.2245, 0.0645, 1.0};
    figura->especular = {0.4, 0.4, 0.4, 0.5};
    figura->brillo = 0.5;

    switch (ilu) {
      case Plana:
        cout << "Iluminación Plana" << endl;
        figura->draw_iluminacion_plana();
        break;
      case Suave:
        cout << "Iluminación Suave" << endl;
        figura->draw_iluminacion_suave();
        break;
    }
  }

  if (circulos) figura->draw_circulos_vertices(0.1, 8, color3);
}
