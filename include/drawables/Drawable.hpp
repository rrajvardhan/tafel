#pragma once
#include <QPainter>
#include <QPainterPath>

struct Drawable
{
  QPen   pen;
  QBrush brush;

  Drawable(const QPen& p, const QBrush& b) : pen(p), brush(b) {}
  virtual ~Drawable()                                    = default;
  virtual void   draw(QPainter& p)                       = 0;
  virtual QRectF bounds() const                          = 0;
  virtual bool   intersects(const QPainterPath& p) const = 0;
};
