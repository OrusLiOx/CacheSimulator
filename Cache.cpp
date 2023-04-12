#include<vector>
#include<iostream>
#include<set>

using namespace std;

class Entry 
{
public:
   Entry()
    {
        valid = false;
        ref = -1;
    }

   void display()
   {
      cout << "Valid: "<< valid;
      if(valid)
         cout << " | Tag: " << tag << " | Ref: " << ref;
   }

   void setTag(int _tag) { tag = _tag; }
   int getTag() { return tag; }

   void setValid(bool _valid) { valid = _valid; }
   bool isValid() { return valid; }

   void setRef(int _ref) { ref = _ref; }
   int getRef() { return ref; }

private:  
   bool valid;
   unsigned tag;
   int ref;
};

class Cache
{
public:
   Cache(unsigned e, unsigned a)
   {
      setSize=e/a;
      assoc = a;

      for(unsigned set = 0; set < a; set++)
      {
         entries.push_back(vector<Entry>());
         for(unsigned k = 0; k<setSize; k++)
            entries[set].push_back(Entry());
      }
   }
   Cache(){}

   void display()
   {
      cout<<"Cache:";
      for(unsigned k = 0; k< assoc; k++)
      {
         cout << endl << k << "------";
         for(int j=0; j<setSize;j++)
         {
            cout<<endl<< j <<" : ";
            entries[k][j].display();
         } 
      }
      cout<<endl << "---------"<<endl;
   }

   string get(unsigned ref, unsigned addr)
   {
      unsigned i = addr%setSize;

      // find if val in cache
      for(unsigned k = 0; k< assoc; k++)
      {
         if(entries[k][i].isValid())
         {
            if(entries[k][i].getTag() == addr-i)
            {
               entries[k][i].setRef(ref);
               return "HIT";
            }
         }
      }

      // val not in cache
      // find where to put
      unsigned oldest = 0;
      for(unsigned k = 0; k< assoc; k++)
      {
         if(!entries[k][i].isValid())
         {
            entries[k][i].setRef(ref);
            entries[k][i].setTag(addr-i);
            entries[k][i].setValid(true);
            return "MISS";
         }
         if(entries[k][i].getRef()<entries[oldest][i].getRef())
            oldest = k;
      }
      entries[oldest][i].setRef(ref);
      entries[oldest][i].setTag(addr-i);
      entries[oldest][i].setValid(true);
      return "MISS";
   }
private:
   unsigned assoc, setSize;
   set<unsigned> accessed;
   vector<std::vector<Entry> > entries;
};