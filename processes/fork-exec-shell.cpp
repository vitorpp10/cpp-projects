#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<vector>
#include<string>
#include<sstream>
#include<sys/wait.h>
#include<ostream>

int main()
{
  while (true)
  {
    std::string line;
   
    std::cout << "TERMINAL DO DEVER>> " << std::flush;
    std::getline(std::cin, line);

    if (line == "exit") { break; }
    if (line == "") { continue; }

    std::istringstream iss(line);
    if (iss.fail()) { std::cout << "Erro no istringstream. "; continue; }
    std::string cmd;

    std::vector<std::string> argvSTR;

    while(iss >> cmd)
    {
      argvSTR.push_back(cmd);
    }

    std::vector<char*> argvCSTR;

    for (const auto& s : argvSTR)
    {
      argvCSTR.push_back(const_cast<char*>(s.c_str()));
    }

    argvCSTR.push_back(nullptr);

    pid_t pid = fork();
    if (pid < 0) return 1;

    if (pid == 0)
    {
      int exec = execvp(argvCSTR[0], argvCSTR.data());
      if (exec < 0) return 1;
    }
    else 
    {
      wait(NULL);
      continue;
    }
  }
  std::cout << "Saindo de vitor-shell... " << std::endl << std::flush;
  sleep(2);
  return 0;
}
