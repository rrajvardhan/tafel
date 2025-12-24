#include "Theme.hpp"
#include "Window.hpp"
#include <QApplication>

int
main(int argc, char** argv)
{
  QApplication app(argc, argv);

  app.setPalette(Theme::Default());

  Window window;
  window.show();

  return app.exec();
}
