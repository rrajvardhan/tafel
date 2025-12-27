#include "drawables/Shapes.hpp"
#include "tools/Line.hpp"

void
TLine::mousePress(QMouseEvent* event)
{
  start      = canvas.toWorld(event->position());
  isDragging = true;
}

void
TLine::mouseMove(QMouseEvent* event)
{
  curr = canvas.toWorld(event->position());
  canvas.repaint();
}

void
TLine::mouseRelease(QMouseEvent* event)
{
  isDragging  = false;
  QPointF end = canvas.toWorld(event->position());
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
