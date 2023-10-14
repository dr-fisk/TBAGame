#ifdef LINUX
  #include <arpa/inet.h>
#elif defined(WINDOWS)
  #include <winsock2.h>
#endif