#include "drawables/Path.hpp"
#include "tools/Pencil.hpp"
#include <QMouseEvent>
#include <QPainter>

void
TPencil::mousePress(QMouseEvent* event)
{

  if (event->button() != Qt::LeftButton)
    return;

  path      = QPainterPath(canvas.toWorld(event->position()));
  isDrawing = true;
}

void
TPencil::mouseMove(QMouseEvent* event)
{
  if (!isDrawing)
    return;

  QPointF p = canvas.toWorld(event->position());

  if (!path.isEmpty())
  {
    QPointF last = path.currentPosition();
    if (QLineF(last, p).length() < 5.0)
      return;
  }

  path.lineTo(p);
  canvas.repaint();
}

void
TPencil::mouseRelease(QMouseEvent* event)
{

  if (event->button() != Qt::LeftButton)
    return;

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
  painter.setBrush(Qt::NoBrush);
  painter.drawPath(path);
}
