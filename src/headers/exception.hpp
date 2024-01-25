#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

class Exception : public std::exception {
  public:
    Exception(const char *cpErrorMsg) : mpError(cpErrorMsg) {
    }
    
    ~Exception() {
    }

    const char *what() {
      return mpError;
    }
  private:
    const char *mpError;
};

#endif