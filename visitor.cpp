// This is the modern implementation of the visitor pattern presented by Klaus Iglberger during CppCon 2022
// https://www.youtube.com/watch?v=PEcy1vYHb8A
// The visitor pattern let's you add functionality (e.g. draw, translate, etc.) to multpile types easily without dependencies. One disadvantage is that it is "hard" to add new types because they'd be added to the definition of `Shape` which is part of all function definitions and thus they all have to be rebuilt. For more information watch the video.

#include <iostream>
#include <variant>
#include <vector>


class Circle
{
public:
  explicit Circle (double rad )
  : radius {rad}
  {}

  double getRadius() const noexcept
  {
    return radius;
  }

private:
  double radius;
};

class Square
{
public:
  explicit Square (double s )
  : side {s}
  {}

  double getSide() const noexcept
  {
    return side;
  }

private:
  double side;
};

class Draw
{
public:
  void operator()( Circle const&) const
  {
    std::cout << "This is supposed to draw a circle...\n";
  }
  void operator()( Square const&) const
  {
    std::cout << "This is supposed to draw a square...\n";
  }
};

using Shape = std::variant<Circle, Square>;

void drawAllShapes( std::vector<Shape> const& shapes )
{
  for( auto const& s : shapes )
    {
      std::visit( Draw{}, s );
    }
}

int main()
{
  using Shapes = std::vector<Shape>;

  Shapes shapes;
  shapes.emplace_back( Circle{2.0} );
  shapes.emplace_back( Square{1.5} );
  shapes.emplace_back( Circle{4.2} );

  drawAllShapes( shapes );
}
