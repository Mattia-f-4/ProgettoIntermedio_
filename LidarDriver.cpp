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

//Funzione che conta gli elemetni presenti nel buffer
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
    //Utilizzo 2 indici per una questione stilistica
    // Itera attraverso il numero di elementi validi nel buffer
    for (int j = 0; j < numMisurazioni; ++j) {
        out << "Misurazione in posizione " << j << " : " << to_string(l.getMisurazione(i)) << std::endl;
        i = (i + 1) % l.getBUFFER_DIM();  // Avanza ciclicamente
    }

    return out;
}


//Funzione per aggiungere una scansione al buffer
void LidarDriver::new_scan(vector<double> ing)
{
    //Controllo il numero di elementi presenti nel vettore in ingresso e controllo quanti ce ne dovrebbero essere in base alla risoluzione dell'oggetto buffer
    int limit= ing.size();
    int correct_size=(180/risoluzione)+1;

    //Correggo la dimensione del vettore in ingresso per adattarla alla risoluzione del buffer
    if(limit<correct_size){
        ing.resize(correct_size+1);
        std::fill(ing.begin()+limit,ing.end(),0);

    }
    else if(limit>correct_size){
        ing.resize(correct_size);
    }


    //Incremento il numero di elementi e sposto di conseguenza i puntatori head e tail del buffer
    buffer[head]=ing;

    head=(head+1)%BUFFER_DIM;

    if(head==tail){
        tail=(tail+1)%BUFFER_DIM;
    }

}

//Funzione per rimuovere lo scan meno recente dal buffer
vector<double> LidarDriver::get_scan()
{
    vector<double> temp;

    //Controllo che il buffer non sia vuoto

    if (isempty()) 
    {
        throw (Invalid::ErrorType::EmptyContainer, "Buffer vuoto.");           
    }

    //Rimuovo l'elemento meno recente e sposto il puntatore tail del buffer

    temp=buffer[tail];
    tail = (tail + 1) % BUFFER_DIM;

    return temp;
    
}


void LidarDriver::clear_buffer()
{
    //Utilizzo della funzione built in di vector per eliminare tutti gli scan, reset dei puntatori del buffer
    buffer.clear();
    head=0;
    tail=0;
}


//Funzione che restituisce la misura nella scansione più recente
double& LidarDriver::get_distance(double val)
{

    //Controllo che il buffer non sia vuoto
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

    //Sceglie la scansione più recente nel buffer
    int recent_pos=(head-1+BUFFER_DIM)%BUFFER_DIM;
    
    //Prende l'indice dello scan corrispondente all'angolo
    int pos = static_cast<int>(val/risoluzione);
    

    return buffer[recent_pos][pos];
}





