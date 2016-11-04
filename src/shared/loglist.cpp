#include "precompiled.h"
#include "loglist.h"
#include "resources.h"


LogItem::LogItem(LogLevel level, const QString &msg) {
    _level = level;
    _msg = msg;
}


LogListModel::LogListModel(QObject *parent)
    : QAbstractListModel(parent) {
    _viewLevel = LogDebug;
    _maxCount = 0;

    QStyle* style = qApp->style();
    _icons[LogDebug] = style->standardIcon(QStyle::SP_MessageBoxQuestion);
    _icons[LogInfo] = style->standardIcon(QStyle::SP_MessageBoxInformation);
    _icons[LogWarn] = style->standardIcon(QStyle::SP_MessageBoxWarning);
    _icons[LogError] = style->standardIcon(QStyle::SP_MessageBoxCritical);
}


LogListModel::~LogListModel() {
    clear();
}


void LogListModel::setMaxCount(int value) {
    if (value >= 0 && value != _maxCount) {
        _maxCount = value;
    }
}


int LogListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _items.size();
}


void LogListModel::clear() {
    int count = _items.size();
    if (count > 0) {
        beginRemoveRows(QModelIndex(), 0, count - 1);
        qDeleteAll(_items);
        _items.clear();
        endRemoveRows();
    }
}


void LogListModel::removeAt(int row) {
    if (row >= 0 && row < _items.size()) {
        beginRemoveRows(QModelIndex(), row, row);
        auto item = at(row);
        _items.removeAt(row);
        delete item;
        endRemoveRows();
    }
}


LogItem* LogListModel::at(int row) const {
    Q_ASSERT(row >= 0 && row < _items.size());
    return _items[row];
}


QVariant LogListModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        auto item = at(row);
        switch (role) {
        case Qt::DisplayRole: return item->msg();
        case Qt::UserRole: return (int)item->level();
        case Qt::DecorationRole: return getIcon(item->level());
        }
    }
    return QVariant();
}


int LogListModel::append(LogLevel level, const QString &msg) {
    if (_maxCount > 0) {
        while (_items.size() > _maxCount)
            removeAt(0);
    }
    auto time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    auto log = QString("[%1] %2").arg(time).arg(msg);

    int row = _items.size();
    beginInsertRows(QModelIndex(), row, row);
    _items.append(new LogItem(level, log));
    endInsertRows();
    return row;
}


QIcon LogListModel::getIcon(LogLevel level) const {
    return _icons[level];
}


void LogListModel::setViewLevel(LogLevel level) {
    _viewLevel = level;
}


bool LogListModel::isHidden(int row) {
    if (row >= 0 && row < _items.size()) {
        return _items[row]->level() < _viewLevel;
    }
    return true;
}


LogList::LogList(QWidget *parent)
    : QListView(parent) {
    _model = new LogListModel(this);
    setModel(_model);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    createContextMen();
}


void LogList::createContextMen() {
    auto copyAct = new QAction(QIcon(":/copy"), strings::copy(), this);
    addAction(copyAct);

    auto clearAct = new QAction(QIcon(":/clear"), strings::clear(), this);
    addAction(clearAct);

    auto sep = new QAction(this);
    sep->setSeparator(true);
    addAction(sep);

    _viewLevelGroup = new QActionGroup(this);
    addViewLevelAction(LogDebug, strings::debug());
    addViewLevelAction(LogInfo, strings::info());
    addViewLevelAction(LogWarn, strings::warning());
    addViewLevelAction(LogError, strings::error());

    connect(copyAct, &QAction::triggered, this, &LogList::copyToClipboard);
    connect(clearAct, &QAction::triggered, this, &LogList::clear);
    connect(_viewLevelGroup, &QActionGroup::triggered, this, &LogList::on_viewLevel);
}


void LogList::addViewLevelAction(LogLevel level, const QString &text) {
    auto action = new QAction(text, this);
    action->setCheckable(true);
    action->setActionGroup(_viewLevelGroup);
    action->setChecked(level == _model->viewLevel());
    action->setProperty("type", "viewLevel");
    action->setProperty("level", (int)level);
    addAction(action);
}


void LogList::setMaxCount(int maxCount) {
    _model->setMaxCount(maxCount);
}


void LogList::copyToClipboard() {
    QStringList lines;
    foreach(QModelIndex index, selectionModel()->selectedIndexes()) {
        auto item = _model->at(index.row());
        lines << item->msg();
    }
    auto text = lines.join("\r\n");
    QApplication::clipboard()->setText(text);
}


void LogList::clear() {
    _model->clear();
}


void LogList::on_viewLevel(QAction *action) {
    auto level = (LogLevel)action->property("level").toInt();

    foreach(QAction* action, _viewLevelGroup->actions()) {
        if (action->property("type").toString() == "viewLevel") {
            auto actionLevel = (LogLevel)action->property("level").toInt();
            action->setChecked(actionLevel == level);
        }
    }

    _model->setViewLevel(level);
    for (int row=0; row<_model->rowCount(); row++)
        setRowHidden(row, _model->isHidden(row));
}


void LogList::log(int level, const QString &msg) {
    int row = _model->append((LogLevel)level, msg);
    setRowHidden(row, _model->isHidden(row));
    scrollTo(_model->index(row));
}

void LogList::debug(const QString &msg) {
    log(LogDebug, msg);
}

void LogList::info(const QString &msg) {
    log(LogInfo, msg);
}

void LogList::warn(const QString &msg) {
    log(LogWarn, msg);
}

void LogList::error(const QString &msg) {
    log(LogError, msg);
}


