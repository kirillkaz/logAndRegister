#include <iostream>
#include "authorizator.h"
#include "windows.h"
#include "tests.cpp"
int main() {
    SetConsoleOutputCP(CP_UTF8);

    run_tests();
    /*Ilogger* log;
    logger* factory = new logger();
    log = factory->create();

    authorizator menu("DataBase.txt",log);

    menu.LogUser();*/
    return 0;
}