#include "lab.hpp"

Lab::Lab( const int width, const int depth ){
  std::random_device seed;
  std::mt19937 tmp_mt(seed());
  mt = tmp_mt;

  std::uniform_int_distribution<int> ini_x_pos(0, width - 1);
  std::uniform_int_distribution<int> ini_y_pos(0, depth - 1);

  x_pos = ini_x_pos(mt);
  y_pos = ini_y_pos(mt);

  significance = 1.0;
  steps = 0;
  no_activity = 0;
}

void Lab::num_of_steps( const double resource ){
  std::poisson_distribution<int> num_steps(resource);
  steps = num_steps(mt);
}

std::vector<int> Lab::get_pos_and_steps() const{
  std::vector<int> ret = {x_pos, y_pos, steps};
  return(ret);
}

void Lab::set_pos_significance(const std::vector<int>& pos, const double significance_find){
  x_pos = pos.at(0);
  y_pos = pos.at(1);
  significance = significance_find;
}

void Lab::set_for_intra_discipline( const int ini_x_pos, const int ini_y_pos ){
  x_pos = ini_x_pos;
  y_pos = ini_y_pos;
  significance = 0.0;
}

void Lab::set_for_inter_discipline(){
  significance = 0.0;
}

void Lab::for_ini_pos(const int ini_x_pos, const int ini_y_pos){
  x_pos = ini_x_pos;
  y_pos = ini_y_pos;
}
