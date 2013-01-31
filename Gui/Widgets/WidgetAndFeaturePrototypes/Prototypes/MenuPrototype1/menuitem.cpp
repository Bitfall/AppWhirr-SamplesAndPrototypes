#include "menuitem.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

// TEST
#include <QPainter>
// --

MenuItemWidget::MenuItemWidget(QString id, QString title, QWidget *parent) :
    QWidget(parent),
    itemId(id)
    //isChildrenCollapsed(false),
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    itemTitleLabel = new QLabel;
    itemTitleLabel->setText(title);
    mainLayout->addWidget(itemTitleLabel);

#if 0
    QWidget *spacerWidget = new QWidget;
    spacerWidget->setMinimumWidth(10);
    spacerWidget->setMaximumWidth(10);
    mainLayout->addWidget(spacerWidget);
    spacerWidget->setStyleSheet("background:#bbccbb");

    QWidget *contentWidget = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout;
    contentWidget->setLayout(contentLayout);
    mainLayout->addWidget(contentWidget);



    QWidget *childContainerWidget = new QWidget;
    childLayout = new QVBoxLayout;
    childContainerWidget->setLayout(childLayout);
    contentLayout->addWidget(childContainerWidget);

    spacerWidget->setContentsMargins(0, 0, 0, 0);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);
    contentWidget->setContentsMargins(0, 0, 0, 0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    childLayout->setContentsMargins(0, 0, 0, 0);
    childLayout->setSpacing(0);
    childContainerWidget->setContentsMargins(0, 0, 0, 0);
    this->setContentsMargins(0, 0, 0, 0);
#endif


/*
#if 0
    this->setMinimumSize(200, 50);
    this->setMaximumSize(200, 50);
#else
    this->setMinimumSize(0, 0);
    this->setMaximumSize(0, 0);
#endif
*/

#if 0 // TEST
    this->setAttribute(Qt::WA_NoSystemBackground, true);
#endif
}

void MenuItemWidget::_activateAnimated()
{
    //itemTitleLabel->setStyleSheet("* {font: bold 24px;}");
    itemTitleLabel->setStyleSheet("* {font: bold;}");
}

void MenuItemWidget::_deactivateAnimated()
{
    itemTitleLabel->setStyleSheet("* {font: ;}");
}

#if 0
void MenuItemWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(100, 100, 120));
}
#endif

void MenuItemWidget::_emitFillSubItemsToThisItemSignal()
{
    emit fillSubItemsToThisItem(this);
}

void MenuItemWidget::_emitItemBecomeTheTopActiveOneSignal()
{
    emit itemBecomeTheTopActiveOne(this);
}

QString MenuItemWidget::getId() const
{
    return itemId;
}

bool MenuItemWidget::event(QEvent *e)
{
#if 1
    if(e->type() == QEvent::MouseButtonPress)
    {
        qDebug("clicked");
        emit itemClick(this);

        //this->showChildren();

        return true;
    }
#endif

    return QWidget::event(e);
}
