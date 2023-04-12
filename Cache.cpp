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
      cout<< "get addr: " << addr << " at " << ref << endl << " i = " << i<<endl; 

      // find if val in cache
      for(unsigned k = 0; k< assoc; k++)
      {
         Entry e = entries[k][i];
         if(e.isValid())
         {
            if(e.getTag() == addr-i)
            {
               e.setRef(ref);
               return "HIT";
            }
         }
      }

      // val not in cache
      // find where to put
      unsigned oldest = 0;
      for(unsigned k = 0; k< assoc; k++)
      {
         Entry e = entries[k][i];
         if(!e.isValid())
         {
            e.setRef(ref);
            e.setTag(addr-i);
            e.setValid(true);
            cout<<"Put: " << e.isValid() << " " << e.getTag()<< " " << e.getRef()<< " in: "<<k<<","<<i<<endl;  
            return "MISS - COMPULSARY";
         }
         if(e.getRef()<entries[oldest][i].getRef())
            oldest = k;
      }
      Entry e = entries[oldest][i];
      e.setRef(ref);
      e.setTag(addr-i);
      e.setValid(true);
      return "MISS - CONFLICT";
   }
private:
   unsigned assoc, setSize;
   set<unsigned> accessed;
   vector<std::vector<Entry> > entries;
};