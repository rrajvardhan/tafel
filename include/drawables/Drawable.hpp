#pragma once
#include <QPainter>
#include <QPainterPath>

struct Drawable
{
  QPen   pen;
  QBrush brush;

  Drawable(const QPen& p, const QBrush& b) : pen(p), brush(b) {}
  virtual ~Drawable()                                             = default;
  virtual void   draw(QPainter& p)                                = 0;
  virtual QRectF bounds() const                                   = 0;
  virtual bool   intersects(const QPainterPath& p) const          = 0;
  virtual void   translate(const QPointF& delta)                  = 0;
  virtual void   scale(const QPointF& anchor, qreal sx, qreal sy) = 0;

  // TODO:
  // virtual void   rotate(const QPointF& center, qreal radians)     = 0;
};
