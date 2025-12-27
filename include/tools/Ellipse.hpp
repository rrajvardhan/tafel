#pragma once

#include "Tool.hpp"

struct TEllipse : Tool
{
  QPoint start;
  QPoint curr;
  int    rad1, rad2;
  bool   isDragging = false;

  explicit TEllipse(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent* event) override;
  void mouseMove(QMouseEvent* event) override;
  void mouseRelease(QMouseEvent* event) override;
  void drawPreview(QPainter& painter) override;
};
