#include "drawables/Spline.hpp"
#include "tools/Spline.hpp"

void
TSpline::mousePress(QMouseEvent* event)
{
  curr = canvas.toWorld(event->position());

  if (event->button() == Qt::RightButton)
  {
    if (points.size() >= 2)
    {

      // this is intentional , for visual
      QPointF end = points.back();
      points.push_back(end);

      canvas.addDrawable(std::make_unique<Spline>(points, canvas.pen()));
    }
    points.clear();
    canvas.repaint();
    return;
  }

  canvas.repaint();
}

void
TSpline::mouseMove(QMouseEvent* event)
{
  curr = canvas.toWorld(event->position());
  canvas.repaint();
}

void
TSpline::mouseRelease(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
  {
    points.push_back(curr);
    canvas.repaint();
    return;
  }
}

void
TSpline::drawPreview(QPainter& painter)
{
  if (points.size() < 1)
    return;

  std::vector<QPointF> previewPts = points;

  previewPts.push_back(curr);
  previewPts.push_back(curr);

  Spline preview(previewPts, canvas.pen());
  preview.draw(painter);
}
