#include "logging.h"


int main(int argc, char *argv[]){
    Logger::LogEvent("something happened");
    Logger::Finalize();
}