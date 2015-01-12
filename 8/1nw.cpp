#include <limits.h>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <stdint.h>
#include <sstream>
using namespace std;
typedef uint8_t u8;
typedef vector<u8> VU8;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<bool> VB;
typedef pair<int,int> PI;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

#if 1
#define C cout
#else
#include <fstream>
ofstream C("/dev/null");
#endif

#if 1
#define INS \
{ \
   static int calls; \
   calls++; \
   cout << __FUNCTION__ << ":" << calls << endl; \
}
#else
#define INS 
#endif
template<class T>
void pv(const vector<T> &v){
   if(!v.size()){
      cout <<"{}\n";
      return;
   }
   cout << "{";
   FOR0(i,v.size()-1){
      cout << v[i] <<", ";
   }
   cout << v[v.size()-1] << "}\n";
}

static const int BLANK = 10;
class State
{
//   int nbsh;
   char h[15];//max
   public:
   State() /*: nbsh(0)*/
   {
      memset(h, BLANK, sizeof(h));
   }
   void set(int i, char val){
      int old = h[i];
      h[i] = val;
//      if(old==BLANK && val != BLANK) nbsh++;
//      if(old!=BLANK && val == BLANK) nbsh--;
   }
   int GetNumBish(int k) const
   {
      int nbsh = 0;
      if(!k) return 0;
      assert(k > 0);
      FOR0(i,k){
         nbsh += (h[i] != BLANK);
      }
      return nbsh;
   }
   bool find(int k, int v) const
   {
      if(!k) return false;
      FOR0(i, k){
         if(h[i] == v) return true;
      }
      return false;
   }
   void print(int k){
      if(!k) return;
      FOR0(i, k){
         C << (int)h[i] << ' ';
      }
      C << endl;
   }
};

class Solver
{
   int nb,n;
   int nsol;

   bool IsSolution(const State &st, int k){
      return st.GetNumBish(k) == nb;
   }

   void findNextMoves(const State &st, int k, char *nxt, int &nnxt)
   {
      nnxt = 0;
      if(st.GetNumBish(k) + 2*n-k-1 > nb){
         nxt[nnxt++] = BLANK;
      }

      int kk = min(k, 2*n-2-k);
      int mx = (kk&1)? (1+kk/2) : (kk/2);
      for(int i = -mx; i <=mx; i++){
         if(i == 0 && (kk&1)) continue; //odd excludes 0
         if(!st.find(k, i)){
            nxt[nnxt++] = i;
         }
      }
   }

   void backtrace(State &st, int k)
   {
      if(IsSolution(st,k)){
//         C << "Sol ";
//         st.print(k);
//         nsol++;
         return;
      }
      char nxt[9];
      int nnxt;
      findNextMoves(st, k, nxt, nnxt);
 //     C << "k=" << k << " nnxt=" << nnxt << endl;
      FOR0(i,nnxt){
         st.set(k, nxt[i]);
         if(IsSolution(st,k+1)){
            C << "Sol ";
            st.print(k+1);
            nsol++;
         }else{
            backtrace(st, k+1);
         }
      }
   }
   public:
   int solve(int n, int nb)
   {
      this->nb = nb;
      this->n = n;
      nsol=0;
      if(nb > 2*n -1){
         return 0;
      }
      State st;
      backtrace(st, 0);
      return nsol;
   }
};

int main(int argc, char **argv)
{
   int n,k;
   while(cin >> n >> k, n){
      Solver slv;
      cout << slv.solve(n,k) << endl;
   }
   return 0;
}
