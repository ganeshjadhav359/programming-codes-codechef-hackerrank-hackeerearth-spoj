#include<bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i,n) for(i=0;i<n;i++)
#define Fo(i,k,n) for(i=k;k<n?i<n:i>n;k<n?i+=1:i-=1)
#define ll long long
#define si(x)	scanf("%d",&x)
#define sl(x)	scanf("%lld",&x)
#define ss(s)	scanf("%s",s)
#define pi(x)	printf("%d\n",x)
#define pl(x)	printf("%lld\n",x)
#define ps(s)	printf("%s\n",s)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for(auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
typedef pair<int, int>	pii;
typedef pair<ll, ll>	pl;
typedef vector<int>		vi;
typedef vector<ll>		vl;
typedef vector<pii>		vpii;
typedef vector<pl>		vpl;
typedef vector<vi>		vvi;
typedef vector<vl>		vvl;
#define N 10100
vi adj[N],cost[N],indx[N];
int p[14][N],subtree[N],depth[N],barray[N],chainNo,chainhead[N],posInbasearr[N],
nodechainNo[N],ptr,otherend[N],st[6*N],ans1;
void make_tree(int s,int e,int pos)
{
	if(s==e)
		st[pos]=barray[s];
	else
	{
		int mid=(s+e)/2;
		make_tree(s,mid,2*pos+1);
		make_tree(mid+1,e,2*pos+2);
		st[pos]=st[2*pos+1] > st[2*pos+2] ? st[2*pos+1] : st[2*pos+2];
	}	
}
int query1(int s,int e,int pos,int l,int r)
{
	if(s>=l && e<=r)
		return st[pos];
	else if(l>e || s>r)
		return 0;
	else
	{
		int mid=(s+e)/2;
		//pos=(pos<<1);
		int lt=query1(s,mid,2*pos+1,l,r);
		int rt=query1(mid+1,e,2*pos+2,l,r);
		return (lt>rt ? lt : rt);
	}	
				
}
void update(int s,int e,int pos ,int loc,int val)
{
	if(s==e)
		st[pos]=val;
	else
	{
		//pos=(pos<<1);
		int mid=(s+e)>>1;
		if(loc<=mid)
			update(s,mid,2*pos+1,loc,val);
		else
			update(mid+1,e,2*pos+2,loc,val);
		st[pos]=st[2*pos+1]>st[2*pos+2] ? st[2*pos+1] : st[2*pos+2];		
	}	
		
}
void query(int u,int v)
{
	//int lc=lca(u,v);
	while(1)
	{
		if(nodechainNo[u]!=nodechainNo[v])
		{
			int ans=query1(0,ptr-1,0,posInbasearr[chainhead[nodechainNo[u]]],posInbasearr[u]);
			//cout<<"first "<<u<<" "<<v<<" "<<ans<<endl;
			u=p[0][chainhead[nodechainNo[u]]];
			if(ans>ans1)
				ans1=ans;
		}
		else if(u==v)
			break;
		else
		{
			int ans=query1(0,ptr-1,0,posInbasearr[v]+1,posInbasearr[u]);
			//cout<<"last "<<u<<" "<<v<<" "<<ans<<endl;
			if(ans>ans1)
				ans1=ans;
			break;	
		}
	
	}
	

}
void hld(int node,int Ncost,int parent)
{
	if(chainhead[chainNo]==-1)
		chainhead[chainNo]=node;
	nodechainNo[node]=chainNo;
	posInbasearr[node]=ptr;
	barray[ptr++]=Ncost;
	int sc=-1,ct,sz=-1;
	for(int i=0;i<adj[node].size();i++)	
		if(adj[node][i]!=parent)
			if(subtree[adj[node][i]]>sz)
			{
				sz=subtree[adj[node][i]];
				sc=adj[node][i];
				ct=cost[node][i];
			}
	if(sc!=-1)	
		hld(sc,ct,node);
	for(int i=0;i<adj[node].size();i++)
	{
		if(adj[node][i]!=parent && adj[node][i]!=sc)
		{
			chainNo++;
			hld(adj[node][i],cost[node][i],node);
		}	
		
	}	
}
void dfs(int curnode,int parent,int depthn=0)
{
	p[0][curnode]=parent;
	subtree[curnode]=1;
	depth[curnode]=depthn;
	for(int i=0;i<adj[curnode].size();i++)
	{
		if(adj[curnode][i]!=parent)
		{
			otherend[indx[curnode][i]]=adj[curnode][i];
			dfs(adj[curnode][i],curnode,depthn+1);
			subtree[curnode]+=subtree[adj[curnode][i]];
		}
	
	}
}
int lca(int u,int v)
{
	//cout<<u<<" "<<v<<endl;
	if(depth[v]>depth[u])
		swap(u,v);
	int diff=depth[u]-depth[v];
	for(int i=0;i<14;i++)
		if((diff>>i) & 1)
			u=p[i][u];
	if(u==v)
		return u;
	for(int i=13;i>=0;i--)
		if(p[i][u]!=p[i][v])
		{
			u=p[i][u];
			v=p[i][v];
		}		
return p[0][u];				
}
int main()
{
int t;
si(t);
while(t--)
{
	int n;
	si(n);
	for(int i=0;i<n;i++)
	{
		adj[i].clear();
		cost[i].clear();
		chainhead[i]=-1;
		indx[i].clear();
		for(int j=0;j<14;j++)
			p[j][i]=-1;
	}
	for(int i=0;i<n-1;i++)
	{
		int u ,v,c;
		si(u);
		si(v);
		si(c);
		--u,--v;
		adj[u].pb(v);
		cost[u].pb(c);
		indx[u].pb(i);
		adj[v].pb(u);
		cost[v].pb(c);
		indx[v].pb(i);
	}
	chainNo=0;
	ptr=0;
	dfs(0,-1);
	hld(0,-1,-1);
	/*cout<<"id  "<<" "; 
	for(int i=0;i<n;i++)
		cout<<i<<" ";
	cout<<endl;	*/
	
	for(int j=1;j<14;j++)
		for(int i=0;i<n;i++)
			if(p[j-1][i]!=-1)
				p[j][i]=p[j-1][p[j-1][i]];
				
	make_tree(0,ptr-1,0);			
	/*for(int j=0;j<14;j++)
	{
		cout<<j<<"th ";
		for(int i=0;i<n;i++)
			//if(p[j-1][i]!=-1)
				cout<<p[j][i]<<" ";
		cout<<endl;		
	}*/	
	/*for(int i=0;i<=chainNo;i++)
		cout<<chainhead[i]<<" ";
	cout<<endl;	
	for(int i=0;i<ptr;i++)
		cout<<nodechainNo[i]<<" ";
	cout<<endl;	
	for(int i=0;i<ptr;i++)
		cout<<posInbasearr[i]<<" ";
	cout<<endl;
	for(int i=0;i<ptr;i++)
		cout<<barray[i]<<" ";
	cout<<endl;*/	
			/*int u,v;
			si(u);
			si(v);
			ans1=0;
			
			int lc=lca(--u,--v);
			cout<<lc<<endl;
			query(u,lc);
			query(v,lc);
			pi(ans1);*/				
	//int q;
	//cin>>q;
	/*int id,val;
	si(id);
	si(val);
	cout<<posInbasearr[otherend[id-1]]<<endl;
	update(0,ptr-1,0,posInbasearr[otherend[id-1]],val);*/
	char s[100];
	while(1)
	{
		ss(s);
		if(s[0]=='C')
		{
			int id,val;
			si(id);
			si(val);
			update(0,ptr-1,0,posInbasearr[otherend[id-1]],val);
		}
		else if(s[0]=='Q')
		{	
			int u,v;
			si(u);
			si(v);
			ans1=0;
			int lc=lca(--u,--v);
			query(u,lc);
			query(v,lc);
			pi(ans1);
		}
		else
			break;	
		
	}

}
return 0;
}
