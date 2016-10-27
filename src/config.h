#pragma once


#include "precompiled.h"


class ConfigItem {
public:
    ConfigItem(QString key, QVariant defaultValue);
    ConfigItem(const ConfigItem& src);
    ConfigItem& operator=(const ConfigItem& src);
    inline QString key()           { return _key; }
    inline QVariant defaultValue() { return _defaultValue; }
    inline QVariant value()        { return _value; }
    inline void setValue(QVariant value) { _value = value; }

private:
    QString _key;
    QVariant _defaultValue;
    QVariant _value;

    void copy(const ConfigItem& src);
};


class Config : public QObject {
    Q_OBJECT
public:
    Config(const QString& group, QObject* parent = nullptr);
    ~Config();
    void load(QSettings* settings);
    void save(QSettings* settings);

protected:
    ConfigItem* define(const QString& key, QVariant defaultValue = QVariant());

private:
    QString            _group;
    QList<ConfigItem*> _items;
};
