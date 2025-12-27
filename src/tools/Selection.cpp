#include "Style.hpp"
#include "tools/Selection.hpp"

void
TSelect::mousePress(QMouseEvent* e)
{
  start = end = e->position();
  isDragging  = false;

  const auto& sel = canvas.selection();

  // 1. Click inside existing selection → prepare to move
  for (Drawable* d : sel)
  {
    if (d->bounds().contains(start))
      return;
  }

  // 2. Click on a drawable → select it
  if (Drawable* hit = canvas.pick(start))
  {
    canvas.setSelection({ hit });
    return;
  }

  // 3. Click on empty space → start box selection
  canvas.clearSelection();
  isDragging = true;
}

void
TSelect::mouseMove(QMouseEvent* e)
{
  end = e->position();

  // Box selection in progress
  if (isDragging)
  {
    canvas.repaint();
    return;
  }

  // Move current selection
  const auto& sel = canvas.selection();
  if (sel.empty())
    return;

  QPointF delta = end - start;
  start         = end;

  for (Drawable* d : sel)
    d->translate(delta);

  canvas.repaint();
}

void
TSelect::mouseRelease(QMouseEvent*)
{
  if (!isDragging)
    return;

  QRectF box(start, end);
  box = box.normalized();

  canvas.selectInRect(box);
  isDragging = false;
}

void
TSelect::drawPreview(QPainter& painter)
{
  if (!isDragging)
    return;

  QRectF r(start, end);
  r = r.normalized();

  QPen pen(Color::SelectionFG);
  pen.setWidth(3);

  painter.setPen(pen);
  painter.setBrush(Color::SelectionBG);

  painter.drawRect(r);
}
