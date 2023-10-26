#ifndef PONGSFML_VECTOR_H
#define PONGSFML_VECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Vector
{
 public:
  Vector();
  ~Vector();
  float x_direction;
  float y_direction;
  void normalise();
  float get_magnitude();

 private:

};

#endif // PONGSFML_VECTOR_H
