#ifndef MENUPROTOTYPE1WINDOW_H
#define MENUPROTOTYPE1WINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QWebView;
class QTextEdit;
QT_END_NAMESPACE

//class MenuManager;
class MenuPresenter;
class MenuItemWidget;

class MenuPrototype1Window : public QMainWindow
{
    Q_OBJECT

public:
    MenuPrototype1Window(QWidget *parent = 0);
    ~MenuPrototype1Window();

    //bool notify(QObject *receiver, QEvent *event);

private slots:
    void switchMenuVisibility();

    void fillSubMenuItemsToGrabSomeApps(MenuItemWidget *menuItem);
    void fillSubMenuItemsToWeb(MenuItemWidget *menuItem);
    void fillSubMenuItemsToWebNews(MenuItemWidget *menuItem);

    void switchPageToMyApps(MenuItemWidget *menuItem);
    void switchPageToGrabSomeApps(MenuItemWidget *menuItem);

    void testMessageBoxSlot();

protected:
    bool event(QEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

private:
    MenuPresenter *menuPresenter;
    bool isControlButtonPressed;

    QWebView *testContentWebView;
    QTextEdit *testContentTextEdit;
};

#endif // MENUPROTOTYPE1WINDOW_H
