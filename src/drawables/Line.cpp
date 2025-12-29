#include "drawables/Shapes.hpp"

Line::Line(const QPointF& start, const QPointF& end, const QPen& p)
    : Drawable(p, Qt::NoBrush), a(start), b(end)
{
}

void
Line::draw(QPainter& p)
{
  p.setPen(pen);
  p.drawLine(a, b);

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
Line::bounds() const
{
  QRectF r(a, b);
  qreal  w = pen.widthF();
  return r.normalized().adjusted(-w, -w, w, w);
}

bool
Line::intersects(const QPainterPath& other) const
{
  QPainterPath linePath;
  linePath.moveTo(a);
  linePath.lineTo(b);

  qreal w = pen.widthF();
  if (w <= 0)
    w = 1.0;

  QPainterPathStroker stroker;
  stroker.setWidth(w);
  QPainterPath strokedPath = stroker.createStroke(linePath);

  for (int i = 0; i < other.elementCount(); ++i)
  {
    QPainterPath::Element e = other.elementAt(i);
    QPointF               point(e.x, e.y);

    if (strokedPath.contains(point))
      return true;
  }

  return false;
}

void
Line::translate(const QPointF& d)
{
  a += d.toPoint();
  b += d.toPoint();
}

void
Line::scale(const QPointF& anchor, qreal sx, qreal sy)
{
  a = anchor + QPointF((a.x() - anchor.x()) * sx, (a.y() - anchor.y()) * sy);

  b = anchor + QPointF((b.x() - anchor.x()) * sx, (b.y() - anchor.y()) * sy);
}
