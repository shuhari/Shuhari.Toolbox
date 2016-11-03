#include "precompiled.h"
#include "app.h"
#include "center/centerwindow.h"


QSettings* appSettings() {
    auto app = qobject_cast<App*>(qApp);
    Q_ASSERT(app != nullptr);
    return app->settings();
}


App::App(int argc, char** argv)
    : QApplication(argc, argv) {
    installTranslators();
    registerSettings();
}


int App::run() {
    CenterWindow win;
    win.show();

    return exec();
}


void App::installTranslators() {
    installTranslatorByName("qt");
    installTranslatorByName("toolbox");
}


void App::installTranslatorByName(const QString &name) {
    QString localeName = QLocale::system().name();
    auto fileName = QString("%1.%2.qm").arg(name).arg(localeName);
    auto translator = new QTranslator(this);
    QString transPath = QDir(applicationDirPath()).absoluteFilePath("translations");
    if (translator->load(fileName, transPath)) {
        installTranslator(translator);
        qDebug() << "Load translation success:" << fileName;
    } else {
        qWarning() << "Load translation failed:" << fileName;
        delete translator;
    }
}


void App::registerSettings() {
    // Settings file in user's document path
    QString baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString appName = "shuhari.toolbox";
    QDir(baseDir).mkdir(appName);
    QString settingPath = QString("%1/%2/%2.ini").arg(baseDir).arg(appName);
    _settings = new QSettings(settingPath, QSettings::IniFormat, this);
}
