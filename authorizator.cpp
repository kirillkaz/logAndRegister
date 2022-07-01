#include "authorizator.h"
#include "CSV_container_converter.h"

authorizator::authorizator(){}

authorizator::authorizator(std::string DataBase, Ilogger* log){
    this->DataBaseName = DataBase;
    this->data.parsing(this->DataBaseName);
    CsvToContainer(this->data,this->DB);
    this->log = log;
}

std::string authorizator::ToHash(std::string stroke) {
    return std::to_string(HashFunc(stroke));
}

bool authorizator::NameIsExist(std::string username){

    std::vector<std::string> names = DB.GetKeyArr();

    for(int i =0;i<names.size();i++){
        if(names[i] == username) return true;
    }
    return false;
}

bool authorizator::IsPasswordCorrect(std::string username, std::string password){

    std::vector<std::string> names = DB.GetKeyArr();
    std::vector<std::string> passwords = DB.GetValArr();

    std::string pass = ToHash(password);

    for(int i =0;i<names.size();i++){
        if(names[i] == username && passwords[i] == pass) return true;
        else if(names[i] == username && passwords[i] != pass) return false;
    }
    return false;
}

void authorizator::UpdateDataBase(){
    std::ofstream file(DataBaseName);

    std::vector<std::string> names = DB.GetKeyArr();
    std::vector<std::string> passwords = DB.GetValArr();

    for(int i = 0;i<names.size()-1;i++) file << names[i]+','+passwords[i]<<std::endl;
    file << names[names.size()-1]+','+passwords[passwords.size()-1]<<std::endl;

    file.close();
}

void authorizator::RegisterUser(){

    bool isCorrectUsername = false;
    bool isCorrectPassword = false;

    std::string username;
    std::string password;
    std::string SecondPassword;

    while(!isCorrectUsername){
        log->logInfo("Введите ваш логин:");
        std::cin>>username;
        if(!NameIsExist(username)){
            isCorrectUsername = true;
        }
        else{
            std::string stroke = "Внимание! Имя пользователя " + username + " уже занято";
            log->logError(stroke);
            std::cout<<std::endl;
        }
    }

    while(!isCorrectPassword){
        std::cout<<std::endl;
        log->logInfo("Введите пароль:");
        std::cout<<std::endl;

        std::cin>>password;

        std::cout<<std::endl;
        log->logInfo("Введите пароль еще раз, для подтверждения:");
        std::cout<<std::endl;

        std::cin >> SecondPassword;

        if(password == SecondPassword){
            isCorrectPassword = true;
        }

        else{
            std::cout<<std::endl;
            log->logError("Внимание! Пароль не подтвержден. Введите пароль еще раз:");
            std::cout<<std::endl;
        }
    }

    DB[username] = ToHash(password);
    UpdateDataBase();

}

void authorizator::RegisterUserHand(std::string username, std::string password){

    bool isCorrectUsername = false;
    bool isCorrectPassword = false;
    std::string SecondPassword;

    DB[username] = ToHash(password);
    UpdateDataBase();

}

void authorizator::LogUser(){

    std::vector<std::string> names = DB.GetKeyArr();
    std::vector<std::string> passwords = DB.GetValArr();

    std::string username;
    std::string password;

    bool isCorrectUsername = false;
    bool isCorrectPassword = false;

    while(!isCorrectUsername){
        log->logInfo("Введите ваш логин:");
        std::cin>>username;
        if(NameIsExist(username)){
            isCorrectUsername = true;
        }
        else{
            log->logInfo("Внимание! Такого логина не существует.");
        }
    }

    while(!isCorrectPassword){
        log->logInfo("Введите пароль:");
        std::cin>>password;
        password = ToHash(password);
        if(password == DB[username]){
            isCorrectPassword = true;
        }
        else{
            log->logWarning("Внимание, вы ввели неверный пароль. Попробуйте ввести пароль еще раз!");
        }
    }

    log->logInfo("Вы успешно вошли в систему!");

}

bool authorizator::LogUserHand(std::string username, std::string password){
    if(NameIsExist(username))
        if(IsPasswordCorrect(username,password))
            return true;

    return false;

}

long long HashFunc(std::string key) {
    long long hashCode = 0;
    int bits_per_char = (64 - 4) / key.size();
    bits_per_char += bits_per_char == 0;
    for (int i = 0; i < key.length(); i++) {
        int curr = key[i];
        for (int j = 0; j < bits_per_char; j++) {
            hashCode += (curr % 2) == 0;
            hashCode <<= 1;
            curr /= 2;
        }
    }
    return hashCode;
}