#include<stdio.h>
#include<conio.h>
#include<process.h>
#define INFINITY 9999
#define MAX 20

void dijkstra(int G[MAX][MAX],int n,int startnode);
int G[MAX][MAX],spanning[MAX][MAX],n;
int prims();

void main()
{
	int i,j,total_cost;
	int G[MAX][MAX],n,u;
	int ch;
	clrscr();
	printf("________________________________________________________________________________");
	printf("\n\tPROGRAM FOR COMPUTING SHORTEST PATH AND MINIMUM SPANNING TREE IN A GRAPH");
	printf("________________________________________________________________________________");
	printf("\n\n1.Dijkstra algorithm for computing shortest path in a graph");
	printf("\n2.Prim's algorithm for minimum spanning tree of a graph");
	printf("\n3.Exit");
	do
	{
	printf("\n\nEnter your choice(1-3):");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1: //for dijkstra
			printf("\n\nEnter no. of vertices:");
			scanf("%d",&n);
			printf("\nEnter the adjacency matrix:\n");
			for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				scanf("%d",&G[i][j]);

			printf("\nEnter the starting node:");
			scanf("%d",&u);
			dijkstra(G,n,u);
			break;

		case 2: //FOR PRIM'S
			printf("\nEnter no. of vertices:");
			scanf("%d",&n);
			printf("\nEnter the adjacency matrix:\n");
			for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				scanf("%d",&G[i][j]);

			total_cost=prims();
			printf("\nspanning tree matrix:\n");
			for(i=0;i<n;i++)
			{
				printf("\n");
				for(j=0;j<n;j++)
				printf("%d\t",spanning[i][j]);
			}

			printf("\n\nTotal cost of spanning tree=%d",total_cost);
			break;

		case 3: exit(0);
			break;

		default: printf("\nWrong choice!!");
			 break;
	}
	}while(ch!=0);
	getch();
}

void dijkstra(int G[MAX][MAX],int n,int startnode)
{

	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];

	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	count=1;

	while(count<n-1)
	{
		mindistance=INFINITY;

		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}

			//check if a better path exists through nextnode
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}

	//print the path and distance of each node
	for(i=0;i<n;i++)
		if(i!=startnode)
		{
			printf("\nDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);

			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=startnode);
	}
}
int prims()
{
	int cost[MAX][MAX];
	int u,v,min_distance,distance[MAX],from[MAX];
	int visited[MAX],no_of_edges,i,min_cost,j;

	//create cost[][] matrix,spanning[][]
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
				spanning[i][j]=0;
		}

	//initialise visited[],distance[] and from[]
	distance[0]=0;
	visited[0]=1;

	for(i=1;i<n;i++)
	{
		distance[i]=cost[0][i];
		from[i]=0;
		visited[i]=0;
	}

	min_cost=0;		//cost of spanning tree
	no_of_edges=n-1;		//no. of edges to be added

	while(no_of_edges>0)
	{
		//find the vertex at minimum distance from the tree
		min_distance=INFINITY;
		for(i=1;i<n;i++)
			if(visited[i]==0&&distance[i]<min_distance)
			{
				v=i;
				min_distance=distance[i];
			}

		u=from[v];

		//insert the edge in spanning tree
		spanning[u][v]=distance[v];
		spanning[v][u]=distance[v];
		no_of_edges--;
		visited[v]=1;

		//updated the distance[] array
		for(i=1;i<n;i++)
			if(visited[i]==0&&cost[i][v]<distance[i])
			{
				distance[i]=cost[i][v];
				from[i]=v;
			}

		min_cost=min_cost+cost[u][v];
	}

	return(min_cost);
}






/*int main()
{
	int i,j,total_cost;
	printf("Enter no. of vertices:");
	scanf("%d",&n);

	printf("\nEnter the adjacency matrix:\n");

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);

	total_cost=prims();
	printf("\nspanning tree matrix:\n");

	for(i=0;i<n;i++)
	{
		printf("\n");
		for(j=0;j<n;j++)
			printf("%d\t",spanning[i][j]);
	}

	printf("\n\nTotal cost of spanning tree=%d",total_cost);
	return 0;
}
*/
