#include "Canvas.hpp"
#include "ui/Stroke.hpp"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

namespace UI
{

struct Paint
{
  std::string name;
  QColor      color;
};

struct PenStyleBtn
{
  std::string  name;
  std::string  icon;
  Qt::PenStyle style;
};

Stroke::Stroke(Canvas* canvas) : QWidget(canvas), canvas(canvas)
{
  setObjectName("Stroke");

  // ---------------------------------------------------------------------------
  // Root layout
  // ---------------------------------------------------------------------------
  auto* rootLayout = new QHBoxLayout(this);
  rootLayout->setContentsMargins(0, 0, 0, 0);
  rootLayout->setSpacing(4);
  rootLayout->setAlignment(Qt::AlignLeft);

  // ---------------------------------------------------------------------------
  // Toggle button
  // ---------------------------------------------------------------------------
  auto* toggle = new QPushButton(this);
  toggle->setCheckable(true);
  toggle->setChecked(false);
  toggle->setFixedSize(80, 80);
  toggle->setIcon(QIcon(":/icons/palette.svg"));
  toggle->setIconSize(QSize(32, 32));
  toggle->setToolTip("pen");

  toggle->setStyleSheet("QPushButton {"
                        "  border: 2px solid #1C1C1C;"
                        "  border-radius: 3px;"
                        "}"
                        "QPushButton:hover {"
                        "  border: 2px dashed rgba(28, 28, 28, 220);"
                        "  border-radius: 3px;"
                        "}"
                        "QPushButton:checked {"
                        "  border: 3px dashed #1C1C1C;"
                        "}");

  rootLayout->addWidget(toggle);

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

  // Row 2: width + style + cap
  auto* rowTools       = new QWidget(controlsWidget);
  auto* rowToolsLayout = new QHBoxLayout(rowTools);
  rowToolsLayout->setContentsMargins(0, 0, 0, 0);
  rowToolsLayout->setSpacing(6);
  rowToolsLayout->setAlignment(Qt::AlignRight);

  controlsLayout->addWidget(rowTools);

  controlsWidget->setVisible(false);
  rootLayout->addWidget(controlsWidget);

  connect(toggle, &QPushButton::toggled, controlsWidget, &QWidget::setVisible);

  // ---------------------------------------------------------------------------
  // Color controls
  // ---------------------------------------------------------------------------
  auto* colorsWidget = new QWidget(controlsWidget);
  auto* colorsLayout = new QHBoxLayout(colorsWidget);
  colorsLayout->setContentsMargins(0, 0, 0, 0);
  colorsLayout->setSpacing(6);

  rowColorsLayout->addWidget(colorsWidget);

  static const Paint paints[] = {
    { "None", QColor(Qt::transparent) }, { "Black", QColor("#0F0F0F") },
    { "Gray", QColor("#6B7280") },       { "White", QColor("#FFFFFF") },
    { "Red", QColor("#EF4444") },        { "Amber", QColor("#F59E0B") },
    { "Lime", QColor("#84CC16") },       { "Cyan", QColor("#06B6D4") },
    { "Blue", QColor("#3B82F6") },       { "Violet", QColor("#8B5CF6") },
  };

  auto* colorGroup = new QButtonGroup(this);
  colorGroup->setExclusive(true);

  for (const auto& p : paints)
  {
    auto* b = new QPushButton(colorsWidget);
    b->setCheckable(true);
    b->setFixedSize(60, 60);
    b->setToolTip(QString::fromStdString(p.name));

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

    colorGroup->addButton(b);
    colorsLayout->addWidget(b);

    connect(b,
            &QPushButton::clicked,
            this,
            [this, p]
            {
              QPen pen = this->canvas->pen();
              pen.setColor(p.color);
              this->canvas->setPen(pen);
            });
  }
  // ---------------------------------------------------------------------------
  // Stroke controls
  // ---------------------------------------------------------------------------
  auto* widthWidget = new QWidget(controlsWidget);
  auto* widthLayout = new QHBoxLayout(widthWidget);
  widthLayout->setContentsMargins(0, 0, 0, 0);
  widthLayout->setSpacing(6);

  rowToolsLayout->addWidget(widthWidget);

  auto* widthGroup = new QButtonGroup(this);
  widthGroup->setExclusive(true);

  const QList<qreal> widths = { 2.0, 4.0, 6.0 };

  for (qreal w : widths)
  {
    auto* b = new QPushButton(widthWidget);
    b->setCheckable(true);
    b->setFixedSize(60, 60);

    b->setIcon(QIcon(":/icons/circle_solid.svg"));

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

    int base     = 4;
    int iconSize = base + static_cast<int>(w * 2.5);
    b->setIconSize(QSize(iconSize, iconSize));

    widthGroup->addButton(b);
    widthLayout->addWidget(b);

    connect(b,
            &QPushButton::clicked,
            this,
            [this, w]
            {
              QPen pen = this->canvas->pen();
              pen.setWidthF(w);
              this->canvas->setPen(pen);
            });
  }

  // ---------------------------------------------------------------------------
  // Pen style controls
  // ---------------------------------------------------------------------------
  auto* styleWidget = new QWidget(controlsWidget);
  auto* styleLayout = new QHBoxLayout(styleWidget);
  styleLayout->setContentsMargins(0, 0, 0, 0);
  styleLayout->setSpacing(6);

  rowToolsLayout->addWidget(styleWidget);

  auto* styleGroup = new QButtonGroup(this);
  styleGroup->setExclusive(true);

  static const PenStyleBtn styles[] = {
    { "Solid", ":/icons/pen_solid.svg", Qt::SolidLine },
    { "Dash", ":/icons/pen_dashed.svg", Qt::DashLine },
  };

  for (const auto& s : styles)
  {
    auto* b = new QPushButton(styleWidget);
    b->setCheckable(true);
    b->setToolTip(QString::fromStdString(s.name));
    b->setFixedSize(60, 60);

    if (!s.icon.empty())
    {
      b->setIcon(QIcon(QString::fromStdString(s.icon)));
      b->setIconSize(QSize(28, 28));
    }
    else
    {
      b->setText(QString::fromStdString(s.icon));
    }

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

    styleGroup->addButton(b);
    styleLayout->addWidget(b);

    connect(b,
            &QPushButton::clicked,
            this,
            [this, s]
            {
              QPen pen = this->canvas->pen();
              pen.setStyle(s.style);
              this->canvas->setPen(pen);
            });
  }
}
} // namespace UI
