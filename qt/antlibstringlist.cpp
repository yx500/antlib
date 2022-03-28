#include "antlibstringlist.h"

#include <QFileInfo>
#include <QDebug>
TStringList::TStringList() :QStringList()
{

}

void TStringList::LoadFromFile(const AntLibString FileName)
{
    QString fileName=QString(FileName.c_str());
    QFile txtfile(fileName);
        if (txtfile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream textStream(&txtfile);
            textStream.setCodec("Windows-1251");
            while (true)
            {
                QString line = textStream.readLine();
                if (line.isNull()) break;

                append(line);
            }
            txtfile.close();
        } else {
            qDebug() << "can't open file" << fileName  << endl;
        }
}

int TStringList::Add(const AntLibString S)
{
    append(QString(S.c_str()));
    return size();
}
