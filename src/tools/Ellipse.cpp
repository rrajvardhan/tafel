
#include "drawables/Shapes.hpp"
#include "tools/Ellipse.hpp"
#include <QMouseEvent>
#include <QPainter>

void
TEllipse::mousePress(QMouseEvent* event)
{
  if (event->button() != Qt::LeftButton)
    return;

  start      = canvas.toWorld(event->position());
  curr       = start;
  isDragging = true;
}

void
TEllipse::mouseMove(QMouseEvent* event)
{
  curr = canvas.toWorld(event->position());
  canvas.repaint();
}

void
TEllipse::mouseRelease(QMouseEvent* event)
{
  if (event->button() != Qt::LeftButton)
    return;

  isDragging = false;

  QPointF end = canvas.toWorld(event->position());

  canvas.addDrawable(std::make_unique<Ellipse>(start, end, canvas.pen(), canvas.brush()));
}

void
TEllipse::drawPreview(QPainter& painter)
{
  if (!isDragging)
    return;

  QRectF rect(start, curr);
  painter.setPen(canvas.pen());
  painter.setBrush(canvas.brush());
  painter.drawEllipse(rect.normalized());
}
