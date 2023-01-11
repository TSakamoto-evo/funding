#include "discipline.hpp"

Discipline::Discipline( const Parameters para ):
  landscape( para.width, para.depth,
              para.x_peak_pos, para.y_peak_pos,
              para.height_peak, para.sigma_peak ){

  paras = para;

  labs.clear();
  indices.clear();
  for(int i = 0; i < paras.num_of_labs; i++){
    labs.emplace_back( paras.width, paras.depth );
    indices.push_back(i);
  }

  std::random_device seed;
  std::mt19937 mt_tmp(seed());
  mt = mt_tmp;
}

void Discipline::assign_resources_equiv_unit(){
  std::vector<int> tmp_indices(paras.num_of_labs);
  std::vector<double> tmp_labs_significances(paras.num_of_labs);
  std::vector<double> tmp_resources(paras.num_of_labs);

  std::shuffle(indices.begin(), indices.end(), mt);

  for(int i = 0; i < paras.num_of_labs; i++){
    tmp_indices.at(i) = i;
    tmp_labs_significances.at(i) = labs.at(indices.at(i)).get_significance();
  }

  std::sort(tmp_indices.begin(), tmp_indices.end(), [tmp_labs_significances](int i1, int i2){
    return tmp_labs_significances.at(i1) > tmp_labs_significances.at(i2);
  });

  for(int i = 0; i < paras.num_of_grant_win; i++){
    tmp_resources.at(indices.at(tmp_indices.at(i))) +=
      paras.total_resource * paras.p_competitive / paras.num_of_grant_win;
  }

  std::shuffle(indices.begin(), indices.end(), mt);

  //winners
  for(int i = 0; i < paras.num_of_lottery_win; i++){
    tmp_resources.at(indices.at(i)) +=
      paras.total_resource * (1.0 - paras.p_competitive) / paras.num_of_lottery_win;
  }

  //assign
  for(int i = 0; i < paras.num_of_labs; i++){
    labs.at(i).num_of_steps( tmp_resources.at(i) );
  }
}

std::vector<int> Discipline::hill_climber( const int x_pos, const int y_pos ){
  int pot_x_pos = -1;
  int pot_y_pos = -1;
  double pot_significance = -1.0;

  for(int i = x_pos - 1; i <= x_pos + 1; i++){
    for(int j = y_pos - 1; j <= y_pos + 1; j++){
      if(i >= 0 && i < paras.width && j >= 0 && j < paras.depth){
        if(landscape.get_point_significance(i, j) > pot_significance){
          pot_x_pos = i;
          pot_y_pos = j;
          pot_significance = landscape.get_point_significance(i, j);
        }
      }
    }
  }
  std::vector<int> ret = {pot_x_pos, pot_y_pos};
  return(ret);
}

void Discipline::move_labs(){
  std::shuffle(indices.begin(), indices.end(), mt);

  for(int i = 0; i < paras.num_of_labs; i++){
    std::vector<int> pos_and_steps = labs.at(indices.at(i)).get_pos_and_steps();
    double significance_find = 0.0;
    std::vector<int> pos = { pos_and_steps.at(0), pos_and_steps.at(1) };

    for(int j = 0; j < pos_and_steps.at(2); j++){
      pos = hill_climber( pos.at(0), pos.at(1) );
      significance_find += paras.lambda * landscape.get_point_significance( pos.at(0), pos.at(1) );
      landscape.landscape_depletion(pos, paras.lambda);
    }
    labs.at(indices.at(i)).set_pos_significance(pos, significance_find);
  }
}

void Discipline::turnover_labs(){
  std::vector<int> remove_labs;
  std::vector<int> not_remove_labs;

  for(int i = 0; i < paras.num_of_labs; i++){
    if(labs.at(i).get_pos_and_steps().at(2) == 0){
      int j = labs.at(i).no_activity_plus();
      if(j == paras.d_threshold){
        remove_labs.push_back(i);
      }else{
        not_remove_labs.push_back(i);
      }
    }else{
      labs.at(i).no_activity_reset();
      not_remove_labs.push_back(i);
    }
  }

  int num_removed = remove_labs.size();

  std::uniform_int_distribution<int> duplicate(0, paras.num_of_labs - num_removed - 1);
  std::bernoulli_distribution inter_turn(paras.q_inter);

  for(int i = 0; i < num_removed; i++){
    if(inter_turn(mt)){
      Lab replace(paras.width, paras.depth);
      replace.set_for_inter_discipline();
      labs.at(remove_labs.at(i)) = replace;
    }else{
      Lab replace(paras.width, paras.depth);
      std::vector<int> pos_and_steps = labs.at(not_remove_labs.at(duplicate(mt))).get_pos_and_steps();
      replace.set_for_intra_discipline(pos_and_steps.at(0), pos_and_steps.at(1));
      labs.at(remove_labs.at(i)) = replace;
    }
  }
}

void Discipline::next_time_unit_equiv(){
  assign_resources_equiv_unit();
  move_labs();
  turnover_labs();
}

std::vector<int> Discipline::lab_positions() const{
  std::vector<int> tmp_pos;
  for(int i = 0; i < paras.num_of_labs; i++){
    tmp_pos.push_back(labs.at(i).get_pos_and_steps().at(0));
    tmp_pos.push_back(labs.at(i).get_pos_and_steps().at(1));
    tmp_pos.push_back(labs.at(i).get_pos_and_steps().at(2));
  }

  return(tmp_pos);
}
