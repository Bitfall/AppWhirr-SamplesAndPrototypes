#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

#define SOLUTION_TYPE 3

#if SOLUTION_TYPE == 1
class DynamicSameSizeHorizontalFlowLayout;
class DelegatingScrollArea;
class DelegateBasedWidget;
#endif

#if SOLUTION_TYPE == 2
class SameSizeHorizontalFlowLayoutBasedScrollArea;
#endif

#if SOLUTION_TYPE == 3
#include "Common/Widgets/sectionbasedhorizontalflowlayoutpresenterdelegate.h"
class MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea;
#endif

#if SOLUTION_TYPE != 3
class MainWindow : public QMainWindow
#endif

#if SOLUTION_TYPE == 3
class MainWindow : public QMainWindow, public SectionBasedHorizontalFlowLayoutPresenterDelegate
#endif
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void addNewItem();

#if SOLUTION_TYPE == 1
    void _contentAreaResized(QResizeEvent *e);
#endif

#if SOLUTION_TYPE == 3
    SameSizeLayoutBase *createLayout();
    QString getSectionTitle(int sectionIndex);
#endif

private:
    int _itemCnt;

#if SOLUTION_TYPE == 1
    DelegateBasedWidget *_mainContentHolderWidget;
    DelegatingScrollArea *testScrollArea;

    DynamicSameSizeHorizontalFlowLayout *_sectionContentHolderLayout_One;
    QWidget *_sectionContentHolderWidget_One;

    DynamicSameSizeHorizontalFlowLayout *_sectionContentHolderLayout_Two;
    QWidget *_sectionContentHolderWidget_Two;
#endif

#if SOLUTION_TYPE == 2
    SameSizeHorizontalFlowLayoutBasedScrollArea *_sameSizeHorizontalFlowScrollArea;
#endif

#if SOLUTION_TYPE == 3
    MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea *_multiSectionSameSizeHorizontalScrollArea;
#endif
};

#endif // MAINWINDOW_H
