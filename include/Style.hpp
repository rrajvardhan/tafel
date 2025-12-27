#pragma once

#include <QPalette>

namespace Color
{

inline const QColor SelectionFG{ 110, 90, 220 };
inline const QColor SelectionBG{ 110, 90, 220, 40 };

inline const QColor Primary{ 28, 28, 28 };
inline const QColor Secondary{ 229, 229, 229 };

inline QPalette
Default()
{
  QPalette p;

  // Base surfaces
  p.setColor(QPalette::Window, Color::Secondary);
  p.setColor(QPalette::Button, Color::Primary);

  return p;
}

}
