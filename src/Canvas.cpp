#include "Canvas.hpp"
#include "Style.hpp"
#include <QVBoxLayout>

Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
  kitContainer = new QFrame(this);
  kitContainer->setObjectName("KitContainer");

  kit = new Kit(this);

  // Layout INSIDE the container
  auto* containerLayout = new QHBoxLayout(kitContainer);
  containerLayout->setContentsMargins(8, 8, 8, 8);
  containerLayout->addWidget(kit);

  // Layout for the canvas
  auto* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 8, 0, 0);
  layout->setSpacing(0);

  layout->addWidget(kitContainer, 0, Qt::AlignTop | Qt::AlignHCenter);
  layout->addStretch();
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
Canvas::resizeEvent(QResizeEvent* e)
{
  QWidget::resizeEvent(e);
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

  if (!selections.empty())
  {
    QRectF bounds;
    for (auto* d : selections)
      bounds |= d->bounds();

    bounds = bounds.adjusted(-4, -4, 4, 4);

    QPen pen(Color::SelectionFG);
    pen.setWidth(3);

    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(bounds);
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

void
Canvas::erase(const QPainterPath& eraser)
{
  selections.clear();

  auto er = eraser.boundingRect();
  drawables.erase(std::remove_if(drawables.begin(),
                                 drawables.end(),
                                 [&](const std::unique_ptr<Drawable>& d)
                                 {
                                   if (!d->bounds().intersects(er))
                                     return false;

                                   return d->intersects(eraser);
                                 }),
                  drawables.end());

  update();
}

Drawable*
Canvas::pick(const QPointF& pos)
{
  QPainterPath p;
  p.addEllipse(pos, 3, 3); // small tolerance

  for (auto it = drawables.rbegin(); it != drawables.rend(); ++it)
  {
    if ((*it)->intersects(p))
      return it->get();
  }
  return nullptr;
}

void
Canvas::selectInRect(const QRectF& rect)
{
  std::vector<Drawable*> hits;

  for (const auto& d : drawables)
  {

    if (rect.contains(d->bounds()))
      hits.push_back(d.get());
  }

  setSelection(hits);
}

void
Canvas::clearSelection()
{
  selections.clear();
  update();
}

void
Canvas::setSelection(const std::vector<Drawable*>& sel)
{
  selections = sel;
  update();
}
