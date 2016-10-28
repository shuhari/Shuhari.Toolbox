#pragma once

#include "precompiled.h"
#include "toolwindow.h"
#include "encoders.h"


class EncodeDecodeWindow : public ToolWindow {
    Q_OBJECT
public:
    EncodeDecodeWindow();
    ~EncodeDecodeWindow();

protected:
    virtual void createChildren();

private:
    QTextEdit*      _inputEdit;
    QTextEdit*      _outputEdit;
    QComboBox*      _typeCombo;
    QComboBox*      _codecCombo;
    QRadioButton*   _encodeRadio;
    QRadioButton*   _decodeRadio;
    QList<Encoder*> _encoders;

    void            addEncoder(Encoder* encoder, const QString& name);

private slots:
    void            updateOutput();
    void            on_swap();
};
