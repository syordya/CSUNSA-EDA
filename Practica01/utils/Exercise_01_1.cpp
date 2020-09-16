#include <iostream>
#include <time.h>

using namespace std;

int main(){

    int vector[1000000];
    int quantity = 1000000;
    srand(time(NULL));

    for(int i = 0; i < quantity; i++)
    {
        // numbers within the range of de 1 to 10
        vector[i] = 1 + rand() % (101 - 1); 
        cout << vector[i] << " ";
    }

    return 0;
}