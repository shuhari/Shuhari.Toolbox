#include "precompiled.h"
#include "app.h"
#include "mainwindow.h"


QSettings* appSettings() {
    return qobject_cast<App*>(qApp)->settings();
}


App::App(int argc, char** argv)
    : QApplication(argc, argv) {
    installTranslators();
    registerSettings();
}


void App::installTranslators() {
    installTranslatorByName("qt");
    installTranslatorByName("toolbox");
}


void App::installTranslatorByName(const QString &name) {
    // Lookup translation file in <app>/translations path
    QString localeName = QLocale::system().name();
    auto fileName = QString("%1.%2.qm").arg(name).arg(localeName);
    auto translator = new QTranslator(this);
    QString translationPath = QDir(applicationDirPath()).absoluteFilePath("translations");
    if (translator->load(fileName, translationPath)) {
        installTranslator(translator);
        qDebug() << "Successed load translation file:" << fileName;
    } else {
        qWarning() << "Failed to load translation file:" << fileName;
    }
}


void App::registerSettings() {
    // Lookup settings file in user's document path
    QString configDir = "shuhari.toolbox";
    QString baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir(baseDir).mkdir(configDir);
    QString settingPath = QString("%1/%2/toolbox.ini").arg(baseDir).arg(configDir);
    _settings = new QSettings(settingPath, QSettings::IniFormat, this);
}


int App::run() {
    auto window = new MainWindow();
    window->show();

    return exec();
}
