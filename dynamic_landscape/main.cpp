#include"parameters.hpp"
#include"discipline.hpp"
#include<vector>
#include<fstream>
#include<iostream>

int main(){
  //Parameter settings
  Parameters paras;

  paras.width = 101;
  paras.depth = 101;
  paras.x_peak_pos.assign( {20.0, 20.0, 80.0, 80.0} );
  paras.y_peak_pos.assign( {20.0, 80.0, 20.0, 80.0} );
  paras.height_peak.assign( {30.0, 30.0, 30.0, 30.0} );
  paras.sigma_peak.assign( {4.0, 4.0, 4.0, 4.0} );

  paras.total_resource = 50.0;
  paras.p_competitive = 0.3;
  paras.num_of_labs = 20;
  paras.num_of_lottery_win = 5;
  paras.num_of_grant_win = 5;

  paras.lambda = 0.9;

  paras.d_threshold = 2;
  paras.q_inter = 0.0;

  paras.ini_num = 20;

  int num_time_units = 10000;
  int burn_in = 1000;
  int reps = 1;
  double add_significance_criteria = 5000.0;

  std::ofstream ofs("significance_change_with_q.txt");
  std::ofstream ofs2("significance_change_with_q_all.txt");

  ofs << "q\toptimal_p\tdiscovery_speed" << std::endl;
  ofs2 << "q\tp\tdiscovery_speed" << std::endl;

  double best_p = -1.0;
  double best_significance = -1.0;

  for(int loop = 0; loop <= 100; loop++){
    paras.p_competitive = loop / 100.0;
    double tmp_sign = 0.0;

    for(int rep = 0; rep < reps; rep++){
      Discipline discipline(paras);

      double start_sign, end_sign;

      for(int i = -burn_in; i < num_time_units; i++){
        if(i == 0){
          start_sign = discipline.get_total_discovered_significance();
        }

        discipline.next_time_unit_equiv();

        if(i == num_time_units - 1){
          end_sign = discipline.get_total_discovered_significance();
        }

        double now_significance = discipline.get_total_significance();
        if(now_significance < add_significance_criteria){
          discipline.add_significance(1, 0.0);
        }
      }

      tmp_sign += (end_sign - start_sign);
    }

    if(tmp_sign > best_significance){
      best_p = paras.p_competitive;
      best_significance = tmp_sign;
    }

    ofs2 << paras.q_inter << "\t" << paras.p_competitive << "\t"
      << tmp_sign * 1.0 / reps / num_time_units << std::endl;
  }

  ofs << paras.q_inter << "\t" << best_p << "\t" << best_significance * 1.0 / reps / num_time_units << std::endl;

  return(0);
}
