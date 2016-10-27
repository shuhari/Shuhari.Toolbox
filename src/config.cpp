#include "precompiled.h"
#include "config.h"


ConfigItem::ConfigItem(QString key, QVariant defaultValue) {
    _key = key;
    _defaultValue = defaultValue;
}


ConfigItem::ConfigItem(const ConfigItem &src) {
    copy(src);
}


ConfigItem& ConfigItem::operator =(const ConfigItem& src) {
    copy(src);
    return *this;
}


void ConfigItem::copy(const ConfigItem &src) {
    _key = src._key;
    _defaultValue = src._defaultValue;
    _value = src._value;
}


Config::Config(const QString& group, QObject* parent)
    : QObject(parent) {
    _group = group;
}


Config::~Config() {
    qDeleteAll(_items.begin(), _items.end());
}


ConfigItem* Config::define(const QString& key, QVariant defaultValue) {
    auto item = new ConfigItem(key, defaultValue);
    _items.append(item);
    return item;
}


void Config::load(QSettings* settings) {
    foreach (ConfigItem* item, _items) {
        QString key = QString("%1/%2").arg(_group).arg(item->key());
        item->setValue(settings->value(key, item->defaultValue()));
    }
}


void Config::save(QSettings *settings) {
    foreach (ConfigItem* item, _items) {
        QString key = QString("%1/%2").arg(_group).arg(item->key());
        settings->setValue(key, item->value());
    }
}
