#pragma once

#include <QPushButton>
#include <QWidget>

class Canvas;

class Kit : public QWidget
{
public:
  explicit Kit(Canvas* canvas);

private:
  Canvas*      canvas = nullptr;
  QPushButton* button1;
  QPushButton* button2;
};
