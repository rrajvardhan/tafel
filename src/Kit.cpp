#include "Canvas.hpp"
#include "Ellipse.hpp"
#include "Erasor.hpp"
#include "Kit.hpp"
#include "Line.hpp"
#include "Pan.hpp"
#include "Pencil.hpp"
#include "Rect.hpp"
#include "Selection.hpp"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>

Kit::Kit(Canvas* canvas) : canvas(canvas), QWidget(canvas)
{
  setObjectName("Kit");

  Buttons tools[] = {
    { "Select", ":/icons/select_arrow.svg", makeTool<TSelect> },
    { "Pencil", ":/icons/pencil.svg", makeTool<TPencil> },
    { "Line", ":/icons/line.svg", makeTool<TLine> },
    { "Rectangle", ":/icons/rect.svg", makeTool<TRect> },
    { "Ellipse", ":/icons/ellipse.svg", makeTool<TEllipse> },
    { "Eraser", ":/icons/eraser.svg", makeTool<TEraser> },
    { "Pan", ":/icons/hand.svg", makeTool<TPan> },
  };

  auto* layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(4);
  layout->setAlignment(Qt::AlignCenter);

  auto* group = new QButtonGroup(this);
  group->setExclusive(true);

  for (auto& tb : tools)
  {
    auto* b = new QPushButton(this);
    b->setCheckable(true);
    b->setIcon(QIcon(tb.icon));
    b->setToolTip(tb.tooltip);
    b->setIconSize(QSize(32, 32));
    b->setFixedSize(80, 80);
    layout->addWidget(b);
    group->addButton(b);

    connect(b,
            &QPushButton::toggled,
            this,
            [this, tool = tb.tool](bool checked)
            {
              if (checked)
              {
                this->canvas->activateTool(tool(this->canvas));
              }
            });
  }
}
