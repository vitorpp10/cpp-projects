/* 
 * this program creates a log file to monitor pc memory
 *
 * */

#include<iostream>
#include<sstream>
#include<string>
#include<fstream>

int main()
{
    std::ifstream file("/proc/meminfo");
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.find("MemTotal") != (std::string::npos))
            {
                std::stringstream ss(line);
                std::string name, type;
                int value;

                ss >> name >> value >> type;

                std::cout << "TOTAL: " << value << " | " << "TYPE: " << type << '\n'; 
            }
        }
    }

    return 0;
}
