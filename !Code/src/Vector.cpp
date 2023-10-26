#include "Vector.h"



Vector::Vector()
{
}

Vector::~Vector()
{
}

void Vector::normalise()
{
  x_direction = x_direction / get_magnitude();
  y_direction = y_direction / get_magnitude();
}

float Vector::get_magnitude()
{
  float x_squared;
  float y_squared;

  x_squared = x_direction * x_direction;
  y_squared = y_direction * y_direction;
  return sqrt(x_squared + y_squared);
}