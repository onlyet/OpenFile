#ifndef CFILEINFODLG_H
#define CFILEINFODLG_H

#include <QDialog>
#include <QFileInfo>

class CFileInfoDlg : public QDialog
{
    Q_OBJECT

public:
    CFileInfoDlg(QFileInfo &file_info,
                 QWidget *parent = 0,
                 Qt::WindowFlags f = 0);
};

#endif // CFILEINFODLG_H
