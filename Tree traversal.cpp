#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//�������Ľṹ��.
 struct TreeNode
 {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}//��ʼ��
 }

class Traversal
{
public:
       /*
	   
         ��Ϊ�ȷ��ʸ��ڵ㣬����ֱ�ӽ�root��val����𰸣�ans������
         ����stack������root��
         ���������������ȡ��root���ű�����������
       */
      vector<int> preorderTraversal(TreeNode* root)
	{
        std::stack<TreeNode*> stack;
        vector<int> ans;
        while(root != NULL || !stack.empty()) 
		{
            while(root != NULL) 
			{
                stack.push(root);
                ans.push_back(root->val);
                root = root->left;
            }
            root = stack.top();
            stack.pop();
            root = root->right;
        }
        return ans;
    }


    vector<int> inorderTraversal(TreeNode* root) 
	{
        vector<int> res;
        stack<TreeNode*> stack;
        //s.push(root);
        while(root || s.size() > 0)
		{
            while(root)
			{
                stack.push(root);
                root = root->left;
            }
            root = stack.top(); 
            stack.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }


/*�ȱ�����ڵ�ֱ����ڵ�Ϊnull��
��ʼ�����ҽڵ㣬�����ҽڵ�����ڵ㣬���ȱ�����ڵ㡣
ʹ��rightchild����¼�ҽڵ��Ƿ��ѱ���������
���ǣ���˵���Ըõ�Ϊ���������ѱ�������������ڵ㡣���񣺾Ϳ�ʼ�����ҽڵ㣬�ص��ڶ�����
*/

	vector<int> postorderTraversal(TreeNode* root)
	{
        vector<int> ans;
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        TreeNode* rightchild = NULL;
        while(cur || !stk.empty())
		{
            while(cur != NULL)
			{
                stk.push(cur);
                cur = cur -> left;
            }
            cur = stk.top();
            if(!cur -> right|| rightchild == cur -> right)
			{
                ans.push_back(cur -> val);
                stk.pop();
                rightchild = cur;
                cur = NULL;
            }
            else
			{
                rightchild = NULL;
                cur = cur -> right;
            }
        }
        return ans;
    }
}



