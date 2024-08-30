#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

class TreeNode
{
public:
    void SetRoot(TreeNode *root)
    {
        root_ = root;
    }

    int Height()
    {
        return Height(root_);
    }

    int Height(TreeNode *node)
    {
        if (!node) return 0;
        return 1 + std::max(Height(node->left), Height(node->right));
    }

    void Print2D();
    void PrintLevel(int n);
    void DisplayLevel(TreeNode *p, int lv, int d);

    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

protected:
    TreeNode *root_ = nullptr;
};

void TreeNode::Print2D()
{
    using namespace std;
    cout << "Height = " << Height() << endl;
    int i = 0;
    while (i < Height()) {
        PrintLevel(i);
        i++;
        cout << endl;
    }
    cout << endl;
}

void TreeNode::PrintLevel(int n) {
    using namespace std;
    TreeNode *temp = root_;
    int val = (int)pow(2.0, Height() - n + 1.0);
    cout << setw(val) << "";
    DisplayLevel(temp, n, val);
}

void TreeNode::DisplayLevel(TreeNode *p, int lv, int d) {
    using namespace std;
    int disp = 2 * d;
    if (lv == 0) {
        if (p == NULL) {
            cout << "   ";
            cout << setw(disp - 3) << "";
            return;
        }
        else {
            cout << p->val << " ";
            cout << setw(static_cast<streamsize>(disp) - 2) << "";
        }
    }
    else
    {
        if (p == NULL && lv >= 1) {
            DisplayLevel(NULL, lv - 1, d);
            DisplayLevel(NULL, lv - 1, d);
        }
        else {
            DisplayLevel(p->left, lv - 1, d);
            DisplayLevel(p->right, lv - 1, d);
        }
    }
}

TreeNode *InverBT(TreeNode *root)
{
    std::queue<TreeNode *> q;
    q.push(root);

    TreeNode *temp = nullptr;

    while (!q.empty())
    {
        auto node = q.front();
        q.pop();

        if (node->left)
        {
            q.push(node->left);
            temp = node->left;
            node->left = node->right;
        }
        if (node->right)
        {
            q.push(node->right);
            node->right = temp;
        }

    }

    return root;
}

int main()
{
    TreeNode *treeNode5 = new TreeNode(9);
    TreeNode *treeNode4 = new TreeNode(6);
    TreeNode *treeNode3 = new TreeNode(7, treeNode4, treeNode5);
    TreeNode *treeNode8 = new TreeNode(3);
    TreeNode *treeNode6 = new TreeNode(1);
    TreeNode *treeNode2 = new TreeNode(2, treeNode6, treeNode8);
    TreeNode *treeNode1 = new TreeNode(4, treeNode2, treeNode3);

    TreeNode *root = treeNode1;

    root->SetRoot(root);
    root->Print2D();

    root = InverBT(root);
    root->Print2D();
}
