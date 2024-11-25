#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H


#include <vector>
using std::vector;


class LidarDriver
{
    private:

    //costanti per dimensione buffer valori e risoluzione Lidar
    constexpr int BUFFER_DIM {10}; 
    const double risoluzione;

    //numero di elementi nel buffer
    int size;

    
    vector<vector<double>> buffer(BUFFER_DIM);

    public:

    LidarDriver(int r); //crea un driver vuoto con risoluzione inserita come parametro
    //PRODUCE ERRORI

    //costruttori di copia, assegnamenti di copia robe così? //SE ABBIAMO TEMPO

    //si potrebbe avere un costruttore che accetta un intero e uno
    //std::vector<std::vector<double>> 

    void new_scan(vector<double>); //lo memorizza sovrascrivendo in caso la meno recente

    vector<double> get_scan();
    
    void clear_buffer();
    
    double& get_distance(double); //ti da in ogni caso un valore
    
    //operator<< va implementato come helper function nel .cpp

    int getSize(){return size;}; //funzione di debug 
    

};
#endif