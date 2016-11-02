#pragma once

#include "precompiled.h"


enum LogLevel {
    L_DEBUG = 1,
    L_INFO = 2,
    L_WARN = 3,
    L_ERROR = 4,
};


class LogItem
{
public:
    LogItem(LogLevel level, const QString& msg);
    LogItem(const LogItem& src);
    LogItem& operator=(const LogItem& src);

    inline LogLevel level() const { return _level; }
    inline QString msg() const { return _msg; }

private:
    void copy(const LogItem& other);

    LogLevel _level;
    QString  _msg;
};


class LogListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    LogListModel(QObject* parent = nullptr);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int rolw = Qt::DisplayRole) const;
    virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

    inline int maxCount() const  { return _maxCount; }
    inline LogLevel viewLevel() const { return _viewLevel; }

    void setMaxCount(int value);
    void setViewLevel(LogLevel level);
    LogItem at(int row);
    void clear();
    int append(LogLevel level, const QString& msg);
    QIcon getIcon(LogLevel lvel) const;
    bool isHidden(int row);

private:
    QList<LogItem>        _items;
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
    void copy();
    void clear();
    void log(int level, const QString& msg);

private:
    LogListModel* _model;
    QActionGroup* _viewLevelGroup;

    void createContextMenu();
    void addViewLevelAction(LogLevel level, const QString& text);

private slots:
    void on_viewLevel(QAction* action);
};
