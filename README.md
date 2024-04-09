Класс для взаимодействия оптического сортировщика с базой данны
![photo_5235672409678404011_w](https://github.com/asuemg1/OptiMySQL/assets/84317505/ee522741-9c1d-4997-a8d5-c82ddd6b6579)

Методы: 
bool MySQLManager::Conncection(QString dataBaseType,        
                                      QString hostName,
                                      QString databaseName,
                                      QString userName,
                                      QString password)
Возвращает 1 при успешном подключении,  0 при неудачном 

bool MySQLManager::TableCreateMaterial(const std::map<QString, int> &statisticMaterial,
                                      const QString &tableStatisticName)
Возвращеи 1 при успешном создании таблицы,  0 при неудачном 




