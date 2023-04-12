#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include"Cache.cpp"

using namespace std;

int main(int argc, char*argv[]) 
{
// VERIFY ARGUMENTS
   // check if correct number of arguments are passed
   if (argc < 4) 
   {
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

// CACHE SIM
   // loop for every address
   // send address to cache
   // cache sends back result
   // record address + result to file

   // setup input stream
   ifstream read;
   read.open(argv[3]);
   string buffer;
   unsigned addr;
   getline(read, buffer);
   istringstream input(buffer);
   input >> buffer;

   // setup output file
   ofstream write;
   remove("cach_sim_output");
	write.open("cach_sim_output", std::fstream::out);

   // prepare for loop
   unsigned count = 0;
   Cache cache(entries,assoc);

   while(input)
   {
      addr = strtoul(buffer.c_str(), NULL, 10);
      input >> buffer;
      
      string result = cache.get(count, addr);
      write << addr << ": " << result << endl;
      count++;
   }

// DONE
   cout << "Check cach_sim_output for results"<<endl;
  
   return 0;
}