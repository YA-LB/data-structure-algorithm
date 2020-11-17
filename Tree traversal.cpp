#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//定义树的结构体.
 struct TreeNode
 {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}//初始化
 }

class Traversal
{
public:
       /*
	   
         因为先访问根节点，所以直接将root的val放入答案（ans）容器
         利用stack来储存root。
         当左子树遍历完后，取出root接着遍历右子树。
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


/*先遍历左节点直到左节点为null。
开始遍历右节点，若该右节点有左节点，优先遍历左节点。
使用rightchild来记录右节点是否已被遍历过。
若是：则说明以该点为根的子树已被遍历，输出根节点。若否：就开始遍历右节点，回到第二步。
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



