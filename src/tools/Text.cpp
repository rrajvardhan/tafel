#include "drawables/Text.hpp"
#include "tools/Text.hpp"
#include <QKeyEvent>

TText::TText(CanvasContext& ctx) : Tool(ctx)
{
}

void
TText::mousePress(QMouseEvent* event)
{
  insertPos = canvas.toWorld(event->position());
  pressPos  = insertPos;

  buffer.clear();
  editing = true;

  font         = QFont();
  baseFontSize = font.pointSizeF();
  if (baseFontSize <= 0)
    baseFontSize = 22.0;

  pen = canvas.pen();
}

void
TText::mouseMove(QMouseEvent* event)
{
  if (!editing)
    return;

  if (!(event->buttons() & Qt::LeftButton))
    return;

  QPointF curr = canvas.toWorld(event->position());
  qreal   dy   = curr.y() - pressPos.y();

  qreal scale   = 1.0 + dy * 0.05;
  qreal newSize = baseFontSize * scale;
  newSize       = std::clamp(newSize, 6.0, 200.0);

  font.setPointSizeF(newSize);
  canvas.repaint();
}

void
TText::keyPress(QKeyEvent* event)
{
  if (!editing)
    return;

  if (event->key() == Qt::Key_Escape)
  {
    editing = false;
    buffer.clear();
    canvas.repaint();
    return;
  }

  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
  {
    if (!buffer.isEmpty())
    {
      canvas.addDrawable(std::make_unique<Text>(buffer, insertPos, font, pen));
    }
    editing = false;
    buffer.clear();
    canvas.repaint();
    return;
  }

  if (event->key() == Qt::Key_Backspace)
  {
    if (!buffer.isEmpty())
      buffer.chop(1);
    canvas.repaint();
    return;
  }

  const QString txt = event->text();

  if (event->key() == Qt::Key_Space)
  {
    buffer += ' ';
    canvas.repaint();
    return;
  }

  if (!txt.isEmpty() && txt.at(0).isPrint())
  {
    buffer += txt;
    canvas.repaint();
  }
}

void
TText::drawPreview(QPainter& painter)
{
  if (!editing)
    return;

  painter.setPen(pen);
  painter.setFont(font);
  painter.drawText(insertPos, buffer + "|");
}
