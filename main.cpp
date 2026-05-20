#include <iostream>
#include <chrono>
#include <windows.h>
#include <thread>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip> 
#include <vector>
#include "pomodoro.h"

using namespace std;

int main()
{
        int choice;
    cout<<"1. Default Pomodoro(25/5)\n2. Custom\n3.Weekly Summary\n4.Set Daily Goal\n5.Terminate\n";
    cin>>choice;

    if(choice==1)
      {
         s=25,b=5;
        start(s*60,b*60);
      } 
    else if(choice==2)
    {
        cout<<"Study Time: ";
        cin>>s;
        cout<<"Break Time: ";
        cin>>b;
        sessionType="Custom";
        start(s*60,b*60);
    }
    else if(choice==3)
    {
      Summary(); 
    }
    else if(choice==4)
    dailyGoal();
    else
    return 0;
}
