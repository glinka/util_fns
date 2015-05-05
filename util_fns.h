#ifndef UTIL_FNS_H
#define UTIL_FNS_H

#include <vector>
#include <string>
#include <fstream>

namespace util_fns {

  std::string create_directory(const std::string dir_basename);
  std::vector< std::vector<double> > read_data(std::ifstream &input_file, const char delimiter=',');
  template <typename T>
    void save_matrix(const std::vector< std::vector<T> >& A, std::ofstream& output_file, const std::string header="", const char delim=',');
  template <typename T>
    void save_vector(const std::vector<T>& v, std::ofstream& output_file, const std::string header="", const char delim='\n');

}

#endif
