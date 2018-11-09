#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTreeView;
class QListView;
class QSplitter;
class QFileSystemModel;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Onclickedtree(const QModelIndex &idx);
    void showContextMenu(const QPoint &pos);
    void info();

private:
    Ui::MainWindow *ui;

    QTreeView *tree;
    QListView *list;
    QSplitter *splitter;
    QFileSystemModel *model;
};

#endif // MAINWINDOW_H
