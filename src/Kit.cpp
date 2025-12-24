#include "Canvas.hpp"
#include "Kit.hpp"
#include "Line.hpp"
#include "Rect.hpp"
#include <QVBoxLayout>

Kit::Kit(Canvas* canvas, QWidget* parent) : QWidget(parent), canvas(canvas)
{
  button1 = new QPushButton("Rect", this);
  QObject::connect(button1,
                   &QPushButton::clicked,
                   [this, canvas]() { canvas->setTool(std::make_unique<TRect>()); });

  button2 = new QPushButton("Line", this);
  QObject::connect(button2,
                   &QPushButton::clicked,
                   [this, canvas]() { canvas->setTool(std::make_unique<TLine>()); });

  auto* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(button2);
  layout->addWidget(button1);
}
