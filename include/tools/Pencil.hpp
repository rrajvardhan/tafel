#pragma once

#include "Tool.hpp"

struct TPencil : Tool
{
  QPainterPath path;
  QPointF      lastPoint;
  bool         isDrawing = false;

  explicit TPencil(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent*) override;
  void mouseMove(QMouseEvent*) override;
  void mouseRelease(QMouseEvent*) override;
  void drawPreview(QPainter&) override;
};
