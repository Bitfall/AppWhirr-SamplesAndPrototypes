#ifndef MENUPRESENTER_H
#define MENUPRESENTER_H

#include <QWidget>
#include <QPixmap>

class MenuItemWidget;
class MenuManagerVertical1;

class MenuPresenter : public QWidget
{
    Q_OBJECT
    //Q_PROPERTY(float showHideRatio READ getShowHideRatio WRITE setShowHideRatio);
public:
    explicit MenuPresenter(QWidget *parent = 0);

    //
    // set the container widget, in-which this presenter will be shown
    //void setContainerWidget(QWidget *widget);

    //
    // targetPos: center, where the menu('s center) should be presented
    void showAnimated(QPoint targetPos);
    void hideAnimated(QPoint targetPos);
    void hideAnimated();

    void switchShowHideStateAnimated(QPoint targetPos);

    MenuManagerVertical1 *getMenuManager();

private slots:
    void hideAnimationFinished();
    void showAnimationFinished();

protected:
    void paintEvent(QPaintEvent *e);
    bool event(QEvent *e);

private:
#if 0
    float getShowHideRatio() const;
    void setShowHideRatio(float ratio);
#endif
    void createMenuLayout();

private:
    QPixmap backgroundPixmap;
    QPoint lastTargetPos;

    MenuManagerVertical1 *menuManager;
    //QWidget *containerWidget;
    //float showHideRatio;

    //QPixmap grabbedPixmap;

    //bool isInGrabMode;
};

#endif // MENUPRESENTER_H
