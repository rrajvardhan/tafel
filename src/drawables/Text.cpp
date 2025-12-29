#include "drawables/Text.hpp"
#include <QFontMetricsF>

Text::Text(const QString& t, const QPointF& p, const QFont& f, const QPen& pn)
    : Drawable(pn, Qt::NoBrush)
{
  text = t;
  pos  = p;
  font = f;
  pen  = pn;
}

void
Text::draw(QPainter& p)
{
  p.setPen(pen);
  p.setFont(font);
  p.drawText(pos, text);
}

QRectF
Text::bounds() const
{
  QFontMetricsF metrics(font);
  QRectF        rect = metrics.boundingRect(text);

  rect.moveTopLeft(pos + QPointF(0, -metrics.ascent()));
  return rect;
}

bool
Text::intersects(const QPainterPath& path) const
{
  return path.intersects(bounds());
}

void
Text::translate(const QPointF& d)
{
  pos += d;
}
