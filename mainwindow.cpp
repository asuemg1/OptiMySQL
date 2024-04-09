#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
#include <QGridLayout>
#include <QIcon>
#include <QStandardItem>
#include <QSize>
#include <QTableWidget>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    this->resize(1920, 1080); // размер окна
    QGridLayout *main_layout = new QGridLayout(); // создать GridLayout главный
    imageScene = new QGraphicsScene(this);  // создать QGraphicsScene

    imageView = new QGraphicsView(imageScene) ; // класс предоставляет виджет QGraphicsView для отображения содержимного  QGraphicsScene
    main_layout->addWidget(imageView, 0, 0, 1, 1);  // добавить в  строку 0 и столбец 0, imageView будет занимать 12 строк и 1 столбец, начиная с верхнего левого угла .
    QWidget *widget = new QWidget(); // создаем кью вижет
    widget->setLayout(main_layout); //  прикрепляем к виджету ayout
    setCentralWidget(widget); // устанавлваем заданный виджет как центр окна

    std::map<QString, int>statisticMaterial3;  // наборы  материалов с количеством для тестов


    statisticMaterial3.insert({"PET_bottle_milk",56});
    statisticMaterial3.insert({"PET_bottle_dark",67});
    statisticMaterial3.insert({"PET_bottle_transp",1010});
    statisticMaterial3.insert({"Paper",89});
    statisticMaterial3.insert({"Tetrapak",99});
    statisticMaterial3.insert({"Newspaper",99});
    statisticMaterial3.insert({"Alum_Cans",99});

    QString tableName = "Statistic_material";    // имя таблицы
    db = new MySQLManager;  // создаю новый sql менеджер
    qDebug() <<"MySQL Conncection  = " << db->Conncection(); // устанавливаю соеднинение с дефолтной базой
    qDebug() <<"MySQL Table Check = " << db->TableCreateMaterial(statisticMaterial3,tableName); // проверить наличие таблицы если нет наличи то создать
    qDebug() <<"MySQL Inset = " << db->InsetMaterialStatistic(statisticMaterial3,tableName); //  вставить данные материала
    qDebug() <<"MySQL Inset = " << db->InsetMaterialStatistic(statisticMaterial3,tableName); // вставить данные материала

    tableView = new QTableView; // виджет таблицы

    QDate cd = QDate::currentDate(); // возвращаем текущую дату
    QTime ct = QTime::currentTime(); // возвращаем текущее время
    QDate dt2;
    dt2= cd.addDays(-3); // дата начала отсчета - 3 дня
    QTime ct2 = QTime::currentTime(); // времся начала отсчета

    qDebug() <<"MySQL Load Table = " <<db->LoadTable(tableName,tableView,cd,ct,dt2,ct); // выборка таблицы

    main_layout->addWidget(tableView, 0, 0, 0, 0); // добавить таблицу на экран
    tableView->resizeColumnsToContents();
    tableView->resizeRowsToContents();
    tableView->show();

   // delete db; // удалить sql менеджер
}
