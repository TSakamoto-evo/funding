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

  int num_time_units = 100;

  std::ofstream ofs("landscape_change.txt");
  std::ofstream ofs2("lab_positions.txt");
  std::ofstream ofs3("total_significance.txt");
  std::ofstream ofs4("parameters.txt");

  ofs4 << paras.width << "\t" << paras.depth << "\t" << num_time_units << std::endl;

  Discipline discipline(paras);

  for(int i = 0; i <= num_time_units; i++){
    if(i % 1 == 0){
      ofs << i << "\t";
      std::vector< std::vector<double> > tmp_land2 = discipline.get_landscape();
      for(int j = 0; j < static_cast<int>(tmp_land2.size()); j++){
        for(int k = 0; k < static_cast<int>(tmp_land2.at(0).size()); k++){
          ofs << tmp_land2.at(j).at(k) << "\t";
        }
      }
      ofs << std::endl;

      ofs2 << i;
      std::vector<int> tmp_pos = discipline.lab_positions();
      for(int j = 0; j < static_cast<int>(tmp_pos.size()); j++){
        ofs2 << "\t" << tmp_pos.at(j);
      }
      ofs2 << std::endl;

      ofs3 << i << "\t" << discipline.get_total_significance() << std::endl;
    }

    discipline.next_time_unit_equiv();
  }

  return(0);
}
