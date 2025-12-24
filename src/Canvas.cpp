#include "Canvas.hpp"
#include "tools/Line.hpp"
#include "tools/Rect.hpp"
#include <QWidget>

Canvas::Canvas(QWidget* parent, int w, int h) : QWidget(parent)
{
}

void
Canvas::addDrawable(std::unique_ptr<Drawable> d)
{
  drawables.push_back(std::move(d));
  update();
}

void
Canvas::setTool(std::unique_ptr<Tool> tool)
{
  currTool = std::move(tool);
  if (currTool)
    currTool->setContext(this);
}

void
Canvas::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  for (const auto& drawable : drawables)
  {
    drawable->draw(painter);
  }

  if (currTool)
  {
    currTool->drawPreview(painter);
  }
}

void
Canvas::mousePressEvent(QMouseEvent* event)
{
  if (currTool)
  {
    currTool->mousePress(event);
  }
}

void
Canvas::mouseMoveEvent(QMouseEvent* event)
{
  if (currTool)
  {
    currTool->mouseMove(event);
  }
}

void
Canvas::mouseReleaseEvent(QMouseEvent* event)
{
  if (currTool)
  {
    currTool->mouseRelease(event);
  }
}
