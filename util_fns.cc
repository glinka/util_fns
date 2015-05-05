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

  std::string create_directory(const std::string dir_basename) {
    int folder_counter = 0;
    std::string dir;
    bool isdir = true;
    std::stringstream ss;
    struct stat stat_dir;
    do {
      ss.str("");
      ss << dir_basename << folder_counter << "/";
      folder_counter++;
      dir = ss.str();
      int check = stat(dir.c_str(), &stat_dir);
      if(check == -1) {
	if(errno == ENOENT) {
	  check = mkdir(dir.c_str(), 0700);
	  if (check != 1) {
	    isdir = false;
	  }
	  else {
	    perror("mkdir error");
	    exit(1);
	  }
	}
	else {
	  perror("mkdir error");
	  exit(1);
	}	  
      }
    } while (isdir);
    return dir;
  }

  std::vector< std::vector<double> > read_data(std::ifstream& input_file, const char delimiter) {
    /*

      Saves each row of data as a column in output_data
    
      The data is expected to be of the form:
      x1 y1 z1 ...
      x2 y2 z2 ...
      ...
      thus each "column" of output_data contains all
      input data of one variable

    */
    // count rows
    std::string line;
    int nrows = 0;
    while(std::getline(input_file, line)) {
      nrows++;
    }
    // count columns
    // determine number of columns by reading first line
    int ncols = 0;
    if(std::getline(input_file, line)) {
      std::stringstream ss(line);
      std::string temp;
      while(std::getline(ss, temp, delimiter)) {
        ncols++;
      }
    }
    else {
      std::cout << "empty input file" << std::endl;
      exit(1);
    }
    // move back to beginning of file
    // need to clear EOF flag first
    input_file.clear();
    input_file.seekg(0);
    std::string val;
    std::vector< std::vector<double> > output_data(nrows, std::vector<double>(ncols));
    int i = 0;
    while(std::getline(input_file, line)) {
      std::stringstream ss(line);
      int j = 0;
      while(std::getline(ss, val, delimiter)) {
	output_data[i][j] = atof(val.c_str());
	j++;
      }
      i++;
      // check that ncols were read
      if(j != ncols) {
	std::cout << "missing data entries in input file" << std::endl;
	exit(1);
      }
    }
    return output_data;
  }

}
