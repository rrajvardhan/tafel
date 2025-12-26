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

struct Line : Drawable
{
  QPoint a;
  QPoint b;

  Line(const QPoint& start, const QPoint& end, const QPen& p)
      : Drawable(p, Qt::NoBrush), a(start), b(end)
  {
  }

  void draw(QPainter& p) override
  {
    p.setPen(pen);
    p.drawLine(a, b);
  }

  QRectF bounds() const override
  {
    QRectF r(a, b);
    qreal  w = pen.widthF();
    return r.normalized().adjusted(-w, -w, w, w);
  }

  bool intersects(const QPainterPath& p) const override
  {
    QPainterPath linePath;
    linePath.moveTo(a);
    linePath.lineTo(b);
    return p.intersects(linePath);
  }
};

struct Rect : Drawable
{
  QPoint a;
  QPoint b;

  Rect(const QPoint& start, const QPoint& end, const QPen& p, const QBrush& br)
      : Drawable(p, br), a(start), b(end)
  {
  }

  void draw(QPainter& p) override
  {
    QRectF r(a, b);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawRect(r.normalized());
  }

  QRectF bounds() const override
  {
    QRectF r(a, b);
    qreal  w = pen.widthF();
    return r.normalized().adjusted(-w, -w, w, w);
  }

  bool intersects(const QPainterPath& path) const override
  {
    QPainterPath rectPath;
    rectPath.addRect(bounds());
    return path.intersects(rectPath);
  }
};

struct Ellipse : Drawable
{
  QPoint a;
  QPoint b;

  Ellipse(const QPoint& start, const QPoint& end, const QPen& p, const QBrush& br)
      : Drawable(p, br), a(start), b(end)
  {
  }

  void draw(QPainter& p) override
  {
    QRectF r(a, b);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawEllipse(r.normalized());
  }

  QRectF bounds() const override
  {
    QRectF r(a, b);
    qreal  w = pen.widthF();
    return r.normalized().adjusted(-w, -w, w, w);
  }

  bool intersects(const QPainterPath& path) const override
  {
    QPainterPath e;
    e.addEllipse(QRectF(a, b).normalized());
    return path.intersects(e);
  }
};

struct Path : Drawable
{
  QPainterPath path;

  Path(const QPainterPath& p, const QPen& pen) : Drawable(pen, Qt::NoBrush), path(p) {}

  void draw(QPainter& painter) override
  {
    painter.setPen(pen);
    painter.drawPath(path);
  }

  QRectF bounds() const override
  {
    qreal w = pen.widthF();
    return path.boundingRect().adjusted(-w, -w, w, w);
  }

  bool intersects(const QPainterPath& other) const override { return other.intersects(path); }
};
