#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>

// namespace BST {
    // class Node
    // {
    //     public:
    //         Node(int value, Node* left, Node* right);
    //         Node();
    //         Node(const Node& node);
    //         friend std::ostream& operator<<(std::ostream& os, const Node& node);
    //         bool operator<(int other) const;
    //         bool operator<=(int other) const;
    //         bool operator==(int other) const;
    //         bool operator>=(int other) const;
    //         bool operator>(int other) const;
    //         // friend bool operator<(int other, Node& node);
    //         // friend bool operator<=(int other, Node& node);
    //         // friend bool operator==(int other, Node& node);
    //         // friend bool operator>=(int other, Node& node);
    //         // friend bool operator>(int other, Node& node);

    //         int value;
    //         Node* left;
    //         Node* right;
    // };

//     bool operator<(int other, Node& node);
//     bool operator<=(int other, Node& node);
//     bool operator==(int other, Node& node);
//     bool operator>=(int other, Node& node);
//     bool operator>(int other, Node& node);

//     class BST
//     {
//         public:
//             Node*& get_root();
//             void bfs(std::function<void(Node*& node)> func);
//             size_t length();
//             bool add_node(int value);
//             Node** find_node(int value);
//             Node** find_parrent(int value);
//             Node** find_successor(int value);
//             bool delete_node(int value);

//         private:
//             Node* root;
//     };

// } // end of BST namespace

class BST
{
public:
    class Node
    {
        public:
            Node(int value, Node* left, Node* right);
            Node();
            Node(const Node& node);
            friend std::ostream& operator<<(std::ostream& os, const Node& node);
            bool operator<(int other) const;
            bool operator<=(int other) const;
            bool operator==(int other) const;
            bool operator>=(int other) const;
            bool operator>(int other) const;
            friend bool operator<(int other, Node& node);
            friend bool operator<=(int other, Node& node);
            friend bool operator==(int other, Node& node);
            friend bool operator>=(int other, Node& node);
            friend bool operator>(int other, Node& node);

            int value;
            Node* left;
            Node* right;
    };
    BST();
    BST(const BST& other); // copy constructor
    BST(BST&& other); // Move Constructor
    ~BST(); // Destructor
    BST(std::initializer_list<int> values);
    BST& operator=(const BST& bst); // copy assignment operator
    BST& operator=(BST&& other); // Move assignment operator
    BST& operator++(); // prefix ++
    BST operator++(int); // postfix ++
    void increment_nodes(Node*); // increment every node in a bst
    Node* copy_tree(Node* node);
    void destroy_tree(Node* node);
    Node*& get_root();
    Node* build_bst(Node* node);
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    size_t length(Node*& node);
    bool add_node(int value);
    bool add_node(int value, Node*& node);
    friend std::ostream& operator<<(std::ostream& os, BST& bst);
    Node** find_node(int value);
    Node** find_node(int value, Node*& node);
    Node** find_parrent(int value);
    Node** find_parrent(int value, Node*& node);
    Node** find_successor(int value);
    // I don't think the test case for find_successor is correct
    bool delete_node(int value);
    Node* get_leftmost_node(Node* node);

private:
    Node* root;
};

#endif //BST_H