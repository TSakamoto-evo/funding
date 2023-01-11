#ifndef LAB
#define LAB

#include <random>
#include <iostream>

class Lab{
private:
  int steps;
  double significance;
  int x_pos;
  int y_pos;
  int no_activity;
  std::mt19937 mt;

public:
  Lab( const int width, const int depth );
  void num_of_steps( const double resource );
  std::vector<int> get_pos_and_steps() const;
  double get_significance() const{ return significance; }
  void set_pos_significance(const std::vector<int>& pos, const double significance_find);
  int no_activity_plus(){ no_activity++; return(no_activity); }
  void no_activity_reset(){ no_activity = 0; }
  void set_for_intra_discipline( const int ini_x_pos, const int ini_y_pos );
  void set_for_inter_discipline();
};

#endif
