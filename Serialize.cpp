#include <iostream>
#include <queue>
#include <string>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
   
class Codec
{
public:
    std::string Serialize(TreeNode * root)
    {
        if (!root)
        {
            return {};
        }

        std::string answer = "";
        std::queue<TreeNode *> s;
        s.push(root);
        answer += std::to_string(root->val) + ' ';

        while (!s.empty())
        {
            TreeNode *current = s.front();
            s.pop();


            if (current->left)
            {
                s.push(current->left);
                answer += std::to_string(current->left->val) + ' ';
            }
            if (current->right)
            {
                s.push(current->right);
                answer += std::to_string(current->right->val) + ' ';
            }
            if (!current->left)
            {
                answer += "n ";
            }
            if (!current->right)
            {
                answer += "n ";
            }
        }

        return answer;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
