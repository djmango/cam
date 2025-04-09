#include "main_window.hpp"

#include <QOpenGLWidget>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QFileInfo>
#include <QApplication>

#include "viewer/OCCTWidget.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  auto *central = new QWidget(this);
  auto *layout = new QVBoxLayout(central);

  viewer = new OCCTWidget(this);
  layout->addWidget(viewer);

  auto *meshButton = new QPushButton("Mesh It!", this);
  connect(meshButton, &QPushButton::clicked, [this]() {
    viewer->meshShape();  // call your mesh function
  });

  layout->addWidget(meshButton);

  setCentralWidget(central);
  setWindowTitle("DFM Visualizer");

  // Get the absolute path to the STEP file
  QString stepFile = "8880T951_Steel U-Bolt.STEP";
  QFileInfo fileInfo(stepFile);
  if (!fileInfo.exists())
  {
    qDebug() << "❌ STEP file not found:" << stepFile;
    return;
  }
  QString absolutePath = fileInfo.absoluteFilePath();
  qDebug() << "📂 STEP file path:" << absolutePath;

  // ✅ Delay loadSTEP until OpenGL context is ready
  QTimer::singleShot(1000, this, [this, absolutePath]()
                     {
    qDebug() << "📦 Triggering loadSTEP from MainWindow";
    viewer->loadSTEP(absolutePath.toStdString()); });

  // ✅ Delay additional redraw AFTER widget is shown on screen
  QTimer::singleShot(1100, viewer, [this]()
                     {
                       qDebug() << "🔁 Forcing post-show repaint";
                       viewer->update();  // schedule paintGL
                       viewer->repaint(); // force immediate paintGL
                     });
}

MainWindow::~MainWindow() = default;
