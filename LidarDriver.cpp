#include "LidarDriver.h"
#include "Invalid.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;


//Costruttore con un solo parametro
LidarDriver::LidarDriver(double r)
{
    buffer = vector<vector<double>>(LidarDriver::BUFFER_DIM);
    
    if(r>1  || r < 0.1)
    {
        throw Invalid(Invalid::ErrorType::InvalidValue, "Risoluzione fuori dal range di valori possibili");
    }

    risoluzione = r;
    size = 0;
    head = 0;
    tail = 0;
}

//Costruttore di copia
LidarDriver::LidarDriver(const LidarDriver& l) : risoluzione{l.risoluzione} , buffer{l.buffer}, size{l.size}, head{l.head}, tail{l.tail} {}


//Move costructor
LidarDriver::LidarDriver(LidarDriver&& l) : risoluzione{l.risoluzione} , buffer{std::move(l.buffer)}, size{l.size}, head{l.head}, tail{l.tail}
{
    l.risoluzione = 0;
    l.size = 0;
    
}

//Operator=
LidarDriver& LidarDriver::operator=(const LidarDriver& l)
{
    if( this != &l)
    {
        risoluzione = l.risoluzione;
        size = l.size;
        buffer = l.buffer;
        head = l.head;
        tail = l.tail;
    }
    
    return *this;
}


//Move assignement
LidarDriver& LidarDriver::operator=(LidarDriver&& l) 
{
    risoluzione = l.risoluzione;
    size = l.size;
    buffer = std::move(l.buffer);
    head = l.head;
    tail = l.tail;
    return *this;
}

bool LidarDriver::isOutOfBounds(int i) const
{
    if (isempty()) {
        return true; // Se il buffer è vuoto, qualsiasi indice è fuori dai limiti
    }

    if (tail <= head) {
        // Caso semplice: buffer non avvolto
        return (i < tail || i >= head);
    } else {
        // Caso avvolto: due segmenti validi
        return (i < tail && i >= head);
    }
}


//Funzione di supporto per operator<<
const vector<double>& LidarDriver::getMisurazione(int i) const
{
    if (isOutOfBounds(i)) {
        throw Invalid(Invalid::ErrorType::IndexOutOfBoundException, "Indice dell'array fuori dai limiti.");
    }
    return buffer[i];
}


//Funzione di supporto per operator<<
std::string to_string(const vector<double>& v)
{
    std::string s;

    for(int i = 0; i < v.size()-1; i++)
    {
        s += std::to_string(v[i]) + " ; ";
    }
    s+=v[v.size()-1];

    return s;
}

//Operator<<
std::ostream& operator<<(std::ostream& out, const LidarDriver& l)
{
    out << "Sono presenti " << l.getSize() << " misurazioni nel buffer." << std::endl;

    int i = l.getTail(); // Partenza dal tail (elemento meno recente)
    for (int j = 0; j < l.getSize(); ++j) 
    { 
        // Itera attraverso il numero di elementi
        
        out << "Misurazione in posizione " << j << " : " << to_string(l.getMisurazione(i)) << std::endl;
        i = (i + 1) % l.getBUFFER_DIM(); // Avanza ciclicamente
    }
    return out;
}



void LidarDriver::new_scan(vector<double> ing)
{

    int limit= ing.size();
    int correct_size=(180/risoluzione)+2;

    //Correggo la dimensione del vettore in ingresso
    if(limit<correct_size){
        ing.resize(correct_size);
        std::fill(ing.begin()+limit,ing.end(),0);

    }
    else if(limit>correct_size){
        ing.resize(correct_size);
    }


    //Incremento il numero di elementi 
    buffer[head]=ing;

    head=(head+1)%BUFFER_DIM;

    if (size < BUFFER_DIM) {
        size++; // Incrementa solo se non pieno
    } else {
        tail = (tail + 1) % BUFFER_DIM; // Sovrascrive il più vecchio
    }

}


vector<double> LidarDriver::get_scan()
{
    vector<double> temp;

    if (isempty()) 
    {
        throw (Invalid::ErrorType::EmptyContainer, "Buffer vuoto.");           
    }

    temp=buffer[tail];
    tail = (tail + 1) % BUFFER_DIM;

    size--;
    return temp;
    
}


void LidarDriver::clear_buffer()
{
    //Utilizzo della funzione built in di vector per eliminare tutti gli scan
    buffer.clear();
    head=0;
    tail=0;
    size=0;
}


double& LidarDriver::get_distance(double val)
{
    if (isempty()) 
    {
        throw Invalid(Invalid::ErrorType::EmptyContainer, "Buffer vuoto.");
    }
    //Porta l'angolo dentro il range
    if(val<0){
        val=0;
    }
    if(val>180){
        val=180;
    }

    int recent_pos=(size%BUFFER_DIM)-1;
    
    //Prende l'indice dello scan corrispondente all'angolo
    int pos = static_cast<int>(val/risoluzione);
    
    //Seleziona lo scan più recente nel buffer
    vector<double> recent_scan=buffer[recent_pos];

    //Restituisce la lettura corrispondente all'angolo dello scan più recente
    double *dist= &recent_scan[pos];

    return *dist;
}





