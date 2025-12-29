#pragma once

#include "Drawable.hpp"

struct Path : Drawable
{
  QPainterPath path;

  Path(const QPainterPath& p, const QPen& pen);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& p) const override;
  void   translate(const QPointF& d) override;
  void   scale(const QPointF& anchor, qreal sx, qreal sy) override;
};
