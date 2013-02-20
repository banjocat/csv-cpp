#include <map>
#include <string>
#include <vector>
#include <fstream>


/* 
   Reads a CSV file
   "stuff here,,," in CSV will cause the reader to skip the ,
   will enter "" for CSV that reads ,,
*/

class CSV {
 public:

  CSV();

  void open(std::string filename);

 
  std::vector<std::vector<std::string> > get_vector();

  std::map<std::string, std::vector<std::string> > get_map(bool head = true);

  /*
    For testing
  */
  void print();

 private:

  std::vector<std::vector<std::string> > data;
  std::string cache;
  std::vector <std::string> line;

  std::vector<std::string> col_to_vector(int col, bool header = true);

  /*
    A non deterministic FA is used for fun.
  */
  void state1(std::ifstream &file);
  void state2(std::ifstream &file);
  void state3(std::ifstream &file);
  void state4(std::ifstream &file);
  
  void clean();
};
