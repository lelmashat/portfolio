#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;

// Helper function to check if a node is a leaf
bool isLeaf(Node* node) {
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}

// Recursive function to determine if all paths from leaves to root are the same length
bool equalPathsHelper(Node* root, int depth, int& leafDepth) {
    // Base case: if root is null, return true    
    if (root == nullptr)
        return true;

    // If the current node is a leaf, update leafDepth if needed
    if (isLeaf(root)) {
        if (leafDepth == -1)
            leafDepth = depth;
        else if (leafDepth != depth)
            return false; // Found a leaf with a different depth
        return true;
    }

    // Recursively check the left and right subtrees
    return equalPathsHelper(root->left, depth + 1, leafDepth) &&
           equalPathsHelper(root->right, depth + 1, leafDepth);
}

// Main function to check for equal paths
bool equalPaths(Node* root) {
    int leafDepth = -1; // Initialize to an invalid depth
    return equalPathsHelper(root, 0, leafDepth);
}


