#include <iostream>

#include "csv.h"


using namespace std;

/* 
   For testing
 */
int main() {

  CSV csv;

  csv.open("test1.csv");

  csv.print();
  
  return 0;
}

CSV::CSV() {
  cache = "";
  line.clear();
  data.clear();
}


/*
  Opens a CSV
  not sure if I"ll have it test for header file here or not
*/
void CSV::open(string filename) {

  ifstream file(filename.c_str());
  
  state1(file);

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
  goes back to beginning state after
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
