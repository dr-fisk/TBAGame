#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class Exception : public std::exception {
  public:
    Exception(const char *errorMsg) : error(errorMsg) {
    }
    
    ~Exception() {
    }
      const char *what() {
      return error;
    }
  private:
    const char *error;
};

#endif