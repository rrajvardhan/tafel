#include "Style.hpp"
#include "Window.hpp"
#include <QApplication>
#include <QFile>
#include <QFontDatabase>

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

  int fontId = QFontDatabase::addApplicationFont(":/fonts/PatrickHand-Regular.ttf");

  if (fontId != -1)
  {
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

    QFont font(family);
    app.setFont(font);
  }

  app.setPalette(Color::Default());

  QString style;
  style += loadQss(":/style/Common.qss");
  style += loadQss(":/style/UI.qss");

  qApp->setStyleSheet(style);

  Window window;
  window.show();

  return app.exec();
}
