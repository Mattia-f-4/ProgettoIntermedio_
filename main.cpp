#include <iostream>
#include "LidarDriver.h"
#include "Invalid.h"
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

    //Vettore con 11 elementi
    vector<double> v3{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0};

    //Vettore con 20 elementi
    vector<double> v4{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0};

    //Costruttore 1 parametro
    LidarDriver lidar1(1.0);

    cout << lidar1 << std::endl;

    lidar1.new_scan(v1);

    cout<<lidar1 << std::endl;

    lidar1.new_scan(v2);
    
    cout<<lidar1 << std::endl;

    lidar1.new_scan(v3);

    cout<<lidar1 << std::endl;

    vector<double> vout = lidar1.get_scan();

    cout << lidar1 << std::endl;

    cout << "Il vettore rimosso e' il seguente: "<< to_string(vout) << std::endl;
    
    //Costruttore di copia
    LidarDriver lidar2(lidar1);
    
    cout << lidar2; //scrivi che devono essere uguali 

    try
    {
        cout << "Provo a definire la definizione come 3.0 per verificare il corretto lancio dell'errore" << std::endl;
        LidarDriver lidar3(3.0);
    }
    catch(Invalid) //capire se va bene così la classe per gestione errori
    {
        cout << "Errore rilevato, ridefinisco lidar3 con risoluzione 1.0" << std::endl;
        LidarDriver lidar3(1.0)    
        cout << lidar3 << std::endl;
    }
    //controllo operator=
    lidar3 = lidar1;

    cout<<lidar3; //scrivi che devono essere uguali

    //Proviamo con un double
    double dout = lidar3.get_distance(90.0);

    cout << dout << std::endl;
    //proviamo con un int
    dout = lidar3.get_distance(10);

    cout << dout << std::endl;
    //proviamo fuori dai limiti
    double dout = lidar3.get_distance(-1.0);

    cout << dout << std::endl;

    //proviamo fuori dai limiti
    double dout = lidar3.get_distance(200);

    cout << dout << std::endl;

    lidar3.clear_buffer();

    cout << lidar3 << std::endl;

  
    //Test move costructor
    LidarDriver test(vector<double> v4)
    {
        LidarDriver lidar4(1.0);
        lidar4.new_scan(v4);

        return v4;
    }

    LidarDirver lidar5 = test(v4);
    cout << lidar5 << std::endl;

    //Test move assignment
    lidar2 = test(v4);
    cout << lidar2 << std::endl;

    return 0;
}
