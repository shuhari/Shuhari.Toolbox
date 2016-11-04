#include "precompiled.h"
#include "baseconfig.h"


ConfigItem::ConfigItem(const QString &key, QVariant defaultValue) {
    _key = key;
    _defaultValue = defaultValue;
    _value = defaultValue;
}


void ConfigItem::setValue(const QVariant &value) {
    _value = value;
}


BaseConfig::BaseConfig(const QString &group, QObject *parent)
    : QObject(parent) {
    _group = group;
}


BaseConfig::~BaseConfig() {
    qDeleteAll(_items);
    _items.clear();
}


ConfigItem* BaseConfig::define(const QString &key, QVariant defaultValue) {
    auto item = new ConfigItem(key, defaultValue);
    _items.append(item);
    return item;
}


void BaseConfig::load(QSettings *settings) {
    foreach (ConfigItem* item, _items) {
        QString key = QString("%1/%2").arg(_group).arg(item->key());
        item->setValue(settings->value(key, item->defaultValue()));
    }
}


void BaseConfig::save(QSettings *settings) {
    foreach (ConfigItem* item, _items) {
        QString key = QString("%1/%2").arg(_group).arg(item->key());
        settings->setValue(key, item->value());
    }
}
