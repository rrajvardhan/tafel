#include "drawables/Shapes.hpp"

Ellipse::Ellipse(const QPoint& start, const QPoint& end, const QPen& p, const QBrush& br)
    : Drawable(p, br), a(start), b(end)
{
}

void
Ellipse::draw(QPainter& p)
{
  QRectF r(a, b);
  p.setPen(pen);
  p.setBrush(brush);
  p.drawEllipse(r.normalized());
}

QRectF
Ellipse::bounds() const
{
  QRectF r(a, b);
  qreal  w = pen.widthF();
  return r.normalized().adjusted(-w, -w, w, w);
}

bool
Ellipse::intersects(const QPainterPath& path) const
{
  QPainterPath e;
  e.addEllipse(QRectF(a, b).normalized());
  return path.intersects(e);
}
