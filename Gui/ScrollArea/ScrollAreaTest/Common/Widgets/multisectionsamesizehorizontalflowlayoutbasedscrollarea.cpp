#include "multisectionsamesizehorizontalflowlayoutbasedscrollarea.h"

// UI
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>

#include "sectionbasedhorizontalflowlayoutpresenterdelegate.h"
#include "../mousegrabscrolldelegate.h"

//
#include <QWheelEvent>
#include <QMouseEvent>

MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea(SectionBasedHorizontalFlowLayoutPresenterDelegate *delegate, int sectionCount, QWidget *parent) :
    QScrollArea(parent),
    _delegate(delegate)
{
    this->setWidgetResizable(false);

    _mainContentHolderWidget = new QWidget;
//    _mainContentHolderWidget->setStyleSheet("QWidget { background-color: #f000f0; }");
    _mainContentHolderWidget->installEventFilter(this);
    QVBoxLayout *mainContentHolderLayout = new QVBoxLayout;
    mainContentHolderLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    _mainContentHolderWidget->setLayout(mainContentHolderLayout);

    for(int i = 0; i < sectionCount; ++i)
    {
        // section title if given
        QString sectionTitleText = _delegate->getSectionTitle(i);
        if(!sectionTitleText.isEmpty()) {
            QLabel *sectionTitleLabel = new QLabel(sectionTitleText);
            sectionTitleLabel->setStyleSheet(_delegate->getSectionTitleLabelStyleSheet(i));
            mainContentHolderLayout->addWidget(sectionTitleLabel);
        }

        QWidget *sectionWidget = new QWidget;
        sectionWidget->installEventFilter(this);
        sectionWidget->setStyleSheet(_delegate->getSectionWidgetStyleSheet(i));
        SameSizeLayoutBase *sectionLayout = _delegate->createLayout();
        sectionWidget->setLayout(sectionLayout);
        this->_sections.append(new SectionData(sectionWidget, sectionLayout));

        mainContentHolderLayout->addWidget(sectionWidget);
    }

    this->setWidget(_mainContentHolderWidget);

    _mouseGrabScrollDelegate = new MouseGrabScrollDelegate(400, 2.0f, 5, 0.3f, this);
    _mouseGrabScrollDelegate->setTargetScrollArea(this);
    this->installEventFilter(this);
}

MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::~MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea() {
    qDeleteAll(this->_sections);
}

void MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::resizeEvent(QResizeEvent *e)
{
    QScrollArea::resizeEvent(e);

    int maxSectionWidth = 0;

    for(int i = 0; i < _sections.size(); ++i)
    {
        SameSizeLayoutBase *sectionLayout = _sections[i]->getSectionLayout();
        QWidget *sectionWidget = _sections[i]->getSectionWidget();

        sectionLayout->recalculateMinimalAndOptimalSizesByTotalLayoutWidth(this->contentsRect().width() - this->verticalScrollBar()->width());
        sectionWidget->setMinimumSize(sectionLayout->getCalculatedMinimalSize());
        sectionWidget->resize(sectionLayout->getCalculatedOptimalSize());

        maxSectionWidth = qMax(maxSectionWidth, sectionLayout->getCalculatedOptimalSize().width());
    }

    //
    // main content holders
    _mainContentHolderWidget->setFixedWidth(_mainContentHolderWidget->contentsMargins().left() + maxSectionWidth + _mainContentHolderWidget->contentsMargins().right());
    _mainContentHolderWidget->adjustSize();
}

void MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::addWidgetToSection(QWidget *widget, int sectionIndex) {
    if(sectionIndex >= 0 && sectionIndex < _sections.size()) {
        SameSizeLayoutBase *sectionLayout = this->_sections[sectionIndex]->getSectionLayout();
        widget->installEventFilter(this);
        sectionLayout->addWidget(widget);
    }
    else {
        WLog("Invalid section index: ") << sectionIndex;
    }
}


bool MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::processMouseWheelEventFilter(QWheelEvent *wheelEvent)
{
    if (wheelEvent->orientation() == Qt::Horizontal) {
        return false; // XXXXX: also add this to smart-box-area as well
    }
    DLog("Wheel") << wheelEvent->delta();
    this->_mouseGrabScrollDelegate->doSmoothDropScroll(0, -1 * wheelEvent->delta() * 2.3f);

    return true;
}

bool MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::processMouseButtonPressEvent(QObject *obj, QMouseEvent *e)
{
    return this->_mouseGrabScrollDelegate->handleMouseButtonPressEvent(e);
}

bool MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::processMouseMoveEvent(QObject *obj, QMouseEvent *e)
{
    return _mouseGrabScrollDelegate->handleMouseMoveEvent(e);
}

bool MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::processMouseButtonReleaseEvent(QObject *obj, QMouseEvent *e)
{
    return this->_mouseGrabScrollDelegate->handleMouseButtonReleaseEvent(e);
}

bool MultiSectionSameSizeHorizontalFlowLayoutBasedScrollArea::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
        if(me)
        {
            if( processMouseButtonPressEvent(obj, me) ) {
                me->accept();
                return true;
            }
        }
        else {
            WLog("Cannot cast");
        }
    }
    else if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
        if(me)
        {
            if( processMouseMoveEvent(obj, me) ) {
                me->accept();
                return true;
            }
        }
        else {
            WLog("Cannot cast");
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
        if(me)
        {
            bool resultOfMouseButtonReleseDelegation = processMouseButtonReleaseEvent(obj, me);
            if( resultOfMouseButtonReleseDelegation ) {
                me->accept();
                return true;
            }
        }
        else {
            WLog("Cannot cast");
        }
    }
    else if(event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent *>(event);
        if(wheelEvent) {
            if(this->processMouseWheelEventFilter(wheelEvent)) {
                wheelEvent->accept(); // XXXXX: this is required in other delegates as well!!! (e.g. smart-box scroll area!)
                return true;
            }
        }
        else {
            WLog("Cannot cast");
        }
    }


    return QScrollArea::eventFilter(obj, event);
}
