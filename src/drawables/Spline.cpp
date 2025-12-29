#include "drawables/Spline.hpp"

static constexpr qreal TENSION = 0.5;

Spline::Spline(std::vector<QPointF> pts, const QPen& pen)
    : Drawable(pen, Qt::NoBrush), points(std::move(pts))
{
}

static QPointF
tangent(const QPointF& p0, const QPointF& p2)
{
  return (1.0 - TENSION) * (p2 - p0) * 0.5;
}

QPainterPath
Spline::buildPath() const
{
  QPainterPath path;
  if (points.size() < 2)
    return path;

  if (points.size() == 2)
  {
    path.moveTo(points[0]);
    path.lineTo(points[1]);
    return path;
  }

  // duplicate endpoints
  std::vector<QPointF> pts;
  pts.reserve(points.size() + 2);
  pts.push_back(points.front());
  pts.insert(pts.end(), points.begin(), points.end());
  pts.push_back(points.back());

  path.moveTo(pts[1]);

  for (size_t i = 1; i + 2 < pts.size(); ++i)
  {
    const QPointF& p0 = pts[i - 1];
    const QPointF& p1 = pts[i];
    const QPointF& p2 = pts[i + 1];
    const QPointF& p3 = pts[i + 2];

    QPointF t1 = tangent(p0, p2);
    QPointF t2 = tangent(p1, p3);

    QPointF c1 = p1 + t1 / 3.0;
    QPointF c2 = p2 - t2 / 3.0;

    path.cubicTo(c1, c2, p2);
  }

  return path;
}

void
Spline::draw(QPainter& p)
{
  p.setPen(pen);
  p.setBrush(Qt::NoBrush);
  p.drawPath(buildPath());
}

QRectF
Spline::bounds() const
{
  QPainterPathStroker s;
  s.setWidth(std::max<qreal>(1.0, pen.widthF()));
  return s.createStroke(buildPath()).boundingRect();
}

bool
Spline::intersects(const QPainterPath& other) const
{
  QPainterPathStroker s;
  s.setWidth(std::max<qreal>(1.0, pen.widthF()));
  return s.createStroke(buildPath()).intersects(other);
}

void
Spline::translate(const QPointF& d)
{
  for (auto& p : points)
    p += d;
}

void
Spline::scale(const QPointF& a, qreal sx, qreal sy)
{
  for (auto& p : points)
    p = a + QPointF((p.x() - a.x()) * sx, (p.y() - a.y()) * sy);
}
