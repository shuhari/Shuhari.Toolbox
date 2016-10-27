#include "precompiled.h"
#include "loglist.h"
#include "resources.h"


LogItem::LogItem(LogLevel level, const QString &msg) {
    _level = level;
    _msg = msg;
}


LogItem::LogItem(const LogItem &src) {
    copy(src);
}


void LogItem::copy(const LogItem &src) {
    _level = src._level;
    _msg = src._msg;
}


LogItem& LogItem::operator =(const LogItem& src) {
    copy(src);
    return *this;
}


LogListModel::LogListModel(QObject *parent)
    : QAbstractListModel(parent) {
    _viewLevel = LogLevel::L_DEBUG;
    _maxCount = 0;

    QStyle* style = qApp->style();
    _icons[L_DEBUG] = style->standardIcon(QStyle::SP_MessageBoxQuestion);
    _icons[L_INFO] = style->standardIcon(QStyle::SP_MessageBoxInformation);
    _icons[L_WARN] = style->standardIcon(QStyle::SP_MessageBoxWarning);
    _icons[L_ERROR] = style->standardIcon(QStyle::SP_MessageBoxCritical);
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


QVariant LogListModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        auto item = _items.at(row);
        switch (role) {
        case Qt::DisplayRole: return item.msg();
        case Qt::UserRole: return (int)item.level();
        case Qt::DecorationRole: return getIcon(item.level());
        }
    }

    return QVariant();
}


LogItem LogListModel::at(int row) {
    return _items[row];
}


bool LogListModel::removeRows(int row, int count, const QModelIndex &parent) {
    Q_UNUSED(parent);

    if (row >= 0 && row + count <= _items.size()) {
        for (int i=0; i<count; i++)
            _items.removeAt(i);
        return true;
    }
    return false;
}


int LogListModel::append(LogLevel level, const QString& msg) {
    if (_maxCount > 0 && _items.size() > _maxCount) {
        removeRows(0, _items.size() - _maxCount);
    }

    auto time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    auto log = QString("[%1] %2").arg(time).arg(msg);

    int row = _items.size();
    beginInsertRows(QModelIndex(), row, row);
    _items.append(LogItem(level, log));
    endInsertRows();
    return row;
}


QIcon LogListModel::getIcon(LogLevel level) const {
    return _icons[level];
}


void LogListModel::clear() {
    int count = _items.size();
    _items.clear();
    removeRows(0, count);
}


void LogListModel::setViewLevel(LogLevel level) {
    _viewLevel = level;
}


bool LogListModel::isHidden(int row) {
    if (row >= 0 && row < _items.size()) {
        return _items[row].level() < _viewLevel;
    }
    return true;
}

LogList::LogList(QWidget *parent)
    : QListView(parent) {
    _model = new LogListModel(this);
    setModel(_model);

    createContextMenu();
}


void LogList::createContextMenu() {
    setContextMenuPolicy(Qt::ActionsContextMenu);

    auto copy = new QAction(QIcon(":/copy"), strings::copy(), this);
    addAction(copy);

    auto clear = new QAction(QIcon(":/clear"), strings::clear(), this);
    addAction(clear);

    auto sep = new QAction(this);
    sep->setSeparator(true);
    addAction(sep);

    _viewLevelGroup = new QActionGroup(this);
    addViewLevelAction(L_DEBUG, strings::debug());
    addViewLevelAction(L_INFO, strings::info());
    addViewLevelAction(L_WARN, strings::warning());
    addViewLevelAction(L_ERROR, strings::error());

    connect(copy, &QAction::triggered, this, &LogList::copy);
    connect(clear, &QAction::triggered, this, &LogList::clear);
    connect(_viewLevelGroup, &QActionGroup::triggered, this, &LogList::on_viewLevel);
}


void LogList::addViewLevelAction(LogLevel level, const QString &text) {
    QIcon icon = _model->getIcon(level);
    auto action = new QAction(icon, text, this);
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


void LogList::copy() {
    QStringList lines;
    foreach(QModelIndex index, selectionModel()->selectedIndexes()) {
        auto item = _model->at(index.row());
        lines << item.msg();
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
    log(L_DEBUG, msg);
}

void LogList::info(const QString &msg) {
    log(L_INFO, msg);
}

void LogList::warn(const QString &msg) {
    log(L_WARN, msg);
}

void LogList::error(const QString &msg) {
    log(L_ERROR, msg);
}


