#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fe first 
#define se second 
const int ele=1000005;
typedef vector<int> vi;
typedef long long ll;
int isprime[ele],sp[ele],a[100005];

struct node
{
 vi fac;
 vi prefix;
 vi count;
};
node tree[400000];

void merge(int pos)
{
	int l=(pos<<1)+1;
	int r=(pos<<1)+2;
	int n=tree[l].fac.size();
	int m=tree[r].fac.size();
	int p=0,q=0,presum=0;
	while(p<n && q<m)
	{
		if(tree[l].fac[p] < tree[r].fac[q])
		{
			tree[pos].fac.pb(tree[l].fac[p]);
			presum+=tree[l].count[p];
			tree[pos].count.pb(tree[l].count[p]);
			tree[pos].prefix.pb(presum);
			p++;
		}	
		else if(tree[l].fac[p] > tree[r].fac[q])
		{
			tree[pos].fac.pb(tree[r].fac[q]);
			presum+=tree[r].count[q];
			tree[pos].count.pb(tree[r].count[q]);
			tree[pos].prefix.pb(presum);
			q++;
		}
		else 
		{
			tree[pos].fac.pb(tree[r].fac[q]);
			presum+=(tree[r].count[q]+tree[l].count[p]);
			tree[pos].count.pb(tree[r].count[q]+tree[l].count[p]);
			tree[pos].prefix.pb(presum);
			q++;
			p++;
		}
		
	}
	
	while(p<n)
	{
			tree[pos].fac.pb(tree[l].fac[p]);
			presum+=tree[l].count[p];
			tree[pos].count.pb(tree[l].count[p]);
			tree[pos].prefix.pb(presum);
			p++;
	}
	
	while(q<m)
	{
			tree[pos].fac.pb(tree[r].fac[q]);
			presum+=tree[r].count[q];
			tree[pos].count.pb(tree[r].count[q]);
			tree[pos].prefix.pb(presum);
			q++;
	}
}
void buildsegtree(int l,int r,int pos)
{
	if(l==r)
	{
		int s=a[l];
		int pre=sp[s],cnt=0,cnt1=0;
		s/=sp[s];
		while(s!=1)
		{	cnt++;
		        cnt1++;
			if(sp[s]==pre)
			{
				
				s/=sp[s];
			}
			else
			{
				tree[pos].fac.pb(pre);
				tree[pos].prefix.pb(cnt);
				tree[pos].count.pb(cnt1);
				cnt1=0;
				pre=sp[s];
				s/=sp[s];
			}
		}
		
		tree[pos].fac.pb(pre);
		tree[pos].prefix.pb(++cnt);
		tree[pos].count.pb(++cnt1);
		/*for(int i=0;i<tree[pos].fac.size();i++)
		{
			cout<<tree[pos].fac[i]<<" "<<tree[pos].prefix[i]<<endl;
		}*/
	}
	else
	{
		int mid=(l+r)/2;
		buildsegtree(l,mid,2*pos+1);
		buildsegtree(mid+1,r,2*pos+2);
		merge(pos);
		/*for(int i=0;i<tree[pos].fac.size();i++)
		{
			cout<<tree[pos].fac[i]<<" "<<tree[pos].prefix[i]<<endl;
		}*/
	}
}

int query(int s,int e,int pos,int l,int r,int x,int y)
{
	if(e<l || r<s)
	  return 0;
	else if(s>=l && e<=r)
	{
		int low=lower_bound(tree[pos].fac.begin(),tree[pos].fac.end(),x)-tree[pos].fac.begin();
		int up=upper_bound(tree[pos].fac.begin(),tree[pos].fac.end(),y)-tree[pos].fac.begin();
		if(!(up))
			return 0;
		else if(!(low))
		 return(tree[pos].prefix[up-1]-0);
		else
		 return (tree[pos].prefix[up-1]-tree[pos].prefix[low-1]); 
	}
	
	int mid=(s+e)/2;
	int p=query(s,mid,2*pos+1,l,r,x,y);	  	
	int q=query(mid+1,e,2*pos+2,l,r,x,y);
	return(p+q);
}

int main()
{	for(int i=0;i<ele;i++)
		isprime[i]=0;
	for(int i=2;i<=ele;i+=2)
		sp[i]=2,isprime[i]=1;
			
	for(int i=3;i<ele;i+=2)
	{
		if(!isprime[i])
		{	sp[i]=i;
			for(int j=i+i;j<ele;j+=i)
			{
				if(!isprime[j])
				{
					sp[j]=i;
					isprime[j]=1;
				}
			}
		}
	}
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	buildsegtree(0,n-1,0);
	
	int q;
	cin>>q;
	/*for(int i=0;i<tree[0].fac.size();i++)
	{
		cout<<tree[0].fac[i]<<" "<<tree[0].prefix[i]<<endl;
	}*/
	for(int i=0;i<q;i++)
	{
		int y,x,l,r;
		cin>>l>>r>>x>>y;
		int ans=query(0,n-1,0,l-1,r-1,x,y);
		cout<<ans<<endl;
	}
return 0;
}
