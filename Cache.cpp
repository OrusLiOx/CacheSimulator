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
      sets = e/a;
      assoc = a;

      for(unsigned i= 0; i<sets; i++)
      {
         entries.push_back(vector<Entry>());
         for(unsigned k = 0; k<a; k++)
            entries[i].push_back(Entry());
      }
   }
   Cache(){}

   void display()
   {
      cout<<"Cache:";
      for(unsigned k = 0; k< sets; k++)
      {
         cout << endl << k << "--------------------";
         for(int j=0; j<assoc;j++)
         {
            cout<<endl<< j <<" : ";
            entries[k][j].display();
         } 
      }
      cout<<endl << "-------------------------"<<endl;
   }

   string get(unsigned ref, unsigned addr)
   {
      unsigned i = addr%sets;

      // find if val in cache
      for(unsigned k = 0; k<assoc; k++)
      {
         if(entries[i][k].isValid())
         {
            if(entries[i][k].getTag() == addr-i)
            {
               entries[i][k].setRef(ref);
               return "HIT";
            }
         }
      }

      // val not in cache
      // find where to put
      unsigned oldest = 0;
      for(unsigned k = 0; k< assoc; k++)
      {
         if(!entries[i][k].isValid())
         {
            entries[i][k].setRef(ref);
            entries[i][k].setTag(addr-i);
            entries[i][k].setValid(true);
            accessed.insert(addr);
            return "MISS - COMPULSORY";
         }
         if(entries[i][k].getRef()<entries[i][oldest].getRef())
            oldest = k;
      }
      entries[i][oldest].setRef(ref);
      entries[i][oldest].setTag(addr-i);
      entries[i][oldest].setValid(true);

      if(accessed.find(addr) == accessed.end())
      {
         accessed.insert(addr);
         return "MISS - COMPULSORY";
      }
      if(isFull())
      {
         return "MISS - CAPACITY  ";
      }
      return "MISS - CONFLICT  ";
   }
private:
   unsigned assoc, sets;
   set<unsigned> accessed;
   vector<std::vector<Entry> > entries;

   bool isFull()
   {
      for(unsigned k = 0; k< sets; k++)
      {
         for(int j=0; j<assoc;j++)
         {
            if(!entries[k][j].isValid())
               return false;
         }
      }
      return true;
   }
};
