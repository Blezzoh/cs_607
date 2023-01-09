#include "logging.h"
#include <bits/types/FILE.h>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <stdio.h>

FILE * Logger::logger = NULL;

Logger::Logger(){
    logger = fopen("logger", "w");
}
void Logger::LogEvent(const char * event){
    if(Logger::logger == NULL){
        Logger::logger = fopen("logger", "w");
    }
    printf("%s\n", event);
    fprintf(logger, "%s\n", event);
}
void Logger::Finalize(){
    fclose(logger);
}

DataFlowException::DataFlowException(const char *type, const char *error){
    sprintf(msg, "Throwing exception: (%s): (%s)", type, error);
    Logger::LogEvent(msg);
}

