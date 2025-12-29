#pragma once

#include "Tool.hpp"

struct TSpline : Tool
{
  QPointF curr;

  std::vector<QPointF> points;

  explicit TSpline(CanvasContext& ctx) : Tool(ctx) {}

  void mousePress(QMouseEvent* event) override;
  void mouseMove(QMouseEvent* event) override;
  void mouseRelease(QMouseEvent* event) override;
  void drawPreview(QPainter& painter) override;
};
