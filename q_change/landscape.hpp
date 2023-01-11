#ifndef LANDSCAPE
#define LANDSCAPE

#include <vector>
#include <random>

class Landscape{
private:
  std::vector< std::vector<double> > significance;
  std::vector< std::vector<double> > significance_discovered;
  std::mt19937 mt;

public:
  Landscape( const int width, const int depth,
             const std::vector<double>& x_peak_pos,
             const std::vector<double>& y_peak_pos,
             const std::vector<double>& height_peak,
             const std::vector<double>& sigma_peak );
  std::vector< std::vector<double> > get_landscape() const{ return significance; };
  std::vector< std::vector<double> > get_landscape_discovered()
    const{ return significance_discovered; };
  double get_point_significance( const int x, const int y )
    const{ return significance.at(x).at(y); };
  void landscape_depletion( const std::vector<int>& pos, const double lambda );
  double get_total_significance() const;
};

#endif
