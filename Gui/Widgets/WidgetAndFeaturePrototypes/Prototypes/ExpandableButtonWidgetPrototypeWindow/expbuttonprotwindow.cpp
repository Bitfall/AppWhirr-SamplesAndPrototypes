#include "expbuttonprotwindow.h"

#include <QHBoxLayout>

#include "Common/Widgets/ExpandableButtonWidget/expandablebuttonwidget.h"
#include "Common/Widgets/ExpandableButtonWidget/intelligentseparatedmultifunctionalbuttonoptionitemmodel.h"

ExpandableButtonWidgetPrototypeWindow::ExpandableButtonWidgetPrototypeWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *centralMainWidget = new QWidget;
    this->setCentralWidget(centralMainWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    centralMainWidget->setLayout(mainLayout);

    // create the intelligent button
    {
        // default option
        QFont defaultOptionFont = QFont("Arial", 12, QFont::Bold);
        IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *defaultOptionModel = new IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel("default option", defaultOptionFont);
        connect(defaultOptionModel, SIGNAL(optionActivated()), this, SLOT(defaultOptionActivated()));

        // other options
        QFont otherOptionFont = QFont("Arial", 12, QFont::Normal);
        QList<IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *> otherOptionModels;
        IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel *otherOption = NULL;

        // option 1
        otherOption = new IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel("option 1", otherOptionFont);
        connect(otherOption, SIGNAL(optionActivated()), this, SLOT(optionOneActivated()));
//        intelligentTestButton->addOptionItemModel(otherOption);
        otherOptionModels.append(otherOption);

        // option 2
        otherOption = new IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel("option 2 xxxxxxxxxxxxxxxxxx", otherOptionFont);
        connect(otherOption, SIGNAL(optionActivated()), this, SLOT(optionTwoActivated()));
//        intelligentTestButton->addOptionItemModel(otherOption);
        otherOptionModels.append(otherOption);

        // option 3
        otherOption = new IntelligentSeparatedMultifunctionalButtonWidgetOptionItemModel("option 3", otherOptionFont);
        connect(otherOption, SIGNAL(optionActivated()), this, SLOT(optionThreeActivated()));
//        intelligentTestButton->addOptionItemModel(otherOption);
        otherOptionModels.append(otherOption);

        _intelligentTestButton = IntelligentSeparatedMultifunctionalButtonWidget::createWithItems(defaultOptionModel, otherOptionModels);



        //    ui->horizontalMainLayout->addWidget(new QLabel("hehe"));
        mainLayout->addWidget(_intelligentTestButton);
    }

}
