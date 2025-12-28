#include "Canvas.hpp"
#include "ui/Brush.hpp"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>

namespace UI
{

struct Paint
{
  std::string name;
  QColor      color;
};

Brush::Brush(Canvas* canvas) : QWidget(canvas), canvas(canvas)
{
  setObjectName("Brush");

  auto* rootLayout = new QHBoxLayout(this);
  rootLayout->setContentsMargins(0, 0, 0, 0);
  rootLayout->setSpacing(4);
  rootLayout->setAlignment(Qt::AlignLeft);

  // toggle button
  auto* toggle = new QPushButton(this);
  toggle->setCheckable(true);
  toggle->setFixedSize(80, 80);
  toggle->setChecked(false);
  rootLayout->addWidget(toggle);

  toggle->setStyleSheet("QPushButton {"
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

  toggle->setIcon(QIcon(":/icons/brush.svg"));
  toggle->setToolTip("brush");
  toggle->setIconSize(QSize(32, 32));

  // container
  auto* colorsWidget = new QWidget(this);
  colorsWidget->setVisible(false);
  auto* colorsLayout = new QHBoxLayout(colorsWidget);
  colorsLayout->setContentsMargins(0, 0, 0, 0);
  colorsLayout->setSpacing(6);
  colorsLayout->setAlignment(Qt::AlignLeft);

  rootLayout->addWidget(colorsWidget);

  static const Paint paints[] = {
    { "None", QColor(Qt::transparent) }, { "Black", QColor("#0F0F0F") },
    { "Gray", QColor("#6B7280") },       { "White", QColor("#FFFFFF") },
    { "Red", QColor("#EF4444") },        { "Amber", QColor("#F59E0B") },
    { "Lime", QColor("#84CC16") },       { "Cyan", QColor("#06B6D4") },
    { "Blue", QColor("#3B82F6") },       { "Violet", QColor("#8B5CF6") },
  };

  auto* group = new QButtonGroup(this);
  group->setExclusive(true);

  for (const auto& p : paints)
  {
    auto* b = new QPushButton(colorsWidget);
    b->setFixedSize(60, 60);
    b->setToolTip(QString::fromStdString(p.name));
    b->setCheckable(true);

    if (p.name == "None")
    {
      b->setIcon(QIcon(":/icons/circle_half.svg"));
      b->setIconSize(QSize(28, 28));

      b->setStyleSheet("QPushButton {"
                       "  border: 1px solid #1C1C1C;"
                       "  border-radius: 3px;"
                       "}"
                       "QPushButton:hover {"
                       "  border: 2px dashed rgba(28, 28, 28, 220);"
                       "  border-radius: 3px;"
                       "}"
                       "QPushButton:checked {"
                       "  border: 3px dashed #1C1C1C;"
                       "}");
    }
    else
    {
      b->setStyleSheet(QString("QPushButton {"
                               " 	background-color : %1;"
                               "  border: 1px solid #1C1C1C;"
                               "  border-radius: 3px;"
                               "}"
                               "QPushButton:hover {"
                               "  border: 2px dashed rgba(28, 28, 28, 220);"
                               "  border-radius: 3px;"
                               "}"
                               "QPushButton:checked {"
                               "  border: 3px dashed #1C1C1C;"
                               "}")
                           .arg(p.color.name()));
    }

    if (p.name == "None")
    {
      b->setIcon(QIcon(":/icons/circle_half.svg"));
      b->setIconSize(QSize(28, 28));
    }

    group->addButton(b);

    connect(b,
            &QPushButton::clicked,
            this,
            [this, p]
            {
              if (p.color == Qt::transparent)
              {
                this->canvas->setBrush(Qt::NoBrush);
              }
              else
              {
                QBrush brush = this->canvas->brush();
                brush.setStyle(Qt::SolidPattern);
                brush.setColor(p.color);
                this->canvas->setBrush(brush);
              }
            });

    colorsLayout->addWidget(b);
  }

  connect(toggle, &QPushButton::toggled, colorsWidget, &QWidget::setVisible);
}

}
