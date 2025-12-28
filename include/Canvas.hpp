#pragma once

#include "drawables/Drawable.hpp"
#include "tools/Tool.hpp"
#include "ui/Brush.hpp"
#include "ui/Kit.hpp"
#include "ui/Stroke.hpp"
#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <vector>

class Canvas : public QWidget, public CanvasContext
{
public:
  explicit Canvas(QWidget* parent = nullptr);
  void activateTool(std::unique_ptr<Tool> tool);
  void setPen(QPen pen) { currentPen = pen; }
  void setBrush(QBrush brush) { currentBrush = brush; }

  //---------------------- context -------------------------
  void      addDrawable(std::unique_ptr<Drawable>) override;
  QPen      pen() const override { return currentPen; }
  QBrush    brush() const override { return currentBrush; }
  void      repaint() override { update(); }
  void      erase(const QPainterPath& eraser) override;
  Drawable* pick(const QPointF& pos) override;

  QPointF toWorld(const QPointF& p) const override { return p - panOffset; }
  void    pan(const QPointF& delta) override
  {
    panOffset += delta;
    update();
  }

  // ---- selection API ----
  void clearSelection() override;
  void setSelection(const std::vector<Drawable*>& sel) override;
  void selectInRect(const QRectF& rect) override;

  const std::vector<Drawable*>& selection() const override { return selections; }

  //--------------------------------------------------------

private:
  std::vector<Drawable*> selections;

  QPen   currentPen{ Qt::black, 4 };
  QBrush currentBrush{ Qt::NoBrush };

  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

  std::vector<std::unique_ptr<Drawable>> drawables;
  std::unique_ptr<Tool>                  currTool;

  QPointF panOffset{ 0, 0 };

  UI::Kit*    _kit;
  UI::Stroke* _stroke;
  UI::Brush*  _brush;
};
