#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <vector>
#include <string>
using std::vector;


class LidarDriver
{
    private:

    //Dimensione fixed del buffer, inizializzata a dim+1 per scelta implementativa
    static constexpr int BUFFER_DIM {11}; 

    //Risoluzione del buffer
    double risoluzione;

    //Puntatori per la gestione del buffer
    int head;
    int tail;

    //Contenitore delle scansioni
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
    
    //Restituisce il puntatore alla head del buffer
    int getHead() const
    {return head;};

    //Restituisce il puntatore alla tail del buffer
    int getTail() const
    {return tail;};

    int getBUFFER_DIM() const
    {return BUFFER_DIM;};

    //Controlla se il buffer è pieno
    bool isFull() const;
    
    //Controlla se il buffer è vuoto
    bool isempty() const;

    //Conta gli elementi nel buffer
    int size() const;
    
    //Funzione di supporto per evitare che getMisurazione vada fuori dai limiti 
    bool isOutOfBounds(int i) const;

    //Funzione di supporto per operator<<
    const vector<double>& getMisurazione(int) const;    

};

std::ostream& operator<<(std::ostream&, const LidarDriver&);
std::string to_string(const vector<double>&); //Funzione utile per non appesantire il codice di operator<<

#endif
