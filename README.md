Класс для взаимодействия оптического сортировщика с базой данны
![photo_5235672409678404011_w](https://github.com/asuemg1/OptiMySQL/assets/84317505/ee522741-9c1d-4997-a8d5-c82ddd6b6579)

Методы: 
bool MySQLManager::Conncection        Возвращает 1 при успешном подключении,  0 при неудачном 
bool MySQLManager::TableCreateMaterial   Возвращает 1 при успешном создании таблицы,  0 при неудачном 
bool MySQLManager::InsetMaterialStatistic  Возвращает 1 при успешной вставке строки в таблицу,  0 при неудачном  
bool MySQLManager::LoadTable  Возвращает 1 при успешной загрузки в таблицы,  0 при неудачном  
bool  MySQLManager::DeleteTable  Возвращает 1 при успешном удалении таблицы,  0 при неудачном
bool  MySQLManager::CloseConncection Возвращает 1 при успешном удалении всех соединений


