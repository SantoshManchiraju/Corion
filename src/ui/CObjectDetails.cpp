#include "CObjectDetails.h"

CObjectDetails::CObjectDetails(QString name, bool isKnown, bool isValid)
{
    m_name = name;
    m_isKnown = isKnown;
    m_isValid = isValid;
}

QString CObjectDetails::name()
{
    return m_name;
}

bool CObjectDetails::isKnown()
{
    return m_isKnown;
}

bool CObjectDetails::isValid()
{
    return m_isValid;
}
