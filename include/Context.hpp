#pragma once

#include "drawables/Drawable.hpp"
#include <QBrush>
#include <QPen>

class CanvasContext
{
public:
  virtual ~CanvasContext()                                          = default;
  virtual void      addDrawable(std::unique_ptr<Drawable>)          = 0;
  virtual QPen      pen() const                                     = 0;
  virtual QBrush    brush() const                                   = 0;
  virtual void      repaint()                                       = 0;
  virtual void      erase(const QPainterPath& eraser)               = 0;
  virtual Drawable* pick(const QPointF& pos)                        = 0;
  virtual void      clearSelection()                                = 0;
  virtual void      setSelection(const std::vector<Drawable*>& sel) = 0;
  virtual void      selectInRect(const QRectF& rect)                = 0;
  virtual void      pan(const QPointF& delta)                       = 0;
  virtual QPointF   toWorld(const QPointF& p) const                 = 0;

  virtual const std::vector<Drawable*>& selection() const = 0;
};
