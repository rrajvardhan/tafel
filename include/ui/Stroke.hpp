#pragma once

#include <QWidget>

class Canvas;

namespace UI
{
class Stroke : public QWidget
{
public:
  explicit Stroke(Canvas* canvas);

private:
  Canvas* canvas = nullptr;
};
}
