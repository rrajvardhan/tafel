#include "Window.hpp"
#include <QVBoxLayout>

Window::Window(QWidget* parent, int w, int h) : QWidget(parent)
{
  resize(w, h);

  canvas = new Canvas(this);

  auto* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(canvas);
}
