#ifndef READLEVEL_H_INCLUDED
#define READLEVEL_H_INCLUDED
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;

string readLevel(int);

void printTitle(void);
void printLose(void);
void printWin(void);

#endif // READLEVEL_H_INCLUDED
