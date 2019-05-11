#include <iostream>

using namespace std;

class Time{
    public: 
        Time(int hour, int minute, int second);
        int Init(int hour, int minute, int second);
        int SetHour(int h);
        int SetMinute(int m);
        int SetSecond(int s);
        void Display24();
        void Display12();
    private:
        int hour, minute, second;
};

Time::Time(int hour, int minute, int second){
    Init(hour, minute, second);
}

int Time::Init(int hour, int minute, int second){
    return ( SetHour(hour) &&
             SetMinute(minute) && 
             SetSecond(second) );
}

int Time::SetHour(int h){
    if (h >= 0 && h < 24){
        hour = h;
        return 1;
    }
    return 0;
}

int Time::SetMinute(int m){
    if (m >= 0 && m < 60){
        minute = m;
        return 1;
    }
    return 0;
}

int Time::SetSecond(int s){
    if (s >= 0 && s < 60){
        second = s;
        return 1;
    }
    return 0;
}

void Time::Display24(){
    cout << hour << " : " << minute << " : " << second << endl;
}

void Time::Display12(){
    if(hour > 11){
        cout << hour - 12 << " : " << minute << " : " << second << " pm" << endl;
    }else {
        cout << hour  << " : " << minute << " : " << second << " am" << endl;
    }
}

int main(){
    cout << "Displaying AM time in both formats" << endl;
    Time tam(10, 11, 12);
    tam.Display24();
    tam.Display12();

    cout << "Displaying PM time in both formats" << endl;
    Time tpm(15, 11, 12);
    tpm.Display24();
    tpm.Display12();

    return 0;
}
