#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *MergeTwoList(ListNode *list1, ListNode *list2)
{
    ListNode *plist1{ list1 };
    ListNode *plist2{ list2 };
    ListNode *plist1_next{ list1->next };
    ListNode *plist2_next{ list2->next };

    while (plist1 != nullptr && plist2 != nullptr)
    {
        if (plist2 != nullptr)
        {
            plist1->next = plist2;
            plist1 = plist1_next;
            if (plist1 != nullptr) plist1_next = plist1->next;
        }

        if (plist1 != nullptr)
        {
            plist2->next = plist1;
            plist2 = plist2_next;
            if (plist2 != nullptr) plist2_next = plist2->next;
        }
    }

    return list1;
}

ListNode *MergeTwoList2(ListNode *list1, ListNode *list2)
{
    auto p1 = list1;
    auto p2 = list2;

    ListNode *temp = new ListNode();
    auto head = temp;

    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->val < p2->val)
        {
            temp->next = p1;
            p1 = p1->next;
        }
        else
        {
            temp->next = p2;
            p2 = p2->next;
        }
        temp = temp->next;
    }

    if (p1 == nullptr)
    {
        temp->next = p2;
    }
    else
    {
        temp->next = p1;
    }

    return head->next;
}

int main()
{

    ListNode list1;
    ListNode list2(1);

    ListNode *print = MergeTwoList(&list1, &list2);
    while (print != nullptr)
    {
        std::cout << print->val;
        print = print->next;
    }
}
