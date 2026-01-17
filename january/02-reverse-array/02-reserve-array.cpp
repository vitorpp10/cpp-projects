/*
 * this program reorganizes the elements in place, directly in memory, using the same array, with no copies and no additional arrays */

#include<iostream>

int main() 
{
    std::cout << '\n';

    int n = 5;
    int vetor[]={10, 20, 30, 40, 50};
    int *s = vetor;
    int *e = vetor + (n - 1);
    int count = 0;
    
    while (s < e) {
        int temp;
        temp = *s;
        *s = *e;
        *e = temp;
         
        s++;
        e--;

        std::cout << "RODADA " << count << '\n';
            
        for (int i = 0; i < 5; i++) {
            std::cout << vetor[i] << " ";
        }

        std::cout << '\n'; 
        count++;

    }

    std::cout << '\n';
  
    return 0;
} 
