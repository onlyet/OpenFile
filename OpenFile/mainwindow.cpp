#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QVboxLayout>
#include <QTreeWidget>
#include <QMessageBox>

#include "cfileinfodlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    resize(1200,600);
    splitter = new QSplitter(centralWidget);

    // model cls
    QString dir = QString("/");
    model = new QFileSystemModel;

    model->setRootPath(dir);

    // view control
    tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(dir));

    // view
    list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(dir));

    // set context menu flag
    list->setContextMenuPolicy(Qt::CustomContextMenu);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(splitter);

    // Set central widget layout, not on  windows.
    centralWidget->setLayout(layout);

    connect(tree,SIGNAL(clicked(QModelIndex)),this,SLOT(Onclickedtree(QModelIndex)));

    connect(list, SIGNAL(customContextMenuRequested(QPoint)),
                                    this, SLOT(showContextMenu(QPoint)));
}

void MainWindow::info()
{
    // path:
    // kind: dir or file
    // size:
    // last modify time
    // other info

    foreach(const QModelIndex &index, list->selectionModel()->selectedIndexes())
    {
        QFileInfo file_info = model->fileInfo(index);
        CFileInfoDlg dlg(file_info, this);
        dlg.exec();
    }
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = list->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Detailed Info", this, SLOT(info()));
    myMenu.addAction("Others");

    // Show context menu at handling position
    myMenu.exec(globalPos);
}

void MainWindow::Onclickedtree(const QModelIndex &idx)
{
    QMessageBox box;
    box.setText("Onclickedtree");
    list->setModel(model);
    list->setRootIndex(idx);
}

MainWindow::~MainWindow()
{
    delete ui;
}
