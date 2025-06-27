// 使用map记录有砖缝的位置，map会自动添加相应位置。
// 然后遍历 map 砖缝获取砖缝出现次数
class Solution {
public:
	int leastBricks(vector<vector<int>>& wall) {
		map<long long, int>ans;
		int n = wall.size();
		for (int i = 0; i < n; i++)
		{
			long long num = 0;
			for (int j = 0; j < wall[i].size() - 1; j++)
			{
				num += wall[i][j];
				ans[num]++;
			}
		}
		int maxx = 0;
		for (auto it : ans)
		{
			if (it.second >= maxx)
				maxx = it.second;
		}
		return n - maxx;
	}
};

// 最佳解
// 看不懂，而且ai判断这个代码有可能出错，所以不管
class Solution {
public:
    priority_queue<int, vector<int>, greater<int>> que;
    int leastBricks(vector<vector<int>>& wall) {
        int m = wall.size();
        int n = wall[0].size();
        if (m == 1) {
            if (n == 1) {
                return 1;
            }
            return 0;
        }
        for (int i = 0; i < m; i++) {
            int sum = 0;
            for (int j = 0; j < wall[i].size() - 1; j++) {
                sum += wall[i][j];
                que.push(sum);
            }
        }
        int pre = -1;
        int ans = 0;
        int curr = 0;
        while (!que.empty())
        {
            int node = que.top();
            que.pop();
            if (node != pre) {
                ans = max(ans, curr);
                curr = 0;
            }
            curr++;
            pre = node;
        }
        ans = max(ans, curr);
        return m - ans;
    }
};