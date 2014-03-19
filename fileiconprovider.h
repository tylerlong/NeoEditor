#ifndef FILEICONPROVIDER_H
#define FILEICONPROVIDER_H


#include <QtWidgets>

class FileIconProvider : public QFileIconProvider
{
public:
    FileIconProvider();
    ~FileIconProvider();

    QIcon icon(IconType type) const;
    QIcon icon(const QFileInfo &info) const;
    QString type(const QFileInfo &info) const;
};


#endif // FILEICONPROVIDER_H
