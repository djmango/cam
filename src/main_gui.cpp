#include <QApplication>
#include <QSurfaceFormat>

#include "main_window.hpp"

int main(int argc, char *argv[]) {
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setVersion(3, 2);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setSamples(4);                                 // Enable multisampling
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer); // Enable double buffering
  QSurfaceFormat::setDefaultFormat(format);

  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}
