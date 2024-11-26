#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <vector>
using std::vector;


class LidarDriver
{
    private:

    //costanti per dimensione buffer valori e risoluzione Lidar
    constexpr int static BUFFER_DIM {10}; 
    double risoluzione; //VERIFICARE SE SI RIESCE COSTANTE

    //numero di elementi nel buffer
    int size;

    
    vector<vector<double>> buffer;

    public:

    //Costruttore per creare un LidarDriver vuoto, con risoluzione inserita come parametro
    explicit LidarDriver(double);
    
    //Costruttore di copia
    LidarDriver(const LidarDriver&);
    
    //Move costructor
    LidarDriver(LidarDriver&&);

    //Operator=
    LidarDriver& operator=(const LidarDriver&);

    //Move assignment
    LidarDriver& operator=(LidarDriver&&);
    
    //Aggiunge una nuova scansione al buffer, sovrascrivendo in caso la meno recente
    void new_scan(vector<double>); 

    //Restituisce la scansione meno recente, rimuovendola dal buffer
    vector<double> get_scan();
    
    //Elimina tutte le scansioni salvate
    void clear_buffer();
    
    //Restituisce, nell'ultima misuraizione, il valore relativo all'angolo inserito come parametro
    double& get_distance(double);
    
    
    //Funzione di debug che restituisce 
    int getSize() const
    {return buffer.max_size();}; 

    //Funzione di supporto per operator<<
    const vector<double>& getMisurazione(int) const;    

};

std.:ostream& operator<<(std::ostream&, const LidarDriver&);

#endif
