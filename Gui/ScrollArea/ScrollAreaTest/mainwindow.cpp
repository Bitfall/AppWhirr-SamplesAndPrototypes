#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#if SOLUTION_TYPE == 1
#include <QScrollBar>

#include "Common/Layouts/flowlayout.h"
#include "Common/Layouts/dynamicsamesizehorizontalflowlayout.h"
#include "Common/Widgets/delegatingscrollarea.h"
#include "Common/Widgets/delegatebasedwidget.h"
#endif

#if SOLUTION_TYPE == 2
#include "Common/Widgets/samesizehorizontalflowlayoutbasedscrollarea.h"
#endif

#if SOLUTION_TYPE == 3
#include "Common/Widgets/multisectionsamesizehorizontalflowlayoutbasedscrollarea.h"
#include "Common/Layouts/samesizehorizontalflowlayout.h"
#endif

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _itemCnt(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *mainCentralWidget = new QWidget;
    mainCentralWidget->setLayout(mainLayout);
    this->setCentralWidget(mainCentralWidget);

#if SOLUTION_TYPE == 1
    testScrollArea = new DelegatingScrollArea;
    testScrollArea->setStyleSheet("QScrollArea { background-color: blue; }");
    connect(testScrollArea, SIGNAL(scrollAreaResized(QResizeEvent*)), this, SLOT(_contentAreaResized(QResizeEvent*)));
    _mainContentHolderWidget = new DelegateBasedWidget;
//    connect(_mainContentHolderWidget, SIGNAL(resizeHappened(QResizeEvent*)), this, SLOT(_contentAreaResized(QResizeEvent*)));
    QVBoxLayout *mainContentHolderLayout = new QVBoxLayout;
    _mainContentHolderWidget->setLayout(mainContentHolderLayout);
//    _mainContentHolderWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
//    mainContentHolderWidget->setFixedSize(800, 800);
    mainContentHolderLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
//    testScrollArea->setWidgetResizable(true); // this will auto-resize (expand) the main-content-holder-widget


    //
    // section 1
    _sectionContentHolderWidget_One = new QWidget;
//    _contentHolderWidget->setObjectName("contentHolder");
//    _contentHolderWidget->setStyleSheet("QWidget#contentHolder { background-color: red; }");
    _sectionContentHolderLayout_One = new DynamicSameSizeHorizontalFlowLayout(QSize(200, 200));
    _sectionContentHolderWidget_One->setLayout(_sectionContentHolderLayout_One);


    QLabel *sectionOneLabel = new QLabel("Section #1");
    mainContentHolderLayout->addWidget(sectionOneLabel);
    mainContentHolderLayout->addWidget(_sectionContentHolderWidget_One);
    // ---

    //
    // section 2
    _sectionContentHolderWidget_Two = new QWidget;
    _sectionContentHolderLayout_Two = new DynamicSameSizeHorizontalFlowLayout(QSize(200, 200));
    _sectionContentHolderWidget_Two->setLayout(_sectionContentHolderLayout_Two);

    QLabel *sectionTwoLabel = new QLabel("Section #2");
    mainContentHolderLayout->addWidget(sectionTwoLabel);
    mainContentHolderLayout->addWidget(_sectionContentHolderWidget_Two);


    testScrollArea->setWidget(_mainContentHolderWidget);
    mainLayout->addWidget(testScrollArea);
#endif

#if SOLUTION_TYPE == 2
    _sameSizeHorizontalFlowScrollArea = new SameSizeHorizontalFlowLayoutBasedScrollArea(new DynamicSameSizeHorizontalFlowLayout(QSize(200, 200)));
    mainLayout->addWidget(_sameSizeHorizontalFlowScrollArea);
#endif

#if SOLUTION_TYPE == 3
    _multiSectionSameSizeHorizontalScrollArea =  new MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea(this, 2);
    mainLayout->addWidget(_multiSectionSameSizeHorizontalScrollArea);
#endif

    this->addNewItem();

    //
    //
    QPushButton *addNewItemButton = new QPushButton(tr("Add new item."));
    connect(addNewItemButton, SIGNAL(clicked()), this, SLOT(addNewItem()));
    mainLayout->addWidget(addNewItemButton);
}

MainWindow::~MainWindow()
{

}

#if SOLUTION_TYPE == 1
void MainWindow::_contentAreaResized(QResizeEvent *e)
{
//    _sectionContentHolderLayout_One->recalculateMinimalAndOptimalSizesByTotalLayoutWidth(testScrollArea->contentsRect().width() - testScrollArea->verticalScrollBar()->width());

//    _mainContentHolderWidget->resize(testScrollArea->contentsRect().width() - testScrollArea->verticalScrollBar()->width(), 50);

    //
    // section 1
    _sectionContentHolderLayout_One->recalculateMinimalAndOptimalSizesByTotalLayoutWidth(testScrollArea->contentsRect().width() - testScrollArea->verticalScrollBar()->width());

    _sectionContentHolderWidget_One->setMinimumSize(_sectionContentHolderLayout_One->getCalculatedMinimalSize());
    _sectionContentHolderWidget_One->resize(_sectionContentHolderLayout_One->getCalculatedOptimalSize());

    //
    // section 2
    _sectionContentHolderLayout_Two->recalculateMinimalAndOptimalSizesByTotalLayoutWidth(testScrollArea->contentsRect().width() - testScrollArea->verticalScrollBar()->width());

    _sectionContentHolderWidget_Two->setMinimumSize(_sectionContentHolderLayout_Two->getCalculatedMinimalSize());
    _sectionContentHolderWidget_Two->resize(_sectionContentHolderLayout_Two->getCalculatedOptimalSize());


    //
    // main content holders
    _mainContentHolderWidget->setFixedWidth(_mainContentHolderWidget->contentsMargins().left() + _sectionContentHolderLayout_Two->getCalculatedMinimalSize().width() + _mainContentHolderWidget->contentsMargins().right());
    _mainContentHolderWidget->adjustSize();


}
#endif

void MainWindow::addNewItem() {
    ++_itemCnt;

    int itemTypeId = _itemCnt % 3;

#if SOLUTION_TYPE == 1
    int targetSection = _itemCnt % 2;
    if(itemTypeId == 0) {
        if(targetSection == 0) {
            _sectionContentHolderLayout_One->addWidget(new QLabel(QString("test label %1").arg(QString::number(_itemCnt))));
        } else {
            _sectionContentHolderLayout_Two->addWidget(new QLabel(QString("test label %1").arg(QString::number(_itemCnt))));
        }
    }
    else if(itemTypeId == 1) {
        if(targetSection == 0) {
            _sectionContentHolderLayout_One->addWidget(new QTextEdit(QString("test text edit %1").arg(QString::number(_itemCnt))));
        }
        else {
            _sectionContentHolderLayout_Two->addWidget(new QTextEdit(QString("test text edit %1").arg(QString::number(_itemCnt))));
        }
    }
    else if(itemTypeId == 2) {
        if(targetSection == 0) {
            _sectionContentHolderLayout_One->addWidget(new QPushButton(QString("test button %1").arg(QString::number(_itemCnt))));
        }
        else {
            _sectionContentHolderLayout_Two->addWidget(new QPushButton(QString("test button %1").arg(QString::number(_itemCnt))));
        }
    }
#endif

#if SOLUTION_TYPE == 2
    if(itemTypeId == 0) {
        _sameSizeHorizontalFlowScrollArea->addWidget(new QLabel(QString("test label %1").arg(QString::number(_itemCnt))));
    }
    else if(itemTypeId == 1) {
        _sameSizeHorizontalFlowScrollArea->addWidget(new QTextEdit(QString("test text edit %1").arg(QString::number(_itemCnt))));
    }
    else if(itemTypeId == 2) {
        _sameSizeHorizontalFlowScrollArea->addWidget(new QPushButton(QString("test button %1").arg(QString::number(_itemCnt))));
    }
#endif

#if SOLUTION_TYPE == 3
    int targetSection = _itemCnt % 2;
    if(itemTypeId == 0) {
        _multiSectionSameSizeHorizontalScrollArea->addWidgetToSection(new QLabel(QString("test label %1").arg(QString::number(_itemCnt))), targetSection);
    }
    else if(itemTypeId == 1) {
        _multiSectionSameSizeHorizontalScrollArea->addWidgetToSection(new QTextEdit(QString("test text edit %1").arg(QString::number(_itemCnt))), targetSection);
    }
    else if(itemTypeId == 2) {
        _multiSectionSameSizeHorizontalScrollArea->addWidgetToSection(new QPushButton(QString("test button %1").arg(QString::number(_itemCnt))), targetSection);
    }
#endif
}

#if SOLUTION_TYPE == 3
SameSizeLayoutBase *MainWindow::createLayout() {
    return new SameSizeHorizontalFlowLayout(QSize(200, 200));
}

QString MainWindow::getSectionTitle(int sectionIndex) {
    return QString("Section %1").arg(sectionIndex);
}

#endif
