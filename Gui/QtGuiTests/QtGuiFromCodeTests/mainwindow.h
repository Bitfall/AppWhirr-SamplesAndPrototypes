#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QWidget;
class QPushButton;
class QStackedLayout;
class QGestureEvent;
class QSwipeGesture;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //
    // animated button slots
    void buttonClicked();
    void animationFinished();

    //
    // stacked layout slots
    void testStackedLayout_GoToPage1();
    void testStackedLayout_GoToPage2();

    //
    // layout header size animated change slots
    void buttonLayoutHeaderSizeAnimatedChangeClicked_Expand();
    void buttonLayoutHeaderSizeAnimatedChangeClicked_Collapse();

    //
    // button grow and shrink with states slots
    void buttonGrowAndShrinkWithStatesAndAnimation();

private:
    void createSomeMenu();

    //
    // test widget creations
    void createTestStackedGui(); // QStackedLayout example, and QMessageBox example, and QProgressDialog example, and QGesture [not working]
    void createTestAnimatedMovingButtonGui(); // uses QPropertyAnimation for animations
    void createTestLayoutHeaderSizeAnimatedChange(); // uses QStateMachine for animations, and CSS for styling, QFrame and frame-style
    void createTestSplitterGui(); // QSplitter example
    void createTestButtonGrowAndShrinkWithStatesAndAnimation(); // QState and QPropertyAnimation example, this is the more complete example of state-management and animation
    void createTestTimelineAnimatedProgressBar(); // animate a progress-bar with the TimeLine animation system

protected:
    bool event(QEvent *event);
    bool gestureEvent(QGestureEvent *event);
private:
    void swipeTriggered(QSwipeGesture *gesture);

private:
    QWidget *centralWidget;
    QPushButton *animationTestButton;

    QStackedLayout *stackLayout;
};

#endif // MAINWINDOW_H
