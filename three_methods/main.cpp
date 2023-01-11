#include "parameters.hpp"
#include "discipline.hpp"
#include <vector>
#include <fstream>
#include <iostream>

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
  paras.p_lottery = 0.0;
  paras.num_of_labs = 20;
  paras.num_of_lottery_win = 5;
  paras.num_of_grant_win = 5;

  paras.lambda = 0.9;

  paras.d_threshold = 2;
  paras.q_inter = 0.1;

  int num_time_units = 50;
  int reps = 1000;

  std::ofstream ofs("significance_change_with_q.txt");
  ofs << "q\tbest_pc\tbest_pl\tremaining_significance\tinitial_significance" << std::endl;

  double best_pc = -1.0;
  double best_pl = -1.0;
  double best_significance = -1.0;
  double best_ini_significance = -1.0;

  for(int loop_pc = 0; loop_pc <= 100; loop_pc++){
    paras.p_competitive = loop_pc / 100.0;

    for(int loop_pl = 0; loop_pl <= 100 - loop_pc; loop_pl++){
      paras.p_lottery = loop_pl / 100.0;

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
        best_pc = paras.p_competitive;
        best_pl = paras.p_lottery;
        best_significance = tmp_sign;
        best_ini_significance = tmp_ini_sign;
      }
    }
  }

  ofs << paras.q_inter << "\t" << best_pc << "\t" << best_pl << "\t" <<
    best_significance * 1.0 / reps << "\t" <<
    best_ini_significance * 1.0 / reps << std::endl;

  return(0);
}
