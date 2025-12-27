#pragma once

#include "Tool.hpp"

struct TSelect : Tool
{
  QPointF start;
  QPointF end;
  bool    isDragging = false;

  explicit TSelect(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent* e) override;
  void mouseMove(QMouseEvent* e) override;
  void mouseRelease(QMouseEvent*) override;
  void drawPreview(QPainter&) override;
};
