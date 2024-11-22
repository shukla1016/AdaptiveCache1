#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include <sstream>

class Node {
public:
    int key;
    int frequency;
    int recency;
    double score;
    Node* left;
    Node* right;

    Node(int k, int time) : key(k), frequency(1), recency(time), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;
    double alpha;
    int max_size;

    Node* rightRotate(Node* x);
    Node* leftRotate(Node* x);
    Node* splay(Node* root, int key);
    void calculateScore(Node* node);
    Node* findMinScoreNode(Node* node);
    void evictIfNeeded();

public:
    int current_size;
    SplayTree(double alpha = 0.5, int max_size = 10);
    Node* search(int key, int current_time);
    void insert(int key, int current_time);
    void remove(int key);
    void print();
    int getCurrentSize() const { return current_size; }
    std::string toString();  // No need for SplayTree:: here
    void inorderTraversal(Node* node, std::ostringstream& oss);  // No need for SplayTree:: here
};

#endif // SPLAY_TREE_H
