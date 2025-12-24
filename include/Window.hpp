#pragma once

#include "Canvas.hpp"
#include "Kit.hpp"
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class Window : public QWidget
{
public:
  explicit Window(QWidget* parent = nullptr, int w = 1600, int h = 900);

private:
  Canvas* canvas;
  Kit*    kit;
};
