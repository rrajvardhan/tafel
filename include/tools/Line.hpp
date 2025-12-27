#pragma once

#include "Tool.hpp"

struct TLine : Tool
{
  QPointF start;
  QPointF curr;
  bool    isDragging = false;

  explicit TLine(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent* event) override;
  void mouseMove(QMouseEvent* event) override;
  void mouseRelease(QMouseEvent* event) override;
  void drawPreview(QPainter& painter) override;
};
