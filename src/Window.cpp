#include "Window.hpp"

Window::Window(QWidget* parent, int w, int h) : QWidget(parent)
{
  setFixedSize(w, h); // later, make it resize();

  canvas = new Canvas(this);
  canvas->setGeometry(rect());
}
