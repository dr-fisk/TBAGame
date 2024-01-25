#ifndef NET_UTILITY_HPP
#define NET_UTILITY_HPP

#ifdef __linux__
  #include <arpa/inet.h>
#elif _WIN32
  #include <winsock2.h>
#endif

#endif