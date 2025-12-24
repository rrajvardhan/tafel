#pragma once

#include "Context.hpp"
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>

struct Tool
{
  virtual ~Tool() = default;
  virtual void mousePress(QMouseEvent* event) {}
  virtual void mouseMove(QMouseEvent* event) {}
  virtual void mouseRelease(QMouseEvent* event) {}
  virtual void drawPreview(QPainter& painter) {}

  void setContext(CanvasContext* ctx) { canvas = ctx; }

protected:
  CanvasContext* canvas = nullptr;
};
