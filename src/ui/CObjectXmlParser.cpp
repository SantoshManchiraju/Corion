#include "CObjectXmlParser.h"

CObjectXmlParser::CObjectXmlParser(QString directoryPath)
{
    m_imgCount = 0;
    m_dirPath = directoryPath;
}

unsigned int CObjectXmlParser::addNewImage(QRect areaOfInterest)
{
    QFile file(m_dirPath + "/details.xml");
    file.open(QIODevice::ReadWrite);

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);

    QXmlStreamReader reader(file.readAll());
    file.remove();
    file.open(QIODevice::ReadWrite);

    while(!reader.atEnd())
    {
        if(reader.isStartDocument())
            writer.writeStartDocument();

        if(reader.isStartElement())
        {
            writer.writeStartElement(reader.name().toString());
            if(reader.name() == "count"){
                foreach(const QXmlStreamAttribute &attr, reader.attributes()) {
                        m_imgCount = attr.value().toUInt();
                }
                writer.writeAttribute("value",QString::number(m_imgCount+1));
            }else{
                writer.writeAttributes(reader.attributes());
            }

            if(reader.name() == "images")
            {
                writer.writeStartElement("image");
                writer.writeAttribute("file",m_dirPath + "/" + QString::number(m_imgCount) + ".jpg");

                writer.writeStartElement("box");
                writer.writeAttribute("top",QString::number(areaOfInterest.y()));
                writer.writeAttribute("left",QString::number(areaOfInterest.x()));
                writer.writeAttribute("width",QString::number(areaOfInterest.width()));
                writer.writeAttribute("height",QString::number(areaOfInterest.height()));
                writer.writeEndElement(); // box

                writer.writeEndElement(); // image
            }
        }
        if(reader.isCharacters()){
            writer.writeCharacters(reader.text().toString());
        }

        if(reader.isEndElement())
            writer.writeEndElement();

        if(reader.isEndDocument())
            writer.writeEndElement();

        reader.readNext();
    }

    file.close();

    return m_imgCount;
}

void CObjectXmlParser::createNewFile(QRect areaOfInterest)
{
    QFile file(m_dirPath + "/details.xml");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    writer.writeStartElement("dataset");
    writer.writeStartElement("count");
    writer.writeAttribute("value",QString::number(m_imgCount+1));
    writer.writeEndElement();
    writer.writeStartElement("images");

    writer.writeStartElement("image");
    writer.writeAttribute("file",m_dirPath + "/" + QString::number(m_imgCount) + ".jpg");

    writer.writeStartElement("box");
    writer.writeAttribute("top",QString::number(areaOfInterest.y()));
    writer.writeAttribute("left",QString::number(areaOfInterest.x()));
    writer.writeAttribute("width",QString::number(areaOfInterest.width()));
    writer.writeAttribute("height",QString::number(areaOfInterest.height()));
    writer.writeEndElement(); // box

    writer.writeEndElement(); // image

    writer.writeEndElement(); // images
    writer.writeEndElement(); // dataset

    file.close();
}

unsigned int CObjectXmlParser::getCount()
{
    return m_imgCount;
}
