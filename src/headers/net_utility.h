#ifndef NET_UTILITY_H
#define NET_UTILITY_H

#ifdef __linux__
  #include <arpa/inet.h>
#elif _WIN32
  #include <winsock2.h>
#endif

#endif