#include <iostream>
#include <queue>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;

const int maxn = 505;
int N, M, s, e;

// nums：每个点人数，d：每个点到原点距离
int nums[maxn], dist[maxn];
// tot:起点到点i最短路的条数， sum:起点到点i人数
int tot[maxn], sum[maxn];
int pre[maxn];
bool vis[maxn];
vector<pair<int, int> > E[maxn];

void dijkstra()
{
    priority_queue<pair<int, int> > Q; // Q.top().first = Q.top()的点到远点的距离（的相反数），Q.top().second是Q.top()的编号
	// 因为pair优先按第一纬排序，所以pair.first需要是dist

	//初始化
    dist[s] = 0;
    Q.push({-dist[s], s});

	// 松弛
    while (!Q.empty())
    {
		// head永远是当前与远点最近的点，每次循环用head来松弛其他点。
		// 每一次用head松弛  与head相连的所有出点

        int head = Q.top().second;// head：当前dist最短的点（距离起始点最近）的点的编号
        Q.pop();
		if (vis[head]) continue;
		vis[head] = 1;
        for (int i = 0; i < E[head].size(); i ++ )
        {
            int v = E[head][i].first;  // 与head相连的边的编号
            int curdist = E[head][i].second;  // 与head相连的边的距起始点的距离

			// 因为head与v相连，所以可以用head   松弛v的dist

			//  与普通最短路的题目不同的是，普通的最短路不需要考虑这种松弛时距离相等的情况
			//  松弛时距离相等：更新可以到达的路径个数，和最大救援数
			//  因为没有更新dist，所以不需要再入队
            if (dist[v] == dist[head] + curdist)
            {
                tot[v] += tot[head];
                sum[v] = max(sum[v], sum[head] + nums[v]);
				pre[v] = head;
            }

			//  可以松弛：更新距离，更新可以到达的路径个数，更新最大救援数
            if (dist[v] > dist[head] + curdist)
            {
                dist[v] = dist[head] + curdist;
                tot[v] = tot[head];
                sum[v] = sum[head] + nums[v];
				pre[v] = head;
                Q.push({-dist[v], v});
            }
        }
    }
}

void output(int x)
{
	vector<int> path;
	for (; x!= -1; x = pre[x])
		path.push_back(x);
	reverse(path.begin(), path.end());
	int n = path.size();
	// PAT的题最后一个空格一定不能加
	// 防止使用size()-1
	for (int i = 0; i < n; i ++) cout << path[i] << " \n"[i==n-1];
}

int main ()
{
	freopen("/Users/zhbink/Documents/C++/C++/in.txt","r",stdin);
    memset(dist, 0x3f, sizeof dist);
	memset(pre, -1, sizeof pre);
    cin >> N >> M >> s >> e;
    for (int i = 0; i < N; i ++ ) cin >> nums[i];
    for (int i = 0; i < M; i ++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        E[a].push_back({b, c});
        E[b].push_back({a, c});
    }
    
    tot[s] = 1;
    sum[s] = nums[s];
    
    dijkstra();

    cout << tot[e] << " " << sum[e] << endl;
	output(e);
    return 0;
}