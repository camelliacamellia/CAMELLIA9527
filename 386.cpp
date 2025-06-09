// 字典排序，使用sort+lambda实现一个按字典排序的函数自动对向量排序，就是效率不太高
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int>ans(n);
        for(int i = 0 ; i< n ; i++)
        {
            ans[i] = i+1;
        }
        sort(ans.begin(),ans.end(),[](int a,int b){return to_string(a)<to_string(b);});      //lambda实现排序
        return ans;
    }
};
