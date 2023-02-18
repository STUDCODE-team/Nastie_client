#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QStandardPaths>
#include <QRandomGenerator>
#include <QFile>
#include <QDir>
#include <QApplication>


#ifdef QT_DEBUG
    #include <QDebug>
    #include <QTime>
#endif

class FileSystem
{
public:
    FileSystem() = delete;

    static int bindDeviceID();

    static bool noUserName();
    static QString name();
    static const QString getRandomUserName();
    static void registerUserName(const QString userName);

    static const int MAX_NAME_LEN = 20;

    static QString macOSXAppBundlePath();
    static QString macOSXAppBundleName();

private:
    static QString getStandartPath();
};

#endif // FILESYSTEM_H
