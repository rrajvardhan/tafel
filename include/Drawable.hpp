#pragma once
#include <QPainter>

struct Drawable
{
  QPen   pen;
  QBrush brush;

  Drawable() : pen(Qt::black, 2), brush(Qt::NoBrush) {}
  virtual ~Drawable()            = default;
  virtual void draw(QPainter& p) = 0;
};

struct Line : Drawable
{
  QPoint a;
  QPoint b;

  Line(const QPoint& start, const QPoint& end, const QPen& p) : a(start), b(end) { pen = p; }

  void draw(QPainter& p) override
  {
    p.setPen(pen);
    p.drawLine(a, b);
  }
};

struct Rect : Drawable
{
  QPoint start;
  int    width;
  int    height;

  Rect(const QPoint& st, int w, int h, const QPen& p, const QBrush& b)
      : start(st), width(w), height(h)
  {
    pen   = p;
    brush = b;
  }

  void draw(QPainter& p) override
  {
    p.setPen(pen);
    p.setBrush(brush);
    p.drawRect(start.x(), start.y(), width, height);
  }
};
