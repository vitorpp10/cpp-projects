#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstdint>
#include<sys/types.h>

int main()
{
  int x = 5;
  long ps = sysconf(_SC_PAGE_SIZE);

  int* ptr = &x;
  size_t index = uintptr_t(ptr) / ps;
  size_t off1 = uintptr_t(ptr) % ps;

  int fd = open("/proc/self/pagemap", O_RDONLY);

  if (fd < 0) 
  { 
    std::cout << "-1 (1) " << std::endl;
    exit(EXIT_FAILURE); 
  }

  size_t off2 = index * 8;
  uint64_t value64;
  lseek(fd, off2, SEEK_SET);
  ssize_t n = read(fd, &value64, sizeof(value64)); 

  if (n != 8)
  {
    std::cout << "-1 (2) " << std::endl;
    exit(EXIT_FAILURE);
  }

  uint64_t ram = (value64 >> 63) & 1;
  uint64_t mask = 0x7FFFFFFFFFFFFF;
  size_t PFN = value64 & mask;

  if (ram == true)
  {
    size_t fisic_adress = (PFN * ps) + off1;
    std::cout << "Virtual: " << ptr << std::endl << "Físico: " << fisic_adress << std::endl;
  }
  else 
  {
    std::cout << "Página não está presente na RAM física (talvez em Swap) " << std::endl;
  }
  return 0;
}
