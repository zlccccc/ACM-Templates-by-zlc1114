#include<cstdio>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbtree;

/*
����һ�ź����
int �ؼ�������
null_type��ӳ��(�Ͱ汾g++Ϊnull_mapped_type)
less<int>��С��������
rb_tree_tag �������splay_tree_tag��
tree_order_statistics_node_update������
����t.insert();
ɾ��t.erase();
Rank:t.order_of_key();
��Kֵ:t.find_by_order();
ǰ��:t.lower_bound();
���t.upper_bound();
a.join(b)b����a ǰ������������key��ȡֵ��Χ���ཻ
a.split(v,b)keyС�ڵ���v��Ԫ������a�����������b
T.lower_bound(x)   >=x��min�ĵ�����
T.upper_bound((x)  >x��min�ĵ�����
T.find_by_order(k) ��k��������С����
*/

rbtree T;
rbtree::iterator it;
int main() {
    T.insert(1);
    T.insert(2);
    for(int v:T) printf("%d",v);
}
