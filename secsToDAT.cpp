#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <chrono>

#define filename "data.txt"

enum string_code {
    eJan,
    eFeb,
    eMar,
    eApr,
    eMay,
    eJun,
    eJul,
    eAug,
    eSep,
    eOct,
    eNov,
    eDec
};

string_code hashit (std::string const& inString) {
    if (inString == "Jan") return eJan;
    if (inString == "Feb") return eFeb;
    if (inString == "Mar") return eMar;
    if (inString == "Apr") return eApr;
    if (inString == "May") return eMay;
    if (inString == "Jun") return eJun;
    if (inString == "Jul") return eJul;
    if (inString == "Aug") return eAug;
    if (inString == "Sep") return eSep;
    if (inString == "Oct") return eOct;
    if (inString == "Nov") return eNov;
    if (inString == "Dec") return eDec;
    return eJan;
}

/*
    - Create output file
    - Open input file
    - Parse line by line
        - Take first int of each line, convert to a string of 00:00:00 format
        - Copy rest of data
    - Close




*/

using namespace std;


void parseFile(string filepath, string outputPath)
{
    ifstream input;
    input.open(filepath);
    if(!input.good()) // Checking if stream is good cause I forgot the other method to close it :)
    {
        std::cout << "\nCould not open file." << endl;
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
    int lineNum=-1;
    string month;
    string monthNum;
    string date;
    string zero = "0";
    string year;
    while(getline(input,line))
    {
        lineNum++;

        fstream outFile;
        outFile.open(outputPath,fstream::out);
        outFile.write(const_cast<char*>(line.c_str()), line.length());
        outFile << endl;

        if(lineNum==0) // Parsing the header
        {
            month = line.substr(4,3);
            //std::cout << month;
            switch(hashit(month))
            {
                case eJan :
                    monthNum = "01";
                    break;
                case eFeb:
                    monthNum = "02";
                    break;
                case eMar:
                    monthNum = "03";
                    break;
                case eApr:
                    monthNum = "04";
                    break;
                case eMay:
                    monthNum = "05";
                    break;
                case eJun:
                    monthNum = "06";
                    break;
                case eJul:
                    monthNum = "07";
                    break;
                case eAug:
                    monthNum = "08";
                    break;
                case eSep:
                    monthNum = "09";
                    break;
                case eOct:
                    monthNum = "10";
                    break;
                case eNov:
                    monthNum = "11";
                    break;
                case eDec:
                    monthNum = "12";
                    break;
            }

            date = line.substr(7,3);
            if(date.at(1)== ' ')
                date = zero.append(1,date.at(2)); //Appends the 0 to the single-digit date

            year = line.substr(line.length()-4,4);
            
        }

        if(line[0]=='4'||key==1) //Scuffed way of skipping to body
        {
            key=1;
            tabInd = line.find('\t');
            //cout << tabInd << endl;
            timeElapsed = stoi(line.substr(0,tabInd)) + 1; //Adding one to get the proper time (starts at 0 on writing program)
            //std::cout << timeElapsed;

           
            hours = timeElapsed/3600;
            mins = (timeElapsed%3600)/60;
            secs = (timeElapsed%3600)%60;

            if(hours<10)
                hourStr = "0" + to_string(hours); //Appending the 0 to the value if it's one digit
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

            format = year + "-" + monthNum + "-" + date + '\t' + hourStr + ":" + minStr + ":" + secStr + '\t'; // Final output of date and time parsing

            //std::cout << " " << hours << " " << mins << " " << secs << " " << format << month << monthNum << date << " year:" << year <<  endl;
            //std::cout << format << endl;





        }
    }
}

int main()
{   
    string input;
    string output;
    std::cout << "Enter filename for input data: ";
    cin >> input;
    std::cout << endl << "Enter output filename: ";
    cin >> output;
    

    chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    parseFile(input, output);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double timeElapsed =  std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Script took " + to_string(timeElapsed/1E6) + " seconds to run" << endl;

    
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