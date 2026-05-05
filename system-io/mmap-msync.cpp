#include<iostream>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstdlib>

int main() {
    const char* dir_path = "texto_msync.txt";
    int fd = open(dir_path, O_RDWR);
    if (fd < 0) { perror("fd"); exit(EXIT_FAILURE); }

    off_t size = lseek(fd, 0, SEEK_END);
    
    char* map = (char*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) { perror("mmap"); exit(EXIT_FAILURE); }

    std::cout << "Dados lidos pelo mmap: " << map << '\n';
    
    map[0] = 'G';

    if (msync(map, size, MS_SYNC) < 0) {
        perror("msync");
        exit(EXIT_FAILURE);
    } else { std::cout << "msycn feito com sucesso.\n"; }

    munmap(map, size);
    close(fd);
    return EXIT_SUCCESS;
}
