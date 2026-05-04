#ifndef POMODORO_H
#define POMODORO_H
#include <chrono>
#include <windows.h>
#include <thread>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip> 
#include <vector>


std::string sessionType,task,type,date;
int Break,totalBreak,totalStudy,Duration;
int s,b,totalSession,session,longbreakDuration,LBS,lb,duration=0,dailygoal;

struct Sessions;
std::string getCurrentDateTime();
std::string getCurrentDateTime1();
std::vector<Sessions> read();
int dailystudy();
void dailyGoal();
int getWeek(std::string date);
void Summary();
void logSession(std::string sessionType,int Duration,int session);
void logSession1(std::string sessionType,int Duration);
void total(int totalStudy,int totalBreak);
void countdown(int totalSeconds);
void start(int studyTime, int breakTime);

#endif