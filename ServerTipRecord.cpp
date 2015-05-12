/* 
 * File:   main.cpp
 * Author: Alexander
 *
 * Created on September 2, 2014, 11:09 PM
 */

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

struct date {
    int month;
    int day;
    int year;
};

struct fr {
    float fr_money;
    float fr_hours;
    date fr_date;
    int fr_secdate;
};



void processinrecords(ifstream&, vector<fr>&);
int getsecdate(date);
int getdow(date);
void processoutrecords(ofstream&, vector<fr>&);
string getweekday(int);
void sortrecords(vector<fr>&);

int main(int argc, char** argv) {
    int dec = 1, tempint0 = 0, tempint1 = 0, tempint2 = 0 , tempint3 = 0, tempint4 = 0;
    float tempfloat0 = 0, tempfloat1 = 0; 
    string command;
    ifstream recordin;
    ofstream recordout;
    vector<fr> records, tempvector;
    fr tempfr;
    date tempdate;

    recordin.open("test.txt");
    processinrecords(recordin, records);
    recordin.close();

    while (dec == 1) {
        cin >> command;
        if ((command == "quit")||(command == "q")) {
            dec = 0;
        } else if (command == "add") {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            fr newrec0;
            newrec0.fr_date.day = ltm->tm_mday;
            newrec0.fr_date.month = (1 + ltm->tm_mon);
            newrec0.fr_date.year = 1900 + ltm->tm_year;
            newrec0.fr_secdate = getsecdate(newrec0.fr_date);
            cin >> newrec0.fr_money;
            cin >> newrec0.fr_hours;
            cout << newrec0.fr_date.month << "/" << newrec0.fr_date.day << "/" << newrec0.fr_date.year << " record added." << endl;
            cout << newrec0.fr_money / newrec0.fr_hours << " hourly." << endl; 
            records.push_back(newrec0);
            recordout.open("test.txt");
            processoutrecords(recordout, records);
            recordout.close();
        } else if (command == "adddate") {
            fr newrec1;
            cin >> newrec1.fr_date.month >> newrec1.fr_date.day >> newrec1.fr_date.year;
            newrec1.fr_secdate = getsecdate(newrec1.fr_date);
            cin >> newrec1.fr_money;
            cin >> newrec1.fr_hours;
            cout << newrec1.fr_date.month << "/" << newrec1.fr_date.day << "/" << newrec1.fr_date.year << " record added." << endl;
            cout << newrec1.fr_money / newrec1.fr_hours << " hourly." << endl; 
            records.push_back(newrec1);
            recordout.open("test.txt");
            processoutrecords(recordout, records);
            recordout.close();
        } else if (command == "all") {
            cout << endl;
            tempfloat0 = 0, tempfloat1 = 0;
            for (int ct1 = 0; ct1 < records.size(); ct1++) {
                tempfloat0 += records[ct1].fr_money;
                tempfloat1 += records[ct1].fr_hours;
                cout << setw(10) << setiosflags(ios::left) << getweekday(getdow(records[ct1].fr_date)) << 
                    setw(2) << records[ct1].fr_date.month << "/" << setw(2) << records[ct1].fr_date.day << "/" << setw(6) <<
                    records[ct1].fr_date.year << "$" << setw(5) <<  records[ct1].fr_money << setw(6) <<  records[ct1].fr_hours <<
                    "hours." << endl;
            }
            cout << endl << "Days Worked: " << records.size() << " | Income: $" << tempfloat0 <<
                    " | Hours: " << tempfloat1 << " | Avg Hourly: $" << setprecision(4)
                    << tempfloat0 / tempfloat1 << endl;
        } else if(command == "week"){
            cout << endl;
            tempdate = date();
            tempint0 = 0, tempint1 = 0, tempint2 = 0, tempint3 = 0, tempint4 = 0, tempfloat0 = 0, tempfloat1 = 0;
            cin >> tempint0 >> tempint1 >> tempint2;
            tempdate.month = tempint0;
            tempdate.day = tempint1;
            tempdate.year = tempint2;
            tempint3 = getsecdate(tempdate);
            tempint3 = tempint3 - getdow(tempdate);
            for(int ct3 = 0; ct3 < records.size(); ct3++){
                if((records[ct3].fr_secdate >= tempint3) && (records[ct3].fr_secdate < (tempint3 + 7))){
                    tempfloat0 += records[ct3].fr_money;
                    tempfloat1 += records[ct3].fr_hours;
                    tempint4++;
                    cout << setw(10) << setiosflags(ios::left) << getweekday(getdow(records[ct3].fr_date)) << 
                    setw(2) << records[ct3].fr_date.month << "/" << setw(2) << records[ct3].fr_date.day << "/" << setw(6) <<
                    records[ct3].fr_date.year << "$" << setw(5) <<  records[ct3].fr_money << setw(6) <<  records[ct3].fr_hours <<
                    "hours." << endl;                  
                }
            }
            if (tempint4 == 0){
                cout << "No records found for time period." << endl;
            } else {
                cout <<  endl << "Days Worked: " << tempint4 << 
                    " | Income: $" << tempfloat0 <<
                    " | Hours: " << tempfloat1 << " | Avg Hourly: $" << setprecision(4)
                    << tempfloat0 / tempfloat1 << endl;
            }
        }else if (command == "month") {
            cout << endl;
            tempint0 = 0, tempint1 = 0, tempint2 = 0, tempfloat0 = 0, tempfloat1 = 0;
            cin >> tempint0 >> tempint1;
            for (int ct2 = 0; ct2 < records.size(); ct2++) {
                if ((records[ct2].fr_date.year == tempint1) && (records[ct2].fr_date.month == tempint0)) {
                    tempfloat0 += records[ct2].fr_money;
                    tempfloat1 += records[ct2].fr_hours;
                    tempint2++;
                    cout << setw(10) << setiosflags(ios::left) << getweekday(getdow(records[ct2].fr_date)) << 
                    setw(2) << records[ct2].fr_date.month << "/" << setw(2) << records[ct2].fr_date.day << "/" << setw(6) <<
                    records[ct2].fr_date.year << "$" << setw(5) <<  records[ct2].fr_money << setw(6) <<  records[ct2].fr_hours <<
                    "hours." << endl;
                    
                }
            }
            if (tempint2 == 0) {
                cout << "No records found for time period." << endl;
            } else {
                cout << endl << "Days Worked: " << tempint2 << " | Income: $" << tempfloat0 <<
                    " | Hours: " << tempfloat1 << " | Avg Hourly: $" << setprecision(4)
                    << tempfloat0 / tempfloat1 << endl;
            }
        }
        else if(command  == "funfact"){
            float ffo0 = records[0].fr_money, 
                    ffo1 = records[0].fr_money, 
                    ffo2 = records[0].fr_hours,
                    ffo3 = records[0].fr_hours,
                    ffo4 = records[0].fr_money/records[0].fr_hours,
                    ffo5 = records[0].fr_money/records[0].fr_hours;
            for(int funfact0 = 0; funfact0 < records.size(); funfact0++){
                if(records[funfact0].fr_money > ffo0){
                    ffo0 = records[funfact0].fr_money;
                }
                if(records[funfact0].fr_money < ffo1){
                    ffo1 = records[funfact0].fr_money;
                }
                if(records[funfact0].fr_hours > ffo2){
                    ffo2 = records[funfact0].fr_hours;
                }
                if(records[funfact0].fr_hours < ffo3){
                    ffo3 = records[funfact0].fr_hours;
                }
                if((records[funfact0].fr_money / records[funfact0].fr_hours) > ffo4){
                    ffo4 = records[funfact0].fr_money / records[funfact0].fr_hours;
                }
                if((records[funfact0].fr_money / records[funfact0].fr_hours) < ffo5){
                    ffo5 = records[funfact0].fr_money / records[funfact0].fr_hours;
                }
            }
            cout << "Most money ever made: $" << ffo0 << '\n' <<
                    "Least money ever made: $" << ffo1 << '\n' <<
                    "Most hours ever worked: " << ffo2 << '\n' <<
                    "Least hours ever worked: " << ffo3 << '\n' <<
                    "Best hourly wage: $" << ffo4 << '\n' <<
                    "Worst hourly wage: $" << ffo5 << '\n';
        }
        else if(command == "help"){
            cout << "Currently supported commands are..." << endl << "add" <<
                endl << "adddate" << endl << "all" << endl << "month" << endl << "week" << 
                endl << "quit" << endl;
            
        }
        else {
            cout << "*" << command << "* is not a recognized command, type 'help' for commands." << endl;
        }
    }
    return 0;
}

void processinrecords(ifstream& a, vector<fr>& b) {
    int c;
    string in;
    fr inrec;
    while (a >> in) {
        inrec.fr_money = atof(in.c_str());
        a >> in;
        inrec.fr_hours = atof(in.c_str());
        a >> in;
        inrec.fr_date.month = atoi(in.c_str());
        a >> in;
        inrec.fr_date.day = atoi(in.c_str());
        a >> in;
        inrec.fr_date. year = atoi(in.c_str());
        a >> in;
        inrec.fr_secdate = atoi(in.c_str());
        b.push_back(inrec);
        c++;
    }
    cout << c << " records successfully loaded." << endl;
}

int getsecdate(date a) {
    int b = a.day;
    switch (a.month) {
        case 1:
            break;
        case 2:
            b += 31;
            break;
        case 3:
            b += 59;
            break;
        case 4:
            b += 90;
            break;
        case 5:
            b += 120;
            break;
        case 6:
            b += 151;
            break;
        case 7:
            b += 181;
            break;
        case 8:
            b += 212;
            break;
        case 9:
            b += 243;
            break;
        case 10:
            b += 273;
            break;
        case 11:
            b += 304;
            break;
        case 12:
            b += 334;
            break;
        default:
            cout << "Something went wrong!";
    }
    if ((a.year % 4 == 0)&&(a.month > 2)) {
        b++;
    }
    return b;
}

int getdow(date a) {
    int y = a.year;
    int d = a.day;
    int m = a.month;
    return (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
}

void processoutrecords(ofstream& a, vector<fr>& b) {
    if (a.is_open()) {
        sortrecords(b);
        for (int ct0 = 0; ct0 < b.size(); ct0++) {
            a << b[ct0].fr_money << " " << b[ct0].fr_hours << " " << b[ct0].fr_date.month <<
                    " " << b[ct0].fr_date.day << " " << b[ct0].fr_date.year << " " << b[ct0].fr_secdate << " " << endl;
        }
    } else cout << "Unable to open file" << endl;
}

string getweekday(int a){
    if(a == 0){
        return "Sunday";
    }
    if(a == 1){
        return "Monday";
    }
    if(a == 2){
        return "Tuesday";
    }
    if(a == 3){
        return "Wednesday";
    }
    if(a == 4){
        return "Thursday";
    }
    if(a == 5){
        return "Friday";
    }
    if(a == 6){
        return "Saturday";
    }
    else{
        return "SOMETHING FUCKED UP BAD";
    }
}

void sortrecords(vector<fr>& a){
    for(int c1 = 1; c1 < a.size(); c1++){
        for(int c2 = c1; c2 > 0; c2--){
            if(a[c2].fr_date.year < a[c2-1].fr_date.year || a[c2].fr_secdate < a[c2-1].fr_secdate && a[c2].fr_date.year == a[c2-1].fr_date.year){
                fr temp;
                temp = a[c2];
                a[c2] = a[c2-1];
                a[c2-1] = temp;
            }
            else{
                c2 = -1;
            }
        }
    }
}