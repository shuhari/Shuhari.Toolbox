#include "precompiled.h"
#include "encdecwindow.h"
#include "resources.h"
#include "common.h"


EncodeDecodeWindow::EncodeDecodeWindow()
    : ToolWindow() {
}


EncodeDecodeWindow::~EncodeDecodeWindow() {
    qDeleteAll(_encoders.begin(), _encoders.end());
    _encoders.clear();
}


void EncodeDecodeWindow::createChildren() {
    auto inputLabel = new QLabel(strings::input());
    inputLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    auto outputLabel = new QLabel(strings::output());
    outputLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    auto typeLabel = new QLabel(strings::type());
    auto directionLabel = new QLabel(strings::direction());
    auto codecLabel = new QLabel(strings::codec());

    _inputEdit = new QTextEdit();
    _outputEdit = new QTextEdit();
    _outputEdit->setReadOnly(true);
    auto palette = _outputEdit->palette();
    palette.setColor(QPalette::Base, QColor(Qt::lightGray));
    _outputEdit->setPalette(palette);
    _typeCombo = new QComboBox();
    _codecCombo = new QComboBox();
    _encodeRadio = new QRadioButton(strings::encode());
    _decodeRadio = new QRadioButton(strings::decode());
    _encodeRadio->setChecked(true);
    auto swapBtn = new QPushButton(strings::swap());

    auto actionBox = new QHBoxLayout();
    actionBox->addWidget(typeLabel);
    actionBox->addWidget(_typeCombo, 1);
    actionBox->addWidget(codecLabel);
    actionBox->addWidget(_codecCombo, 1);
    actionBox->addWidget(directionLabel);
    actionBox->addWidget(_encodeRadio);
    actionBox->addWidget(_decodeRadio);
    actionBox->addWidget(swapBtn);

    auto grid = new QGridLayout();
    grid->addWidget(inputLabel, 0, 0);
    grid->addWidget(_inputEdit, 0, 1);
    grid->addLayout(actionBox, 1, 1);
    grid->addWidget(outputLabel, 2, 0);
    grid->addWidget(_outputEdit, 2, 1);
    setCentralLayout(grid);

    addEncoder(new Base64Encoder(), "Base64");
    addEncoder(new Md5Encoder(), "MD5");
    addEncoder(new UrlEncoder(), "URL");
    addEncoder(new HtmlEncoder(), "HTML");
    _typeCombo->setCurrentIndex(0);

    auto codecs = QTextCodec::availableCodecs();
    QStringList codecList;
    for (int i=0; i<codecs.size(); i++)
        codecList << QString(codecs[i]);
    codecList.sort(Qt::CaseInsensitive);
    for (int i=0; i<codecList.size(); i++)
        _codecCombo->addItem(codecList[i]);
    _codecCombo->setCurrentText("UTF-8");

    void (QComboBox::*comboIndexChanged)(int) = &QComboBox::currentIndexChanged;
    connect(_inputEdit, &QTextEdit::textChanged, this, &EncodeDecodeWindow::updateOutput);
    connect(_typeCombo, comboIndexChanged, this, &EncodeDecodeWindow::updateOutput);
    connect(_codecCombo, comboIndexChanged, this, &EncodeDecodeWindow::updateOutput);
    connect(_encodeRadio, &QRadioButton::toggled, this, &EncodeDecodeWindow::updateOutput);
    connect(_decodeRadio, &QRadioButton::toggled, this, &EncodeDecodeWindow::updateOutput);
    connect(swapBtn, &QPushButton::clicked, this, &EncodeDecodeWindow::on_swap);

    updateOutput();
}


void EncodeDecodeWindow::addEncoder(Encoder *encoder, const QString &name) {
    encoder->setName(name);
    _typeCombo->addItem(encoder->name(), varFromPointer(encoder));
}


void EncodeDecodeWindow::updateOutput()
{
    auto encoder = (Encoder*)varToPointer(_typeCombo->currentData());
    auto codecName = _codecCombo->currentText();
    auto input = _inputEdit->toPlainText().trimmed();
    if (encoder && !codecName.isEmpty())  {
        _encodeRadio->setEnabled(encoder->supportEncode());
        _decodeRadio->setEnabled(encoder->supportDecode());

        auto codec = QTextCodec::codecForName(codecName.toLocal8Bit());
        QString output = _encodeRadio->isChecked() ?
                    encoder->encode(input, codec) :
                    encoder->decode(input, codec);
        _outputEdit->setPlainText(output);
    }
}


void EncodeDecodeWindow::on_swap()
{
    auto input = _inputEdit->toPlainText().trimmed();
    auto output = _outputEdit->toPlainText().trimmed();
    _inputEdit->setPlainText(output);
    _outputEdit->setPlainText(input);
}
