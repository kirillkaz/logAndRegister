#include <iostream>
#include "authorizator.h"
#include "windows.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);

     Ilogger* log;
     logger* factory = new logger();
     log = factory->create();

     authorizator menu("DataBase.txt",log);

     menu.RegisterUser();
    return 0;
}