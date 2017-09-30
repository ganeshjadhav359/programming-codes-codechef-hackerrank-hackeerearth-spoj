#include<bits/stdc++.h>
using namespace std;
int suff[20][100006],lcparray[100006];
long long rank[100006];
struct node
{
	int ind;
	int pr[2];
};
node p[100006];

int  lcp(int x,int y,int st,long long len)
{
	int ret=0;
	for(;st>=0 && x<len && y<len;st--)
	{
		if(suff[st][x]==suff[st][y])
		{
			x+=1<<st;
			y+=1<<st;
			ret+=1<<st;
		}	//cout<<x<<" "<<y<<" " <<ret<< " "<<st<<endl;
	}
	return ret; 	
}
int cmp(node a,node b)
{
	return (a.pr[0]==b.pr[0] ? (a.pr[1] < b.pr[1] ? 1: 0) : (a.pr[0] < b.pr[0] ? 1 : 0));
}
void suffixarray(char a[],long long len)
{
	for(int i=0;i<len;i++)
		suff[0][i]=a[i]-'a';
	int step,cnt;
	for( step=1,cnt=1;cnt<len ;cnt*=2,step++)
	{
		for(int i=0;i<len;i++)
		{
			p[i].pr[0]=suff[step-1][i];
			p[i].pr[1]=i+cnt<len ? suff[step-1][i+cnt]:-1;
			p[i].ind=i;
		}
		sort(p,p+len,cmp);
		for(int i=0;i<len;i++)
		{
			suff[step][p[i].ind]= i>0 &&  p[i-1].pr[0]==p[i].pr[0] && p[i-1].pr[1]==p[i].pr[1] ? suff[step][p[i-1].ind] : i; 
		}
		/*cout<<" tuple for : "<< step <<endl;
		for(int i=0;i<len;i++)
		{
			
			cout<<step<<" "<<p[i].ind<<" "<<suff[step][p[i].ind]<<" " ;
			cout<<endl;	
		}*/
	}
	for(int i=1;i<len;i++)
		lcparray[i]=lcp(p[i-1].ind,p[i].ind,step-1,len);
	lcparray[0]=0;
	/*for(int i=0;i<len;i++)
	{
		
			cout<<lcparray[i]<<" " ;
		
	}*/
	//lcparray[0]=lcp(5,2,step-1,len);
	//cout<<endl;
	//rank[0]=(len-p[0].ind) * (len-p[0].ind+1)/2;
	//cout<<rank[0]<<" ";
	for(int i=0;i<len;i++)
	{
		long long m=(len-p[i].ind);
		long long n=lcparray[i];
		rank[i]=(m*(m+1))/2 - (n*(n+1))/2;
		//cout<<rank[i]<<" ";
	}
	//cout<<endl;
}
void answer(long long k,int len,char a[])
{
	for(int i=0;i<len;i++)
	{
		if(k==rank[i])
		{
			cout<<a[len-1]<<endl;
			break;
		}
		else if(k>rank[i])
			k-=rank[i];
		else
		{
			for(int j=lcparray[i];j<len;j++)
			{
				if(k<=(j+1))
				{
					cout<<a[p[i].ind+k-1]<<endl;
					break;
				}	
				else
				k-=(j+1);
			}
			break;
		}		
		
		
	}
}
int main()
{
   int t;
   cin>>t;
   while(t--)
   {
   	char a[100006];
   	long long k;
   	cin>>a;
   	suffixarray(a,strlen(a));
   	//for(int i=0;i<11;i++)
   	//{
   		cin>>k;
   		answer(k,strlen(a),a);
   	//}	
   }
 return 0; 
}
