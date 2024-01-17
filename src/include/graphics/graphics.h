#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics
{
  public:
    Graphics() = default;
    virtual ~Graphics() = default;
    virtual void draw() = 0;
  private:
};

#endif