#include "splay_tree.h"
#include <bits/stdc++.h>

using namespace std;

// Constructor
SplayTree::SplayTree(double alpha, int max_size) 
    : root(nullptr), alpha(alpha), max_size(max_size), current_size(0) {}

// Right rotation
Node* SplayTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotation
Node* SplayTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay function
Node* SplayTree::splay(Node* root, int key) {
    // Base case: If the tree is empty or the root key is the key, return root
    if (root == nullptr || root->key == key) {
        return root;
    }

    // Key lies in the left subtree
    if (key < root->key) {
        if (root->left == nullptr) {
            return root; // Key not found
        }

        // Key lies in the left-left subtree
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root); // Perform right rotation
        }
        // Key lies in the left-right subtree
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr) {
                root->left = leftRotate(root->left); // Perform left rotation
            }
        }
        // Return the new root
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    // Key lies in the right subtree
    else {
        if (root->right == nullptr) {
            return root; // Key not found
        }

        // Key lies in the right-left subtree
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr) {
                root->right = rightRotate(root->right); // Perform right rotation
            }
        }
        // Key lies in the right-right subtree
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root); // Perform left rotation
        }
        // Return the new root
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}



// Calculate the score for a node
void SplayTree::calculateScore(Node* node) {
    node->score = alpha * node->recency + (1 - alpha) * node->frequency;
}

// Find the node with the minimum score
Node* SplayTree::findMinScoreNode(Node* node) {
    if (!node) return nullptr; // Base case: if the node is null, return null

    // Initialize minNode to the current node
    Node* minNode = node;

    // Create a queue for level order traversal to check all nodes
    std::queue<Node*> queue;
    queue.push(node);

    while (!queue.empty()) {
        Node* currentNode = queue.front();
        queue.pop();

        // Compare the score of the current node with the minNode
        if (currentNode->score < minNode->score) {
            minNode = currentNode; // Update minNode if a lower score is found
        }

        // Add left and right children to the queue for further exploration
        if (currentNode->left) {
            queue.push(currentNode->left);
        }
        if (currentNode->right) {
            queue.push(currentNode->right);
        }
    }

    return minNode; // Return the node with the minimum score
}


// Evict the least valuable node if the cache exceeds its size limit
void SplayTree::evictIfNeeded() {
    if (current_size >= max_size) {
        Node* minNode = findMinScoreNode(root);
        std::cout << minNode->key << std::endl;
        remove(minNode->key);
        current_size--;
    }
}

// Search for a key and update its frequency and recency
Node* SplayTree::search(int key, int current_time) {
    root = splay(root, key);
    if (root && root->key == key) {
        root->frequency++;
        root->recency = current_time;
        calculateScore(root);
        return root;
    }
    return nullptr;
}

void SplayTree::insert(int key, int current_time) {
    // Evict the least recently used node if the cache is full
    evictIfNeeded();
    
    // If the tree is empty, create a new root node
    if (!root) {
        root = new Node(key, current_time);
        current_size++;
    } else {
        root = splay(root, key);
        // If the root's key is not the key being inserted
        if (root->key != key) {
            // Create a new node with the key
            Node* newNode = new Node(key, current_time);
            // Insert the new node as the new root
            if (key < root->key) {
                // New node becomes the new root, right child is current root
                newNode->right = root;
                newNode->left = root->left; // Set the left child of the new node
                root->left = nullptr; // Clear the left child of the old root
            } else {
                // New node becomes the new root, left child is current root
                newNode->left = root;
                newNode->right = root->right; // Set the right child of the new node
                root->right = nullptr; // Clear the right child of the old root
            }
            root = newNode; // Update the root to the new node
            current_size++;
        }
    }
    calculateScore(root);
}


void SplayTree::remove(int key) {
    if (!root) return; // Tree is empty

    // Splay the tree to bring the key to the root if it exists
    root = splay(root, key);

    // If the root key does not match the key, return (key not found)
    if (key != root->key) return;

    Node* temp = root; // Store the current root node to free it later

    // If there's no left child, promote the right child
    if (!root->left) {
        root = root->right; // Move right child up
    } else {
        // If there's a left child, splay the maximum node in the left subtree
        root = splay(root->left, key);
        root->right = temp->right; // Attach the right subtree to the new root
    }

    delete temp; // Clean up the old root node
}

void preOrder(Node* node) {
    if (node != nullptr) {
        std::cout << "Key: " << node->key << ", Frequency: " << node->frequency << ", Recency: " << node->recency  << ", Score: " << node->score << std::endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

// Function to print the tree (in-order traversal)
void SplayTree::print() {
    Node *temp = root;
    preOrder(temp);
}
