#pragma once

#include "qsqldatabase.h"
#include "qsqltablemodel.h"
#include "qtableview.h"
#include <QObject>

class MySQLManager : public QObject
{
    Q_OBJECT
public:
    explicit MySQLManager(QObject *parent = nullptr);
    ~MySQLManager();

    bool Conncection(QString dataBaseType = "QMYSQL",
                            QString hostName = "127.0.0.1",
                            QString databaseName = "OptiAnalizer" ,
                            QString userName = "root" ,
                            QString password = "Atg8n45!"
                            );
    bool InsetMaterialStatistic(const std::map<QString, int> &statisticMaterial, const QString &tableStatisticName);
    bool CloseConncection ();
    bool TableCreateMaterial(const std::map<QString, int> &statisticMaterial, const QString &tableStatisticName);
    bool DeleteTable (const QString &tableStatisticName);
    bool LoadTable (const QString &tableStatisticName,
                        QTableView *testTableView,
                        QDate startData,
                        QTime startTime,
                        QDate stopData,
                        QTime stopTime);
private:
    QSqlTableModel * tableModel = nullptr;

signals:

};

