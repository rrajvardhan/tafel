#include "tools/Rect.hpp"

void
TRect::mousePress(QMouseEvent* event)
{
  start      = event->pos();
  isDragging = true;
}

void
TRect::mouseMove(QMouseEvent* event)
{
  curr = event->pos();

  width  = curr.x() - start.x();
  height = curr.y() - start.y();

  if (canvas)
  {
    canvas->repaint();
  }
}

void
TRect::mouseRelease(QMouseEvent* event)
{
  isDragging = false;

  if (canvas)
  {
    QPen   currentPen   = canvas->pen();
    QBrush currentBrush = canvas->brush();
    canvas->addDrawable(std::make_unique<Rect>(start, width, height, currentPen, currentBrush));
  }
  width  = 0;
  height = 0;
}

void
TRect::drawPreview(QPainter& painter)
{
  if (false == isDragging)
    return;

  painter.setPen(canvas->pen());
  painter.setBrush(canvas->brush());

  painter.drawRect(start.x(), start.y(), width, height);
}
