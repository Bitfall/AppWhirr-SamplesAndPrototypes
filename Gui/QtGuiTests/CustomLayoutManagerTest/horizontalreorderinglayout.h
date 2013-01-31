#ifndef HORIZONTALREORDERINGLAYOUT_H
#define HORIZONTALREORDERINGLAYOUT_H

#include <QLayout>
#include <QList>

QT_BEGIN_NAMESPACE
class QLayoutItem;
QT_END_NAMESPACE

class HighPerformanceHorizontalLayout : public QLayout
{
public:
    HighPerformanceHorizontalLayout(QWidget *parent=0);
    ~HighPerformanceHorizontalLayout();

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QLayoutItem *takeAt(int index);
    void setGeometry(const QRect &rect);

private:
    void performLayoutUpdate(const QRect &rect);

private:
    QList<QLayoutItem *> itemList;
};

#endif // HORIZONTALREORDERINGLAYOUT_H
