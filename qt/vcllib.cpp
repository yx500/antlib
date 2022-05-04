#include "vcllib.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
//#include <filesystem>


String ChangeFileExt(const String &filename, const char *ext)
{
  QString file  = QString::fromLocal8Bit(filename.c_str(), filename.size());
  QString suffix=QString(".%1").arg(QFileInfo(file).suffix());
  file.replace(suffix , ext );
  return file.toStdString();
}

String ExtractFileName(const String &filename)
{
  return QFileInfo(QString::fromLocal8Bit(filename.c_str(), filename.size())).fileName().toStdString();
}

String ExtractFileDir(const String &filename)
{
  return QFileInfo( QString::fromLocal8Bit(filename.c_str(), filename.size()) ).dir().path().toStdString();
}

bool FileExists(const String &filename)
{
  return QFileInfo::exists( QString::fromLocal8Bit(filename.c_str(), filename.size()) );
}
