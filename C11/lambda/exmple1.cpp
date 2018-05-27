#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;;

vector<int> nums;

void Add(const int val)
{
    auto print = [&]
    {
        for (auto s : nums)
        {
            cout << s << '\t';
        }
        cout << endl;
    };

    for (auto i = nums.begin(); i != nums.end(); ++i)
    {
        *i = *i + val;
    }
    print();

    for_each(nums.begin(), nums.end(), bind2nd(plus<int>(), val));
    print();

    transform(nums.begin(), nums.end(), nums.begin(),bind2nd(plus<int>(), val));
    print();
    for_each(nums.begin(), nums.end(), [=](int &i)
    {
        i+= val;
    });
    print();
}


int main()
{
    for(int i = 0; i < 10; i++)
    {
        nums.push_back(i);
    }
    Add(10);
    return 1;
}