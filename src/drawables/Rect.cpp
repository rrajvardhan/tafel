#include "drawables/Shapes.hpp"

Rect::Rect(const QPoint& start, const QPoint& end, const QPen& p, const QBrush& br)
    : Drawable(p, br), a(start), b(end)
{
}

void
Rect::draw(QPainter& p)
{
  QRectF r(a, b);
  p.setPen(pen);
  p.setBrush(brush);
  p.drawRect(r.normalized());

  // --- DEBUG: draw bounding rect ---
  // QPen debugPen(Qt::red);
  // debugPen.setStyle(Qt::DashLine);
  // debugPen.setWidth(1);
  // p.setPen(debugPen);
  // p.setBrush(Qt::NoBrush);
  //
  // p.drawRect(bounds());
}

QRectF
Rect::bounds() const
{
  QRectF r(a, b);
  qreal  w = pen.widthF();
  return r.normalized().adjusted(-w, -w, w, w);
}

bool
Rect::intersects(const QPainterPath& other) const
{
  QRectF r = QRectF(a, b).normalized();

  QPainterPath rectPath;
  rectPath.addRect(r);

  QPainterPath testPath;

  if (brush != Qt::NoBrush)
  {
    testPath = rectPath;
  }
  else
  {
    qreal w = pen.widthF();
    if (w <= 0)
      w = 1.0;

    QPainterPathStroker stroker;
    stroker.setWidth(w);
    testPath = stroker.createStroke(rectPath);
  }

  return testPath.intersects(other);
}

void
Rect::translate(const QPointF& delta)
{
  a += delta.toPoint();
  b += delta.toPoint();
}
