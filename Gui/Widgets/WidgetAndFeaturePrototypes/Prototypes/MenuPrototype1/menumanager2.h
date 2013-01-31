#ifndef MENUMANAGER2_H
#define MENUMANAGER2_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
QT_END_NAMESPACE

class MenuItem2;

class MenuManager2 : public QWidget
{
    Q_OBJECT
public:
    explicit MenuManager2(QWidget *parent = 0);

    void addRootItem(MenuItem2 *item);

signals:

public slots:

private:
    QList<MenuItem2 *> menuItems;
    QHBoxLayout *theLayout;

};

#endif // MENUMANAGER2_H
