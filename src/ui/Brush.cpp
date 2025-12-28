#include "Canvas.hpp"
#include "ui/Brush.hpp"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <qnamespace.h>

namespace UI
{

struct Paint
{
  std::string name;
  QColor      color;
};

struct BrushPatternBtn
{
  const char*    name;
  const char*    icon;
  Qt::BrushStyle style;
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

  // ---------------------------------------------------------------------------
  // Master controls container (everything toggled together)
  // ---------------------------------------------------------------------------
  auto* controlsWidget = new QWidget(this);
  auto* controlsLayout = new QVBoxLayout(controlsWidget);
  controlsLayout->setContentsMargins(0, 0, 0, 0);
  controlsLayout->setSpacing(6);
  controlsLayout->setAlignment(Qt::AlignLeft);

  // Row 1: colors
  auto* rowColors       = new QWidget(controlsWidget);
  auto* rowColorsLayout = new QHBoxLayout(rowColors);
  rowColorsLayout->setContentsMargins(0, 0, 0, 0);
  rowColorsLayout->setSpacing(6);
  rowColorsLayout->setAlignment(Qt::AlignLeft);

  controlsLayout->addWidget(rowColors);

  auto* rowTools       = new QWidget(controlsWidget);
  auto* rowToolsLayout = new QHBoxLayout(rowTools);
  rowToolsLayout->setContentsMargins(0, 0, 0, 0);
  rowToolsLayout->setSpacing(6);
  rowToolsLayout->setAlignment(Qt::AlignRight);

  controlsLayout->addWidget(rowTools);
  controlsWidget->setVisible(false);

  rootLayout->addWidget(controlsWidget);

  connect(toggle, &QPushButton::toggled, controlsWidget, &QWidget::setVisible);

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
    auto* b = new QPushButton(rowColors);
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
                brush.setColor(p.color);
                this->canvas->setBrush(brush);
              }
            });

    rowColorsLayout->addWidget(b);
  }

  auto* patternWidget = new QWidget(rowTools);
  auto* patternLayout = new QHBoxLayout(patternWidget);
  patternLayout->setContentsMargins(0, 0, 0, 0);
  patternLayout->setSpacing(6);

  rowToolsLayout->addWidget(patternWidget);

  static const BrushPatternBtn patterns[] = {
    { "Solid", ":/icons/sqaure_solid.svg", Qt::SolidPattern },
    // { "Diag", ":/icons/brush.svg", Qt::BDiagPattern },
    { "Cross", ":/icons/brush.svg", Qt::CrossPattern },
  };

  auto* patternGroup = new QButtonGroup(this);
  patternGroup->setExclusive(true);

  for (const auto& pat : patterns)
  {
    auto* b = new QPushButton(patternWidget);
    b->setCheckable(true);
    b->setFixedSize(60, 60);
    b->setToolTip(pat.name);

    b->setIcon(QIcon(pat.icon));
    b->setIconSize(QSize(28, 28));

    b->setStyleSheet("QPushButton {"
                     "  border: 1px solid #1C1C1C;"
                     "  border-radius: 3px;"
                     "}"
                     "QPushButton:hover {"
                     "  border: 2px dashed rgba(28,28,28,220);"
                     "}"
                     "QPushButton:checked {"
                     "  border: 3px dashed #1C1C1C;"
                     "}");

    patternGroup->addButton(b);
    patternLayout->addWidget(b);

    connect(b,
            &QPushButton::clicked,
            this,
            [this, pat]
            {
              QBrush brush = this->canvas->brush();
              brush.setStyle(pat.style);
              this->canvas->setBrush(brush);
            });
  }
}

}
