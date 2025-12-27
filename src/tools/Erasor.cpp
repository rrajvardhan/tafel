#include "Erasor.hpp"

void
TEraser::mousePress(QMouseEvent* event)
{
  path      = QPainterPath(event->pos());
  isErasing = true;
}

void
TEraser::mouseMove(QMouseEvent* event)
{
  if (!isErasing)
    return;

  path.lineTo(event->pos());
  canvas.repaint();
}

void
TEraser::mouseRelease(QMouseEvent* event)
{
  if (!isErasing)
    return;

  isErasing = false;
  canvas.erase(path);
}

void
TEraser::drawPreview(QPainter& painter)
{
  if (!isErasing)
    return;

  QPen pen(Qt::gray, size, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);
  painter.drawPath(path);
}
