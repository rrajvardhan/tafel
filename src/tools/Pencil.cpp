#include "drawables/Path.hpp"
#include "tools/Pencil.hpp"
#include <QMouseEvent>
#include <QPainter>

void
TPencil::mousePress(QMouseEvent* event)
{
  path      = QPainterPath(canvas.toWorld(event->position()));
  isDrawing = true;
}

void
TPencil::mouseMove(QMouseEvent* event)
{
  if (!isDrawing)
    return;

  path.lineTo(canvas.toWorld(event->position()));
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
