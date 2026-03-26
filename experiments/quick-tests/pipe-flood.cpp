#include<iostream>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int fildes[2];
    if (pipe(fildes) < 0) { perror("Erro no pipe.\n"); exit(EXIT_FAILURE); }
    
    pid_t pid = fork();
    if (pid < 0) { perror("Erro no fork.\n"); exit(EXIT_FAILURE); }
    
    if (pid == 0)
    {
        close(fildes[1])
        
        char buffer[1024];
        
        while (true)
        {
            sleep(1);
            
            ssize_t r = read(fildes[0], buffer, sizeof(buffer));
            if (r < 0) { perror("Erro no read.\n"); break; }
            
            std::cout << "Filho leu 1024 bytes!\n";
        }
    }
    else 
    {
        close(fildes[0])
        
        char lixo[1024];
        
        int count = 0;
        
        while (true)
        {
            ssize_t w = write(fildes[1], lixo, sizeof(lixo));
            if (w < 0) { perror("Erro no write.\n"); break; }
            
            count++;
            std::cout << "Pai escreveu o pacote número: " << count << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
