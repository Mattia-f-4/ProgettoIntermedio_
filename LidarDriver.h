#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <vector>
#include <string>
using std::vector;


class LidarDriver
{
    private:

    //costanti per dimensione buffer valori e risoluzione Lidar
    static constexpr int BUFFER_DIM {11}; 
    double risoluzione; //VERIFICARE SE SI RIESCE COSTANTE

    //numero di elementi nel buffer
    int head;
    int tail;

    
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
    

    int getHead() const
    {return head;};

    int getTail() const
    {return tail;};

    int getBUFFER_DIM() const
    {return BUFFER_DIM;};

    bool isFull() const;
    
    bool isempty() const;

    int size() const;
    

    bool isOutOfBounds(int i) const;

    //Funzione di supporto per operator<<
    const vector<double>& getMisurazione(int) const;    

};

std::ostream& operator<<(std::ostream&, const LidarDriver&);
std::string to_string(const vector<double>&);

#endif
