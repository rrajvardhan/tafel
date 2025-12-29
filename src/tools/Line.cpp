#include "drawables/Shapes.hpp"
#include "tools/Line.hpp"

void
TLine::mousePress(QMouseEvent* event)
{

  if (event->button() != Qt::LeftButton)
    return;

  start      = canvas.toWorld(event->pos());
  curr       = start;
  isDragging = true;
}

void
TLine::mouseMove(QMouseEvent* event)
{
  curr = canvas.toWorld(event->pos());
  canvas.repaint();
}

void
TLine::mouseRelease(QMouseEvent* event)
{
  if (event->button() != Qt::LeftButton)
    return;

  isDragging  = false;
  QPointF end = canvas.toWorld(event->position());

  if (start == curr)
    return;

  canvas.addDrawable(std::make_unique<Line>(start, end, canvas.pen()));
}

void
TLine::drawPreview(QPainter& painter)
{
  if (!isDragging)
    return;

  painter.setPen(canvas.pen());
  painter.drawLine(start, curr);
}
