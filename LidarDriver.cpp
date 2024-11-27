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
    head = 0;
    tail = 0;
}

//Costruttore di copia
LidarDriver::LidarDriver(const LidarDriver& l) : risoluzione{l.risoluzione} , buffer{l.buffer}, head{l.head}, tail{l.tail} {}


//Move costructor
LidarDriver::LidarDriver(LidarDriver&& l) : risoluzione{l.risoluzione} , buffer{std::move(l.buffer)}, head{l.head}, tail{l.tail}
{
    l.risoluzione = 0;
    
}

//Operator=
LidarDriver& LidarDriver::operator=(const LidarDriver& l)
{
    if( this != &l)
    {
        risoluzione = l.risoluzione;
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


bool LidarDriver::isFull() const
    {
    return (head+1) % BUFFER_DIM == tail;  // Il buffer è pieno quando head è un passo avanti rispetto a tail
    }

bool LidarDriver::isempty() const
    {
    // Buffer vuoto se head == tail e il buffer non è pieno
    return head == tail && !isFull();
    }


//Funzione di supporto per operator<<
const vector<double>& LidarDriver::getMisurazione(int i) const
{
    if (isOutOfBounds(i)) {
        throw Invalid(Invalid::ErrorType::IndexOutOfBoundException, "Indice dell'array fuori dai limiti.");
    }
    return buffer[i];
}


int LidarDriver::size() const{
    if (head >= tail) {
            return head - tail;
        }
        return  BUFFER_DIM - (tail - head);
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
    if (l.isempty()) {
        out << "Il buffer è vuoto." << std::endl;
        return out;
    }

    

    int i = l.getTail();  // Partenza dal tail (elemento meno recente)
    
    // Calcolare il numero di misurazioni nel buffer
    int numMisurazioni = l.size();

    out << "Sono presenti "<<numMisurazioni<<" misurazioni nel buffer." << std::endl;

    // Itera attraverso il numero di elementi validi nel buffer
    for (int j = 0; j < numMisurazioni; ++j) {
        out << "Misurazione in posizione " << j << " : " << to_string(l.getMisurazione(i)) << std::endl;
        i = (i + 1) % l.getBUFFER_DIM();  // Avanza ciclicamente
    }

    return out;
}



void LidarDriver::new_scan(vector<double> ing)
{

    int limit= ing.size();
    int correct_size=(180/risoluzione)+1;

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

    if(head==tail){
        tail=(tail+1)%BUFFER_DIM;
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

    return temp;
    
}


void LidarDriver::clear_buffer()
{
    //Utilizzo della funzione built in di vector per eliminare tutti gli scan
    buffer.clear();
    head=0;
    tail=0;
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

    int recent_pos=(head-1+BUFFER_DIM)%BUFFER_DIM;
    
    //Prende l'indice dello scan corrispondente all'angolo
    int pos = static_cast<int>(val/risoluzione);
    

    return buffer[recent_pos][pos];
}





