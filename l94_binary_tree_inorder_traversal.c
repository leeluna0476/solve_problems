/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int count_nodes(struct TreeNode* root) {
    if (!root) {
        return 0;
    }
    else {
        int c = count_nodes(root->left);
        c += count_nodes(root->right);
        return c + 1;
    }
}

int *record_inorder(struct TreeNode* root, int *record) {
    if (!root) {
        return record;
    }
    else {
        record = record_inorder(root->left, record);
        *record = root->val;
        ++record;
        record = record_inorder(root->right, record);
        return record;
    }
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = count_nodes(root);
    int *record = malloc(sizeof(int) * *returnSize);
    record_inorder(root, record);
    return record;
}
