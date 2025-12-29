#include "drawables/Shapes.hpp"

Ellipse::Ellipse(const QPointF& start, const QPointF& end, const QPen& p, const QBrush& br)
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
Ellipse::bounds() const
{
  QRectF r(a, b);
  qreal  w = pen.widthF();
  return r.normalized().adjusted(-w, -w, w, w);
}

bool
Ellipse::intersects(const QPainterPath& other) const
{
  QRectF r = QRectF(a, b).normalized();

  QPainterPath ellipsePath;
  ellipsePath.addEllipse(r);

  QPainterPath testPath;

  if (brush != Qt::NoBrush)
  {
    // Filled ellipse → area
    testPath = ellipsePath;
  }
  else
  {
    // Hollow ellipse → stroke only
    qreal w = pen.widthF();
    if (w <= 0)
      w = 1.0;

    QPainterPathStroker stroker;
    stroker.setWidth(w);
    testPath = stroker.createStroke(ellipsePath);
  }

  for (int i = 0; i < other.elementCount(); ++i)
  {
    QPainterPath::Element e = other.elementAt(i);
    QPointF               point(e.x, e.y);

    if (testPath.contains(point))
      return true;
  }

  return false;
}

void
Ellipse::translate(const QPointF& d)
{
  a += d.toPoint();
  b += d.toPoint();
}

void
Ellipse::scale(const QPointF& anchor, qreal sx, qreal sy)
{
  a = anchor + QPointF((a.x() - anchor.x()) * sx, (a.y() - anchor.y()) * sy);

  b = anchor + QPointF((b.x() - anchor.x()) * sx, (b.y() - anchor.y()) * sy);
}
