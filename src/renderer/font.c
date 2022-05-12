#include "font.h"

Font::Font() {
  
}

Font::~Font() {

}

int Font::loadFromFile(std::string ttf) {
  std::ifstream fp(ttf);
  return 1;
}