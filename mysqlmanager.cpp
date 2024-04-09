#include "mysqlmanager.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "qsqlquery.h"
#include "qsqltablemodel.h"
#include "qtableview.h"
#include <QSqlError>
#include <QTableView>

// конструктор класса
MySQLManager::MySQLManager(QObject *parent)
    : QObject{parent}
{
}
// деструктор класса
MySQLManager::~MySQLManager()  {
    delete tableModel;
}

// метод подключения к базе данных. По умолчанию подключается к локал хост базе данны
bool MySQLManager::Conncection(QString dataBaseType,
                                      QString hostName,
                                      QString databaseName,
                                      QString userName,
                                      QString password) {
if (!QSqlDatabase::contains()) {
        QSqlDatabase db = QSqlDatabase::addDatabase( dataBaseType);
        db.setHostName(hostName);
        db.setDatabaseName(databaseName);
        db.setUserName(userName);
        db.setPassword(password);
            if(!db.open())
            {
                qDebug() << db.lastError();
                qDebug("MySQL DB failed to connect!" );
                return 0;
            }
                qDebug( "MySQL DB Connected. " );
                return 1;
    } else {
                qDebug("MySQL DB already exist! " );
                return 0;
    }
}

// метод проверки наличия таблицы данных / создание таблицы данных если таблицы нет
bool MySQLManager::TableCreateMaterial(const std::map<QString, int> &statisticMaterial, const QString &tableStatisticName) {
    if (QSqlDatabase::contains()) {
                qDebug( "MySQL DB Сontains ok." );
                QSqlQuery qry;
                QString tablePart1;
                QString tablePart2;
                tablePart1.clear();
                tablePart1 = "CREATE TABLE " + tableStatisticName;
                int productsSize =  statisticMaterial.size();
                int counterSize = 0 ;
                   for (auto i:statisticMaterial) {
                   counterSize = counterSize + 1;
                   tablePart2 = tablePart2 + i.first + " INT" ;
                if(counterSize < productsSize) {
                   tablePart2 = tablePart2 +",";
                   }
                }
                   tablePart1 = tablePart1 + " ("+ "DataTime DATETIME" +"," + tablePart2 + " )";
                qDebug()<< tablePart1 ;
                qry.prepare( tablePart1 );
                if( !qry.exec() ) {
                    qDebug() <<"MySQL DB error TableCheck " << qry.lastError();
                return 0;
                }  else {
                    qDebug( "MySQL DB TableCheck ok." );
                return 1;
                }
    } else {
                    qDebug( "MySQL DB not contains!" );
                return 0;
    }
}

// метод сохранения счетчика материалов в таблицу  в формате Дата + количесвто объектов каждтого типа. Дата генерируется автоматически
bool MySQLManager::InsetMaterialStatistic(const std::map<QString, int> &statisticMaterial, const QString &tableStatisticName) {
    if (QSqlDatabase::contains()) {
        qDebug( "MySQL DB Сontains ok." );
        QSqlQuery qry;
        QString firstPartInsert;
        QString secondPartInsert;
        QString readyQuery;
        firstPartInsert.clear();
        secondPartInsert.clear();
        readyQuery.clear();
        int productsSize =  statisticMaterial.size();
        int counterSize = 0 ;
        for (auto i:statisticMaterial) {
            counterSize = counterSize + 1;
            firstPartInsert = firstPartInsert + i.first;
            secondPartInsert = secondPartInsert + QString::number(i.second);
            if(counterSize < productsSize) {
                firstPartInsert = firstPartInsert + ", " ;
                secondPartInsert = secondPartInsert + ", ";
            }
        }
        readyQuery = "INSERT INTO " + tableStatisticName + " " + "("+"DataTime"+ ", " + firstPartInsert + ") " +"VALUES " +"(" + "CURRENT_TIMESTAMP"+", " +secondPartInsert +")" ;
        qry.prepare(readyQuery);
        if( !qry.exec() ) {
            qDebug() <<"MySQL DB error Inserted " << qry.lastError();
            return 0;
        }  else {
            qDebug( "MySQL DB Inserted ok." );
            return 1;
        }
    } else {
        qDebug( "MySQL DB not contains!" );
        return 0;
    }
}

// метод для закрытия всех соединений
bool  MySQLManager::CloseConncection() {
auto a = QSqlDatabase::connectionNames();
for (auto i:a) {
    QSqlDatabase::removeDatabase(i);
    qDebug() << "MySQL Removed DB connection" <<i <<"!";
    }
    return 1;
}

// метод для закрытия таблицы
bool  MySQLManager::DeleteTable (const QString &tableStatisticName) {
    if (QSqlDatabase::contains()) {
        qDebug( "MySQL DB Сontains ok." );
        QSqlQuery qry;
        QString dropTable = "DROP TABLE ";
        dropTable = dropTable + tableStatisticName;
        qry.prepare(dropTable);
        if( !qry.exec() ) {
            qDebug() <<"MySQL DB error Inserted " << qry.lastError();
            return 0;
        }  else {
            qDebug( "MySQL DB Inserted ok." );
            return 1;
        }
    } else {
        qDebug( "MySQL DB not contains!" );
        return 0;
    }
}

// метод для отображение таблицы из базы данных  необходимо указать имя таблицы, ссылку на qt таблицы, дата и время начала выборки, дата и время окончания выборки
bool MySQLManager::LoadTable (const QString &tableStatisticName,
                                  QTableView *testTableView,
                                  QDate startData,
                                  QTime startTime,
                                  QDate stopData,
                                  QTime stopTime ) {
    if (QSqlDatabase::contains()) {
        qDebug( "MySQL DB Сontains ok." );
        tableModel = new QSqlTableModel;
        tableModel->setTable(tableStatisticName);
        tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        QString startDataStr,startCurrentTimeStr,stopCurrentDataStr,stopCurrentTimeStr;
        // Выполняем конвертацию даты и времени в строки и выводим их
        startDataStr = startData.toString("yyyy-MM-dd");
        startCurrentTimeStr = startTime.toString();
        stopCurrentDataStr = stopData.toString("yyyy-MM-dd");
        stopCurrentTimeStr = stopTime.toString();
        QString filterString = "DataTime between '"+stopCurrentDataStr +" "+ stopCurrentTimeStr + "' and '" + startDataStr +" " + startCurrentTimeStr + "' ";
        qDebug() <<filterString;
        tableModel->setFilter(filterString);
        tableModel->select();
        testTableView->setModel(tableModel);
        return 1;
    } else {
        qDebug( "MySQL DB not contains!" );
        return 0;
    }
}
