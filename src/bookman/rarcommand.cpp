#include "precompiled.h"
#include "rarcommand.h"
#include <windows.h>


RarCommand::RarCommand(const QString &exePath) {
    _exePath = exePath;
}


bool RarCommand::extract(const QString& rarPath, const QString& path, OverwriteMode override) {
    QString srcPath = rarPath;
    QString destPath = path;
    if (destPath.isEmpty()) {
        destPath = QFileInfo(rarPath).absolutePath();
    }
    srcPath = srcPath.replace('/', '\\');
    destPath = destPath.replace('/', '\\');

    QStringList arguments;
    arguments << "e";
    arguments << "-scu";
    switch (override)
    {
    case OverwriteMode::Ask: arguments << "-o"; break;
    case OverwriteMode::Overwrite: arguments << "-o+"; break;
    case OverwriteMode::Skip: arguments << "-o-"; break;
    case OverwriteMode::DontCare: break;
    }
    arguments << QString("\"%1\"").arg(srcPath);
    arguments << QString("\"%1\"").arg(destPath);
    QString cmd =  QString("\"%1\"").arg(_exePath);
    QString argLine = arguments.join(" ");
    qDebug() << "rar cmd:" << cmd << argLine;
    // record command line for diagnostics
    /*
    QFile cmdFile("cmd.log");
    if (cmdFile.open(QFile::Text | QFile::WriteOnly | QFile::Append))
    {
        cmdFile.write(cmd.toLatin1());
        cmdFile.write(arguments.join(" ").toLatin1());
        cmdFile.write("\r\n");
        cmdFile.close();
    }*/

    // TODO: run rar.exe through QProcess return code 10
    //  don't know why, use windows process instead
    /*
    QProcess process;
    process.start(cmd, arguments, QIODevice::ReadWrite);
    if (!process.waitForFinished()) {
        qDebug() << "process waitForFinished failed";
        return false;
    }
    int exitCode = process.exitCode();
    qDebug() << "process exitCode=" << exitCode;
    return (exitCode == 0);
    */
    argLine = QString("\"%1\" ").arg(_exePath) + argLine;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    PROCESS_INFORMATION pi;
    DWORD dwExitCode = STILL_ACTIVE;
    BOOL res = CreateProcess(NULL,
        (PWSTR)argLine.utf16(),
        NULL,
        NULL,
        FALSE,
        NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
        NULL,
        (PCWSTR)destPath.utf16(),
        &si,
        &pi);
    if (res)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &dwExitCode);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    qDebug() << "result:" << dwExitCode;
    return dwExitCode == 0;

}
