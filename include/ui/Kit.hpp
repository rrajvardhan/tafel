#pragma once

#include "Tool.hpp"
#include <QWidget>

class Canvas;

namespace UI
{
struct Buttons
{
  const char*                                   tooltip;
  const char*                                   icon;
  std::function<std::unique_ptr<Tool>(Canvas*)> tool;
};

template <typename T>
std::unique_ptr<Tool>
makeTool(Canvas* c)
{
  return std::make_unique<T>(*c);
}

class Kit : public QWidget
{
public:
  explicit Kit(Canvas* canvas);

private:
  Canvas* canvas = nullptr;
};
}
