#ifndef _logger_
#define _logger_

#include <iostream>
#include <string>
#include <fstream>

std::ofstream CreateLogger(std::string fileName){
	std::string LogName = "Logs/"+fileName+".txt";
	remove(LogName.c_str());
	std::ofstream log_file(  LogName, std::ios_base::out | std::ios_base::app );
    log_file << "Log file for "<< fileName <<"\n"<< std::endl;
    return log_file;
}


void Logger(std::string fileName, const std::string &text){
    std::string LogName = "Logs/"+fileName+".txt";
    std::ofstream log_file(
        LogName, std::ios_base::out | std::ios_base::app );
    log_file << text << std::endl;
}


#endif