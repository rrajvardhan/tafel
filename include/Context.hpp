#pragma once

#include "Drawable.hpp"
#include <QBrush>
#include <QPen>

class CanvasContext
{
public:
  virtual ~CanvasContext()                              = default;
  virtual void   addDrawable(std::unique_ptr<Drawable>) = 0;
  virtual QPen   pen() const                            = 0;
  virtual QBrush brush() const                          = 0;
  virtual void   repaint()                              = 0;
};
