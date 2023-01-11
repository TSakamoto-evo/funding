#ifndef PARAMETERS
#define PARAMETERS

#include <vector>

class Parameters{
public:
  int width;
  int depth;
  std::vector<double> x_peak_pos;
  std::vector<double> y_peak_pos;
  std::vector<double> height_peak;
  std::vector<double> sigma_peak;

  double total_resource;
  double p_competitive;
  int num_of_labs;
  int num_of_lottery_win;
  int num_of_grant_win;

  double lambda;

  int d_threshold;
  double q_inter;

};

#endif
