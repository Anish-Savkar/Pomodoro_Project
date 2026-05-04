#include <iostream>
#include <chrono>
#include <windows.h>
#include <thread>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip> 
#include <vector>

using namespace std;

extern string sessionType,task,type,date;;
extern int Break,totalBreak,totalStudy,Duration;
extern int s,b,totalSession,session,longbreakDuration,LBS,lb,duration,dailygoal;

struct Sessions
{
    string type;
    int duration;
    string date;
};

string getCurrentDateTime()
    {
        time_t now=time(0);
        tm* ltm=localtime(&now);

        ostringstream oss;
        oss<<"[ "<<1900+ltm->tm_year<<"-"
        <<setw(2)<< setfill('0')<<1+ltm->tm_mon<<"-"
        <<setw(2)<< setfill('0')<<ltm->tm_mday <<"  "
        <<setw(2)<< setfill('0')<<ltm->tm_hour<<":"
        <<setw(2)<< setfill('0')<<ltm->tm_min<<":"
        <<setw(2)<< setfill('0')<<ltm->tm_sec<<" ]";
        
        return oss.str();

    }
    string getCurrentDateTime1()
    {
        time_t now=time(0);
        tm* ltm=localtime(&now);

        ostringstream vss;
        vss<<1900+ltm->tm_year<<"-"
        <<setw(2)<< setfill('0')<<1+ltm->tm_mon<<"-"
        <<setw(2)<< setfill('0')<<ltm->tm_mday;
        
        return vss.str();

    }
    
    
    vector<Sessions> read()
    {
    ifstream file("log.txt");
     vector<Sessions> S;

     while(file>>type>>duration>>date)
        {
            S.push_back({type,duration,date});
        }
        return S;
    }
    
    int dailystudy()
    {
        int dailyStudy=0;
        vector<Sessions> S=read();
        string Date;
        Date=getCurrentDateTime1();
        
        for(auto &k: S)
        {
            if(k.type=="Focus" && k.date==Date)
            {
                dailyStudy+=k.duration;
            }
        }
        return dailyStudy;
    }  
    
    void dailyGoal()
    {
        float progress=0,posit=0,study=0,barWidth=30;
        
        cout<<"Enter Daily Goal: ";
        cin>>dailygoal;
        study=dailystudy();
        
        progress= study/dailygoal;
        posit= barWidth*progress;

        cout<<"Daily Progress: [";

        for(int i=0;i<barWidth;i++)
        {
            if(i<=posit) cout<<"#";
            else cout<<" ";
        }
        cout<<"]"<<progress*100<<"%"<<endl;
    }

    int getWeek(string date)
    {
        tm tm_date={};
        int year, month, day;
        char dash;

        stringstream ss(date);
        ss >> tm_date.tm_year >> dash >> tm_date.tm_mon
        >> dash >> tm_date.tm_mday;

        tm_date.tm_year-=1900;
        tm_date.tm_mon-=1;

        time_t sessionTime=mktime(&tm_date);
        time_t now=time(0);
       
        double diff= difftime(now,sessionTime);

        return diff<=(7*24*3600);
      
    }
    void Summary()
    {
        vector<Sessions> S = read();
        int currentWeek= getWeek(getCurrentDateTime());
        int study=0,brk=0;

        for(auto &k: S)
        {
            if (!getWeek(k.date))
            continue;

            if (k.type=="Focus")
            study+=k.duration;
            else if(k.type=="Break")
            brk+=k.duration;
        }    
             ofstream file("Weekly Summary.txt",ios::app);

        ostringstream lss;
        lss<<"=============WEEKLY STATS(past 7 days)============="<<endl<<
        "Total Study Time: "<<study<<" minutes"<<endl<<"Total Break Time: "<<brk<<" minutes"<<endl<<
        "============================================================="<<endl;

        file<<lss.str()<<endl;
    }
        
        void logSession(string sessionType,int Duration,int session)
    {
        ofstream file("Sessions.txt",ios::app);

        ostringstream dss;
        dss<<"======= "<<"Session Type: "<<sessionType<<" ======="<<endl<<"Date & Time: "<<
        getCurrentDateTime()<<endl<<"   Task: "<<task<<endl<<"   Duration: "<<Duration
        <<" minutes "<<endl<<"   Session #"<<session<<endl;

        file<<dss.str()<<"\n";
    }
    void logSession1(string sessionType,int Duration)
    {
        ofstream file("log.txt",ios::app);

        ostringstream kss;
        kss<<sessionType<<" "<<Duration<<" "<<getCurrentDateTime1();

        file<<kss.str()<<"\n";
    }

    void total(int totalStudy,int totalBreak)
    {
        ofstream file("Sessions.txt",ios::app);

        ostringstream pss;
        pss<<"========================"<<endl<<"Total Time Studied: "<<totalStudy<<endl
        <<"Total Break Time: "<<totalBreak<<endl<<"========================"<<endl;

        file<<pss.str()<<"\n";
    }

    void countdown(int totalSeconds)
{
    int tick=0;
    bool paused=false;
    static bool prevPressed =false;

    while(totalSeconds>=0)
    {
        bool currentPressed= GetAsyncKeyState('P')& 0x8000;

        if(currentPressed && !prevPressed)
        {
            paused=!paused;
        }
        prevPressed=currentPressed;
        
        if(!paused)
       {
            tick++;
            if (tick==9)         //processing takes 100ms each loop//
        {    
            int mins=totalSeconds/60;
            int secs=totalSeconds%60;
    
             cout<<"\rTime left: "<<mins<<":"
             <<(secs<10?"0":"")<<secs<<flush;

            totalSeconds--;
            tick=0;
        }    
       }
       else if(paused)
       {
            cout<<"\rPaused  "<<flush;
       }
       this_thread::sleep_for(chrono::milliseconds(100));
       
    }
    PlaySound(TEXT("beep.wav"),NULL,SND_SYNC);
    cout<<"\nTime is up :)\n";
}

void start(int studyTime, int breakTime)
{
    cout<<"Number of Sessions: ";
    cin>>totalSession;
    cout<<"Long break Duration: ";
    cin>>longbreakDuration;
    lb=longbreakDuration*60;
    cout<<"long break after: ";
    cin>>LBS;
    cout<<"Task: ";
    cin>>task;

    if(LBS<=totalSession && LBS!=0)  //to avoid invalid inputs and errors//
    {
        for(session=1;session<=totalSession;session++)
        {

            cout<<"\n=== Session "<<session<<" ===\n";

            cout<<"\nStudy Session\n";
            countdown(studyTime);
            Duration=s;
            sessionType="Focus";
            logSession(sessionType,Duration,session);
            logSession1(sessionType,Duration);

            if(session==LBS && session!=totalSession)
           {
               cout<<"\nLong Break\n";
               countdown(lb);
               sessionType="Long Break";
               logSession(sessionType,longbreakDuration,1);
               sessionType="Break";
               logSession1(sessionType,Duration);
           }
            else
            {
                cout<<"\nBreak Time\n";
                countdown(breakTime);
                Duration=b;
                sessionType="Short Break";
                logSession(sessionType,Duration,session);
                sessionType="Break";
                logSession1(sessionType,Duration);
            }    
        }
        cout<<"\n All Sessions Complete!! \n ";
         Break=b*(totalSession-1);                
         totalBreak=Break+longbreakDuration;
         totalStudy=totalSession*s;
        total(totalStudy,totalBreak);
    } 
    else
    cout<<"INVALID INPUT!"<<endl;
}   
