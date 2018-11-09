#include "cfileinfodlg.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDateTime>

CFileInfoDlg::CFileInfoDlg(QFileInfo &file_info,
                               QWidget *,
                               Qt::WindowFlags)
{
    resize(300, 150);
    QGridLayout *layout = new QGridLayout;

    QLabel *lable_kind = new QLabel(QString("kind: "), this);
    QLineEdit *kind = new QLineEdit(file_info.isDir()?"dir":"file", this);
    kind->setReadOnly(true);

    layout->addWidget(lable_kind, 0,0,1,1,Qt::AlignRight);
    layout->addWidget(kind,0,1);

    QLabel *lable_path = new QLabel(QString("path: "), this);
    QLineEdit *path = new QLineEdit(file_info.absoluteFilePath(), this);
    path->setReadOnly(true);

    layout->addWidget(lable_path,1,0,1,1,Qt::AlignRight);
    layout->addWidget(path,1,1);

    QLabel *lable_size = new QLabel(QString("size: "), this);
    QLineEdit *size = new QLineEdit(QString::number(file_info.size()), this);
    size->setReadOnly(true);

    layout->addWidget(lable_size,2,0,1,1,Qt::AlignRight);
    layout->addWidget(size,2,1);

    QLabel *label_modified = new QLabel(QString("modified: "), this);
    QDateTime modified_tm = file_info.lastModified();
    QLineEdit *tm = new QLineEdit(modified_tm.toString(), this);
    tm->setReadOnly(true);

    layout->addWidget(label_modified,3,0,1,1,Qt::AlignRight);
    layout->addWidget(tm,3,1);

    this->setLayout(layout);
}

