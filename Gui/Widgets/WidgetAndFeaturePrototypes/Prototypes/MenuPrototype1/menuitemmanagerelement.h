#ifndef MENUITEMMANAGERELEMENT_H
#define MENUITEMMANAGERELEMENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QPropertyAnimation;
class QParallelAnimationGroup;
QT_END_NAMESPACE

class MenuItemWidget;

class MenuItemManagerElementWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY (float backgroundColorRate READ getBackgroundColorRate WRITE setBackgroundColorRate);
public:
    explicit MenuItemManagerElementWidget(MenuItemWidget *item, QWidget *parent = 0);

    void addChildToLayout(MenuItemManagerElementWidget *child);
    QList<MenuItemManagerElementWidget *> getChildrenElements();

    void addCustomWidget(QWidget *customWidget);

    MenuItemWidget *getRelatedMenuItem();

    void showImmediatelly(bool isTerminateShowHideAnimation = true);
    void hideImmediatelly();

    void _showAnimated();
    void hideAndDeleteAfterAnimated();
    void activateWithLevelAnimated(int level);
    void deactivateAnimated();

signals:
    void _startToShowSignal();
    void _startToHideSignal();

    void willDeleteItselfSignal(MenuItemManagerElementWidget *itemElem);

private slots:
    void showAnimationEnded();
    void hideAnimationEnded();
    void activateAnimationEnded();

    void _removeThisChild(MenuItemManagerElementWidget *child);

protected:
    void paintEvent(QPaintEvent *e);
    bool event(QEvent *e);

private:
    void terminateShowHideAnimation();

private:

    void _willDeleteItself();

    QPropertyAnimation *createActivateAnimation(float startRate, float endRate, int duration);
    void _doHideAnimated();

    //
    // properties
    float getBackgroundColorRate() const;
    void setBackgroundColorRate(float value);

private:
    QColor highlightBackgroundColor;
    float backgroundColorRate;
    MenuItemWidget *menuItem;
    QList<MenuItemManagerElementWidget *> childrenElements;

    QVBoxLayout *mainLayout;
    QVBoxLayout *customWidgetHolderLayout;

    QTimer *forceRefreshTimer;
    QParallelAnimationGroup *showHideAnimationGroup;
    bool isHideAnimationProposed;
};

#endif // MENUITEMMANAGERELEMENT_H
