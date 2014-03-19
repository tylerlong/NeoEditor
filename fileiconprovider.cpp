#include "fileiconprovider.h"

FileIconProvider::FileIconProvider()
{
}

FileIconProvider::~FileIconProvider()
{
}

QIcon FileIconProvider::icon(IconType type) const
{
    return QFileIconProvider::icon(type);
}

QIcon FileIconProvider::icon(const QFileInfo &info) const
{
    return QFileIconProvider::icon(info);
}

QString FileIconProvider::type(const QFileInfo &info) const
{
    return QFileIconProvider::type(info);
}
