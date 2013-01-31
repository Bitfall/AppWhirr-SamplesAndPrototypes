#ifndef MENUITEM_H
#define MENUITEM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
QT_END_NAMESPACE

class MenuItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuItemWidget(QString id, QString title, QWidget *parent = 0);

    QString getId() const;

    void _emitFillSubItemsToThisItemSignal();
    void _emitItemBecomeTheTopActiveOneSignal();

    void _activateAnimated();
    void _deactivateAnimated();

signals:
    void itemClick(MenuItemWidget *source);
    void fillSubItemsToThisItem(MenuItemWidget *source);
    void itemBecomeTheTopActiveOne(MenuItemWidget *source);

protected:
    bool event(QEvent *e);
    //void paintEvent(QPaintEvent *e);

private:
    QString itemId;
    QHBoxLayout *mainLayout;
    QLabel *itemTitleLabel;
};

#endif // MENUITEM_H
