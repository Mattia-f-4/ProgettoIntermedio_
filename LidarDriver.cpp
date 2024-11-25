#include <LidarDriver.h>
#include <Invalid.h>

LidarDriver::LidarDriver(double r)
{
    buffer = vector<vector<double>>(BUFFER_DIM);
    
    if(risoluzione>1  || risoluzione < 0.1)
    {
        throw Invalid(Invalid::ErrorType::InvalidValue, "Risoluzione fuori dal range di valori possibili");
    }

    risoluzione = r;
};

LidarDriver::LidarDriver(double r, vector<vector<double>> b)
{
    buffer = b; 
    
    if(risoluzione>1  || risoluzione < 0.1)
    {
        throw Invalid(Invalid::ErrorType::InvalidValue, "Risoluzione fuori dal range di valori possibili");
    }

    risoluzione = r;
}

LidarDriver::LidarDriver(const LidarDriver& l)
{
    risoluzione = l.risoluzione
    std::copy()
}




