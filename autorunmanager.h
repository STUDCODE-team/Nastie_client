#ifndef AUTORUNMANAGER_H
#define AUTORUNMANAGER_H
#pragma once
#include <QProcess>
#include <FileSystem.h>
#include <QSettings>

class AutoRunManager
{
public:
    AutoRunManager() = delete;

    static void addAppAsLoginItem();
    static void deleteAppFromLoginItem();

private:
    static void include_this_app();
    static void exclude_this_app();

};

#endif // AUTORUNMANAGER_H
