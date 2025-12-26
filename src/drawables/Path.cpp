#include "drawables/Path.hpp"

Path::Path(const QPainterPath& p, const QPen& pen) : Drawable(pen, Qt::NoBrush), path(p)
{
}

void
Path::draw(QPainter& painter)
{
  painter.setPen(pen);
  painter.drawPath(path);
}

QRectF
Path::bounds() const
{
  qreal w = pen.widthF();
  return path.boundingRect().adjusted(-w, -w, w, w);
}

bool
Path::intersects(const QPainterPath& other) const
{
  // Create a stroked version of this path
  qreal w = pen.widthF();
  if (w <= 0)
    w = 1.0;

  QPainterPathStroker stroker;
  stroker.setWidth(w);
  QPainterPath strokedPath = stroker.createStroke(path);

  // Check if any point from the eraser is inside the stroked path
  for (int i = 0; i < other.elementCount(); ++i)
  {
    QPainterPath::Element e = other.elementAt(i);
    QPointF               point(e.x, e.y);

    if (strokedPath.contains(point))
      return true;
  }

  return false;
}
