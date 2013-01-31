# Basic mechanism

* Every test-run is a private slot of a UnitTest Class (special class, dedicated to UnitTests)
* If a test fails in a private slot test method then the method won't continue
** But other tests in other private slots will, they are independent

# For more information on Qt Unit Testing check these links

* http://developer.qt.nokia.com/doc/qt-4.7/qtestlib-tutorial1.html#id-5d49966b-b76e-42a6-b745-b9139c6341ee
* http://doc.qt.nokia.com/4.7/qtestlib-manual.html (or the new version: http://developer.qt.nokia.com/doc/qt-4.7/qtestlib-manual.html)
* http://developer.qt.nokia.com/doc/qt-4.7/qtest.html

# This is also useful

* http://stackoverflow.com/questions/1524390/qt-what-unit-testing-framework
