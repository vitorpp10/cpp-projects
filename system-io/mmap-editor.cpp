#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<cstring>

int main()
{
  int fd = open("memoria_comp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

  if (fd < 0) { exit(EXIT_FAILURE); }

  size_t len = lseek(fd, 64, SEEK_SET);

  const char* text = ".";
  ssize_t n = write(fd, text, strlen(text));

  void* ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  char* dados = (char*)ptr;

  strcpy(dados, "Editado via RAM");

  std::cout << "Dados escritos na memoria.";

  int end = munmap(ptr, len);

  if (end == 0) { exit(EXIT_SUCCESS); }
  
  return 0;
}
