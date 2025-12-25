#pragma once

#include "Tool.hpp"

class Canvas;

struct TRect : Tool
{
  QPoint start;
  QPoint curr;
  int    width, height;
  bool   isDragging = false;

  explicit TRect(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent* event) override;
  void mouseMove(QMouseEvent* event) override;
  void mouseRelease(QMouseEvent* event) override;
  void drawPreview(QPainter& painter) override;
};
