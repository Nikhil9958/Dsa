/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    public:
        bool isIdentical(TreeNode* root, TreeNode* subroot){
            if(root==NULL&&subroot==NULL)
                return true;
            if(root==NULL||subroot==NULL)
                return false;
            if(root->val!=subroot->val)
                return false;
            return isIdentical(root->left,subroot->left)&& isIdentical(root->right,subroot->right);
        }
    
        bool isSubtree(TreeNode* root, TreeNode* subroot) {
            if(root==NULL&&subroot==NULL)
                return true;
            if(root==NULL||subroot==NULL)
                return false;
            if(root->val==subroot->val){
                if(isIdentical(root,subroot))
                    return true;
            }
            bool left = isSubtree(root->left,subroot);
            bool right = false;
            if(!left)
                right=isSubtree(root->right,subroot);
            return (left||right);
        }
    };