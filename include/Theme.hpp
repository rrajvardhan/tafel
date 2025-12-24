#pragma once

#include <QPalette>

namespace Theme
{

inline QPalette
Default()
{
  QPalette p;

  // Base surfaces
  p.setColor(QPalette::Window, QColor("#21202e"));        // background
  p.setColor(QPalette::Base, QColor("#1c1b22"));          // inputs, text fields
  p.setColor(QPalette::AlternateBase, QColor("#26213D")); // selection-ish alt bg

  // Text
  p.setColor(QPalette::WindowText, QColor("#edecee"));
  p.setColor(QPalette::Text, QColor("#edecee"));
  p.setColor(QPalette::ButtonText, QColor("#edecee"));
  p.setColor(QPalette::PlaceholderText, QColor("#4d4d4d"));

  // Buttons
  p.setColor(QPalette::Button, QColor("#21202e"));

  // Selection / highlight
  p.setColor(QPalette::Highlight, QColor("#26213D"));
  p.setColor(QPalette::HighlightedText, QColor("#edecee"));

  // Links / URLs
  p.setColor(QPalette::Link, QColor("#61ffca"));
  p.setColor(QPalette::LinkVisited, QColor("#a277ff"));

  // Disabled state (don’t forget this or Qt will)
  p.setColor(QPalette::Disabled, QPalette::WindowText, QColor("#4d4d4d"));
  p.setColor(QPalette::Disabled, QPalette::Text, QColor("#4d4d4d"));
  p.setColor(QPalette::Disabled, QPalette::ButtonText, QColor("#4d4d4d"));

  return p;
}

}
