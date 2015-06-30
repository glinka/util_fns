namespace util_fns {

  template <typename T>
  void save_matrix(const std::vector< std::vector<T> >& A, std::ofstream& output_file, const std::string header, const char delim) {
    if(!header.empty()) {
      output_file << header << std::endl;
    }
    for(typename std::vector< std::vector<T> >::const_iterator v = A.begin(); v != A.end(); v++) {
      save_vector(*v, output_file, "", delim);
    }
  }

  template <typename T>
  void save_matrix(const std::vector< std::vector<T> >& A, const std::string filename, const std::string header, const char delim) {
    std::ofstream output_file(filename.c_str());
    return save_matrix(A, output_file, header, delim);
  }

  template <typename T>
  void save_vector(const std::vector<T>& v, std::ofstream& output_file, const std::string header, const char delim) {
    if(!header.empty()) {
      output_file << header << std::endl;
    }

    for(typename std::vector<T>::const_iterator val = v.begin(); val != v.end()-1; val++) {
      output_file << *val << delim;
    }
    // always ends with newline
    output_file << v.back() << std::endl;
  }

  template <typename T>
  void save_vector(const std::vector<T>& v, const std::string filename, const std::string header, const char delim) {
    std::ofstream output_file(filename.c_str());
    return save_vector(v, output_file, header, delim);
  }
  
}
