
#include "Drawable.hpp"
#include "tools/Ellipse.hpp"
#include <QMouseEvent>
#include <QPainter>

void
TEllipse::mousePress(QMouseEvent* event)
{
  start      = event->pos();
  curr       = start;
  isDragging = true;
}

void
TEllipse::mouseMove(QMouseEvent* event)
{
  curr = event->pos();
  canvas.repaint();
}

void
TEllipse::mouseRelease(QMouseEvent* event)
{
  isDragging = false;

  canvas.addDrawable(std::make_unique<Ellipse>(start, event->pos(), canvas.pen(), canvas.brush()));
}

void
TEllipse::drawPreview(QPainter& painter)
{
  if (!isDragging)
    return;

  QRect rect(start, curr);
  painter.setPen(canvas.pen());
  painter.setBrush(canvas.brush());
  painter.drawEllipse(rect.normalized());
}
