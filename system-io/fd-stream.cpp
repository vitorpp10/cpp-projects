#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>

int main()
{
  int fd = open("teste.txt", O_RDONLY);
  if (fd < 0) { exit(EXIT_FAILURE); }

  char buffer[1024];

  while (true)
  {
    ssize_t r = read(fd, buffer, sizeof(buffer));
    if (r < 0) { exit(EXIT_FAILURE); } 
    if (r == 0) { break; }

    ssize_t w = write(1, buffer, r);
    if (w < 0) { exit(EXIT_FAILURE); }
  }

  close(fd);

  return 0;
}
