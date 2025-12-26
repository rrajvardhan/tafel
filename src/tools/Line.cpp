#include "Drawable.hpp"
#include "tools/Line.hpp"

void
TLine::mousePress(QMouseEvent* event)
{
  start      = event->pos();
  isDragging = true;
}

void
TLine::mouseMove(QMouseEvent* event)
{
  curr = event->pos();
  canvas.repaint();
}

void
TLine::mouseRelease(QMouseEvent* event)
{
  isDragging = false;
  canvas.addDrawable(std::make_unique<Line>(start, event->pos(), canvas.pen()));
}

void
TLine::drawPreview(QPainter& painter)
{
  if (!isDragging)
    return;

  painter.setPen(canvas.pen());
  painter.drawLine(start, curr);
}
