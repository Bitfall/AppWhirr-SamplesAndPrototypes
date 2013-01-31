#include "databasetableschemedescription.h"

DatabaseTableSchemeDescription::DatabaseTableSchemeDescription() :
    _isValid(false)
{
}

void DatabaseTableSchemeDescription::addItem(DatabaseTableSchemeDescriptionItem item) {
    _items.append(item);
}

QList<DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem> DatabaseTableSchemeDescription::getItems() const {
    return _items;
}

bool DatabaseTableSchemeDescription::isEmpty() const {
    return _items.isEmpty();
}

bool DatabaseTableSchemeDescription::isContainsItemWithName(QString name) const {
    int itemCnt = _items.size();
    bool isFound = false;
    for(int i = 0; i < itemCnt && !isFound; i++) {
        if(_items[i].getName() == name) {
            isFound = true;
        }
    }

    return isFound;
}

void DatabaseTableSchemeDescription::removeOneByColumnName(QString name) {
    int itemCnt = _items.size();
    int foundIdx = -1;
    for(int i = 0; i < itemCnt && foundIdx < 0; i++) {
        if(_items[i].getName() == name) {
            foundIdx = i;
        }
    }

    if(foundIdx >= 0) {
        // remove it
        this->_items.removeAt(foundIdx);
    }
}

QString DatabaseTableSchemeDescription::getTableColumnNameAndTypeListString() const
{
    QString result;

    for(int i = 0; i < this->_items.size(); i++) {
        if(i > 0) {
            result += ", ";
        }
        result += this->_items[i].getName() + " " + this->_items[i].getType();
    }

    return result;
}

QString DatabaseTableSchemeDescription::getTableColumnNameListString() const
{
    QString result;

    for(int i = 0; i < this->_items.size(); i++) {
        if(i > 0) {
            result += ", ";
        }
        result += this->_items[i].getName();
    }

    return result;
}
