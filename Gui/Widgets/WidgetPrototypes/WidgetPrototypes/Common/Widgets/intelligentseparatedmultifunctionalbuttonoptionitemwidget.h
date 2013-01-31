#ifndef IntelligentSeparatedMultifunctionalButtonWidgetOPTIONITEMWIDGET_H
#define IntelligentSeparatedMultifunctionalButtonWidgetOPTIONITEMWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

#include "Common/Widgets/BaseWidgets/AnimatedTwoFixedSizeWidgetBase/animatedtwofixedsizewidgetbase.h"

class IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel;

class IntelligentSeparatedMultifunctionalButtonWidgetOptionItemWidget : public AnimatedTwoFixedSizeWidgetBase
{
    Q_OBJECT
public:
    explicit IntelligentSeparatedMultifunctionalButtonWidgetOptionItemWidget(IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *relatedOptionItem, QSize collapsedSize, QSize expandedSize, bool isExpandedByDefault, QWidget *parent = 0);

    IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *getRelatedOptionItemModel() const;

protected:
    void mousePressEvent(QMouseEvent * event);

private:
    IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *relatedOptionItem;
    QLabel *titleLabel;
};

#endif // IntelligentSeparatedMultifunctionalButtonWidgetOPTIONITEMWIDGET_H
