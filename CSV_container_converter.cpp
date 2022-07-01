//
// Created by vladi on 11.06.2022.
//

#include "CSV_container_converter.h"
void CsvToContainer(Csv csv, container<std::string>& storage){
    for(int i = 0;i<csv.CsvArray.size();i++){
        storage[csv.CsvArray[i][0]] = csv.CsvArray[i][1];
    }
}

void ContainerToCsv(Csv& csv, container<std::string> storage){

    Csv NewCsv;
    std::vector<std::string> valArr = storage.GetValArr();
    std::vector<std::string> keyArr = storage.GetKeyArr();

    for(int i =0;i<storage.Size();i++){
        std::vector<std::string> newvec;
        NewCsv.CsvArray.push_back(newvec);
        NewCsv.CsvArray[i].push_back(valArr[i]);
        NewCsv.CsvArray[i].push_back(keyArr[i]);
    }
}