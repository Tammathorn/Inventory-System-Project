#ifndef LOGGING_H
#define LOGGING_H

void init_Log(const char *filename); //Open log file
void log_Action(const char *action); //Write log
void close_Log();  //Close log file                  

#endif