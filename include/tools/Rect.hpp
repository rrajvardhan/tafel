#pragma once

#include "Tool.hpp"

struct TRect : Tool
{
  QPoint start;
  QPoint curr;
  bool   isDragging = false;

  explicit TRect(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent* event) override;
  void mouseMove(QMouseEvent* event) override;
  void mouseRelease(QMouseEvent* event) override;
  void drawPreview(QPainter& painter) override;
};
