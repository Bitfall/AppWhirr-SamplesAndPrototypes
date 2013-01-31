#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

#include "Common/multicontentmanager.h"
#include "Common/referencecountingidbasedcollection.h"
#include "Common/Widgets/idbasedwidget.h"

#define CONTENT_ONE_CONTENTID           QString("content-one")
#define CONTENT_TWO_CONTENTID           QString("content-two")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    //
    // action buttons
    QHBoxLayout *actionButtonHolderLayout = new QHBoxLayout;
    mainLayout->addLayout(actionButtonHolderLayout);

    QPushButton *switchToContentOneButton = new QPushButton(tr("Switch to content 1"));
    connect(switchToContentOneButton, SIGNAL(clicked()), this, SLOT(_switchToContentOne()));
    actionButtonHolderLayout->addWidget(switchToContentOneButton);

    QPushButton *switchToContentTwoButton = new QPushButton(tr("Switch to content 2"));
    connect(switchToContentTwoButton, SIGNAL(clicked()), this, SLOT(_switchToContentTwo()));
    actionButtonHolderLayout->addWidget(switchToContentTwoButton);

    QPushButton *addContentToContentTwoButton = new QPushButton(tr("Add content to content 2"));
    connect(addContentToContentTwoButton, SIGNAL(clicked()), this, SLOT(_addContentToContentTwo()));
    actionButtonHolderLayout->addWidget(addContentToContentTwoButton);

    QPushButton *removeContentTwoButton = new QPushButton(tr("Remove content 2"));
    connect(removeContentTwoButton, SIGNAL(clicked()), this, SLOT(_removeContentTwo()));
    actionButtonHolderLayout->addWidget(removeContentTwoButton);


    //
    // the content holder widget
    QVBoxLayout *contentHolderLayout = new QVBoxLayout;
    mainLayout->addLayout(contentHolderLayout);
    _multiContentManager = new MultiContentManager(contentHolderLayout);

    //
    // the actual contents
    _contentItemCollection = new ReferenceCountingIdBasedCollection(false, this);

    IdBasedWidget *contentOneWidget = new IdBasedWidget(CONTENT_ONE_CONTENTID);
    QHBoxLayout *contentOneLayout = new QHBoxLayout;
    contentOneWidget->setLayout(contentOneLayout);
    QLabel *labOne = new QLabel(tr("Test 1"));
    contentOneLayout->addWidget(labOne);
    QTextEdit *textEditOne = new QTextEdit(tr("Test 1"));
    contentOneLayout->addWidget(textEditOne);
    _multiContentManager->setContentWidgetToId(CONTENT_ONE_CONTENTID, contentOneWidget);
    _contentItemCollection->addItem(contentOneWidget);


    IdBasedWidget *contentTwoWidget = new IdBasedWidget(CONTENT_TWO_CONTENTID);
    QVBoxLayout *contentTwoLayout = new QVBoxLayout;
    contentTwoWidget->setLayout(contentTwoLayout);
    QLabel *labTwo = new QLabel(tr("Test 2"));
    contentTwoLayout->addWidget(labTwo);
    QPushButton *buttonTwo = new QPushButton(tr("Test 2"));
    contentTwoLayout->addWidget(buttonTwo);
    _multiContentManager->setContentWidgetToId(CONTENT_TWO_CONTENTID, contentTwoWidget);
    _contentItemCollection->addItem(contentTwoWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::_switchToContentOne() {
    _multiContentManager->switchContent(CONTENT_ONE_CONTENTID);
}

void MainWindow::_switchToContentTwo() {
    _multiContentManager->switchContent(CONTENT_TWO_CONTENTID);
}

void MainWindow::_addContentToContentTwo() {
    QWidget *contentWidgetTwo = _multiContentManager->getContentWidget(CONTENT_TWO_CONTENTID);
    if(contentWidgetTwo != NULL) {
        contentWidgetTwo->layout()->addWidget(new QLabel(tr("Added test label")));
    }
}

void MainWindow::_removeContentTwo() {
    _contentItemCollection->releaseItem(CONTENT_TWO_CONTENTID);
//    QWidget *contentWidgetTwo = _multiContentManager->getContentWidget(CONTENT_TWO_CONTENTID);
//    if(contentWidgetTwo != NULL) {
//        contentWidgetTwo->setParent(0);
//        contentWidgetTwo->deleteLater();
//    }
}
