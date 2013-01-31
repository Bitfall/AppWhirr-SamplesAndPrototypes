#include "menumanager2.h"

#include <QHBoxLayout>

#include "menuitem2.h"

MenuManager2::MenuManager2(QWidget *parent) :
    QWidget(parent)
{
    theLayout = new QHBoxLayout;
    this->setLayout(theLayout);

#if 0
    this->setMinimumWidth(200);
    this->setMaximumWidth(200);
#endif

#if 0
    theLayout->setContentsMargins(0, 0, 0, 0);
    theLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);
#endif
}

void MenuManager2::addRootItem(MenuItem2 *item)
{
    menuItems << item;
    theLayout->addWidget(item);
}
