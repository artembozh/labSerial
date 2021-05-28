#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime> 

using namespace std;


long long binpow(long long a, long long e, long long m) {
  long long res = 1;
  while (e != 0) {
    if (e % 2 == 1)
      res = (res * a) % m;

    e = e / 2;
    a = (a * a) % m;
  }
  return res % m;
}
long long gcd(long long a, long long m)
{
    while (a != 0 && m != 0) {
        if (a > m) {
            a = a % m;
        }
        else m = m % a;
    }
    return a + m;
}
int JacobiSymbol(long long a1, long long p1)
{
  if (p1 < 1 || (p1 % 2 == 0))
    return 10;
  if (gcd(a1, p1) != 1)
    return 0;
  long long a = a1;
  long long p = p1;
  a = a % p;
  long long t = 1;
  while (a != 0) {
    while ((a % 2 == 0)) {
      a = a / 2;
      long long r = p % 8;
      if (r == 3 || r == 5)
        t = -t;
    }
    long long x = p;
    p = a;
    a = x;
    if (a % 4 == 3 && p % 4 == 3)
      t = -t;

    a = a % p;
  }
  if (p == 1)
    return t;
  return 0;
}
int TestSoloveya(long long a)
{
  const int N = 500;
  int res = 1;
  int i;

  for (int i = 0; i < N; i += 1)
  {
    long long k = 1 + rand() % (a - 1);

    if (gcd(a, k) > 1)
    {
      res = 0;
      break;
    }

    long long j = binpow(k, ((a - 1) / 2), a);
    int jacobiSymbol = JacobiSymbol(k, a);
    if (jacobiSymbol < 0)
      j = j - a;

    if (j != jacobiSymbol)
    {
      res = 0;
      break;
    }

  }
  return res;
}

long long F(long long x)
{
    return x * x + 1;
}
long long RhoPollard(long long n)
{
  if (n <= 1)
  {
    return -1;
  }
  if (TestSoloveya(n))
  {
    return -1;
  }
    long long divisor = 1;

        long long x = 1;
        long long y = 1;

        long long difference;
        while (divisor == 1 || divisor == n)
        {
            y = F(y) % n;
            x = F(F(x) % n) % n;
            difference = x - y;
            divisor = gcd(abs(difference), n);    
        }
    

    return divisor;
}


int main(int argc, char* argv[])
{
  int* arr;
  int N;
  fstream file;
  string fileName;
  cin >> fileName;
  file.open(fileName, ios::in);
  file >> N;
  arr = new int[N];
  for (int i = 0; i < N; i++)
    file >> arr[i];
  file.close();
    long long n;
    long start_time = clock();
  for (int i = 0; i < N; i++)
  {
     RhoPollard(arr[i]);
  }
    long end_time = clock();
    long search_time = end_time - start_time;
    cout << "time: " << search_time;
    return 0;
}