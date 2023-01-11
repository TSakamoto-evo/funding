#include "landscape.hpp"

Landscape::Landscape( const int width, const int depth,
                       const std::vector<double>& x_peak_pos,
                       const std::vector<double>& y_peak_pos,
                       const std::vector<double>& height_peak,
                       const std::vector<double>& sigma_peak){

  std::vector< std::vector<double> > sign_tmp(width, std::vector<double>(depth, 0.0));
  significance = sign_tmp;
  significance_discovered = sign_tmp;

  std::random_device seed;
  std::mt19937 mt_tmp(seed());
  mt = mt_tmp;

  std::uniform_real_distribution<double> rugged(0.0, 1.0);

  for(int i = 0; i < width; i++){
    for(int j = 0; j < depth; j++){
      for(int k = 0; k < static_cast<int>(x_peak_pos.size()); k++){
        significance.at(i).at(j) += height_peak.at(k) * std::exp(-1.0 / 2.0 /
                                    sigma_peak.at(k) / sigma_peak.at(k) *
                                    ((i - x_peak_pos.at(k)) * (i - x_peak_pos.at(k)) +
                                    (j - y_peak_pos.at(k)) * (j - y_peak_pos.at(k))));
      }
      significance.at(i).at(j) += rugged(mt);
    }
  }
}

void Landscape::landscape_depletion( const std::vector<int>& pos, const double lambda ){
  significance_discovered.at(pos.at(0)).at(pos.at(1)) +=
    lambda * significance.at(pos.at(0)).at(pos.at(1));
  significance.at(pos.at(0)).at(pos.at(1)) *= (1.0 - lambda);
}

double Landscape::get_total_significance() const{
  double total = 0.0;
  for(int i = 0; i < static_cast<int>(significance.size()); i++){
    for(int j = 0; j < static_cast<int>(significance.at(0).size()); j++){
      total += significance.at(i).at(j);
    }
  }
  return(total);
}
