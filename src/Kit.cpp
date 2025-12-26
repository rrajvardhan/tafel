#include "Canvas.hpp"
#include "Ellipse.hpp"
#include "Erasor.hpp"
#include "Kit.hpp"
#include "Line.hpp"
#include "Pencil.hpp"
#include "Rect.hpp"
#include <QHBoxLayout>
#include <QSizePolicy>

Kit::Kit(Canvas* canvas) : canvas(canvas), QWidget(canvas)
{

  button1 = new QPushButton("Line", this);
  QObject::connect(button1,
                   &QPushButton::clicked,
                   [this, canvas]() { canvas->activateTool(std::make_unique<TLine>(*canvas)); });

  button2 = new QPushButton("Pencil", this);
  QObject::connect(button2,
                   &QPushButton::clicked,
                   [this, canvas]() { canvas->activateTool(std::make_unique<TPencil>(*canvas)); });

  button3 = new QPushButton("Ersor", this);
  QObject::connect(button3,
                   &QPushButton::clicked,
                   [this, canvas]() { canvas->activateTool(std::make_unique<TEraser>(*canvas)); });

  const int size = 64;

  for (auto* b : { button1, button2, button3 })
  {
    b->setFixedSize(size, size);
    b->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  }

  auto* layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(4);
  layout->setAlignment(Qt::AlignCenter);

  layout->addWidget(button1);
  layout->addWidget(button2);
  layout->addWidget(button3);
}
