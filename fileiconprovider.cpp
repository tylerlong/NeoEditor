#include "fileiconprovider.h"

FileIconProvider::FileIconProvider()
{
    fileIcon = QIcon(":/images/treeview/file.svg");
    folderIcon = QIcon(":/images/treeview/folder.svg");
}

FileIconProvider::~FileIconProvider()
{
}

QIcon FileIconProvider::icon(IconType type) const
{
    switch(type)
    {
        case QFileIconProvider::File:
            return fileIcon;
        case QFileIconProvider::Folder:
            return folderIcon;
        default:
            return QFileIconProvider::icon(type);
    }
}

QIcon FileIconProvider::icon(const QFileInfo &info) const
{
    if(info.isFile())
    {
        return fileIcon;
    }
    else if(info.isDir())
    {
        return folderIcon;
    }
    else
    {
        return QFileIconProvider::icon(info);
    }
}

QString FileIconProvider::type(const QFileInfo &info) const
{
    QString type = QFileIconProvider::type(info);
    return type;
}
