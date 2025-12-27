#pragma once

#include "Drawable.hpp"

struct Line : Drawable
{
  QPointF a;
  QPointF b;

  Line(const QPointF& start, const QPointF& end, const QPen& p);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& p) const override;
  void   translate(const QPointF& d) override;
};

struct Rect : Drawable
{
  QPointF a;
  QPointF b;

  Rect(const QPointF& start, const QPointF& end, const QPen& p, const QBrush& br);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& path) const override;
  void   translate(const QPointF& d) override;
};

struct Ellipse : Drawable
{
  QPointF a;
  QPointF b;

  Ellipse(const QPointF& start, const QPointF& end, const QPen& p, const QBrush& br);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& path) const override;
  void   translate(const QPointF& d) override;
};
