#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "mysqlmanager.h"
#include "qtablewidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QListView>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsScene *imageScene;
    QGraphicsView *imageView;

    QSqlTableModel *tableModel;
    QTableView *tableView;

private:
    Ui::MainWindow *ui;
    void initUI();
    MySQLManager *db;

};
#endif // MAINWINDOW_H
