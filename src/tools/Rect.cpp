#include "drawables/Shapes.hpp"
#include "tools/Rect.hpp"

void
TRect::mousePress(QMouseEvent* event)
{
  start      = canvas.toWorld(event->position());
  isDragging = true;
}

void
TRect::mouseMove(QMouseEvent* event)
{
  curr = canvas.toWorld(event->position());
  canvas.repaint();
}

void
TRect::mouseRelease(QMouseEvent* event)
{
  isDragging = false;

  QPen   currentPen   = canvas.pen();
  QBrush currentBrush = canvas.brush();

  canvas.addDrawable(std::make_unique<Rect>(start, curr, currentPen, currentBrush));
}

void
TRect::drawPreview(QPainter& painter)
{
  if (!isDragging)
    return;

  painter.setPen(canvas.pen());
  painter.setBrush(canvas.brush());

  int width  = curr.x() - start.x();
  int height = curr.y() - start.y();

  painter.drawRect(start.x(), start.y(), width, height);
}
