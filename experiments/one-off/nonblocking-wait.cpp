#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
  pid_t pid = fork();
  if (pid < 0) { perror("Erro no fork.\n"); exit(EXIT_FAILURE); }

  if (pid == 0)
  {
    std::cout << "Filho trabalhando...\n";

    sleep(3);

    std::cout << "Filho terminou!\n";
    exit(EXIT_SUCCESS);
  }
  else 
  {
    while (true)
    {
      pid_t wait = waitpid(pid, NULL, WNOHANG);
      if (wait == 0)
      {
        std::cout << "Pai fazendo tarefas enquanto o filho roda...\n";
        sleep(1);
        continue;
      }
      else if (wait == pid)
      {
        std::cout << "Opa, o filho morreu! Cadaver recolhido.\n";
        break;
      }
      else if (wait == -1)
      {
        perror("Erro no waitpid.\n");
        break;
      }
    }
  }
  std::cout << "Encerrando programa." << std::endl;
  return EXIT_SUCCESS;
}

/* Terminal:

[vitor@vitor ~]$ g++ -Wall -Wextra -Werror s.cpp -o a && ./a
Pai fazendo tarefas enquanto o filho roda...
Filho trabalhando...
Pai fazendo tarefas enquanto o filho roda...
Pai fazendo tarefas enquanto o filho roda...
Filho terminou!
Opa, o filho morreu! Cadaver recolhido.
Encerrando programa.
[vitor@vitor ~]$ 
*/ 
