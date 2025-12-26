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
}

QRectF
Rect::bounds() const
{
  QRectF r(a, b);
  qreal  w = pen.widthF();
  return r.normalized().adjusted(-w, -w, w, w);
}

bool
Rect::intersects(const QPainterPath& path) const
{
  QPainterPath rectPath;
  rectPath.addRect(bounds());
  return path.intersects(rectPath);
}
