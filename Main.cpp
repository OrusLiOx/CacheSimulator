#include<iostream>
#include<cstdlib>

using namespace std;
 
int main(int argc, char*argv[]) 
{
  // check if correct number of arguments are passed
  if (argc < 4) {
    cout << "Usage: " << endl;
    cout << "   ./cache num_entries associativity filename" << endl;
    return 0;
  }

  // move arguments into variables of proper types
  unsigned entries = atoi(argv[1]);
  unsigned assoc = atoi(argv[2]);

  string filename = argv[3];

  // print arguments
  cout << "Number of entries: " << entries << endl;
  cout << "Associativity: " << assoc << endl;
  cout << "Input File Name: " << filename << endl;
  
  return 0;
}