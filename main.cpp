#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <iterator>
#include <climits>
#include <algorithm>
#include <ctime>

struct Node {
    int val;
    std::shared_ptr<Node> next;
    Node(int v, const std::shared_ptr<Node> & nx=nullptr) : val(v), next(nx) {}
};

using pNode = std::shared_ptr<Node>;

pNode createList(const std::vector<int> & nums) {
    pNode head = nullptr;
    for (auto it = nums.rbegin(); it != nums.rend(); ++it)
        head = std::make_shared<Node>(*it, head);
    return head;
}

void printList(const pNode & node) {
    if (node != nullptr) {
        pNode p = node;
        while (p != nullptr) {
            std::cout << p->val << " ";
            p = p->next;
        }
    }
}

class solution {
  public:
    pNode mergeKLists(const std::vector<pNode> & lists) {
        std::vector<pNode> currs;
        for (size_t i = 0; i < lists.size(); ++i)
            currs.push_back(lists[i]);
        std::vector<int> vals;
        for (size_t i = 0; i < currs.size(); ++i) {
            if (currs[i] != nullptr)
                vals.push_back(currs[i]->val);
            else
                vals.push_back(INT_MAX);
        }
        
        std::vector<int> sorted;
        auto it = std::min_element(vals.begin(), vals.end());
        while (*it != INT_MAX) {
            sorted.push_back(*it);
            currs[std::distance(vals.begin(),it)] = currs[std::distance(vals.begin(),it)]->next;
            vals.clear();
            for (size_t i = 0; i < currs.size(); ++i) {
                if (currs[i] != nullptr)
                    vals.push_back(currs[i]->val);
                else
                    vals.push_back(INT_MAX);
            }
            it = std::min_element(vals.begin(), vals.end());
        }

        return createList(sorted);
    }
};

int main() {
    srand(time(0));
    std::cout << "Before merge:\n";
    std::vector<pNode> lists;
    for (size_t i = 0; i < 3; i++) {
        std::vector<int> vec;
        std::generate_n(std::inserter(vec, vec.begin()), 10, [](){
            return int(rand()%20);
        });
        std::sort(vec.begin(), vec.end());

        lists.push_back(createList(vec));
        std::cout << "List " << i << ":\n";
        printList(lists.back());
        std::cout << std::endl;
    }

    solution soln;
    pNode merged = soln.mergeKLists(lists);
    std::cout << "\nAfter merge:\n";
    printList(merged);
    std::cout << std::endl;
}
