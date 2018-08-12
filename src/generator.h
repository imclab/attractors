#ifndef MVE_ATTRACTORS_GENERATOR_HEADER
#define MVE_ATTRACTORS_GENERATOR_HEADER

#include <functional>
#include <vector>

#include "math/vector.h"

/**
 * Class for sampling the attractor function and generating a 1D curve embedded
 * in 3D space. The resulting curve can be scaled and centered into the unit
 * cube, and adaptively simplified to remove unnecessarily dense samples.
 */
class Generator {
 public:
  typedef math::Vec3d Point;
  typedef std::vector<Point> Curve;
  typedef std::function<Point(const Point&, double)> GeneratorFn;

  struct Options {
    /* Generator options. */
    GeneratorFn generator;
    double delta = 0.01;
    std::size_t iterations = 20000;
    Point start = math::Vec3f(0.1, 0.0, 0.0);

    /* Simplification options (defaults for scaled and centered curve). */
    double angle_threshold = MATH_DEG2RAD(2.0);
    double min_distance = 1e-8;
    double max_distance = 0.05;
  };

 public:
  explicit Generator(const Options& options);
  void generate();
  void scale_and_center();
  void simplify();
  void save_ply(const std::string& filename);

  const Curve& getCurve() const;

 private:
  Options options_;
  Curve curve_;
};

#endif /* MVE_ATTRACTORS_GENERATOR_HEADER */
