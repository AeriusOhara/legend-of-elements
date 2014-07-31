#include <iostream>
#include <fstream>

extern void log(std::string text);
extern void open_log();
extern void close_log();
extern std::ofstream logFile;