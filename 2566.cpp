// 使用字符串来处理数字，找到最小最大差值
// 但是devc++无法使用to_string函数，猝
class Solution {
public:
    int minMaxDifference(int num) {
        string nums1 = to_string(num);
        string nums2 = to_string(num);
        int n = nums1.length();
        char a;
        char b = nums1[0];
        for (int i = 0; i < n; i++)
        {
            if (nums1[i] != '9')
            {
                a = nums1[i];
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (nums1[i] == a)
                nums1[i] = '9';
            if (nums2[i] == b)
                nums2[i] = '0';
        }
        return stoi(nums1) - stoi(nums2);
    }
};
// 

// 最佳解大差不差哦
class Solution {
public:
    int minMaxDifference(int num) {
        string max_num = to_string(num), min_num = max_num;
        char max_flag = 'X', min_flag = min_num[0];

        for (auto& ch : max_num) {
            if (ch != '9' && max_flag == 'X')
                max_flag = ch;
            if (max_flag == ch)
                ch = '9';
        }

        for (auto& ch : min_num)
            if (ch == min_flag)
                ch = '0';

        return stoi(max_num) - stoi(min_num);
    }
};