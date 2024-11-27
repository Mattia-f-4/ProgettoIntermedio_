#include <iostream>
#include "LidarDriver.h"
#include "Invalid.h"
#include <vector>
#include <string>
#include <windows.h>


using std::cout;

int main() 
{
    //Creazione di 12 scansioni da aggiungere al buffer
    vector<double> v1{1.0};
    vector<double> v2{1.0,2.0};
    vector<double> v3{1.0,2.0,3.0};
    vector<double> v4{1.0,2.0,3.0,4.0};
    vector<double> v5{1.0,2.0,3.0,4.0,5.0};
    vector<double> v6{1.0,2.0,3.0,4.0,5.0,6.0};
    vector<double> v7{1.0,2.0,3.0,4.0,5.0,6.0,7.0};
    vector<double> v8{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
    vector<double> v9{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
    vector<double> v10{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    vector<double> v11{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0};

    //Vettore con 190 elementi
    vector<double> v12;

    // Inserimento di valori da 0 a 190
    for (double i = 0; i <= 190; ++i) 
    {
        v12.push_back(i);
    }

    //Buffer con risoluzione 1
    LidarDriver lidar1(1);

    //Inserimento di 12 scansioni (v1 e v2 vengono sovrascritti)
    lidar1.new_scan(v1);
    lidar1.new_scan(v2);
    lidar1.new_scan(v3);
    lidar1.new_scan(v4);
    lidar1.new_scan(v5);
    lidar1.new_scan(v6);
    lidar1.new_scan(v7);
    lidar1.new_scan(v8);
    lidar1.new_scan(v9);
    lidar1.new_scan(v10);
    lidar1.new_scan(v11);
    lidar1.new_scan(v12);


    cout<<lidar1;

    //Estrazione scansione meno recente 
    vector<double> ext = lidar1.get_scan();

    //Controllo che sia v3
    for (double i: ext)
        std::cout << i << ' ';

    std::cout<<std::endl;

    //Richiedo la misurazione all'angolo 130, dovrebbe restituire 130 poichè la scansione più recente è v12
    std::cout<<"La misura a 130 gradi è: "<<lidar1.get_distance(130)<<std::endl;

    //Svuoto il buffer 
    lidar1.clear_buffer();

    //Controllo che sia vuoto
    cout<<lidar1;

    system("pause");
    return 0;
}

