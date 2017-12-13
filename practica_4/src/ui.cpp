#include "ui.h"

UI::UI(_piramide& p, _cubo& c, _brazoRobot& b) {
  this->brazoRobot = &b;
  this->piramide = &p;
  this->cubo = &c;
}

void UI::SetTextura(_imagen& i) {
  this->textura = &i;
}

void UI::SetPLY(_objetoPLY& o) {
  this->objeto = &o;
}

void UI::SetRevolucion(_revolucion& revolucion, int n, bool tapas) {
  this->revolucion = &revolucion;
  this->revolucion->parametros(tapas, n);
}

void UI::Muestra(TipoObjeto objeto, Visualizacion viMode, Iluminacion ilu, Material material, bool circulos, bool tapas) {
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
    this->brazoRobot->Draw(viMode);
    return; // No tiene sentido hacer el switch
  } else if (objeto == Textura) {
    this->textura->draw();
    return;
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
    
    switch (material) {
      case Oro:
        figura->ambiente_difusa = {0.24725, 0.2245, 0.0645, 1.0};
        figura->especular = {0.797357, 0.723991, 0.208006, 1.0};
        figura->brillo = 83.2;
        break;
      case Obsidiana:
        figura->ambiente_difusa = {0.05375, 0.05, 0.06625, 0.82};
        figura->especular = {0.332741, 0.328634, 0.346435, 0.82};
        figura->brillo = 38.4;
        break;
      case Esmeralda:
        figura->ambiente_difusa = {0.0215, 0.1745, 0.0215, 0.55};
        figura->especular = {0.633, 0.727811, 0.633, 0.55};
        figura->brillo = 76.8;
        break;
    }

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
