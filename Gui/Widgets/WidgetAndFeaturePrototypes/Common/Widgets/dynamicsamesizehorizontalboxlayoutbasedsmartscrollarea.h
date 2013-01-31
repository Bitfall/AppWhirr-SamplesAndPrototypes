#ifndef DYNAMICSAMESIZEHORIZONTALBOXLAYOUTBASEDSMARTSCROLLAREA_H
#define DYNAMICSAMESIZEHORIZONTALBOXLAYOUTBASEDSMARTSCROLLAREA_H

#include <QScrollArea>

#include "Common/ApplicationDescriptionModel/applicationdescriptionmodel.h"
#include "Common/Sorting/widgetlistsnapshot.h"

class DynamicSameSizeHorizontalBoxLayout;
class MouseGrabScrollDelegate;
class CleverApplicationIconPresenterSortingDelegate;
class WidgetListSnapshotHandlerDelegate;
class IdBasedSelectableAndHighlightableWidgetBase;
class IdBasedWidgetCollection;
class IdBasedWidgetBase;
class SameSizeLayoutSnapshotChangeDelegateBase;

//
// it can only manage IconPresenters now
class DynamicSameSizeHorizontalBoxLayoutBasedSmartScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit DynamicSameSizeHorizontalBoxLayoutBasedSmartScrollArea(QSize itemSize, SameSizeLayoutSnapshotChangeDelegateBase *layoutSnapshotChangeDelegate, bool isCenterizeItemsHorizontally, QWidget *parent = 0);

    //
//    void addWidgetToList(IdBasedSelectableAndHighlightableWidgetBase *widgetToAdd, bool isPresentItAsWell);
    void addIdBasedWidgetToCurrentWorkingSnapshot(IdBasedSelectableAndHighlightableWidgetBase *widgetToAdd);

    //
    // commit handling
    QList<QWidget *> getCurrentWorkingSnapshotAsWidgetList() const;
    QList<IdBasedWidgetBase *> getCurrentWorkingSnapshot() const;
    IdBasedWidgetBase *getItemFromWorkingSnapshotByItemId(QString itemId) const;
    void _commitCurrentWorkingSnapshot(); // probably you don't want to use this directly, but call _commitCurrentWorkingSnapshotWithThisOrder instead (after a sorting)

    IdBasedWidgetCollection *__getIdBasedWidgetCollection() const; // DEPRECATED - use getCurrentWorkingSnapshot and commitCurrentWorkingSnapshot methods instead of directly communicating with the working-snapshot-holder object
    WidgetListSnapshotHandlerDelegate *getSnapshotHandlerDelegate() const;

    //
    // will activate the currently selected item or the first one, of none selected - like the user clicked it / activated it
    void activateCurrentItem();

//    QSize sizeHint() const;

Q_SIGNALS:
    void itemActivatedSignal(IdBasedSelectableAndHighlightableWidgetBase *source);
    void itemSelectedSignal(IdBasedSelectableAndHighlightableWidgetBase *item);
    void itemDeselectedSignal(IdBasedSelectableAndHighlightableWidgetBase *item);

//    void mouseEnteredToItemSignal(IdBasedSelectableAndHighlightableWidgetBase *source);
//    void mouseLeavedFromItemSignal(IdBasedSelectableAndHighlightableWidgetBase *source);

public Q_SLOTS:
    void _commitCurrentWorkingSnapshotWithThisOrder(WidgetListSnapshot sortingResultSnapshot); // the snapshot's items have to be added to the working-snapshot before you call this - if not, they won't be added

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    bool event(QEvent *event);
    void resizeEvent(QResizeEvent *event);

private Q_SLOTS:
    void itemActivated(IdBasedSelectableAndHighlightableWidgetBase *source);
    void itemSelected(QWidget *item);
    void itemDeselected(QWidget *item);

    void mouseEnteredToItem(IdBasedSelectableAndHighlightableWidgetBase *source);
    void mouseLeavedFromItem(IdBasedSelectableAndHighlightableWidgetBase *source);

    void _updateContentSizeByLastGivenWidth();

private:

    void _updateContentSize(int targetContentWidth);

    void ensureCurrentSelectedItemCenterizedInScrollArea();
    //
    // will return the selected item, or tries to get the first one if no one is selected
    //  returns NULL if neither of them could be retrieved
    IdBasedSelectableAndHighlightableWidgetBase *getCurrentSelectedItemOrTheFirst() const;

    // mouse
    bool processMouseButtonPressEvent(QObject *obj, QMouseEvent *e);
    bool processMouseMoveEvent(QObject *obj, QMouseEvent *e);
    bool processMouseButtonReleaseEvent(QObject *obj, QMouseEvent *e);
    // keyboard
    bool processKeyPressEvent(QKeyEvent *event);
    bool processKeyReleaseEvent(QKeyEvent *event);
    // keyboard event filter
    bool processKeyPressEventFilter(QKeyEvent *keyEvent);
    // mouse event filter
    bool processMouseWheelEventFilter(QWheelEvent *wheelEvent);

private:
    DynamicSameSizeHorizontalBoxLayout* contentLayout;

    IdBasedWidgetCollection *_idBasedWidgetCollection; // contains the current working-snapshot
    MouseGrabScrollDelegate *mouseGrabScrollDelegate;

    QWidget *contentWidget;
    int _lastGivenContentWidth;
};

#endif // DYNAMICSAMESIZEHORIZONTALBOXLAYOUTBASEDSMARTSCROLLAREA_H
