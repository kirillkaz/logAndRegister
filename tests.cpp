#include <gtest/gtest.h>
#include <fstream>
#include "authorizator.h"
#include "Csv/Csv.h"
void run_tests(){
    RUN_ALL_TESTS();
}

TEST(authorizator,NameIsExist){
    Ilogger* log;
    logger* factory = new logger();
    log = factory->create();

    Csv dataBase;
    dataBase.parsing("DataBase.txt");

    authorizator menu("DataBase.txt",log);

    bool myNameIsExists = menu.NameIsExist("name");

    bool systemNameIsExists = false;

    for(int i=0;i<dataBase.CsvArray.size();i++) if("name" == dataBase.CsvArray[i][0]) systemNameIsExists=true;

    EXPECT_EQ(myNameIsExists,systemNameIsExists);
}

TEST(authorizator,IsPasswordCorrect){
    Ilogger* log;
    logger* factory = new logger();
    log = factory->create();

    Csv dataBase;
    dataBase.parsing("DataBase.txt");

    authorizator menu("DataBase.txt",log);

    bool myIsPasswordCorrect = menu.IsPasswordCorrect("name","1234");

    bool systemIsPasswordCorrect = false;

    for(int i=0;i<dataBase.CsvArray.size();i++)
        if(std::to_string(HashFunc("1234")) == dataBase.CsvArray[i][1] && "name" == dataBase.CsvArray[i][0]) systemIsPasswordCorrect = true;

    EXPECT_EQ(myIsPasswordCorrect,systemIsPasswordCorrect);
}

TEST(authorizator,RegisterUser){
    Ilogger* log;
    logger* factory = new logger();
    log = factory->create();

    authorizator menu("DataBase.txt",log);

    menu.RegisterUserHand("newName","newPassword");

    bool isRegSuccess = false;

    if(menu.NameIsExist("newName"))
        if(menu.IsPasswordCorrect("newName","newPassword"))
            isRegSuccess = true;

    //refactor file
    std::ofstream file("DataBase.txt");

    std::vector<std::string> names = menu.DB.GetKeyArr();
    std::vector<std::string> passwords = menu.DB.GetValArr();

    for(int i = 0;i<names.size()-1;i++) file << names[i]+','+passwords[i]<<std::endl;

    file.close();
    EXPECT_EQ(true,isRegSuccess);
}

TEST(authorizator,LogUser){
    Ilogger* log;
    logger* factory = new logger();
    log = factory->create();

    authorizator menu("DataBase.txt",log);

    bool correctData = menu.LogUserHand("name","1234");

    bool correctDataCheck = false;

    if(menu.NameIsExist("name"))
        if(menu.IsPasswordCorrect("name","1234"))
            correctDataCheck = true;

    EXPECT_EQ(correctData,correctDataCheck);

    bool incorrectData = menu.LogUserHand("namesghdsgdhfsdadfghfdghfdsfgertberbrbrvgs","1256456g45by6y45vt345t34");
    bool inCorrectDataCheck = false;

    if(menu.NameIsExist("namesghdsgdhfsdadfghfdghfdsfgertberbrbrvgs"))
        if(menu.IsPasswordCorrect("namesghdsgdhfsdadfghfdghfdsfgertberbrbrvgs","1256456g45by6y45vt345t34"))
            inCorrectDataCheck = true;

    EXPECT_EQ(incorrectData,inCorrectDataCheck);

    incorrectData = menu.LogUserHand("name","1256456g45by6y45vt345t34");
    if(menu.NameIsExist("name"))
        if(menu.IsPasswordCorrect("namesghdsgdhfsdadfghfdghfdsfgertberbrbrvgs","1256456g45by6y45vt345t34"))
            inCorrectDataCheck = true;

    EXPECT_EQ(incorrectData,inCorrectDataCheck);
}