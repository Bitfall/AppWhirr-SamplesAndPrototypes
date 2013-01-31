#ifndef FRAMEWORKINFO_H
#define FRAMEWORKINFO_H

#include <QString>

class FrameworkInfo
{
public:
    /*! Default constructor - required by Qt meta info system
    */
    explicit FrameworkInfo();
    explicit FrameworkInfo(quint32 frameworkId, QString frameworkPrintableName);

    quint32 getFrameworkId() const;
    QString getFrameworkPrintableName() const;
    
private:
    quint32 _frameworkId;
    QString _frameworkPrintableName;
};

#endif // FRAMEWORKINFO_H
