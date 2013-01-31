#ifndef MENUITEM2_H
#define MENUITEM2_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
QT_END_NAMESPACE

class MenuItem2 : public QWidget
{
    Q_OBJECT
public:
    explicit MenuItem2(QWidget *parent = 0);

    void setTitle(QString title);

    void addChildItem(MenuItem2 *item);

    void showChildren();
    void hideChildren();

    void showAnimated();
    void hideAnimated();

    void setActive(bool state);


signals:
    void activated();

    void startToShowSignal();
    void startToHideSignal();

private slots:
    void showAnimationEnded();
    void hideAnimationEnded();

protected:
    bool event(QEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    QList<MenuItem2 *> childMenuItems;
    QVBoxLayout *mainLayout;
    QVBoxLayout *childLayout;
    QLabel *itemTitleLabel;

    bool isChildrenCollapsed;
    bool isActivated;

};

#endif // MENUITEM2_H
