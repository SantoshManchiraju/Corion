#ifndef COBJECT_H
#define COBJECT_H

#include <QString>

class CObjectDetails
{
    QString m_name;
    bool m_isKnown;
    bool m_isValid;
public:
    CObjectDetails(QString name,bool isKnown, bool isValid);

    QString name();
    bool isKnown();
    bool isValid();
};

#endif // COBJECT_H
