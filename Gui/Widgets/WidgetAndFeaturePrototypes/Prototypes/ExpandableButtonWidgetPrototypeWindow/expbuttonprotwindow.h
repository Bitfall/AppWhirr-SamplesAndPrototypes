#ifndef EXPANDABLEBUTTONWIDGETPROTOTYPEWINDOW_H
#define EXPANDABLEBUTTONWIDGETPROTOTYPEWINDOW_H

#include <QMainWindow>

class IntelligentSeparatedMultifunctionalButtonWidget;

class ExpandableButtonWidgetPrototypeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ExpandableButtonWidgetPrototypeWindow(QWidget *parent = 0);

private:
    IntelligentSeparatedMultifunctionalButtonWidget *_intelligentTestButton;

};

#endif // EXPANDABLEBUTTONWIDGETPROTOTYPEWINDOW_H
