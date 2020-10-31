#include <iostream>




using namespace std;

typedef struct double_list_node
{
	int data;
	double_list_node* next;
	double_list_node* reve;
} DL;


/*创建一个节点*/
DL* Create_node(int data)
{
	DL* double_node = (DL*)malloc(sizeof(double_node));
	if (double_node == NULL)
	{
		cout << "malloc fail for double_node" << endl;
	}
	memset(double_node, 0, sizeof(double_node));
	double_node->data = data;
	double_node->next = NULL;
	double_node->reve = NULL;
	return double_node;
}



/*链表插入节点*/
void insert_node(DL* ph, DL *NEW)
{
	DL* p = ph;
    NEW->next=p->next;
	p->next = NEW->reve;
}

/*双链表尾插*/
void tail_insert_node(DL *ph,DL* new_node)
{
	DL* p = ph;
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = new_node->reve;
	new_node->next = NULL;
}


/*后向遍历*/
void Scan_node(DL* ph)
{
	DL* p = ph;
	while (p->next != NULL)
	{
		cout << p->next << endl;
	}
}


/*前向遍历*/
void Scan_node(DL* ph)
{
	DL* p = ph;
	while (p->reve != NULL)
	{
		cout << p->reve<< endl;
		p = p->reve;
	}
}

/*查找元素*/
int find_data(DL* ph, int data)
{
	DL* p = ph;
	if (p->data = data)
	{
		cout << "find the data" << endl;
		return 1;
	}
	else if (p->next != NULL)
	{
		p = p->next;
		while (p->data = data)
		{
			cout << "find the data" << endl;
			return 1;
		}
	}
	else
		p = ph;
	if (p->reve!= NULL)
	{
		p = p->reve;
		while (p->data = data)
		{
			cout << "find the data" << endl;
			return 1;
		}
	}
	cout << "find the data" << endl;
	return 0;
}