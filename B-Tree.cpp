// C++ʵ�ֵ������ͱ�������
#include<iostream>
using namespace std;
 
// һ��B���Ľڵ�
class BTreeNode
{
    int *keys;     // �ؼ�������
    int t;         // ��С�� (�����˽ڵ�ؼ��ֵ���������)
    BTreeNode **C; // �ڵ��Ӧ���ӽڵ������ָ��
    int n;         // �ڵ㵱ǰ�Ĺؼ�������
    bool leaf;     // ���ڵ���Ҷ�ӽڵ��ʱ��Ϊtrue ����Ϊfalse
public:
    BTreeNode(int _t, bool _leaf);   // ���캯��
 
    // ���������Ըýڵ�Ϊ���������Ĺؼ���
    void traverse();
 
    // ��ѯһ���ؼ������Ըýڵ�Ϊ����������    
    BTreeNode *search(int k);   // ����NULL�������ؼ���û�б��ҵ�
 
    // ʹBTree��Ϊ�ýڵ����Ԫ��,ʹ�����ܹ�����BTree���˽�г�Ա
friend class BTree;
};
 
// B��
class BTree
{
    BTreeNode *root; // ���ڵ�ָ��
    int t;  //��С��
public:
    // ���캯�� (��ʼ��һ������)
    BTree(int _t)
    {  root = NULL;  t = _t; }
 
    // ���������ķ���
    void traverse()
    {  if (root != NULL) root->traverse(); }
 
    // �����в�ѯ�ؼ���
    BTreeNode* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }
};
 
// BTreeNode��Ĺ��췽��
BTreeNode::BTreeNode(int _t, bool _leaf)
{
    // ���Ʋ����е���С�����Լ�Ҷ�Ӳ���ֵ
    t = _t;
    leaf = _leaf;
 
    // ����ڵ���Դ�Źؼ��ֵ�����ڴ棬�Լ�����ָ��
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
 
    // ��ʼ���ڵ��ڲ��ĺ�����Ŀ
    n = 0;
}
 
// ����������ڵ�Ϊ�������������ϵĹؼ���
void BTreeNode::traverse()
{
    // �ڵ��ڹ���n���ؼ���,n+1������
    int i;
    for (i = 0; i < n; i++)
    {
        // ����ýڵ㲻��Ҷ�ӽڵ㣬�ڴ�ӡ�ؼ���֮ǰ�������ӽڵ�
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
 
    // ��ӡ���һ�������ϵ����нڵ�
    if (leaf == false)
        C[i]->traverse();
}
 
// ����������ڵ�Ϊ�����ϵĹؼ����Ƿ���k
BTreeNode *BTreeNode::search(int k)
{
    // ��

���ڵ��ϵ�һ������k��Ĺؼ���
    int i = 0;
    while (i < n && k > keys[i])
        i++;
 
    // ����ҵ��Ĺؼ��ֵ���k,����
    if (keys[i] == k)
        return this;
 
    // ���û���ҵ�k�ұ��ڵ���Ҷ�ӽڵ㣬�򷵻�NULL
    if (leaf == true)
        return NULL;
 
    // ����Ӧָ���Ӧ����������Ѱ
    return C[i]->search(k);
}

oid BTree::insert(int k)
{
    // �ж����ǲ��ǿյ�
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
 
//����ǿսڵ�
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
 
// ������
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
