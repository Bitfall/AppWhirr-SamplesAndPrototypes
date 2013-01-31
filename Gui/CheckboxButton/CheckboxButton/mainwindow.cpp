#include "mainwindow.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QCheckBox>

//
#include "checkboxbutton.h"
#include "checkboxbutton2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    //
    QTextEdit *testTextEdit = new QTextEdit;
    mainLayout->addWidget(testTextEdit);

    //
    CheckboxButton *checkboxButton = new CheckboxButton;

    checkboxButton->setObjectName("checkboxButton");
    QString testStyle = lowPriorityGreyButtonStyleSheet();


    testStyle += "QCheckBox {"
                                "spacing: 5px;"
                              "}"

                              "QCheckBox::indicator {"
                                "width: 20px;"
                                "height: 20px;"
                              "}"

                              "QCheckBox::indicator:unchecked {"
                                   "image: url(:/Checkbox-Default-Normal);"
                              "}"

                              "QCheckBox::indicator:checked {"
                                   "image: url(:/Checkbox-Checked-Normal);"
                              "}";

    checkboxButton->setStyleSheet(testStyle);
    checkboxButton->setTitleText(tr("Click me!!"));
//    checkboxButton->setFixedSize(50, 50);
    mainLayout->addWidget(checkboxButton);

    CheckboxButton2 *checkboxButton2 = new CheckboxButton2;
    checkboxButton2->setText(tr("Checkbox Button #2"));
    mainLayout->addWidget(checkboxButton2);

    //
    QPushButton *testPushButton = new QPushButton;
    mainLayout->addWidget(testPushButton);

    // Checkbox-Checked-Normal

    QCheckBox *testCheckBox = new QCheckBox;
//    QString testCheckboxStyle("QCheckBox {"
//                                "spacing: 5px;"
//                                "background-color: #00ff00;"
//                              "}"

//                              "QCheckBox::indicator {"
//                                "width: 30px;"
//                                "height: 30px;"
//                              "}"

//                              "QCheckBox::indicator:unchecked {"
//                                   "image: url(:/Checkbox-Default-Normal);"
//                              "}"

//                              "QCheckBox::indicator:checked {"
//                                   "image: url(:/Checkbox-Checked-Normal);"
//                              "}"
//                              );
//    testCheckBox->setStyleSheet(testCheckboxStyle);
    mainLayout->addWidget(testCheckBox);
}

MainWindow::~MainWindow()
{

}

const QString MainWindow::lowPriorityGreyButtonStyleSheet()
{
    QString r("QWidget#checkboxButton {"
                "border-style: solid;"
                "border-width: 1px;"
                "border-radius: 2px;"
                "border-color: #999999;"

                "padding: 5px;"

                "font: 14px arial, sans-serif;"
              "}"

              "QWidget#checkboxButton:hover {"
                "border-color: #000000;"
              "}"
              );

    r += "QWidget#checkboxButton {"
            "background-color: #f0f0f0;"

            "font: 14px arial, sans-serif;"
            "color: #333333;"
          "}"

          "QWidget#checkboxButton:hover {"
//            "background-color: #d6d6d6;"
            "color: #000000;"
            "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d6d6d6, stop:0.1 #f0f0f0, stop:0.9 #f0f0f0, stop:1 #d6d6d6);"
          "}"

          "QWidget#checkboxButton:!enabled {"
            "background-color: #d6d6d6;"
//            "color: #666666;"
          "}";

    return r;
}
