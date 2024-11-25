#ifndef Invalid_h
#define Invalid_h

#include <string>

    class Invalid
    {
        public:

        //LO DEFINISCO QUI PER RENDERLO UTILIZZABILE ANCHE DA FUORI
        enum class ErrorType
        {
            IndexOutOfBoundException
            InvalidValue //lo usiamo per la definizione e per getdistance?
        };

        explicit Invalid(ErrorType, const std::string&);

        
        const std::string& getMessage() const {return message;}
        ErrorType getErrorType() const {return type;} 

        private:
        
        ErrorType type;
        std::string message;
    };

#endif 