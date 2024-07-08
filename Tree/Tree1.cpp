#include <iostream>
#include <stack>
#include <queue>

struct Node
{
    int mData;

    Node *mpLeft;
    Node *mpRight;

    Node(int data, Node *pLeft = nullptr, Node *pRight = nullptr)
    {
        mData = data;
        mpLeft = pLeft;
        mpRight = pRight;
    }
};

class BinaryTree
{
private:
    Node *mpRoot;

public:
    BinaryTree() { mpRoot = CreateNode(0); }

    Node *GetRoot() { return mpRoot; }
    Node *CreateNode(int data)
    {
        return new Node(data);
    }

    Node *InsertLeft(Node *parent, int data)
    {
        parent->mpLeft = CreateNode(data);
        return parent->mpLeft;
    }

    Node *InsertRight(Node *parent, int data)
    {
        parent->mpRight = CreateNode(data);
        return parent->mpRight;
    }

    void Visit(Node *pNode) { std::cout << pNode->mData << " "; }

    // n 노드의 개수
    // Time Complexity : O(n)
    // Space Complexity : O(n)
    void BreadthFirst()
    {
        std::queue<Node *> q;
        q.push(mpRoot);

        while (!q.empty())
        {
            auto node = q.front();
            Visit(node);
            q.pop();

            if (node->mpLeft) { q.push(node->mpLeft); }
            if (node->mpRight) { q.push(node->mpRight); }
        }
    }
    
    // Time Complexity : O(n)
    // Space Complexity : O(n)
    void DepthFirst()
    {
        std::stack<Node *> s;
        s.push(mpRoot);

        while (!s.empty())
        {
            auto node = s.top();
            Visit(node);
            s.pop();

            if (node->mpRight)
            {
                s.push(node->mpRight);
            }
            if (node->mpLeft)
            {
                s.push(node->mpLeft);
            }
        }
    }

    // stack -> call stack
    // Time Complexity : O(n)
    // Space Complexity : O(n)
    void DepthFirstR(Node* pNode)
    {
        // base case
        if (pNode == nullptr)
        {
            return;
        }

        // recursive case

        // Pre-Order
        // 1 2 4 5 3 6 7
        Visit(pNode);
        DepthFirstR(pNode->mpLeft);
        DepthFirstR(pNode->mpRight);

        // In-Order
        // 4 2 5 1 6 3 7
        DepthFirstR(pNode->mpLeft);
        Visit(pNode);
        DepthFirstR(pNode->mpRight);

        // Post-Order
        // 4 5 2 6 7 3 1
        DepthFirstR(pNode->mpLeft);
        DepthFirstR(pNode->mpRight);
        Visit(pNode);

    }
};


int main()
{
    BinaryTree myTree;

    auto pRoot = myTree.GetRoot();
    pRoot->mData = 1;

    auto pNode = myTree.InsertLeft(pRoot, 2);
    myTree.InsertLeft(pNode, 4);
    myTree.InsertRight(pNode, 5);

    pNode = myTree.InsertRight(pRoot, 3);
    myTree.InsertLeft(pNode, 6);
    myTree.InsertRight(pNode, 7);

    myTree.BreadthFirst();
    std::cout << std::endl;

    myTree.DepthFirst();
    std::cout << std::endl;

    myTree.DepthFirstR(myTree.GetRoot());
    std::cout << std::endl;


}
