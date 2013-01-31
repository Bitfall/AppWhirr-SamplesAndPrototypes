#ifndef EXPANDABLEBUTTONWIDGET_H
#define EXPANDABLEBUTTONWIDGET_H

#include <QWidget>
#include <QList>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
QT_END_NAMESPACE

#include "Common/Widgets/animatedtwofixedsizewidgetbase.h"

class IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel;
class IntelligentSeparatedMultifunctionalButtonWidgetOptionItemWidget;
class SimpleImagePresenterWidget;

class IntelligentSeparatedMultifunctionalButtonWidget : public AnimatedTwoFixedSizeWidgetBase
{
    Q_OBJECT
private:
    explicit IntelligentSeparatedMultifunctionalButtonWidget(IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *defaultOptionItemModel, QList<IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *> otherOptionItemModels, QSize collapsedSize, QSize expandedSize, bool isExpandedByDefault, QWidget *parent = 0);

public:
    //
    // factory method - this will automatically calculate the sizes
    static IntelligentSeparatedMultifunctionalButtonWidget *createWithItems(IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *defaultOptionItemModel, QList<IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *> otherOptionItemModels, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);

public slots:

//private slots: // tmp
    void expandCollapseWidgetClicked();

private:
    IntelligentSeparatedMultifunctionalButtonWidgetOptionItemWidget *createWidgetFromOptionItemModel(IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *optionItemModel, QSize collapsedSize, QSize expandedSize, bool isExpandedByDefault);

private:
    IntelligentSeparatedMultifunctionalButtonWidgetOptionItemWidget *defaultOptionItemWidget;
    QList<IntelligentSeparatedMultifunctionalButtonWidgetOptionItemWidget *> otherOptionItemWidgets;
    QVBoxLayout *mainLayout;
    QHBoxLayout *defaultOptionItemLineHorizontalLayout;
    SimpleImagePresenterWidget *expandCollapseImageWidget;

    QPixmap backgroundPixmap;
};

#endif // EXPANDABLEBUTTONWIDGET_H
