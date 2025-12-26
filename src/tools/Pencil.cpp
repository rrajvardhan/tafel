
#include "Drawable.hpp"
#include "tools/Pencil.hpp"
#include <QMouseEvent>
#include <QPainter>

void
TPencil::mousePress(QMouseEvent* event)
{
  path      = QPainterPath(event->pos());
  isDrawing = true;
}

void
TPencil::mouseMove(QMouseEvent* event)
{
  if (!isDrawing)
    return;

  path.lineTo(event->pos());
  canvas.repaint();
}

void
TPencil::mouseRelease(QMouseEvent* event)
{
  if (!isDrawing)
    return;

  isDrawing = false;

  canvas.addDrawable(std::make_unique<Path>(path, canvas.pen()));
}

void
TPencil::drawPreview(QPainter& painter)
{
  if (!isDrawing)
    return;

  painter.setPen(canvas.pen());
  painter.drawPath(path);
}
