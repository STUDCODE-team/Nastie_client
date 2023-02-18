#include "FileSystem.h"

//#define MULTI_DEVICE

int FileSystem::bindDeviceID()
{
#ifdef MULTI_DEVICE
    return QRandomGenerator::global()->bounded(0, INT_MAX);
#endif
    QString m_dataLocation = getStandartPath();

    QFile file(m_dataLocation + "/deviceID.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        qFatal("Device ID unreachable");
    }

    QString id = file.readAll();
    int deviceID;
    if(id.isEmpty())
    {// first application usement
        deviceID = QRandomGenerator::global()->bounded(0, INT_MAX);
        file.write(QString::number(deviceID).toLatin1());
    }
    else
    {// non-first usement
        deviceID = id.toInt();
    }
    file.close();

#ifdef QT_DEBUG
        qInfo() << QTime::currentTime().toString() << "DEVICE_ID: \t" << deviceID;
#endif

        return deviceID;
}

bool FileSystem::noUserName()
{
    QString m_dataLocation = getStandartPath();

    QFile file(m_dataLocation + "/userName.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        qFatal("Device ID unreachable");
    }

    return file.readLine().isEmpty();
}

QString FileSystem::name()
{
    QString m_dataLocation = getStandartPath();

    QFile file(m_dataLocation + "/userName.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        qFatal("Device ID unreachable");
    }

    return file.readLine();
}

const QString FileSystem::getRandomUserName()
{
    int len = QRandomGenerator::global()->bounded(0, 9);
    QString s(len);
    for(int i = 0; i < len; ++i)
    {
        s[i] = QRandomGenerator::global()->bounded('A', 'Z');
    }
    return s;
}

void FileSystem::registerUserName(const QString userName)
{
    QString m_dataLocation = getStandartPath();

    QFile file(m_dataLocation + "/userName.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        qFatal("Device ID unreachable");
    }

    file.write(userName.toLatin1());
}

QString FileSystem::macOSXAppBundlePath()
{
#ifdef Q_OS_MAC
    QDir dir = QDir ( QCoreApplication::applicationDirPath() );
    dir.cdUp();
    dir.cdUp();
    QString absolutePath = dir.absolutePath();
    // absolutePath will contain a "/" at the end,
    // but we want the clean path to the .app bundle
    if ( absolutePath.length() > 0 && absolutePath.right(1) == "/" ) {
        absolutePath.chop(1);
    }
    return absolutePath;
#else
    return "";
#endif
}

QString FileSystem::macOSXAppBundleName()
{
#ifdef Q_OS_MAC
    QString bundlePath = macOSXAppBundlePath();
    QFileInfo fileInfo(bundlePath);
    return fileInfo.baseName();
#else
    return "";
#endif
}

QString FileSystem::getStandartPath()
{
    // get folder path for currect working on mobile devices;
    QString m_dataLocation = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).value(0);

#ifndef QT_DEBUG
    if (!QDir(m_dataLocation).exists() and !QDir("").mkpath(m_dataLocation))
    {
        qFatal("Failed to reach app data directory.");
    }
#else
    if (QDir(m_dataLocation).exists()){
        qDebug() << "App data directory exists. " << m_dataLocation;
    } else {
        if (QDir("").mkpath(m_dataLocation)) {
            qDebug() << "Created app data directory. " << m_dataLocation;
        } else {
            qFatal("Failed to create app data directory.");
        }
    }
#endif
    return m_dataLocation;
}
