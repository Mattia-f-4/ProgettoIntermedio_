#include <iostream>
#include "LidarDriver.h"
#include <vector>
#include <string>

using std::cout;

int main() 
{
    //Vettore con 4 elementi
    vector<double> v1{1.0,2.0,3.0,4.0};

    //Vettore con 190 elementi
    vector<double> v2;

    // Inserimento di valori da 0 a 190
    for (double i = 0; i <= 190; ++i) 
    {
        v2.push_back(i);
    }

    

    //Costruttore 1 parametro
    LidarDriver lidar1(1.0);

    std::cout << lidar1;

    LidarDriver lidar2(0.5);

    LidarDriver lidar3(lidar1);
    

   return 0;
}
