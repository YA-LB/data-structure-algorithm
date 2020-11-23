// C++实现的搜索和遍历方法
#include<iostream>
using namespace std;
 
// 一个B树的节点
class BTreeNode
{
    int *keys;     // 关键字数组
    int t;         // 最小度 (定义了节点关键字的数量限制)
    BTreeNode **C; // 节点对应孩子节点的数组指针
    int n;         // 节点当前的关键字数量
    bool leaf;     // 当节点是叶子节点的时候为true 否则为false
public:
    BTreeNode(int _t, bool _leaf);   // 构造函数
 
    // 遍历所有以该节点为根的子树的关键字
    void traverse();
 
    // 查询一个关键字在以该节点为根的子树上    
    BTreeNode *search(int k);   // 返回NULL如果这个关键字没有被找到
 
    // 使BTree成为该节点的友元类,使我们能够访问BTree类的私有成员
friend class BTree;
};
 
// B树
class BTree
{
    BTreeNode *root; // 根节点指针
    int t;  //最小度
public:
    // 构造函数 (初始化一个空树)
    BTree(int _t)
    {  root = NULL;  t = _t; }
 
    // 遍历该树的方法
    void traverse()
    {  if (root != NULL) root->traverse(); }
 
    // 在树中查询关键字
    BTreeNode* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }
};
 
// BTreeNode类的构造方法
BTreeNode::BTreeNode(int _t, bool _leaf)
{
    // 复制参数中的最小度数以及叶子布尔值
    t = _t;
    leaf = _leaf;
 
    // 分配节点可以存放关键字的最大内存，以及孩子指针
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
 
    // 初始化节点内部的孩子数目
    n = 0;
}
 
// 遍历以这个节点为跟的所有子树上的关键字
void BTreeNode::traverse()
{
    // 节点内共计n个关键字,n+1个孩子
    int i;
    for (i = 0; i < n; i++)
    {
        // 如果该节点不是叶子节点，在打印关键字之前，遍历子节点
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
 
    // 打印最后一棵子树上的所有节点
    if (leaf == false)
        C[i]->traverse();
}
 
// 查找以这个节点为树根上的关键字是否有k
BTreeNode *BTreeNode::search(int k)
{
    // 找

到节点上第一个不比k大的关键字
    int i = 0;
    while (i < n && k > keys[i])
        i++;
 
    // 如果找到的关键字等于k,返回
    if (keys[i] == k)
        return this;
 
    // 如果没有找到k且本节点是叶子节点，则返回NULL
    if (leaf == true)
        return NULL;
 
    // 从相应指针对应的子树上搜寻
    return C[i]->search(k);
}

oid BTree::insert(int k)
{
    // 判断树是不是空的
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
    }
    else 
    {
        if (root->n == 2*t-1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}
 
//插入非空节点
void BTreeNode::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = n-1;
 
    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
 
        // Insert the new key at found location
        keys[i+1] = k;
        n = n+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;
 
        // See if the found child is full
        if (C[i+1]->n == 2*t-1)
        {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);
 
            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}
 
// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
 
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
 

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
    y->n = t - 1;
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    C[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];
    n = n + 1;
}
 
// 主函数
int main()
{
    BTree t(3); 
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
 
    cout << "Traversal of the constucted tree is ";
    t.traverse();
    int k = 6;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    k = 15;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    return 0;
}
