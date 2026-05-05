#include<sys/types.h>
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstdlib>
#include<sys/resource.h>

void print_usage(int who, const char* msg) {
    struct rusage usage;
    getrusage(who, &usage);
    std::cout << msg << "Tempo: " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << "s | " << "Max RSS: " << usage.ru_maxrss << "kb\n\n";
}

int main() {
    const char* dir_path = "texto.txt";
    int fd = open(dir_path, O_RDONLY | O_DIRECT);
    if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }

    void* buffer = nullptr;
    if (posix_memalign(&buffer, 4096, 4096) != 0) {
        std::cout << "Erro nos dados manipulados.\n";
        exit(EXIT_FAILURE);
    } else { std::cout << "Sucesso nos dados manipulados.\n"; }

    ssize_t r = read(fd, buffer, 4096);
    if (r < 0) { perror("read"); exit(EXIT_FAILURE); }

    std::cout << "Dados lidos: " << r << std::endl;

    print_usage(RUSAGE_SELF, "\nTempo inserindo sem Page Cache:\n");

    free(buffer);
    close(fd);
}
