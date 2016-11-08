#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"


class EncodeWindow : public ToolWindow {
    Q_OBJECT
public:
    EncodeWindow();
    virtual ~EncodeWindow();

    static ToolItem* define();

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
