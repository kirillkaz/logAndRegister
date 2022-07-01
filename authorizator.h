#ifndef LOGANDREGISTER_AUTHORIZATOR_H
#define LOGANDREGISTER_AUTHORIZATOR_H

#include <iostream>
#include <cmath>
#include "Csv/Csv.h"
#include "logger/logFactory/logger.h"
#include "key-value/container.h"
#include <fstream>

class authorizator {


public:
    Ilogger* log;
    Csv data;
    container<std::string> DB;
    std::string DataBaseName;

    ///////////////

    bool NameIsExist(std::string username);

    bool IsPasswordCorrect(std::string username, std::string password);

    std::string ToHash(std::string stroke);

    void UpdateDataBase();

    //////////////

    authorizator();

    authorizator(std::string DataBase, Ilogger* log);

    void RegisterUser();
    void RegisterUserHand(std::string password, std::string username);

    void LogUser();
    bool LogUserHand(std::string username, std::string password);

};

long long HashFunc(std::string str);

#endif //LOGANDREGISTER_AUTHORIZATOR_H
