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
  paras.p_competitive = 1.0;
  paras.num_of_labs = 20;
  paras.num_of_lottery_win = 20;
  paras.num_of_grant_win = 5;

  paras.lambda = 0.9;

  paras.d_threshold = 2;
  paras.q_inter = 0.0;

  int num_time_units = 50;
  int reps = 1000;

  std::ofstream ofs3 ("significance_change_with_q.txt");

  ofs3 << "q\toptimal_p\tremaining_significance\tinitial_significance" << std::endl;

  for(int q_loop = 0; q_loop <= 100; q_loop++){
    paras.q_inter = q_loop / 100.0;

    double best_p = -1.0;
    double best_significance = -1.0;
    double best_ini_significance = -1.0;

    for(int loop = 0; loop <= 100; loop++){
      paras.p_competitive = loop / 100.0;
      double tmp_sign = 0.0;
      double tmp_ini_sign = 0.0;

      for(int rep = 0; rep < reps; rep++){
        Discipline discipline(paras);

        tmp_ini_sign += discipline.get_total_significance();

        for(int i = 0; i < num_time_units; i++){
          discipline.next_time_unit_equiv();
        }

        tmp_sign += discipline.get_total_significance();
      }

      if(tmp_sign < best_significance || best_significance < 0){
        best_p = paras.p_competitive;
        best_significance = tmp_sign;
        best_ini_significance = tmp_ini_sign;
      }
    }

    ofs3 << paras.q_inter << "\t" << best_p << "\t" << best_significance * 1.0 / reps << "\t" << best_ini_significance * 1.0 / reps << std::endl;
  }

  return(0);
}
