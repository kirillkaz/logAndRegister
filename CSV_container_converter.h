//
// Created by vladi on 11.06.2022.
//
#ifndef LOGANDREGISTER_CSV_CONTAINER_CONVERTER_H
#define LOGANDREGISTER_CSV_CONTAINER_CONVERTER_H

#include "Csv/Csv.h"
#include "key-value/container.h"

void CsvToContainer(Csv csv, container<std::string>& storage);

void ContainerToCsv(Csv& csv, container<std::string> storage);


#endif //LOGANDREGISTER_CSV_CONTAINER_CONVERTER_H
