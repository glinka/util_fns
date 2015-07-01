#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "util_fns.h"

namespace util_fns {

  bool create_directory(const std::string dir_basename) {
    int check = mkdir(dir_basename.c_str(), 0700);
    return check;
  }

  std::vector< std::vector<double> > read_data(std::ifstream& input_file, const char delimiter, const int skip_rows) {
    // count rows
    std::string line;
    int nrows = 0;
    while(std::getline(input_file, line).good()) {
      nrows++;
    }
    // subtract number of file header lines from overall count
    nrows -= skip_rows;
    if(!input_file.eof()) {
      std::cout << "an error occurred attempting to read from file" << std::endl;
      exit(1);
    }      
    if(nrows == 0) {
      std::cout << "empty input file" << std::endl;
      exit(1);
    }
    // move back to beginning of file
    // need to clear EOF flag first
    input_file.clear();
    input_file.seekg(0);
    // count columns
    // determine number of columns by reading first line
    int ncols = 0;
    // skip header before counting columns
    for(int i = 0; i < skip_rows; i++) {
      std::getline(input_file, line);
    }
    std::getline(input_file, line);
    std::stringstream ss(line);
    std::string temp;
    while(std::getline(ss, temp, delimiter).good()) {
      ncols++;
    }
    if(!ss.eof()) {
      std::cout << "an error occurred attempting to read from file" << std::endl;
      exit(1);
    }
    // need to add one more as the final check will fail because of the lack of a trailing delimiter (e.g. '1,2,3' and not '1,2,3,')
    ncols++;
    // move back to beginning of file
    input_file.clear();
    input_file.seekg(0);
    std::string val;
    std::vector< std::vector<double> > output_data(nrows, std::vector<double>(ncols));
    // skip first 'skip_rows' header lines before reading
    for(int i = 0; i < skip_rows; i++) {
      std::getline(input_file, line);
    }
    for(int i = 0; i < nrows; i++) {
      std::getline(input_file, line);
      std::stringstream ss(line);
      int j = 0;
      while(std::getline(ss, val, delimiter).good()) {
	output_data[i][j++] = atof(val.c_str());
      }
      // one more, again no trailing delimiter
      output_data[i][j++] = atof(val.c_str());
      // check that ncols were read
      if(j != ncols) {
	std::cout << "missing data entries in input file, found " << j << " entries, expected " << ncols << std::endl;
	exit(1);
      }
    }
    return output_data;
  }

  std::vector< std::vector<double> > read_data(const std::string input_filename, const char delimiter, const int skip_rows) {
    std::ifstream input_file(input_filename.c_str());
    return read_data(input_file, delimiter, skip_rows);
  }

}
