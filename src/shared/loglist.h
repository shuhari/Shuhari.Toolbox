#pragma once

#include "precompiled.h"

enum LogLevel {
    LogDebug = 1,
    LogInfo = 2,
    LogWarn = 3,
    LogError = 4
};


class LogItem {
public:
    LogItem(LogLevel level, const QString& msg);

    inline LogLevel level() const { return _level; }
    inline QString  msg() const   { return _msg; }

private:
    LogLevel _level;
    QString  _msg;
};


class LogListModel : public QAbstractListModel {
    Q_OBJECT
public:
    LogListModel(QObject* parent = nullptr);
    virtual ~LogListModel();

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int rolw = Qt::DisplayRole) const;

    inline int maxCount() const       { return _maxCount; }
    inline LogLevel viewLevel() const { return _viewLevel; }
    void removeAt(int row);

    void setMaxCount(int value);
    void setViewLevel(LogLevel level);
    LogItem* at(int row) const;
    void clear();
    int append(LogLevel level, const QString& msg);
    QIcon getIcon(LogLevel level) const;
    bool isHidden(int row);

private:
    QList<LogItem*>       _items;
    QMap<LogLevel, QIcon> _icons;
    LogLevel              _viewLevel;
    int                   _maxCount;
};


class LogList : public QListView {
    Q_OBJECT
public:
    LogList(QWidget* parent = nullptr);
    void setMaxCount(int maxCount);

    void debug(const QString& msg);
    void info(const QString& msg);
    void warn(const QString& msg);
    void error(const QString& msg);

public slots:
    void log(int level, const QString& msg);
    void copyToClipboard();
    void clear();

private:
    LogListModel* _model;
    QActionGroup* _viewLevelGroup;

    void createContextMen();
    void addViewLevelAction(LogLevel level, const QString& text);
    void removeAt(int row);

private slots:
    void on_viewLevel(QAction* action);
};
