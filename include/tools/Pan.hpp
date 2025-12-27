#pragma once
#include "Tool.hpp"

struct TPan : Tool
{
  QPointF last;

  explicit TPan(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent* e) override { last = e->position(); }

  void mouseMove(QMouseEvent* e) override
  {
    QPointF curr  = e->position();
    QPointF delta = curr - last;
    last          = curr;

    canvas.pan(delta);
  }
};
