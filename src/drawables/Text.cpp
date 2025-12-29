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

void
Text::scale(const QPointF&, qreal sx, qreal sy)
{

  qreal size = font.pointSizeF();
  if (size <= 0)
    size = 18.0;

  if (sy > 1.0)
    size += 1.0;
  else if (sy < 1.0)
    size -= 1.0;

  if (sx > 1.0)
    size += 1.0;
  else if (sx < 1.0)
    size -= 1.0;

  size = std::clamp(size, 6.0, 200.0);
  font.setPointSizeF(size);
}
