#pragma once

#include "tools/Tool.hpp"
#include <QFont>
#include <QString>

class TText : public Tool
{
public:
  explicit TText(CanvasContext& ctx);

  void mousePress(QMouseEvent* event) override;
  void mouseMove(QMouseEvent* event) override;
  void drawPreview(QPainter& painter) override;

  void keyPress(QKeyEvent* event) override;

private:
  QString buffer;
  QPointF insertPos;
  bool    editing = false;

  QFont font;
  QPen  pen;

  QPointF pressPos;
  qreal   baseFontSize = 22.0;
};
