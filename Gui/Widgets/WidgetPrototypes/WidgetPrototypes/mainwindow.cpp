#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QMessageBox>

#include "Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonoptionitemmodel.h"
#include "Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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

        intelligentTestButton = IntelligentSeparatedMultifunctionalButtonWidget::createWithItems(defaultOptionModel, otherOptionModels);



        //    ui->horizontalMainLayout->addWidget(new QLabel("hehe"));
        ui->horizontalMainLayout->addWidget(intelligentTestButton);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::defaultOptionActivated()
{
    QMessageBox::information(this, "default", "default option activated");
}

void MainWindow::optionOneActivated()
{
    QMessageBox::information(this, "1", "option 1 activated");
}

void MainWindow::optionTwoActivated()
{
    QMessageBox::information(this, "2", "option 2 activated");
}

void MainWindow::optionThreeActivated()
{
    QMessageBox::information(this, "3", "option 3 activated");
}

void MainWindow::on_pushButton_clicked()
{
    intelligentTestButton->expandCollapseWidgetClicked();
}
