#include "bst.h"
#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <deque>
#include <string>

BST::Node::Node(int value, Node* left, Node* right)
    : value(value), left(left), right(right) {}

BST::Node::Node(const Node& node)
    : value(node.value), left(node.left), right(node.right) {}

BST::Node::Node()
    : value(0), left(nullptr), right(nullptr) {}

std::ostream& operator<<(std::ostream& os, const BST::Node& node) {
    os << "0x" << &node << " => value:" << node.value;
    if (node.left) {
        os << "  left: " << node.left;
    } else {
        os << "  left: 0";
    }
    if (node.right) {
        os << "  right: " << node.right;
    } else {
        os << "  right: 0";
    }
    // os << ")";
    return os;
}

bool BST::Node::operator<(int other) const {
    return value < other;
}

bool BST::Node::operator<=(int other) const {
    return value <= other;
}

bool BST::Node::operator==(int other) const {
    return value == other;
}

bool BST::Node::operator>=(int other) const {
    return value >= other;
}

bool BST::Node::operator>(int other) const {
    return value > other;
}

bool operator<(int other, BST::Node& node) {
    return other < node.value;
}

bool operator<=(int other, BST::Node& node) {
    return other <= node.value;
}

bool operator==(int other, BST::Node& node) {
    return other == node.value;
}

bool operator>=(int other, BST::Node& node) {
    return other >= node.value;
}

bool operator>(int other, BST::Node& node) {
    return other > node.value;
}

BST::Node*& BST::get_root() {
    return root;
}

BST::BST() : root(nullptr) {}

BST::BST(const BST& other) {
    root = build_bst(other.root);
}

BST::BST(BST&& other) {
    root = other.root;
    other.root = nullptr;
}

BST::Node* BST::build_bst(BST::Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    Node* curr = new Node(node->value, nullptr, nullptr);
    curr->left = build_bst(node->left);
    curr->right = build_bst(node->right);
    return curr;
}

BST& BST::operator=(const BST& bst) {
    if (this->root != bst.root) {
        root = build_bst(bst.root);
    }
    return *this;

}

BST& BST::operator=(BST&& other) {
    if (this->root != other.root) {
        this->root = std::move(other.root);
    }
    other.root = nullptr;
    return *this;
}

BST& BST::operator++() {
    increment_nodes(root);
    return *this;
}

BST BST::operator++(int) {
    BST temp = *this;
    increment_nodes(root);
    return temp;
}

void BST::increment_nodes(Node* node) {
    if (node == nullptr) {
        return;
    }
    node->value += 1;
    increment_nodes(node->left);
    increment_nodes(node->right);
}

BST::~BST()
 {
 	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
 		delete node;
    // destroy_tree(root);
 }

BST::BST(std::initializer_list<int> values) {
    root = nullptr;
    for (const int& num: values) {
        add_node(num);
    }
}

BST::Node* BST::copy_tree(BST::Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    return new Node(*node);
}

void BST::destroy_tree(BST::Node* node) {
    if (node) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}


void BST::bfs(std::function<void(Node*& node)> func) {
    if (!root) return;
    std::queue<Node*> queue;
    queue.push(root);

    while (!queue.empty()) {
        Node* curr = queue.front();
        queue.pop();
        func(curr);
        if (curr->left) {
            queue.push(curr->left);
        }
        if (curr->right) {
            queue.push(curr->right);
        }
    }
}

bool BST::add_node(int value) {
    return add_node(value, root);
}

bool BST::add_node(int value, BST::Node*& node) {
    if (node == nullptr) {
        node = new Node(value, nullptr, nullptr);
        return true;
    }
    if (node->value > value) {
        return add_node(value, node->left);
    } else if (node->value == value) {
        return false;
    } else {
        return add_node(value, node->right);
    }
}

size_t BST::length() {
    return length(root);
}

size_t BST::length(BST::Node*& node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + length(node->left) + length(node->right);
}

std::ostream& operator<<(std::ostream& os, BST& bst) {
    std::string stars(20, '*');
    os << stars << std::endl;
    BST::Node* root = bst.get_root();
    if (root) {
        std::queue<BST::Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            BST::Node* curr = queue.front();
            queue.pop();
            os << *curr << std::endl;
            if (curr->left) {
                queue.push(curr->left);
            }
            if (curr->right) {
                queue.push(curr->right);
            }
        }
    }
    os << "binary tree size: " << bst.length() << std::endl;
    os << stars << std::endl;    
    
    return os;
}

BST::Node** BST::find_node(int value) {
    return find_node(value, BST::get_root());
}

BST::Node** BST::find_node(int value, BST::Node*& node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->value == value) {
        return &node;
    } else if (node->value > value) {
        return find_node(value, node->left);
    } else {
        return find_node(value, node->right);
    }
}

BST::Node** BST::find_parrent(int value) {
    return find_parrent(value, root);
}

BST::Node** BST::find_parrent(int value, BST::Node*& node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->left != nullptr && node->left->value == value || node->right != nullptr && node->right->value == value) {
        return &node;
    }
    if (value < node->value) {
        return find_parrent(value, node->left);
    } else {
        return find_parrent(value, node->right);
    }
}

BST::Node* BST::get_leftmost_node(BST::Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BST::Node** BST::find_successor(int value) {
    BST::Node** p = find_node(value);
    if (p == nullptr || *p == nullptr) {
        return nullptr;
    }
    if ((*p)->right) {
        BST::Node* successor = get_leftmost_node((*p)->right);
        return find_node(successor->value, root);
    }
    BST::Node** successor = nullptr;
    BST::Node* ancestor = get_root();
    while (ancestor != nullptr) {
        if ((*p)->value < ancestor->value) {
            successor = &ancestor;  
            ancestor = ancestor->left;  
        } else if ((*p)->value > ancestor->value) {
            ancestor = ancestor->right;  
        } else {
            break;  
        }
    }
    return successor;
}

bool BST::delete_node(int value) {
    BST::Node** node = BST::find_node(value);
    if (node == nullptr || *node == nullptr) {
        return false;
    }
    BST::Node** parent = BST::find_parrent(value);
    if ((*node)->left == nullptr && (*node)->right == nullptr) {
        delete *node;
        *node = nullptr;
    } else if ( (*node)->left == nullptr) {
        Node* temp = *node;
        *node = (*node)->right;
        delete temp;
    } else if ( (*node)->right == nullptr) {
        Node* temp = *node;
        *node = (*node)->left;
        delete temp;
    } else {
        Node** successor = find_successor(value);
        
        (*node)->value = (*successor)->value;
        Node* temp = *successor;
        *successor = (*successor)->right;
        delete temp;
    }
    return true;
}