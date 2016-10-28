#pragma once

#include "precompiled.h"

class Encoder {
public:
    virtual ~Encoder();
    inline QString name()
        { return _name; }
    inline void setName(const QString& name)
        { _name = name; }

    inline virtual bool supportEncode() { return true; }
    inline virtual bool supportDecode() { return true; }
    virtual QString encode(const QString& input, QTextCodec* codec) = 0;
    virtual QString decode(const QString& input, QTextCodec* codec) = 0;

private:
    QString _name;
};


class Base64Encoder : public Encoder {
public:
    virtual QString encode(const QString& input, QTextCodec* codec);
    virtual QString decode(const QString& input, QTextCodec* codec);
};


class Md5Encoder : public Encoder {
public:
    inline virtual bool supportDecode() { return false; }
    virtual QString encode(const QString& input, QTextCodec* codec);
    virtual QString decode(const QString& input, QTextCodec* codec);
};


class UrlEncoder : public Encoder {
public:
    virtual QString encode(const QString& input, QTextCodec* codec);
    virtual QString decode(const QString& input, QTextCodec* codec);
};

class HtmlEncoder : public Encoder {
public:
    HtmlEncoder();
    virtual QString encode(const QString& input, QTextCodec* codec);
    virtual QString decode(const QString& input, QTextCodec* codec);

private:
    QMap<QString, QString> _encodeMap;
    QMap<QString, QString> _decodeMap;

    void registerMap(wchar_t before, const QString& after);
};
