#pragma once

#include "drawables/Drawable.hpp"
#include <QFont>
#include <QString>

struct Text : Drawable
{
  QString text;
  QPointF pos;
  QFont   font;

  Text(const QString& t, const QPointF& p, const QFont& f, const QPen& pen);

  void   draw(QPainter& p) override;
  QRectF bounds() const override;
  bool   intersects(const QPainterPath& path) const override;
  void   translate(const QPointF& d) override;
};
