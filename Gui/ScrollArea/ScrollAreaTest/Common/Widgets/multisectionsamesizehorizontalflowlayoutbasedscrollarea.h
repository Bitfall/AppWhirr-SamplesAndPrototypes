#ifndef MULTISECTIONSAMESIZEHORIZONTALFLOWLAYOUTBASEDSCROLLAREA_H
#define MULTISECTIONSAMESIZEHORIZONTALFLOWLAYOUTBASEDSCROLLAREA_H

#include <QScrollArea>

#include "../Layouts/samesizelayoutbase.h"

class SectionBasedHorizontalFlowLayoutPresenterDelegate;
class MouseGrabScrollDelegate;

class MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea : public QScrollArea
{
    Q_OBJECT

private:
    class SectionData {
    public:
        SectionData(QWidget *sectionWidget, SameSizeLayoutBase *sectionLayout) : _sectionWidget(sectionWidget), _sectionLayout(sectionLayout) {}

        QWidget *getSectionWidget() const { return _sectionWidget; }
        SameSizeLayoutBase *getSectionLayout() const { return _sectionLayout; }

    private:
        QWidget *_sectionWidget;
        SameSizeLayoutBase *_sectionLayout;
    };

public:
    //
    // the delegate won't be deleted, you have to do it's memory-management
    explicit MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea(SectionBasedHorizontalFlowLayoutPresenterDelegate *delegate, int sectionCount, QWidget *parent = 0);
    ~MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea();

    void addWidgetToSection(QWidget *widget, int sectionIndex);

protected:
    void resizeEvent(QResizeEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    bool processMouseWheelEventFilter(QWheelEvent *wheelEvent);
    bool processMouseButtonPressEvent(QObject *obj, QMouseEvent *e);
    bool processMouseMoveEvent(QObject *obj, QMouseEvent *e);
    bool processMouseButtonReleaseEvent(QObject *obj, QMouseEvent *e);

protected:
    QWidget *_mainContentHolderWidget;
    QList<SectionData *> _sections;
    SectionBasedHorizontalFlowLayoutPresenterDelegate *_delegate;

    MouseGrabScrollDelegate *_mouseGrabScrollDelegate;
};

#endif // MULTISECTIONSAMESIZEHORIZONTALFLOWLAYOUTBASEDSCROLLAREA_H
