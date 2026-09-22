#include <iostream>
#include <stdexcept>

struct ListNode {
    int data;
    ListNode* next;

    explicit ListNode(int value) : data(value), next(nullptr) {}
};

// 只遍历链表一趟，返回值最大的结点。
ListNode* findMaxNode(ListNode* head) {
    if (head == nullptr) {
        return nullptr;
    }

    ListNode* maxNode = head;
    for (ListNode* current = head->next; current != nullptr;
         current = current->next) {
        if (current->data > maxNode->data) {
            maxNode = current;
        }
    }

    return maxNode;
}

int main() {
    int n;
    std::cin >> n;

    if (n <= 0) {
        std::cout << "链表为空，没有最大值结点。\n";
        return 0;
    }

    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;

        ListNode* node = new ListNode(value);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    ListNode* maxNode = findMaxNode(head);
    std::cout << "最大值为：" << maxNode->data << '\n';

    while (head != nullptr) {
        ListNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }

    return 0;
}
