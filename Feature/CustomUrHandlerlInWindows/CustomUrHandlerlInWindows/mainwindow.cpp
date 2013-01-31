#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>

#ifdef Q_WS_WIN
#include <windows.h>
#include <Tchar.h>
//#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"advapi32.lib")
#endif

MainWindow::MainWindow(QString initialStatusMessage, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);

    _statusLabel = new QLabel;
    _statusLabel->setText(initialStatusMessage);
    mainLayout->addWidget(_statusLabel);

    QPushButton *registerUrlHandlerButton = new QPushButton;
    registerUrlHandlerButton->setText(tr("Register this app as url handler for the url scheme: testscheme://the-given-part"));
    connect(registerUrlHandlerButton, SIGNAL(clicked()), this, SLOT(registerUrlSchemeButtonPressed()));
    mainLayout->addWidget(registerUrlHandlerButton);
}

MainWindow::~MainWindow()
{

}

void MainWindow::registerUrlSchemeButtonPressed()
{

    if(this->win_RegisterCustomUrlScheme("testscheme", QApplication::applicationFilePath(), QApplication::applicationFilePath())) {
        this->_statusLabel->setText(tr("Scheme registered."));
    }
    else {
        this->_statusLabel->setText(tr("Cannot register the scheme!"));
    }
}


bool MainWindow::win_RegisterCustomUrlScheme(QString urlScheme, QString targetAppPathToCall, QString iconPath)
{
    bool isSuccess = true;
    HKEY hKey;
    HKEY hRootSchemeKey;
    LPCTSTR sk = TEXT("Software\\Classes");

    targetAppPathToCall = targetAppPathToCall.replace("/", "\\");
    iconPath = iconPath.replace("/", "\\");

    //
    // step 1: open the root of url scheme handlers
    LONG regOpResult = RegOpenKeyEx(HKEY_CURRENT_USER, sk, 0, KEY_ALL_ACCESS , &hKey);

    if(regOpResult != ERROR_SUCCESS) {
        WLog("Cannot open the root registry key.");
        return false;
    }

    //
    // step 2: create the base scheme key ----------------
//    WCHAR *win_urlScheme = (WCHAR *)malloc(sizeof(WCHAR) * (urlScheme.size() + 1));
//    urlScheme.toWCharArray(win_urlScheme);
//    // null terminate!!!
//    win_urlScheme[urlScheme.size()] = 0;

    regOpResult = RegCreateKeyEx(hKey, urlScheme.utf16(), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hRootSchemeKey, NULL);
    // free up
//    free(win_urlScheme);

    if (regOpResult == ERROR_SUCCESS) {
        DLog("Success creating and opening root scheme key.");

        // default value
        QString protocolName = "URL:"+urlScheme+" protocoll";
//        WCHAR *win_protocolName = (WCHAR *)malloc(sizeof(WCHAR) * (protocolName.size() + 1));
//        protocolName.toWCharArray(win_protocolName);
//        // null terminate!!!
//        win_protocolName[protocolName.size()] = 0;

//        protocolName.toStdWString().c_str()

        // convert it to MBS (MultiByte String)
//        size_t mbs_protocolName_size = WideCharToMultiByte (NULL, protocolName.toStdWString());

//        unsigned char* str = new unsigned char[protocolName.length];
//        memmove(str,(const char*)s,s.length);
//        protocolName.toStdWString()
        regOpResult = RegSetValueExW(hRootSchemeKey, NULL, 0, REG_SZ, (const BYTE*)protocolName.toStdWString().c_str(), (lstrlen(protocolName.toStdWString().c_str()) + 1) * sizeof(WCHAR));
//        free(win_protocolName);

        if(regOpResult == ERROR_SUCCESS) {
            // URL Protocol value
            regOpResult = RegSetValueEx(hRootSchemeKey, TEXT("URL Protocol"), 0, REG_SZ, 0, 0);
        }
    }
    else {
        WLog("Error opening root scheme key.");
        isSuccess = false;
    }

    if (regOpResult != ERROR_SUCCESS){
        WLog("Error creating/set root scheme values.");
        isSuccess = false;
    }

    if(RegCloseKey(hKey) != ERROR_SUCCESS) {
        WLog("Cannot close the root registry key.");
        isSuccess = false;
    }

    //
    // step 3: create sub-keys ---------------------

    // shell subkey tree
    regOpResult = RegCreateKeyEx(hRootSchemeKey, TEXT("shell\\open\\command"), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

    if (regOpResult == ERROR_SUCCESS) {
        DLog("Success creating and opening shell subtree keys.");

        // default value
        QString commandString = "\""+targetAppPathToCall+"\" \"%1\"";
//        WCHAR *win_commandString = (WCHAR *)malloc(sizeof(WCHAR) * (commandString.size() + 1));
//        commandString.toWCharArray(win_commandString);
//        // null terminate!!!
//        win_commandString[commandString.size()] = 0;
//        regOpResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, win_commandString, commandString.size() + 1);

//        QString testString("Hello édes drága registry! Miért teszed ezt velem?? Még pár karakter üóűÉÁÜÓŰ");
//        size_t convertedCharCnt;
//        char *pMBBuffer = (char *)malloc( 10000 );
//        DLog("Conversion result: ") << wcstombs_s(&convertedCharCnt, pMBBuffer, (size_t)10000, testString.toStdWString().c_str(), (size_t)10000 );
//        DLog("Conversion result: ") << /*count = */wcstombs(pMBBuffer, testString.toStdWString().c_str(), 10000 );
//        TCHAR szData[] = TEXT("Hello édes drága registry! Miért teszed ezt velem?? Még pár karakter üóűÉÁÜÓŰ");
//        regOpResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szData, sizeof(szData));
        regOpResult = RegSetValueExW(hKey, NULL, 0, REG_SZ, (CONST BYTE*)commandString.toStdWString().c_str(), (lstrlen(commandString.toStdWString().c_str()) + 1) * sizeof(WCHAR));
//        free(win_commandString);

        if (regOpResult != ERROR_SUCCESS){
            WLog("Error creating/set command key values.");
            isSuccess = false;
        }
    } else {
        WLog("Error creating shell subtree keys.");
        isSuccess = false;
    }

    if(RegCloseKey(hKey) != ERROR_SUCCESS) {
        WLog("Cannot close the shell subtree keys.");
        isSuccess = false;
    }

    // DefaultIcon subkey
    regOpResult = RegCreateKeyEx(hRootSchemeKey, TEXT("DefaultIcon"), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

    if(regOpResult == ERROR_SUCCESS) {
        DLog("Success creating and opening DefaultIcon sub-key.");

        QString iconString = "\"" + iconPath + "\"";
        regOpResult = RegSetValueExW(hKey, NULL, 0, REG_SZ, (CONST BYTE*)iconString.toStdWString().c_str(), (lstrlen(iconString.toStdWString().c_str()) + 1) * sizeof(WCHAR));
//        free(win_commandString);

        if (regOpResult != ERROR_SUCCESS){
            WLog("Error creating/set DefaultIcon key values.");
            isSuccess = false;
        }
    }
    else {
        WLog("Error: creating and opening DefaultIcon sub-key!");
    }

    if(RegCloseKey(hKey) != ERROR_SUCCESS) {
        WLog("Cannot close the DefaultIcon subkey.");
        isSuccess = false;
    }

    if(RegCloseKey(hRootSchemeKey) != ERROR_SUCCESS) {
        WLog("Cannot close the root scheme key.");
        isSuccess = false;
    }

    if(!isSuccess) {
        WLog("Couldn't create the required registry keys.");
        return false;
    }

    return isSuccess;

//    LPCTSTR value = TEXT("TestSoftwareKey");
//    LPCTSTR data = TEXT("TestData");

//    LONG setRes = RegSetValueEx (hKey, value, 0, REG_SZ, (LPBYTE)data, wcslen(data)+1);

//    if (setRes == ERROR_SUCCESS) {
//        DLog("Success writing to Registry.");
//    } else {
//        DLog("Error writing to Registry.");
//    }

//    LONG closeOut = RegCloseKey(hKey);

//    if (closeOut == ERROR_SUCCESS) {
//        DLog("Success closing key.");
//    } else {
//        DLog("Error closing key.");
//    }
}
