#include "menumanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

#include "menuitem.h"
#include "menuitemmanagerelement.h"

MenuManagerVertical1::MenuManagerVertical1(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    /*this->setMinimumWidth(200);
    this->setMaximumWidth(200);*/
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);

    QWidget *menuContentHolderWidget = new QWidget;
    menuContentLayout = new QVBoxLayout;
    menuContentHolderWidget->setLayout(menuContentLayout);
    menuContentHolderWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainLayout->addWidget(menuContentHolderWidget);

    QWidget *spacerWidget = new QWidget;
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(spacerWidget);
}

void MenuManagerVertical1::addRootItem(MenuItemWidget *item)
{
    //menuItems << item;
    connect(item, SIGNAL(itemClick(MenuItemWidget*)), this, SLOT(itemClickedSlot(MenuItemWidget*)));
    MenuItemManagerElementWidget *newElem = new MenuItemManagerElementWidget(item);
    //theLayout
    rootMenuItems << newElem;

    menuContentLayout->addWidget(newElem);
}

MenuItemWidget *MenuManagerVertical1::getCurrentTopActiveItem()
{
    if(currentActiveItemElementPath.isEmpty())
    {
        return NULL;
    }

    return currentActiveItemElementPath.last()->getRelatedMenuItem();
}


bool MenuManagerVertical1::addChildToItem(MenuItemWidget *newChildItem, MenuItemWidget *theParentItem, QWidget *customWidgetToThisItem)
{
    MenuItemManagerElementWidget *parentItemElem = getItemElementByItem(theParentItem);
    if(parentItemElem == NULL)
    {
        // parent cannot be found
        return false;
    }

    connect(newChildItem, SIGNAL(itemClick(MenuItemWidget*)), this, SLOT(itemClickedSlot(MenuItemWidget*)));
    MenuItemManagerElementWidget *newElem = new MenuItemManagerElementWidget(newChildItem);

    if(customWidgetToThisItem != NULL)
    {
        newElem->addCustomWidget(customWidgetToThisItem);
    }

    parentItemElem->addChildToLayout(newElem);

    newElem->hideImmediatelly();

    return true;
}

void MenuManagerVertical1::itemClickedSlot(MenuItemWidget *source)
{
    qDebug("slot");

    MenuItemManagerElementWidget *containerElem = getItemElementByItem(source);
    if(containerElem != NULL)
    {
        if(!currentActiveItemElementPath.isEmpty())
        {
            if( currentActiveItemElementPath.last()->getRelatedMenuItem() == source )
            {
                // the clicked element is the currently selected one
                // so (at least now) don't do anything
                return;
            }
        }
        //qDebug("found");
        //qDebug(containerElem->getRelatedMenuItem()->getId().toAscii());
        int idxInPath = getIndexInCurrentActiveItemPath(source);
        if(idxInPath != -1)
        {
            // the clicked item is in the currently active item-path
            // so change only the path
            this->activateCurrentItemPathToThisIndex(idxInPath);
        }
        else
        {
            // this item is not in the active-item-path, so
            //  this will be a new item -> fill it's sub-items
            //emit fillSubItemsToThisItem(source);
            source->_emitFillSubItemsToThisItemSignal();

            // the clicked item is not in the currently active item-path
            // so it has to be a root item or a child of the currently active elem

            bool isFound = false;

            // check: is it a child of an item in the active-item-path?
            int activeItemPathCnt = currentActiveItemElementPath.size();
            for(int i = 0; i < activeItemPathCnt && !isFound; i++)
            {
                QList<MenuItemManagerElementWidget *> currentlyActiveItemElementChildren = currentActiveItemElementPath[i]->getChildrenElements();
                int childrenCnt = currentlyActiveItemElementChildren.size();
                for(int j = 0 ; j < childrenCnt && !isFound; j++)
                {
                    if(currentlyActiveItemElementChildren[j]->getRelatedMenuItem() == source)
                    {
                        isFound = true;
                        //addThisItemElementToActiveItemElementPathAndActivate(currentlyActiveItemElementChildren[i]);
                        stepBackToThisIndexInActiveItemPathAndAddAndActivateThisItemElement(i, currentlyActiveItemElementChildren[j]);
                    }
                }
            }


            // check: is it a root item?
            if(!isFound)
            {
                int rootCnt = rootMenuItems.size();
                for(int i = 0; i < rootCnt && !isFound; i++)
                {
                    if(rootMenuItems[i]->getRelatedMenuItem() == source)
                    {
                        isFound = true;
                        activateThisRootItem(rootMenuItems[i]);
                    }
                }

                if(!isFound)
                {
                    qDebug("Clicked item was not found in the root items as well. What the heck? Something is incorrect.");
                }
            }
        }

        //emit itemClickedSignal(source);
        source->_emitItemBecomeTheTopActiveOneSignal();
        return;
    }

    qDebug("the clicked item not found!!!");
}

void MenuManagerVertical1::stepBackToThisIndexInActiveItemPathAndAddAndActivateThisItemElement(int index, MenuItemManagerElementWidget *itemElement)
{
    int itemCnt = currentActiveItemElementPath.size();

    if(index < 0 || index > itemCnt-1)
    {
        qDebug("invalid index - stepBackToThisIndexInActiveItemPathAndAddAndActivateThisItemElement");
    }

#if 0
    int itemCnt = currentActiveItemElementPath.size();
    for(int i = itemCnt-1; i > index; i--)
    {
        currentActiveItemElementPath[i]->hideAnimated();
        currentActiveItemElementPath.removeAt(i);
    }

    addThisItemElementToActiveItemElementPathAndActivate(itemElement);
#endif

    QList<MenuItemManagerElementWidget *> newItemPath;
    for(int i = 0; i <= index; i++)
    {
        newItemPath << currentActiveItemElementPath[i];
    }
    newItemPath << itemElement;

    activateCurrentItemPathBySnapshotChange(currentActiveItemElementPath, newItemPath);
}

void MenuManagerVertical1::addThisItemElementToActiveItemElementPathAndActivate(MenuItemManagerElementWidget *itemElement)
{
#if 0
    currentActiveItemElementPath << itemElement;
    activateCurrentItemPathToThisIndex(currentActiveItemElementPath.size() - 1);
#endif
    QList<MenuItemManagerElementWidget *> newItemPath;
    for(int i = 0; i < currentActiveItemElementPath.size(); i++)
    {
        newItemPath << currentActiveItemElementPath[i];
    }
    newItemPath << itemElement;
    activateCurrentItemPathBySnapshotChange(currentActiveItemElementPath, newItemPath);
}

void MenuManagerVertical1::activateCurrentItemPathToThisIndex(int index)
{
    int itemCnt = currentActiveItemElementPath.size();

    if(index < 0 || index > itemCnt-1)
    {
        qDebug("invalid index - activateCurrentItemPathToThisIndex");
    }

#if 0
    int itemCnt = currentActiveItemElementPath.size();
    for(int i = itemCnt-1; i >= 0; i--)
    {
        /*if(i == 0)
        {
            // index = 0: it's a root, don't hide it, only deactivate
            currentActiveItemElementPath[i]->animatedDeactivate();
        }
        else */if(i > index)
        {
            currentActiveItemElementPath[i]->hideAnimated();
            currentActiveItemElementPath.removeAt(i);
        }
        /*else if(i == index)
        {
            currentActiveItemElementPath[i]->animatedDeactivate();
        }*/
        else
        {
            qDebug() << "ll" << i << index;
            // level 0 is the top-active level
            currentActiveItemElementPath[i]->animatedActivateWithLevel(index - i);
        }
    }
#endif
    QList<MenuItemManagerElementWidget *> newItemPath;
    for(int i = 0; i <= index; i++)
    {
        newItemPath << currentActiveItemElementPath[i];
    }
    activateCurrentItemPathBySnapshotChange(currentActiveItemElementPath, newItemPath);
}

void MenuManagerVertical1::activateThisRootItem(MenuItemManagerElementWidget *itemElement)
{
#if 0
    // deactivate every item in the current path
    int itemCnt = currentActiveItemElementPath.size();
    if(itemCnt > 0)
    {
        // index = 0: it's a root, don't hide it, only deactivate
        currentActiveItemElementPath[0]->animatedDeactivate();
        for(int i = 1; i < itemCnt; i++)
        {
            currentActiveItemElementPath[i]->hideAnimated();
        }
    }

    // and also clear it
    currentActiveItemElementPath.clear();

    // now activate the selected root elem
    itemElement->animatedActivateWithLevel(0);

    // and add it to the path
    currentActiveItemElementPath << itemElement;

    // TEST
    printThisListOfMenuItemElements(currentActiveItemElementPath);
#endif

    QList<MenuItemManagerElementWidget *> newItemPath;
    newItemPath << itemElement;
    activateCurrentItemPathBySnapshotChange(currentActiveItemElementPath, newItemPath);
}

void MenuManagerVertical1::activateCurrentItemPathBySnapshotChange(QList<MenuItemManagerElementWidget *> sourceSnapshot, QList<MenuItemManagerElementWidget *> targetSnapshot)
{
    // TEST
    qDebug("# source");
    printThisListOfMenuItemElements(sourceSnapshot);

    qDebug("# target");
    printThisListOfMenuItemElements(targetSnapshot);
    //


    int sourceSnapshotCnt = sourceSnapshot.size();
    int targetSnapshotCnt = targetSnapshot.size();

    // first compare source to target
    // - remove the ones found only in source but not in target
    for(int i = 0; i < sourceSnapshotCnt; i++)
    {
        bool isFound = false;
        for(int j = 0; j < targetSnapshotCnt && !isFound; j++)
        {
            if(sourceSnapshot[i] == targetSnapshot[j])
            {
                isFound = true;
            }
        }

        if(!isFound)
        {
            // not found in target, so remove it (or deactivate if it's a root item)
            if(i == 0) {
                // index 0 = root item, don't hide it!
                sourceSnapshot[0]->deactivateAnimated();
            } else {
                sourceSnapshot[i]->hideAndDeleteAfterAnimated();
            }
            //sourceSnapshot.removeAt(i);
        }
    }

    // second: compare target to source
    // - add the ones found only in target but not in source
    for(int i = 0; i < targetSnapshotCnt; i++)
    {
        bool isFound = false;
        for(int j = 0; j < sourceSnapshotCnt && !isFound; j++)
        {
            if(targetSnapshot[i] == sourceSnapshot[j])
            {
                isFound = true;
            }
        }

        if(!isFound)
        {
            // not found in source, so add it
            targetSnapshot[i]->_showAnimated();
        }
    }

    // and apply the target as current
    currentActiveItemElementPath = targetSnapshot;

    // and activate them
    int currItemPathCnt = currentActiveItemElementPath.size();
    for(int i = currItemPathCnt - 1; i >= 0; i--)
    {
        //currentActiveItemElementPath[i]->showImmediatelly(); // bit of a heck
        currentActiveItemElementPath[i]->activateWithLevelAnimated(currItemPathCnt - 1 - i);
    }
}

int MenuManagerVertical1::getIndexInCurrentActiveItemPath(MenuItemWidget *item)
{
    int cnt = currentActiveItemElementPath.size();
    for(int i = 0; i < cnt; i++)
    {
        if(currentActiveItemElementPath[i]->getRelatedMenuItem() == item)
        {
            return i;
        }
    }

    // not found
    return -1;
}

MenuItemManagerElementWidget *MenuManagerVertical1::getItemElementByItem(MenuItemWidget *itemToSearchFor)
{
    MenuItemManagerElementWidget *ret = NULL;
    int cnt = rootMenuItems.size();
    for(int i = 0; i < cnt; i++)
    {
        ret = getItemElementByItemRecursive(rootMenuItems[i], itemToSearchFor);
        if(ret != NULL)
        {
            return ret;
        }
    }

    // not found
    return NULL;
}

MenuItemManagerElementWidget *MenuManagerVertical1::getItemElementByItemRecursive(MenuItemManagerElementWidget *head, MenuItemWidget *itemToSearchFor)
{
    MenuItemManagerElementWidget *ret = NULL;
    if(head->getRelatedMenuItem() == itemToSearchFor)
    {
        return head;
    } else {
        QList<MenuItemManagerElementWidget *> tmpChildren = head->getChildrenElements();
        int cnt = tmpChildren.size();
        for(int i = 0; i < cnt; i++)
        {
            ret = getItemElementByItemRecursive(tmpChildren[i], itemToSearchFor);
            if(ret != NULL)
            {
                return ret;
            }
        }
    }

    return NULL;
}

void MenuManagerVertical1::printThisListOfMenuItemElements(QList<MenuItemManagerElementWidget *> menuItemElementList)
{
    qDebug() << " -- item-path:";
    int cnt = menuItemElementList.size();
    for(int i = 0; i < cnt; i++)
    {
        qDebug() << menuItemElementList[i]->getRelatedMenuItem()->getId();
    }
    qDebug() << " -- end";
}

