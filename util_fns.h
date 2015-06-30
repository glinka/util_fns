#ifndef UTIL_FNS_H
#define UTIL_FNS_H

#include <vector>
#include <string>
#include <fstream>

namespace util_fns {

  /**
   * Either creates a new directory at 'dir_basename' (relative to the directory from which the program is run) or does nothing if the directory already exists
   * \param dir_basename directory name, relative to directory from which the program is run
   * \return indicator of whether the operation succeeded: True for file already exists or was created, False for file creation failure
   *
   * \todo **give example of dir_basename, i.e. './myfile' or '/myfile' or 'myfile/' etc.**
   */
  bool create_directory(const std::string dir_basename);
  /**
   * Reads numerical data in ASCII format from file 'input_file' in which entries are separated by 'delimiter'
   * \param input_file file to read data from
   * \param delimiter character separating entries in file
   * \param skip_rows number of rows to skip before reading, typically corresponding to some file header
   * \return data read from file, in which data[i] refers to the i-th row of data read, i.e. column major ordering is used
   */
  std::vector< std::vector<double> > read_data(std::ifstream &input_file, const char delimiter=',', const int skip_rows=0);
  /**
   * Convenienve function for reading data from file located at 'input_filename'
   * \param input_filename location of file from which to read data, given relative to program execution directory
   * \param delimiter character separating entries in file
   * \param skip_rows number of rows to skip before reading, typically corresponding to some file header
   * \return data read from file, in which data[i] refers to the i-th row of data read, i.e. column major ordering is used
   */
  std::vector< std::vector<double> > read_data(const std::string input_filename, const char delimiter=',', const int skip_rows=0);
  /**
   * Saves data from matrix 'A' in file 'output_file', including the optional 'header', and separating data by 'delimiter'
   * \param A matrix to save. column major ordering is assumed, so A[i] refers to the i-th row of A
   * \param output_file file to save data in
   * \param header string to be inserted at beginning of file
   * \param delimiter character separating entries in file
   */
  template <typename T>
    void save_matrix(const std::vector< std::vector<T> >& A, std::ofstream& output_file, const std::string header="", const char delim=',');
  /**
   * Convenience function to save data in file specified by string 'filename'. Saves data from matrix 'A' in file 'output_file', including the optional 'header', and separating data by 'delimiter'
   * \param A matrix to save. column major ordering is assumed, so A[i] refers to the i-th row of A
   * \param filename location of new file to save data in, relative to program execution directory
   * \param header string to be inserted at beginning of file
   * \param delimiter character separating entries in file
   */
  template <typename T>
    void save_matrix(const std::vector< std::vector<T> >& A, const std::string filename, const std::string header="", const char delim=',');
  /**
   * Saves vector of data in 'outputfile', including the optional 'header', and separating data by 'delimiter'
   * \param v vector of data to save
   * \param output_file file to save data in
   * \param header string to be inserted at beginning of file
   * \param delimiter character separating entries in file
   */
  template <typename T>
    void save_vector(const std::vector<T>& v, std::ofstream& output_file, const std::string header="", const char delim='\n');
  /**
   * Convenience function to save data in new file at 'filename'. Saves vector of data in 'outputfile', including the optional 'header', and separating data by 'delimiter'
   * \param v vector of data to save
   * \param filename location of new file to save data in, relative to program execution directory
   * \param header string to be inserted at beginning of file
   * \param delimiter character separating entries in file
   */
  template <typename T>
    void save_vector(const std::vector<T>& v, const std::string filename, const std::string header="", const char delim='\n');

}

#include "util_fns.tpp"

#endif
