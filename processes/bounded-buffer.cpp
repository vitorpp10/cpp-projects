#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<cstdlib>
#include<unistd.h>

#define MAX_SIZE 5

std::queue<int> fila;
std::mutex mtx;
std::condition_variable cv_consumidor, cv_produtor;

void produtor()
{
  for (int i = 0; i < 10; i++)
  {
    std::unique_lock<std::mutex> lock(mtx);

    cv_produtor.wait(lock, [] { return fila.size() < MAX_SIZE; });

    fila.push(i);

    std::cout << "Produziu: " << fila.size() << std::endl;

    cv_consumidor.notify_one();
  }
  usleep(100'000);
}

void consumidor()
{
  for (int i = 0; i < 10; i++)
  {
    std::unique_lock<std::mutex> lock(mtx);

    cv_consumidor.wait(lock, [] { return !fila.empty(); });

    int valor = fila.front();
    fila.pop();

    std::cout << "Consumiu: " << valor << std::endl;

    cv_produtor.notify_one();
  }
} 

int main()
{
  std::thread t1(produtor);
  std::thread t2(consumidor);

  t1.join();
  t2.join();
  std::cout << "\nTUDO NUMA BOA!\n";
  return EXIT_SUCCESS;
}
