#include<cstdio>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbtree;

/*
定义一颗红黑树
int 关键字类型
null_type无映射(低版本g++为null_mapped_type)
less<int>从小到大排序
rb_tree_tag 红黑树（splay_tree_tag）
tree_order_statistics_node_update结点更新
插入t.insert();
删除t.erase();
Rank:t.order_of_key();
第K值:t.find_by_order();
前驱:t.lower_bound();
后继t.upper_bound();
a.join(b)b并入a 前提是两棵树的key的取值范围不相交
a.split(v,b)key小于等于v的元素属于a，其余的属于b
T.lower_bound(x)   >=x的min的迭代器
T.upper_bound((x)  >x的min的迭代器
T.find_by_order(k) 有k个数比它小的数
*/

rbtree T;
rbtree::iterator it;
int main() {
    T.insert(1);
    T.insert(2);
    for(int v:T) printf("%d",v);
}
