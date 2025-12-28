#pragma once

#include <QWidget>

class Canvas;

namespace UI
{
class Brush : public QWidget
{
public:
  explicit Brush(Canvas* canvas);

private:
  Canvas* canvas = nullptr;
};
}
