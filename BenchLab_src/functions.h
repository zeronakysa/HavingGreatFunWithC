#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <omp.h>
#include <cpuid.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <MYSQL/mysql.h>
#include <winsock2.h>
#include <time.h>

#pragma comment(lib, "user32.lib")

#define BDDADRESS "81.57.99.100" // ou localhost
#define BDDNAME "test4" //ou autre
#define EXECNAME "BenchLab.exe"

struct hardInfo{
    unsigned long long inf1;      //Total Virtual Mem (octet)
    unsigned long long inf2;      //Total Physi Mem (octet)
    float inf3;     //Total Virtual Mem (Go)
    float inf4;     //Total Physi Mem (Go)
    int inf5;       //OEM ID
    int inf6;       //Numb of Processors
    int inf7;       //Page Size
    int inf8;       //Processor Type
    char inf9[10];   //Min app address
    char inf10[10];  //Max app address
    int inf11;      //Active Processor Mask
    int inf12;      //Base Frequency(MHz)
    int inf13;      //Max Frequency(MHz)
    int inf14;      //Bus Frequency(MHz)
    int inf15;      //Amount of core
};

struct user{
    int id;             //from Database
    char nickname[255]; //NickName
    int language;       //0 = FR; 1 = EN;
    struct hardInfo hardInfos;
    char bddName[255];      //
    char bddAdress[255];    //
};

void menuEN();
void menuFR();
void startMenuEN();
void startMenuFR();
void reminder();
void memoryTest();
void maxThread();
void cpuFrequency();
void cpuBrand();
void hardwareInfos();
void input(struct user* s);
void printToConfig(struct user config);
void cpuFullUse();
void updateResult(int choiceLeaderboard, char *username, int testValue);
void createOrUpdateResult(int choiceLeaderboard, char *username, int testValue);

void createUser(char *username);
void createResult(int choiceLeaderboard, char *username, int testValue);
void getLeaderboard(int choiceLeaderboard);

void startWSAS ();

void *current_Memory(void *nothing);
void *inc_num(void *y_void_ptr);
void *inc_x(void *x_void_ptr);
void *inc_y(void *y_void_ptr);
void *thread ( void *vargp);
void *inc_ram(void *x_void_ptr);

int getId(char *username);
int getUser(char *username);

int sendToServer(SOCKET sockclt, SOCKADDR_IN *sin, char *buffer);
int calculatePing();

int cpuTest1();
int cpuTest2();
int cpuTest3();
int cpuTest4();
int cpuTest5();
int cpuTest6();
int cpuTest7();
int cpuTest8();
int cpuBench();
int testMemory();
int test4GB();
int pthreadtest();
int test();
int numBlocks(int nbLines,char* fileToRead);
int memTest(int argc, char** argv);

struct user* allocateConfig(int size);
struct user* launch();
struct user* hardwaretoStruct(struct user* config);

char *trimwhitespace(char *str);

char** readFLinesConfigToBuffer(char** buffer);
char** readFileToBuffer(int nbBlocks, int nbLines, char* buffer[],char* fileToRead);

float calculateSpeed(float timer, int sizeOfPacket);
float sendPacketToServer(int packetsize);

float findCPUFreuency();
float fTimer(char action, float starter);

#endif //FUNCTIONS_H
