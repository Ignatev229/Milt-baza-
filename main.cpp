#include "ViewModel/main_vm.h"
#include <QApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QPixmap>
#include <QQmlApplicationEngine>
// the only one
MainVM theMainVM;

int main(int argc, char *argv[]) {
  qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QApplication app(argc, argv);
  app.setOrganizationName("BottleInsp");
  app.setOrganizationDomain("@BottleInsp.com");
  app.setApplicationName("BottleInsp");
  app.setApplicationDisplayName("BottleInsp");
  app.setDesktopFileName("BottleInsp");
  app.setWindowIcon(QIcon(QPixmap(":/Resources/AppIcon.png")));

  QQmlApplicationEngine engine;

  QUrl url;
  theMainVM.Init(engine, &app);
  engine.rootContext()->setContextProperty("mainVM", &theMainVM);
  url = QUrl(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
