#ifndef Invalid_h
#define Invalid_h

#include <string>

    class Invalid
    {
        public:

        enum class ErrorType
        {
            IndexOutOfBoundException,
            InvalidValue
        };

        explicit Invalid(ErrorType, const std::string&);

        
        const std::string& getMessage() const {return message;}
        ErrorType getErrorType() const {return type;} 

        private:
        
        ErrorType type;
        std::string message;
    };

#endif 