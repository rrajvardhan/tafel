#include "Canvas.hpp"
#include "ExportButton.hpp"

#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QPainter>

namespace UI
{

ExportButton::ExportButton(Canvas* canvas) : QPushButton(canvas), canvas(canvas)
{
  connect(this, &QPushButton::clicked, this, &ExportButton::exportImage);

  setFixedSize(80, 80);
  setStyleSheet("QPushButton {"
                "  border: 2px solid #1C1C1C;"
                "  border-radius: 3px;"
                "}"
                "QPushButton:hover {"
                "  border: 2px;"
                "  border-style: dashed;"
                "  border-color: rgba(28, 28, 28, 220);"
                "  border-radius: 3px;"
                "}"
                "QPushButton:checked {"
                "  border:3px dashed #1C1C1C;"
                "}");

  setIcon(QIcon(":/icons/export.svg"));
  setToolTip("export");
  setIconSize(QSize(32, 32));
}

void
ExportButton::exportImage()
{
  if (!canvas)
    return;

  const QString filePath = QFileDialog::getSaveFileName(
      this, "Export Canvas", "tafel-export.png", "PNG Image (*.png);;JPEG Image (*.jpg)");

  if (filePath.isEmpty())
    return;

  const QSize size = canvas->canvasSize();
  QImage      image(size, QImage::Format_ARGB32_Premultiplied);
  image.fill(Qt::white);

  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing, true);
  canvas->renderToPainter(painter);
  painter.end();

  if (!image.save(filePath))
  {
    QMessageBox::warning(this, "Export Failed", "Could not save the image.");
  }
}
}
