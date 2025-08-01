/*
* generated using ChatGPT. the prompt was "decision tree armadillo c++ code".
*
* search query inputter: Peratham Wiriyathammabhum
*/
#include <iostream>
#include <armadillo>
#include <limits>

using namespace arma;
using namespace std;

struct TreeNode {
    bool isLeaf;
    int featureIndex;
    double threshold;
    int classLabel;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : isLeaf(false), featureIndex(-1), threshold(0.0), classLabel(-1), left(nullptr), right(nullptr) {}
};

double giniIndex(const mat& y) {
    int m = y.n_rows;
    if (m == 0) return 0.0;

    vec counts = sum(y, 0).t(); // count of each class
    vec probs = counts / m;
    return 1.0 - dot(probs, probs);
}

void bestSplit(const mat& X, const mat& y, int& bestFeature, double& bestThreshold, double& bestScore) {
    int n_samples = X.n_rows, n_features = X.n_cols;
    bestScore = numeric_limits<double>::infinity();

    for (int feature = 0; feature < n_features; ++feature) {
        vec thresholds = unique(X.col(feature));
        for (double threshold : thresholds) {
            uvec left_idx = find(X.col(feature) <= threshold);
            uvec right_idx = find(X.col(feature) > threshold);

            if (left_idx.is_empty() || right_idx.is_empty())
                continue;

            mat y_left = y.rows(left_idx);
            mat y_right = y.rows(right_idx);

            double gini = (y_left.n_rows * giniIndex(y_left) + y_right.n_rows * giniIndex(y_right)) / n_samples;

            if (gini < bestScore) {
                bestScore = gini;
                bestFeature = feature;
                bestThreshold = threshold;
            }
        }
    }
}

TreeNode* buildTree(const mat& X, const mat& y, int depth = 0, int maxDepth = 3) {
    TreeNode* node = new TreeNode();

    vec counts = sum(y, 0).t();
    uword majority = index_max(counts);
    node->classLabel = majority;

    if (depth >= maxDepth || giniIndex(y) == 0.0) {
        node->isLeaf = true;
        return node;
    }

    int bestFeature;
    double bestThreshold, bestScore;
    bestSplit(X, y, bestFeature, bestThreshold, bestScore);

    if (bestScore == numeric_limits<double>::infinity()) {
        node->isLeaf = true;
        return node;
    }

    uvec left_idx = find(X.col(bestFeature) <= bestThreshold);
    uvec right_idx = find(X.col(bestFeature) > bestThreshold);

    node->featureIndex = bestFeature;
    node->threshold = bestThreshold;

    node->left = buildTree(X.rows(left_idx), y.rows(left_idx), depth + 1, maxDepth);
    node->right = buildTree(X.rows(right_idx), y.rows(right_idx), depth + 1, maxDepth);

    return node;
}

int predict(TreeNode* node, const rowvec& x) {
    if (node->isLeaf)
        return node->classLabel;

    if (x(node->featureIndex) <= node->threshold)
        return predict(node->left, x);
    else
        return predict(node->right, x);
}

void freeTree(TreeNode* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

// Dummy example
int main() {
    // X: 6 samples, 2 features
    mat X = {
        {2.0, 3.0},
        {1.0, 5.0},
        {2.5, 4.0},
        {3.5, 2.0},
        {3.0, 1.0},
        {4.5, 1.0}
    };

    // y: One-hot labels (2 classes)
    mat y = {
        {1, 0},
        {1, 0},
        {1, 0},
        {0, 1},
        {0, 1},
        {0, 1}
    };

    TreeNode* tree = buildTree(X, y);

    for (int i = 0; i < X.n_rows; ++i) {
        int pred = predict(tree, X.row(i));
        cout << "Sample " << i << " predicted class: " << pred << endl;
    }

    freeTree(tree);
    return 0;
}
