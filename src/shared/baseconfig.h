#pragma once

#include "precompiled.h"


class ConfigItem {
public:
    ConfigItem(const QString& key, QVariant defaultValue = QVariant());

    inline QString key()             { return _key; }
    inline QVariant defaultValue()   { return _defaultValue; }
    inline QVariant value()          { return _value; }
    inline QString stringValue()     { return _value.toString(); }
    inline int intValue()            { return _value.toInt(); }

    void setValue(const QVariant& value);

private:
    QString  _key;
    QVariant _defaultValue;
    QVariant _value;
};


class BaseConfig : public QObject {
    Q_OBJECT
public:
    BaseConfig(const QString& group, QObject* parent = nullptr);
    virtual ~BaseConfig();

    void load(QSettings* settings);
    void save(QSettings* settings);

protected:
    ConfigItem* define(const QString& key, QVariant defaultValue = QVariant());

private:
    QString            _group;
    QList<ConfigItem*> _items;
};
