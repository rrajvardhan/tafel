#pragma once

#include "Tool.hpp"
#include <QPainterPath>

struct TEraser : Tool
{
  QPainterPath path;
  bool         isErasing = false;
  qreal        size      = 5.0;

  explicit TEraser(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent*) override;
  void mouseMove(QMouseEvent*) override;
  void mouseRelease(QMouseEvent*) override;
  void drawPreview(QPainter&) override;
};
