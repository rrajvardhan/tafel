#pragma once

#include "Drawable.hpp"

struct Line : Drawable
{
  QPoint a;
  QPoint b;

  Line(const QPoint& start, const QPoint& end, const QPen& p);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& p) const override;
};

struct Rect : Drawable
{
  QPoint a;
  QPoint b;

  Rect(const QPoint& start, const QPoint& end, const QPen& p, const QBrush& br);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& path) const override;
};

struct Ellipse : Drawable
{
  QPoint a;
  QPoint b;

  Ellipse(const QPoint& start, const QPoint& end, const QPen& p, const QBrush& br);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& path) const override;
};
