#pragma once

#include "Drawable.hpp"

struct Spline : Drawable
{
public:
  std::vector<QPointF> points;
  Spline(std::vector<QPointF> pts, const QPen& pen);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& p) const override;
  void   translate(const QPointF& d) override;
  void   scale(const QPointF& anchor, qreal sx, qreal sy) override;

private:
  QPainterPath buildPath() const;
};
