#include "drawables/Shapes.hpp"

Line::Line(const QPoint& start, const QPoint& end, const QPen& p)
    : Drawable(p, Qt::NoBrush), a(start), b(end)
{
}

void
Line::draw(QPainter& p)
{
  p.setPen(pen);
  p.drawLine(a, b);
}

QRectF
Line::bounds() const
{
  QRectF r(a, b);
  qreal  w = pen.widthF();
  return r.normalized().adjusted(-w, -w, w, w);
}

bool
Line::intersects(const QPainterPath& p) const
{
  QPainterPath linePath;
  linePath.moveTo(a);
  linePath.lineTo(b);
  return p.intersects(linePath);
}
