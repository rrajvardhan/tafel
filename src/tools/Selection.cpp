#include "Style.hpp"
#include "tools/Selection.hpp"

static QRectF
scaleHandle(const QRectF& r)
{
  constexpr qreal s  = 10.0;
  QPointF         br = r.bottomRight();
  return QRectF(br.x(), br.y(), s, s);
}

void
TSelect::mousePress(QMouseEvent* e)
{
  if (e->button() != Qt::LeftButton)
    return;

  start = end = canvas.toWorld(e->position());
  isDragging  = false;
  isScaling   = false;

  const auto& sel = canvas.selection();

  if (!sel.empty())
  {
    QRectF bounds;
    for (Drawable* d : sel)
      bounds |= d->bounds();

    if (scaleHandle(bounds).contains(start))
    {
      isScaling    = true;
      scaleAnchor  = bounds.topLeft();
      lastScalePos = start;
      return;
    }
  }

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
  end = canvas.toWorld(e->position());

  if (isScaling)
  {
    const auto& sel = canvas.selection();
    if (sel.empty())
      return;

    QPointF curr = end;

    qreal dx0 = lastScalePos.x() - scaleAnchor.x();
    qreal dy0 = lastScalePos.y() - scaleAnchor.y();

    qreal dx1 = curr.x() - scaleAnchor.x();
    qreal dy1 = curr.y() - scaleAnchor.y();

    if (dx0 == 0.0 || dy0 == 0.0)
    {
      lastScalePos = curr;
      return;
    }

    qreal sx = dx1 / dx0;
    qreal sy = dy1 / dy0;

    sx = std::clamp(sx, 0.05, 20.0);
    sy = std::clamp(sy, 0.05, 20.0);

    for (Drawable* d : sel)
      d->scale(scaleAnchor, sx, sy);

    lastScalePos = curr;
    canvas.repaint();
    return;
  }

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
TSelect::mouseRelease(QMouseEvent* e)
{
  if (e->button() != Qt::LeftButton)
    return;

  if (isScaling)
  {
    isScaling = false;
    return;
  }

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
  // Existing box-selection preview
  if (isDragging)
  {
    QRectF r(start, end);
    r = r.normalized();

    QPen pen(Color::SelectionFG);
    pen.setWidth(3);

    painter.setPen(pen);
    painter.setBrush(Color::SelectionBG);
    painter.drawRect(r);
  }

  // ------------------ scale handle ------------------
  const auto& sel = canvas.selection();
  if (sel.empty())
    return;

  QRectF bounds;
  for (Drawable* d : sel)
    bounds |= d->bounds();

  painter.setBrush(Color::SelectionFG);
  painter.setPen(Qt::NoPen);
  painter.drawRect(scaleHandle(bounds));
  // --------------------------------------------------
}
