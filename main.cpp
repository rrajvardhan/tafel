#include "Style.hpp"
#include "Window.hpp"
#include <QApplication>
#include <QFile>

QString
loadQss(const QString& path)
{

  QFile f(path);
  if (!f.open(QFile::ReadOnly))
    qDebug() << "QSS NOT LOADED";

  return QString::fromUtf8(f.readAll());
}

int
main(int argc, char** argv)
{
  QApplication app(argc, argv);

  app.setPalette(Color::Default());

  QString style;
  style += loadQss(":/style/Common.qss");
  style += loadQss(":/style/UI.qss");

  qApp->setStyleSheet(style);

  Window window;
  window.show();

  return app.exec();
}
