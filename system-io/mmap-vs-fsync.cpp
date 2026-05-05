#include<iostream>
#include<sys/mman.h>
#include<vector>
#include<unistd.h>
#include<fcntl.h>
#include<cstdlib>
#include<cstring>
#include<sys/types.h>
#include<chrono>

using namespace std::chrono;
const size_t FILE_SIZE = 100 * 1024 * 1024;

void apenas_ler() {
const char* dir_path = "apenas_ler.db";
int fd = open(dir_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
if (fd < 0) { perror("open1"); exit(EXIT_FAILURE); }

std::vector<char> data(4096, 'A');

auto start = high_resolution_clock::now();
for (size_t i = 0; i < FILE_SIZE; i += 4096) {
write(fd, data.data(), 4096);
}
auto end = high_resolution_clock::now();

close(fd);
std::cout << "Tempo apenas lendo: " << duration_cast<milliseconds>(end - start).count() << "s" << std::endl;
}

void ler_com_fsync() {
const char* dir_path = "ler_com_fsync.db";
int fd = open(dir_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
if (fd < 0) { perror("open2"); exit(EXIT_FAILURE); 

std::vector<char> data(4096, 'A');

auto start = high_resolution_clock::now();
for (size_t i = 0; i < FILE_SIZE; i += 4096) {
write(fd, data.data(), 4096);
fsync(fd);
}
auto end = high_resolution_clock::now();
  
close(fd);
std::cout << "Tempo lendo + fsync: " << duration_cast<milliseconds>(end - start).count() << "s"<<std::endl;
}

void ler_com_mmap() {
const char* dir_path = "ler_com_mmap.db";
int fd = open(dir_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
if (fd < 0) { perror("open3"); exit(EXIT_FAILURE); }

//para o arquivo ter o tamanho correto no disco, pois mmap necessita disso
ftruncate(fd, FILE_SIZE);

auto start = high_resolution_clock::now();
char* map = (char*)mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (map == MAP_FAILED) { perror("mmap"); exit(EXIT_FAILURE); }
  
memset(map, 'A', FILE_SIZE);
msync(map, FILE_SIZE, MS_SYNC);
munmap(map, FILE_SIZE);
auto end = high_resolution_clock::now();

close(fd);
std::cout << "Tempo lendo + mmap: " << duration_cast<milliseconds>(end - start).count() << "s" <<std::endl;
}

int main() {
std::cout << "Iniciando testes.\n\n";
apenas_ler();
ler_com_mmap();
ler_com_fsync();
return EXIT_SUCCESS;
}
