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

  QPainterPath closedPath = path;
  if (closedPath.elementCount() > 0)
  {
    closedPath.closeSubpath();
  }

  QPen pen(Qt::gray, size, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);
  painter.drawPath(closedPath);
}
