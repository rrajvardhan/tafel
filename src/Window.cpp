#include "Kit.hpp"
#include "Window.hpp"
#include <QVBoxLayout>
#include <QWidget>

Window::Window(QWidget* parent, int w, int h) : QWidget(parent)
{
  setFixedSize(w, h); // later, make it resize();

  canvas = new Canvas(this);
  kit    = new Kit(canvas, this);

  auto* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(kit);
  layout->addWidget(canvas);

  setLayout(layout);
}
