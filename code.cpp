#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main()
{
    ifstream inFile;

    string posId;
    string posStatus;
    string timeIn;
    string timeOut;
    string duration;
    string payStartDate;
    string payEndDate;
    string employeeNameF;
    string employeeNameL;
    string fileNumber;

    int cnst = 0, cnt = 0;
    string prv = "";
    map<string, int> day;
    map<string, string> dur;
    map<string, string> info;

    auto fn = [&](string posId, string duration)
    {
        string a = "", b = "", c = "", d = "";
        int id = 0;
        while (id < dur[posId].size() && dur[posId][id] != ':')
            a += dur[posId][id++];
        id++;
        while (id < dur[posId].size())
            c += dur[posId][id++];

        id = 0;
        while (id < duration.size() && duration[id] != ':')
            b += duration[id++];
        id++;
        while (id < duration.size())
            d += duration[id++];

        if (a != "" && b != "")
        {
            if (stoi(a) == stoi(b))
            {
                if (c != "" && d != "")
                {
                    if (stoi(c) < stoi(d))
                        dur[posId] = duration;
                    else
                        dur[posId] = dur[posId];
                }
            }
            else if (stoi(a) < stoi(b))
                dur[posId] = duration;
            else
                dur[posId] = dur[posId];
        }
    };

    inFile.open("data1.csv");
    while (!inFile.eof())
    {
        getline(inFile, posId, ',');
        getline(inFile, posStatus, ',');
        getline(inFile, timeIn, ',');
        getline(inFile, timeOut, ',');
        getline(inFile, duration, ',');
        getline(inFile, payStartDate, ',');
        getline(inFile, payEndDate, ',');
        getline(inFile, employeeNameF, ',');
        if (cnst)
            getline(inFile, employeeNameL, ',');

        getline(inFile, fileNumber, '\n');

        if (!cnst)
        {
            cnst++;
            continue;
        }

        // condition check

        info[posId] = employeeNameF + "," + employeeNameL;

        if (prv != posId)
        {
            day[prv] = max(day[prv], cnt);
            prv = posId;

            if (dur.count(prv))
                fn(prv, duration);
            else
                dur[prv] = duration;

            cnt = 1;
        }
        else
        {
            cnt++;
            day[posId] = max(day[posId], cnt);
            if (dur.count(posId))
                fn(posId, duration);
            else
                dur[posId] = duration;
        }
    }
    inFile.close();

    for (auto i : info)
    {
        string id = i.first;
        string name = i.second;
        string tm = "";
        int j = 0, hrs = 0;

        while (j < dur[posId].size() && dur[posId][j] != ':')
            tm += dur[posId][j++];

        if (tm != "")
            hrs = stoi(tm);

        if (day[id] == 7 || (hrs > 1 && hrs < 10) || hrs > 14)
            cout << id << " " << name << '\n';
    }

    return 0;
}