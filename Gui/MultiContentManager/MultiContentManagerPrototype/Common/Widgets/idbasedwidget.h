#ifndef IDBASEDWIDGET_H
#define IDBASEDWIDGET_H

#include <QWidget>
#include "../idbasediteminterface.h"

class IdBasedWidget : public QWidget, public IdBasedItemInterface
{
    Q_OBJECT
public:
    explicit IdBasedWidget(QString itemId, QWidget *parent = 0);

    QString getId() const;

protected:
    void paintEvent(QPaintEvent *e);

private:
    QString _itemId;
};

#endif // IDBASEDWIDGET_H
