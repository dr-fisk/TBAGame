#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

class Graphics
{
  public:
    Graphics() = default;
    virtual ~Graphics() = default;
    virtual void draw() = 0;
  private:
};

#endif