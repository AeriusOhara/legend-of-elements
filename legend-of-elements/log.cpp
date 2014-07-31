#include "log.h"

std::ofstream logFile;

void open_log(){
	logFile.open("log.txt");
}

void close_log(){
	logFile.close();
}

void log(std::string text){
	// Print to the console
	printf(text.c_str());

	// Print to the log file
	logFile.open("log.txt");
	logFile << text.c_str();
	logFile.close();
}