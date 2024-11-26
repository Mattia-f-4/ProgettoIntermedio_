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
    buffer = vector<vector<double>>(BUFFER_DIM);
    
    if(r>1  || r < 0.1)
    {
        throw Invalid(Invalid::ErrorType::InvalidValue, "Risoluzione fuori dal range di valori possibili");
    }

    risoluzione = r;
    size = 0;
}

//Costruttore di copia
LidarDriver::LidarDriver(const LidarDriver& l) : risoluzione{l.risoluzione} , buffer{l.buffer}, size{l.size} {}


//Move costructor
LidarDriver::LidarDriver(LidarDriver&& l) : risoluzione{l.risoluzione} , buffer{std::move(l.buffer)}, size{0}
{
    l.risoluzione = 0;
    l.size = 0;
    
}

//Operator=
LidarDriver& LidarDriver::operator=(const LidarDriver& l)
{
    risoluzione = l.risoluzione;
    size = l.size;
    buffer = l.buffer;
}


//Move assignement
LidarDriver& LidarDriver::operator=(LidarDriver&& l) 
{
    risoluzione = l.risoluzione;
    size = l.size;
    buffer = std::move(l.buffer);
}


//Funzione di supporto per operator<<
const vector<double>& LidarDriver::getMisurazione(int i)
{
    if(i<0 || i>=getSize())
    {
        throw Invalid(Invalid::ErrorType::IndexOutOfBoundException, "Indice dell'array fuori dai limiti");
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

    for(int i = 0; i < l.getSize(); i++)
    {
        out << "Misurazione in posizione " << i << " : " << std::endl << to_string(l.getMisurazione(i)) << std::endl;
    }

    return out;
}

//PIETRO

void LidarDriver::new_scan(vector<double> ing)
{

    int limit= ing.size();
    int correct_size=(180/risoluzione)+1;
    int pos=size%BUFFER_DIM;

    //Correggo la dimensione del vettore in ingresso
    if(limit<correct_size){
        std::fill(ing.begin()+limit,ing.end(),0);

    }
    else if(limit>correct_size){
        ing.resize(correct_size);
    }

    buffer[pos]=ing;
    size++;

}

vector<double> LidarDriver::get_scan()
{

    int old;
    vector<double> temp;
    
    if(size<10){
        old=0;
    }
    
    else{

        old=(size%BUFFER_DIM)+1;

        if(old==10){
            old=0;
        }
    }

    temp=buffer[old];

    buffer.erase(buffer.begin()+old);

    return temp;
}

void LidarDriver::clear_buffer()
{
    buffer.clear();
}

double& LidarDriver::get_distance(double val)
{

    if(val<0){
        val=0;
    }
    if(val>180){
        val=180;
    }

    int pos=(val/risoluzione)+1;
    
    vector<double> recent_scan=buffer[size%BUFFER_DIM];

    double *dist= &recent_scan[pos];

    return *dist;
}





