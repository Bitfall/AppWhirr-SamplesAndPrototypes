#include "horizontalreorderinglayout.h"

#include <QLayoutItem>
#include <QWidget>
#include <QStyle>

HighPerformanceHorizontalLayout::HighPerformanceHorizontalLayout(QWidget *parent) :
        QLayout(parent)
{
}

HighPerformanceHorizontalLayout::~HighPerformanceHorizontalLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

int HighPerformanceHorizontalLayout::count() const
{
    // QList::size() returns the number of QLayoutItems in the list
    return itemList.size();
}

QLayoutItem *HighPerformanceHorizontalLayout::itemAt(int index) const
{
    // QList::value() performs index checking, and returns 0 if we are
    // outside the valid range
    return itemList.value(index);
}

#if 0
int HighPerformanceHorizontalLayout::getMinimumContentHeight()
{
    QLayoutItem *item;
    int h = 0;
    foreach (item, itemList)
    {
        h = qMax(h, item->minimumSize().height());
    }

    return h;
}
#endif

QLayoutItem *HighPerformanceHorizontalLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
    {
        QLayoutItem *itemToRemove = itemList.takeAt(index);
        //contentTotalMinimumSize.setHeight(this->getMinimumContentHeight());
        return itemToRemove;
    }

    return NULL;
}

void HighPerformanceHorizontalLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
    //contentTotalMinimumSize.setWidth(contentTotalMinimumSize.width() + item->minimumSize().width());
    //qDebug(QString("curr min w: %1").arg(contentTotalMinimumSize.width()));
}

QSize HighPerformanceHorizontalLayout::sizeHint() const
{
    return minimumSize();
}

QSize HighPerformanceHorizontalLayout::minimumSize() const
{
#if 1
    //QSize size;
    QLayoutItem *item = NULL;
    int w = 0;
    int h = 0;
    foreach (item, itemList)
    {
        //size = size.expandedTo(item->minimumSize());
        w += item->minimumSize().width();
        h = qMax(h, item->minimumSize().height());
        //qDebug(QString("h: %1").arg(h).toAscii());
    }

    //size += QSize(2*margin(), 2*margin());
    return QSize(w, h);
#else
    return contentTotalMinimumSize;
#endif
}

void HighPerformanceHorizontalLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    performLayoutUpdate(rect);
}

void HighPerformanceHorizontalLayout::performLayoutUpdate(const QRect &rect)
{
    //qDebug(QString("LayoutRect: %1, %2").arg(rect.width()).arg(rect.height()).toAscii());

    //int left, top, right, bottom;
    //getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect;
    //effectiveRect.setSize(this->contentTotalSize);
    QSize minSize = minimumSize();
    effectiveRect.setSize(minSize);
    //QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    //qDebug(QString("effectiveRect: %1, %2").arg(effectiveRect.width()).arg(effectiveRect.height()).toAscii());
    float x = effectiveRect.x();
    float y = effectiveRect.y();
    //int lineHeight = 0;

    //int spaceX = 0;
    //int spaceY = 0;

    //
    // calculate total width




    //
    // do the layout

    QLayoutItem *item;
    QSize itemSizeHint;
    int itemY = 0;
    foreach (item, itemList) {

        itemSizeHint = item->sizeHint();

#if 0
        //
        // vertical centerization
        {
            //int itemSpaceingHeight = minSize.height() - itemSizeHint.height();
            int itemSpaceingHeight = rect.height() - itemSizeHint.height();
            if(itemSpaceingHeight != 0) {
                itemSpaceingHeight /= 2;
            }
            itemY = y + itemSpaceingHeight;
            qDebug(QString("y %1").arg(y).toAscii());
            qDebug(QString("itemY %1").arg(itemY).toAscii());
        }
#endif

        float nextX = x + itemSizeHint.width();
#if 0
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + itemSizeHint.width() + spaceX;
            lineHeight = 0;
        }
#endif

        item->setGeometry(QRect(QPoint(x, itemY), itemSizeHint));

        x = nextX;
        //lineHeight = qMax(lineHeight, itemSizeHint.height());
    }

}
