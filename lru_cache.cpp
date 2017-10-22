#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#define cache_size (8*1024)
//#define block_size 32					//no of bytes in each block
#define associativity 2

#define M 1000		

using namespace std;

class Line
{
private:
	int valid;
	unsigned long int tag;
	unsigned long int index;
	int count;
public:
	
	void setValidBit()
	{
		this->valid = 1;
	}
	void clearValidBit()
	{
		this->valid = 0;
	}
	int getValid()
	{
		return this->valid;
	}
	void setTag(unsigned long int tag)
	{
		this->tag = tag;
	}
	bool checkTag(unsigned long int tag)
	{
		if(this->tag == tag)
			return true;
		else
			return false;
	}
	void setIndex(unsigned long int index)
	{
		this->index = index;
	}
	unsigned long int getIndex()
	{
		return this->index;
	}
	void setCount(int count)
	{
		this->count = count;
	}
	int getCount()
	{
		return this->count;
	}
	void clearCount()
	{
		this->count = 0;
	}
	void incrementCount()
	{
		this->count++;
	}
};

struct set
{
	Line l[associativity];
};
		
typedef struct set Set;

class Cache
{
private:
	unsigned long int C;	
	int B,E,S,s,b,m,t,hit,miss;
	
	Set *cache;

public:
	int getHit()
	{
		return hit;
	}
	int getMiss()
	{
		return miss;
	}
	int base2(int x)
	{
		int temp=  ceil(log(x) / log(2));
		return temp;
	}

	long power(int base,int exp)
	{
		long i,temp = 1;
		for(i=0;i<exp;i++)
			temp = temp * base;
		return temp;
	}

	long allOnes(int num)
	{
		long res = power(2,num)-1;
		return res;
	}

	Cache(unsigned long int cache_size,int block_size,int add_bits)
	{
		int i,j;
		C = cache_size;
		B = block_size;
		E = associativity;
		S = C / (E*B);
		cache = new Set[S];

		b = base2(B);
		s = base2(S);				//no of bits needed for S
		m = add_bits;
	    
	    t = m - (s + b);

	    clear_status();

	    for(i=0; i < S; i++)

			for(j=0; j<E; j++)
			{
				cache[i].l[j].clearValidBit();
				cache[i].l[j].setCount(j);
			}		

	}
	void clear_status()
	{
		hit =0;
		miss=0;
	}
	void put(unsigned long int address)
	{
		unsigned long int A,ind,tag;			//A is block address
		int valid,present_count,count;
		A = address & allOnes(32);				//taking only 32 bit of the address
		A = A >> b;								//finding block address = input address/2^b
		ind = A & allOnes(s);					//find index = block address % No of sets
		tag =  A >> s;							//find tag = block address / No of sets

		bool found = false;
		for(int i=0; i<associativity;i++)
		{
			valid = cache[ind].l[i].getValid();
			if(valid==0)
			{
				miss++;
				cache[ind].l[i].setValidBit();
				cache[ind].l[i].setIndex(ind);
				cache[ind].l[i].setTag(tag);
				count = cache[ind].l[i].getCount();
				found = true;
				//get block of data from higher memory
				break;
			}
			if(cache[ind].l[i].checkTag(tag))
			{
				hit++;
				count = cache[ind].l[i].getCount();
				found = true;
				break;
			}

		}
		if(found)
		{
			//only need to update counters
			for(int i=0; i<associativity;i++)
			{
				present_count = cache[ind].l[i].getCount();
				if(present_count == count)
					cache[ind].l[i].clearCount();
				else if(present_count < count)
					cache[ind].l[i].incrementCount();
			}
		}
		else
		{
			/*replace the least recently used block which has count as associativity-1*/
			for(int i=0; i<associativity;i++)
			{
				present_count = cache[ind].l[i].getCount();
				if(present_count == associativity-1)
				{
					cache[ind].l[i].clearCount();
					miss++;
					cache[ind].l[i].setValidBit();
					cache[ind].l[i].setIndex(ind);
					cache[ind].l[i].setTag(tag);
					//get block of data from higher memory
				}
				else
					cache[ind].l[i].incrementCount();
				
			}
		}

		/*Now have to realize which line to replace and update counts accordingly to mainatin LRU*/



	}

	bool contains(unsigned long int address)
	{
		unsigned long int A,ind,tag;			//A is block address
		int valid,present_count,count;
		A = address & allOnes(32);				//taking only 32 bit of the address
		A = A >> b;								//finding block address = input address/2^b
		ind = A & allOnes(s);					//find index = block address % No of sets
		tag =  A >> s;							//find tag = block address / No of sets

		bool found = false;
		for(int i=0; i<associativity;i++)
		{
			valid = cache[ind].l[i].getValid();
			if(valid && cache[ind].l[i].checkTag(tag))
			{
				return true;
			}

		}
		return false;
	}

};

static void showUsage(string name)
{
	cerr<<"Usage: " << name << " cache_size "<< " block size"<<endl;
	exit(0);
}

int main(int argc, char const *argv[])
{
	if(argc<3)
		showUsage(argv[0]);

	int i,j,k,B,count;
	unsigned long int input,C;
	float hit_rate,miss_rate;
	C = atoi(argv[1]) * 1024;
	//C = 8 * 1024;
	B = atoi(argv[2]);		
	//B=32;
	Cache *c1 = new Cache(C,B,32);
		
	for(count=0; count < M; count++)
	{
		cin>>hex>>input;
		c1->put(input);
	}

	float hit = c1->getHit();
	float miss = c1->getMiss();
	hit_rate = ( hit / (hit+miss) ) * 100;
	miss_rate = ( miss / (hit+miss) ) * 100;

	cout<<"Hit rate = "<< hit_rate<<endl;
	cout<<"Miss rate = "<< miss_rate<<endl;		
	return 0;
}
