#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <chrono>

#define filename "data.txt"

/*
    - Create output file
    - Open input file
    - Parse line by line
        - Take first int of each line, convert to a string of 00:00:00 format
        - Copy rest of data
    - Close




*/

using namespace std;

void parseFile(string filepath)
{
    ifstream input;
    input.open(filepath);
    if(!input.good()) // Checking if stream is good cause I forgot the other method to close it :)
    {
        cout << "\nCould not open file." << endl;
        return;
    }

    string line;
    int timeElapsed;
    int tabInd;
    int key = 0;
    string hourStr;
    string minStr;
    string secStr;
    string format;
    int hours, mins, secs;

    while(getline(input,line))
    {
        if(line[0]=='4'||key==1) //Scuffed way of skipping file header
        {
            key=1;
            tabInd = line.find('\t');
            //cout << tabInd << endl;
            timeElapsed = stoi(line.substr(0,tabInd)) + 1;
            cout << timeElapsed ;

           
            hours = timeElapsed/3600;
            mins = (timeElapsed%3600)/60;
            secs = (timeElapsed%3600)%60;
            if(hours<10)
                hourStr = "0" + to_string(hours);
            else    
                hourStr = to_string(hours);
            if(mins<10)
                minStr = "0" + to_string(mins);
            else    
                minStr = to_string(mins);
            if(secs<10)
                secStr = "0" + to_string(secs);
            else    
                secStr = to_string(secs);

            format = hourStr + ":" + minStr + ":" + secStr;
            cout << " " << hours << " " << mins << " " << secs << " " << format << endl;





        }
    }
}

int main()
{
    chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    parseFile(filename);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double timeElapsed =  std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Script took " + to_string(timeElapsed/1E6) + " seconds to run" << endl;

    
    /*
    fstream outFile;
    outFile.open("output.txt",fstream::out);
    string var;

    
    fstream inFile;
    inFile.open(filename);
    inFile >> var;
    cout << var;
    
    outFile << var;
    outFile.close();
    */
}