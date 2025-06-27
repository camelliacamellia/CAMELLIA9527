// ʹ��map��¼��ש���λ�ã�map���Զ������Ӧλ�á�
// Ȼ����� map ש���ȡש����ִ���
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

// ��ѽ�
// ������������ai�ж���������п��ܳ������Բ���
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