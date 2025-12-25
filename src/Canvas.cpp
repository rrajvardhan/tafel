#include "Canvas.hpp"

Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
  kit = new Kit(this);
}

void
Canvas::addDrawable(std::unique_ptr<Drawable> d)
{
  drawables.push_back(std::move(d));
  update();
}

void
Canvas::activateTool(std::unique_ptr<Tool> tool)
{
  currTool = std::move(tool);
}

void
Canvas::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

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
  if (event->button() != Qt::LeftButton)
    return;

  if (currTool)
  {
    currTool->mousePress(event);
  }
}

void
Canvas::mouseMoveEvent(QMouseEvent* event)
{

  if (!(event->buttons() & Qt::LeftButton))
    return;

  if (currTool)
  {
    currTool->mouseMove(event);
  }
}

void
Canvas::mouseReleaseEvent(QMouseEvent* event)
{
  if (event->button() != Qt::LeftButton)
    return;

  if (currTool)
  {
    currTool->mouseRelease(event);
  }
}
