#pragma once

#include <QPushButton>

class Canvas;

namespace UI
{

class ExportButton : public QPushButton
{
public:
  explicit ExportButton(Canvas* canvas);

  void exportImage();

private:
  Canvas* canvas;
};

}
