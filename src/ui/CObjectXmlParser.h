#ifndef COBJECTXMLPARSER_H
#define COBJECTXMLPARSER_H

#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QRect>
#include <QDir>

class CObjectXmlParser
{
private:
    unsigned int m_imgCount;
    QString m_dirPath;
public:
    CObjectXmlParser(QString directoryPath);
    unsigned int addNewImage(QRect areaOfInterest);
    void createNewFile(QRect areaOfInterest);
    unsigned int getCount();
};

#endif // COBJECTXMLPARSER_H
