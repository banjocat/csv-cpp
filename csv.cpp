#include <iostream>

#include "csv.h"


using namespace std;

/* 
   Example
 */
int main() {

  CSV csv;

  csv.open("titanic.csv");

 
  map<string, vector<string> > mymap = csv.get_map();

  int size = 0;

  cout << "Outputing Map." << endl;
  cout << "Size: " << mymap.size() << endl;

  cout << mymap["name"][0] << endl;
  size = mymap["name"].size();

  for (int i = 0; i < size; i++) {
 
    cout << mymap["name"][i] << endl;
  }
  
  return 0;
}

CSV::CSV() {
  cache = "";
}


CSV::~CSV() {
}


vector<std::vector<std::string> > CSV::get_vector() {
  return data;
}

/*
  converts the vector into an ordered map
  with keys being attribute names on header file.
*/
map<string, vector<string> > CSV::get_map(bool head) {
  
  int size = data.size();

  map<string, vector<string> > themap;

  vector<string> line;

  int colsize = data[0].size();

  for (int i = 0; i < colsize; i++) {

    themap[data[0][i]] = col_to_vector(i, true);
  }

  
  return themap;

}

/*
  Returns a vector of one col of the data
*/
vector <string> CSV::col_to_vector(int col, bool header) {

  vector<string> value;

  int size = data.size();

  for (int i = 0; i < size; i++) {

    if (i == 0 && header == true) {
      continue;
    }

    if (col < data[i].size()) {
   
      value.push_back(data[i][col]);
    }

  }

  return value;
      
}

/*
  Opens a CSV
  not sure if I"ll have it test for header file here or not
*/
void CSV::open(string filename) {

  ifstream file(filename.c_str());
  
  state1(file);

  file.close();
}



/*
  Used for testing
*/
void CSV::print() {

  cout << "Printing CSV." << endl;
  int size = data.size();

  for (int i = 0; i < size; i++) {

    int lsize = data[i].size();

    for (int j = 0; j < lsize; j++) {
      cout << data[i][j] << " ";
    }
    cout << endl;
  }
}

/*
  This is the starting state
  Saves to the cache all but special chars
*/
void CSV::state1(ifstream &file) {

  char c;

  if ( !file.get(c) ) {
    clean();
    return;
  }


  if (c == '"') {
    state4(file);
  }
  else if (c == ',') {
    state2(file);
  }
  else if (c == '\n') {
    state3(file);
  }
  else {
    cache.push_back(c);
    state1(file);
  }
}

/*
  This is an acccepting state
  It then moves without input to state1
*/
void CSV::state2(ifstream &file) {

  line.push_back(cache);
  cache = "";

  state1(file);
}
  
/*
  Another accepting state
  This is end of line
  without input it goes back to the beginning state.
*/
void CSV::state3(ifstream &file) {

 
  line.push_back(cache);
  data.push_back(line);
  line.clear();
  cache = "";

  state1(file);
  
}

/*
  Reached a special char "
  Skips , till another " or EOL
  This will not add the " to the data
*/
void CSV::state4(ifstream &file) {
  
  char c;

  if ( !file.get(c) ) {
    clean();
    return;
  }

  if (c == '"')  {
    state1(file);
  }
  else if (c == '\n') {
    state3(file);
  }
  else {
    cache.push_back(c);
    state4(file);
  }
}



/*
  flushes all data if EOF was reached
*/
void CSV::clean() {

  if (cache.size() > 0) {


    line.push_back(cache);
  }

  if (line.size() > 0) {
    data.push_back(line);
  }

  cache.clear();
  line.clear();
}
