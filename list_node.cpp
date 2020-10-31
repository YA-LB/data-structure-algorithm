/*单向链表*/

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

//指针结构体
typedef struct list_node
{
    int data;//存放数据，数据域
    struct list_node* next;//访问数据节点，遍历，指向下一节点
}list_single;



/*创建链表单个节点*/
list_node *create_node(int data)
{
  //定义一个链表头指针,并分配空间
    list_single * node = (list_single*)malloc(sizeof(list_single));
    if (node == NULL)
    {
        cout << "malloc fail" << endl;
        return NULL;
    }
    memset(node, 0, sizeof(list_single));//清节点数据
    node->data = data;//链表节点赋值
    node->next = NULL;//链表指针域指针指向null
    return node; //返回指针
}

/*单链表尾插*/
//ph:当前指针位置
//newl新指针位置
void tail_insert(list_single* ph, list_single* newl)
{
    list_single* p = ph;//获取当前节点
    while (p->next!= NULL)
    {     
        p = p->next;//p指向下面的节点
    }
    p->next = newl;
}


//单链表头插
//插入到当前节点的和其指向下一节点的中间
void top_insert(list_single* ph, list_single* newl)
{
    list_single* p = ph;
    newl->next = p->next;
    p->next = newl;
}

//链表遍历
void scan_list(list_single* ph)
{
    list_single* p = ph;//获取当前位置
    p = p->next;//获取第一节点的位置
    //下一节点不为空
    while (p->next!=NULL)
    {
        cout << "data:"<<p->data << endl;
        p = p->next;//指向下一节点
    }
    //如果没有循环，证明是尾节点
    cout << "data:" << p->data << endl;
}

//删除指针
int delete_list_node(list_node* ph, int data)
{
    list_single* p = ph;//获取当前节点位置
    list_single* prev = NULL;//定义一个结构体指针保存当前节点的上一节点的指针
    while (NULL != p->next)
    {
        prev = p;//保存当前节点的前一节点的指针
        p = p->next;//指针后移
        if (p->data = data)
        {
            //普通节点的情况
            if (NULL != p->next)
            {
                prev->next = p->next;
                free(p);
            }
            else
            {
                prev->next = NULL;
                free(p);
            }
            return 0;
        }
    }
    cout << "this data are not exist!" << endl;
    return -1;

}
int main(void)
{
    int data = 100;
    list_single* newnode = create_node(data);
    cout << "newnode->data=" << newnode->data << endl;
    cout << "newnode->next=" << newnode->next << endl;
    free(newnode);
    return 0;
}

