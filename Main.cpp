#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include"Cache.cpp"

using namespace std;

void multiLevel(unsigned L1Entries, unsigned L1Assoc, unsigned L2Entries, unsigned L2Assoc, char* file)
{
   // print variables
   cout << "Number of entries in L1: " << L1Entries << endl;
   cout << "Associativity in L1: " << L1Assoc << endl;
   cout << "Number of entries in L2: " << L2Entries << endl;
   cout << "Associativity in L2: " << L2Assoc << endl;
   cout << "Input File Name: " << file << endl << endl;

   // CACHE SIM
   // set up stuff
   string buffer;
   unsigned addr;
   
   ifstream read;
   read.open(file);

   getline(read, buffer);
   istringstream input(buffer);
   
   
   unsigned count = 0;
   Cache l1(L1Entries,L1Assoc);
   Cache l2(L2Entries,L2Assoc);

   input >> buffer;

   // clear + open output file
   ofstream write;
   remove("cache_sim_output");
	write.open("cache_sim_output", std::fstream::out);
   
   // loop for every address
   while(input)
   {
      // send address to cache
      // cache sends back result
      // record address + result to file
      addr = strtoul(buffer.c_str(), NULL, 10);
      input >> buffer;
      
      string result = "L1 - " + l1.get(count, addr);
      if(result[5] == 'M')
      {
         result += " | L2 - " + l2.get(count, addr);
      }
      write << addr << ": " << result << endl;
      count++;
   }
}
void singleLevel(unsigned entries, unsigned assoc, char* file)
{
   // print variables
   cout << "Number of entries " << entries << endl;
   cout << "Associativity in L1: " << assoc << endl;
   cout << "Input File Name: " << file << endl << endl;

   // CACHE SIM
   // set up stuff
   unsigned addr;
   string buffer;

   ifstream read;
   read.open(file);

   getline(read, buffer);
   istringstream input(buffer);

   unsigned count = 0;
   Cache cache(entries,assoc);

   input >> buffer;

   // clear + open output file
   ofstream write;
   remove("cache_sim_output");
	write.open("cache_sim_output", std::fstream::out);
   
   // loop for every address
   while(input)
   {
      // send address to cache
      // cache sends back result
      // record address + result to file
      addr = strtoul(buffer.c_str(), NULL, 10);
      input >> buffer;
      
      string result = cache.get(count, addr);

      write << addr << ": " << result << endl;
      count++;
   }
}

int main(int argc, char*argv[]) 
{
   // VERIFY ARGUMENTS
   // check if correct number of arguments are passed
   if (argc < 4) 
   {
      cout << endl;
      cout << "Usage: " << endl;
      cout << "   ./cache num_entries associativity filename" << endl;
      cout << "For multi-level cache: " << endl;
      cout << "   ./cache L1_num_entries L1_associativity L2_num_entries L2_associativity filename" << endl;
      cout << endl;
      return 0;
   }

   cout << endl;
   // multi level or single level depending on num of arguments
   if(argc>=6)
      multiLevel(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[5]);
   else
      singleLevel(atoi(argv[1]),atoi(argv[2]),argv[3]);//*/
      
   // DONE
   cout << "Check cache_sim_output for results"<<endl<<endl;
  
   return 0;
}
