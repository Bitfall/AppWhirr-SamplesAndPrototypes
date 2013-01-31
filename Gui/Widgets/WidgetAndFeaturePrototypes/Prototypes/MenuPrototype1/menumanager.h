#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
QT_END_NAMESPACE

class MenuItemWidget;
class MenuItemManagerElementWidget;

class MenuManagerVertical1 : public QWidget
{
    Q_OBJECT
public:
    explicit MenuManagerVertical1(QWidget *parent = 0);

    void addRootItem(MenuItemWidget *item);
    bool addChildToItem(MenuItemWidget *newChildItem, MenuItemWidget *theParentItem, QWidget *customWidgetToThisItem = NULL);

    MenuItemWidget *getCurrentTopActiveItem();

public slots:
    void itemClickedSlot(MenuItemWidget *source);

private:
    MenuItemManagerElementWidget *getItemElementByItem(MenuItemWidget *itemToSearchFor);
    MenuItemManagerElementWidget *getItemElementByItemRecursive(MenuItemManagerElementWidget *head, MenuItemWidget *itemToSearchFor);

    // return: -1 = not found; else = the index
    int getIndexInCurrentActiveItemPath(MenuItemWidget *item);

    void activateCurrentItemPathToThisIndex(int index);
    void activateThisRootItem(MenuItemManagerElementWidget *itemElement);
    void addThisItemElementToActiveItemElementPathAndActivate(MenuItemManagerElementWidget *itemElement);
    void stepBackToThisIndexInActiveItemPathAndAddAndActivateThisItemElement(int index, MenuItemManagerElementWidget *itemElement);

    void activateCurrentItemPathBySnapshotChange(QList<MenuItemManagerElementWidget *> sourceSnapshot, QList<MenuItemManagerElementWidget *> targetSnapshot);

    void printThisListOfMenuItemElements(QList<MenuItemManagerElementWidget *> menuItemElementList);

private:
    QList<MenuItemManagerElementWidget *> rootMenuItems;
    QVBoxLayout *menuContentLayout;

    // path of the items
    //  e.g.: selected Browser, then Web -> currentActiveItemPath will be { BrowserItemElement, WebItemElement }
    QList<MenuItemManagerElementWidget *> currentActiveItemElementPath;
};

#endif // MENUMANAGER_H
