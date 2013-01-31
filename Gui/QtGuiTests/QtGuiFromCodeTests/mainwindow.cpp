#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStackedLayout>
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QPalette>
#include <QFrame>
#include <QMessageBox>
#include <QProgressDialog>
#include <QProgressBar>

#include <QState>
#include <QStateMachine>
#include <QSignalTransition>
#include <QTimeLine>

//#include <QTimer>
#include <QThread>

#include <QGestureEvent>
#include <QSwipeGesture>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(640, 480);
    this->setMinimumSize(320, 240);

    this->setWindowTitle(tr("MainWindowTitle"));

    centralWidget = new QWidget(this);
    /*centralWidget->setBackgroundRole(QPalette::Dark);*/
    this->setCentralWidget(centralWidget);

    this->createSomeMenu();




    //
    // allow only one of these tests

//    createTestStackedGui();
//    createTestAnimatedButtonGui();
//    createTestSplitterGui();
    createTestLayoutHeaderSizeAnimatedChange();
//    createTestButtonGrowAndShrinkWithStatesAndAnimation();
//    createTestTimelineAnimatedProgressBar();



    //
    //
//    QObject::connect(this, res)
}

MainWindow::~MainWindow()
{

}


// -----------------------------------------------------------------------------------------------
// ----- test layout header size animated change

void MainWindow::createTestLayoutHeaderSizeAnimatedChange()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);

    //
    // create the header
    QFrame *headerWidget = new QFrame();
//    headerWidget->setObjectName("someNameToHeaderWidget");  // can be set this way, then the css requires: QWidget#someNameToHeaderWidget
    headerWidget->setProperty("cssHasToHaveGrayBackground", true); // or we can add a special property dynamically (on the fly) to mark the widgets will be affected by the style sheet

    headerWidget->setStyleSheet("*[cssHasToHaveGrayBackground=\"true\"] { background-color: #aaaaaa }");
    headerWidget->setFrameStyle( QFrame::Box | QFrame::Raised );
    //headerWidget->setFrameShadow( );

    mainLayout->addWidget(headerWidget);
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerWidget->setLayout(headerLayout);

    QPushButton *button1 = new QPushButton(tr("Click to expand"));
    headerLayout->addWidget(button1);
    button1->setMaximumWidth(150);
    //button1->setProperty("cssHasToHaveGrayBackground", true);
    button1->setStyleSheet("QPushButton { background-color: #dddddd }");
    //QObject::connect(button1, SIGNAL(clicked()), this, SLOT(buttonLayoutHeaderSizeAnimatedChangeClicked_Expand()));

    QPushButton *button2 = new QPushButton(tr("Click to collapse"));
    headerLayout->addWidget(button2);
    button2->setMaximumWidth(150);
    button2->setStyleSheet("QPushButton { background-color: #dddddd }");
    //QObject::connect(button2, SIGNAL(clicked()), this, SLOT(buttonLayoutHeaderSizeAnimatedChangeClicked_Collapse()));

    //QMacStyle *macStyle = new QMacStyle();
    //button2->setStyle( new QMacStyle() );



    //
    // create the footer
    QFrame *footerWidget = new QFrame();
    footerWidget->setObjectName("footerWidget");
    footerWidget->setStyleSheet("QFrame#footerWidget { background-color: #dddddd }");
    mainLayout->addWidget(footerWidget);
    QHBoxLayout *footerLayout = new QHBoxLayout();
    footerWidget->setLayout(footerLayout);

    QListView *testListView = new QListView();
    footerLayout->addWidget(testListView);

    QTreeView *testTreeView = new QTreeView();
    footerLayout->addWidget(testTreeView);

    //headerLayout->setStretch(0, 20);
    //headerLayout->setSpacing(500);
//    button1->setGeometry(QRect(0, 0, 100, 500));
//    button1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    button1->setGeometry(QRect(0, 0, 100, 500));
//    button1->setMinimumHeight(300);
    //headerLayout->invalidate();

    button1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    headerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    headerWidget->setMinimumHeight(100);


    //
    // and add some animations
    QStateMachine *machine = new QStateMachine();
    QState *state1 = new QState(machine);
    QState *state2 = new QState(machine);

    state1->assignProperty(headerWidget, "minimumHeight", headerWidget->minimumHeight());
    state1->assignProperty(button2, "minimumWidth", button1->minimumWidth());
    state2->assignProperty(headerWidget, "minimumHeight", 100);
    state2->assignProperty(button2, "minimumWidth", 300);

    state1->addTransition(button1, SIGNAL(clicked()), state2);
    state2->addTransition(button2, SIGNAL(clicked()), state1);


    // and add a default animation
    QPropertyAnimation *defaultAnim = new QPropertyAnimation(headerWidget, "minimumHeight");
    defaultAnim->setDuration(1000);
    defaultAnim->setEasingCurve(QEasingCurve::OutQuad);
    machine->addDefaultAnimation(defaultAnim);

    QPropertyAnimation *defaultAnim2 = new QPropertyAnimation(button2, "minimumWidth");
    defaultAnim2->setDuration(1000);
    defaultAnim2->setEasingCurve(QEasingCurve::InOutQuad);
    machine->addDefaultAnimation(defaultAnim2);

    machine->setInitialState(state1);
    machine->start();

}

void MainWindow::buttonLayoutHeaderSizeAnimatedChangeClicked_Expand()
{
#ifdef DO_IT_ONLY_IN_DEBUG
    qDebug("buttonLayoutHeaderSizeAnimatedChangeClicked_Expand");
#endif


}

void MainWindow::buttonLayoutHeaderSizeAnimatedChangeClicked_Collapse()
{
#ifdef DO_IT_ONLY_IN_DEBUG
    qDebug("buttonLayoutHeaderSizeAnimatedChangeClicked_Collapse");
#endif

}

// -----------------------------------------------------------------------------------------------



// -----------------------------------------------------------------------------------------------
// ----- test button grow and shrink with states and animation

void MainWindow::createTestTimelineAnimatedProgressBar()
{
    QVBoxLayout *theLayout = new QVBoxLayout();
    centralWidget->setLayout(theLayout);

    QProgressBar *progressBar = new QProgressBar();
    progressBar->setRange(0, 100);

    // Construct a 1-second timeline with a frame range of 0 - 100
    //QTimeLine *timeLine = new QTimeLine(1000, this);
    QTimeLine *timeLine = new QTimeLine();
    timeLine->setDuration(5000);
    timeLine->setFrameRange(0, 100);
    timeLine->setEasingCurve(QEasingCurve::InOutCubic);
    connect(timeLine, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));

    // Clicking the push button will start the progress bar animation
    QPushButton *pushButton = new QPushButton(tr("Start animation"));
    connect(pushButton, SIGNAL(clicked()), timeLine, SLOT(start()));

    connect(timeLine, SIGNAL(finished()), timeLine, SLOT(toggleDirection()));
    connect(timeLine, SIGNAL(finished()), timeLine, SLOT(start()));
    // [!] Doc sais the signals will be emitted in the order of connect
    //      http://doc.trolltech.com/4.7/signalsandslots.html
    // but to be sure in a more realistic app create another method
    //  which will call toggleDirection and start in the order required

    theLayout->addWidget(progressBar);
    theLayout->addWidget(pushButton);
}

// -----------------------------------------------------------------------------------------------



// -----------------------------------------------------------------------------------------------
// ----- test button grow and shrink with states and animation

void MainWindow::createTestButtonGrowAndShrinkWithStatesAndAnimation()
{
    QRect geometryState1(100, 100, 150, 50);
    QRect geometryState2(100, 100, 250, 150);

    QPushButton *testButton = new QPushButton(centralWidget);
    testButton->setGeometry(geometryState1);
    QObject::connect(testButton, SIGNAL(clicked()), this, SLOT(buttonGrowAndShrinkWithStatesAndAnimation()));

    QStateMachine *machine = new QStateMachine();
    QState *state1 = new QState(machine);
    QState *state2 = new QState(machine);

    state1->assignProperty(testButton, "geometry", geometryState1);
    state2->assignProperty(testButton, "geometry", geometryState2);

    QSignalTransition *transition = NULL;

    /*transition = */state1->addTransition(testButton, SIGNAL(clicked()), state2);
    transition = state2->addTransition(testButton, SIGNAL(clicked()), state1);
    transition->addAnimation(new QPropertyAnimation(testButton, "geometry")); // we can add custom, per state transition based animations, or add only 1 default animation

    // and add a default animation
    QPropertyAnimation *defaultAnim = new QPropertyAnimation(testButton, "geometry");
    defaultAnim->setDuration(3000);
    defaultAnim->setEasingCurve(QEasingCurve::InOutQuad);
    machine->addDefaultAnimation(defaultAnim);

//    machine->addState(state1);
//    machine->addState(state2);
    machine->setInitialState(state1);
    machine->start();
}

void MainWindow::buttonGrowAndShrinkWithStatesAndAnimation()
{
#ifdef DO_IT_ONLY_IN_DEBUG
    qDebug("buttonGrowAndShrinkWithStatesAndAnimation");
#endif
}

// -----------------------------------------------------------------------------------------------



// -----------------------------------------------------------------------------------------------
// ----- test splitter based gui

void MainWindow::createTestSplitterGui()
{
    QHBoxLayout *theLayout = new QHBoxLayout();
    centralWidget->setLayout(theLayout);

    QSplitter *splitter = new QSplitter();
    theLayout->addWidget(splitter);
    QListView *listview = new QListView;
    QTreeView *treeview = new QTreeView;
    QTextEdit *textedit = new QTextEdit;
    splitter->addWidget(listview);
    splitter->addWidget(treeview);
    splitter->addWidget(textedit);
}

// -----------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------
// ----- test animated button

void MainWindow::createTestAnimatedMovingButtonGui()
{
    //
    // Button
    animationTestButton = new QPushButton(tr("Press me"), centralWidget);
    QObject::connect(animationTestButton, SIGNAL(clicked()),
                     this, SLOT(buttonClicked()));
    animationTestButton->setGeometry(10, 10, 100, 50);
}

void MainWindow::animationFinished()
{
//    animationTestButton->setGeometry(0, 0, 100, 30);
//    stackLayout->setCurrentIndex(1);
}


void MainWindow::buttonClicked()
{

    //
    // play a little animation

    QPropertyAnimation *animation = new QPropertyAnimation(animationTestButton, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(animationTestButton->geometry());
    QRect targetValue = QRect(animationTestButton->geometry().x() + 30,
                              animationTestButton->geometry().y(),
                              animationTestButton->geometry().width(),
                              animationTestButton->geometry().height());
    animation->setEndValue(targetValue);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // way-points (key-value points) can be also added
//    animation->setKeyValueAt(0.8, QRect(250, 250, 100, 30));

    // and it could also allow to set a path
    /*animation->setKeyValueAt(0, QRect(0, 0, 100, 30));
    animation->setKeyValueAt(0.8, QRect(250, 250, 100, 30));
    animation->setKeyValueAt(1, QRect(200, 400, 100, 30));*/


    // Listen animation finished signal
    QObject::connect(animation, SIGNAL(finished()), this, SLOT(animationFinished()));

    // this will delete itself after the animation ended
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    qDebug("button clicked event");
}

// -----------------------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------------------
// ----- test stacked gui

void MainWindow::createTestStackedGui()
{
    //
    // A stacked layout
    stackLayout = new QStackedLayout();
    centralWidget->setLayout(stackLayout);
//    stackLayout->addWidget(animationTestButton);

    //
    // index 0
    QWidget *firstPageWidget = new QWidget();
    stackLayout->addWidget(firstPageWidget);
    QVBoxLayout *firstPageLayout = new QVBoxLayout();
    firstPageWidget->setLayout(firstPageLayout);

    QPushButton *buttonTest0 = new QPushButton(tr("Go to page 2"));
    firstPageLayout->addWidget(buttonTest0);
    QObject::connect(buttonTest0, SIGNAL(clicked()), this, SLOT(testStackedLayout_GoToPage2()));

    // some other test buttons
    for(int i = 0; i < 10; i++)
    {
        QPushButton *testButton = new QPushButton(tr("Just some test button"));
        firstPageLayout->addWidget(testButton);
    }


    //
    // index 1
    QWidget *secondPageWidget = new QWidget();
    stackLayout->addWidget(secondPageWidget);
    QVBoxLayout *secondPageLayout = new QVBoxLayout();
    secondPageWidget->setLayout(secondPageLayout);

    QPushButton *buttonTest1 = new QPushButton("Go to page 1");
    secondPageLayout->addWidget(buttonTest1);
    QObject::connect(buttonTest1, SIGNAL(clicked()), this, SLOT(testStackedLayout_GoToPage1()));

    //
    // and subscribeing to swipe gesture (will be handled in event())
    this->grabGesture(Qt::SwipeGesture);
}

void MainWindow::testStackedLayout_GoToPage2()
{
    stackLayout->setCurrentIndex(1);


    QMessageBox msgBox(QMessageBox::Information, tr("Some title"), tr("Some text to present"));
    // or use the default constructor and set these this way:
    /*msgBox.setText(tr("The document has been modified. Or may be not. I don't really have a clue."));
    msgBox.setWindowTitle(tr("Test message box"));*/

    msgBox.setInformativeText(tr("Do you want to save your changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setDetailedText(tr("some detaild text to show\n"
                              "and another line of it"));

    int dres = msgBox.exec();
    switch (dres) {
    case QMessageBox::Save:
        // Save was clicked
        qDebug("Save was pressed");
        break;
    case QMessageBox::Discard:
        // Don't Save was clicked
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        break;
    default:
        // should never be reached
        break;
    }
    //msgBox.show();



    // or this way
    QMessageBox::warning(this, tr("My Application"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save | QMessageBox::Discard
                                    | QMessageBox::Cancel,
                                    QMessageBox::Save);
}

void MainWindow::testStackedLayout_GoToPage1()
{
    int numFiles = 1000;
    QProgressDialog progress("Some processing...", "Abort the processing", 0, numFiles, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (int i = 0; i < numFiles; i++) {
        progress.setValue(i);

        if (progress.wasCanceled())
            break;
        //... copy one file
        //sleep(500);  // wait for relay to close
        for(int i = 0; i < 999999; i++)
        {

        }
    }
    progress.setValue(numFiles);

    stackLayout->setCurrentIndex(0);
}

//
// gesture
bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QWidget::event(event);
}

bool MainWindow::gestureEvent(QGestureEvent *event)
 {
     if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
         swipeTriggered(static_cast<QSwipeGesture *>(swipe));
     return true;
 }

void MainWindow::swipeTriggered(QSwipeGesture *gesture)
{
    qDebug("swipe triggered");
    if (gesture->state() == Qt::GestureFinished) {
        if (gesture->horizontalDirection() == QSwipeGesture::Left
            || gesture->verticalDirection() == QSwipeGesture::Up)
            testStackedLayout_GoToPage1();
        else
            testStackedLayout_GoToPage2();
        update();
    }
}

// -----------------------------------------------------------------------------------------------


void MainWindow::createSomeMenu()
{
    //
    // Menu bar
    QAction *quit = new QAction("&Quit", this);

    QMenu *fileMenu;
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(quit);

    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(close()));
}
