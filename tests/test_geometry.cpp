#include <iostream>
#include "src/core/geometry.h"

int main()
{
  core::geometry::Point p1{0,0,0};
  core::geometry::Point p2{3,0,0};
  core::geometry::Point p3{0,4,0};

  core::geometry::Vector v12{p1, p2};
  core::geometry::Vector v13{p1, p3};
  auto v23 = core::geometry::subtract(v13, v12);

  std::cout << v23.length() << std::endl;
  v23.normalize();
  std::cout << v23.length() << std::endl;

  std::cout << 2.0 * core::geometry::angle_between(v12, v13) << std::endl;

  std::cout << core::geometry::triple_product(v12, v13, v23) << std::endl;

  auto v = core::geometry::vector_product(v12, v13);

  std::cout << v.x << " , " << v.y << " , " << v.z << std::endl;
  return 0;
}
