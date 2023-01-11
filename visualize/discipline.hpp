#ifndef DISCIPLINE
#define DISCIPLINE

#include "parameters.hpp"
#include "landscape.hpp"
#include "lab.hpp"
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <iostream>

class Discipline{
private:
  Parameters paras;
  Landscape landscape;
  std::vector<Lab> labs;
  std::mt19937 mt;
  std::vector<int> indices;

public:
  Discipline( const Parameters para );
  std::vector< std::vector<double> > get_landscape()
    const{ return landscape.get_landscape(); };
  double get_total_significance()
    const{ return landscape.get_total_significance(); };
  std::vector< std::vector<double> > get_landscape_discovered()
    const{ return landscape.get_landscape_discovered(); };
  void assign_resources_equiv_unit();
  std::vector<int> hill_climber( const int x_pos, const int y_pos );
  void move_labs();
  void turnover_labs();
  void next_time_unit_equiv();
  std::vector<int> lab_positions() const;
};

#endif
