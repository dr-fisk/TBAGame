#ifndef COMMON_H
#define COMMON_H

#ifdef __linux__
  #define LINUX
#elif _WIN32
  #define WINDOWS
#endif

#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <ctime>
#include <cstdint>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <fstream>
#include <memory>
#include <zlib.h>

#ifdef LINUX
  #include <arpa/inet.h>
#elif defined(WINDOWS)
  #include <winsock2.h>
#endif

enum Status {
    FAIL,
    SUCCESS
};

#define MESH16_SIZE 256

#endif