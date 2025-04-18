#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;

    Node(int data)
    {
        this->data = data;
        left = right = NULL;
    }
};
static int idx = -1;
Node *preorder(vector<int> v)
{
    idx++;
    if (v[idx] == -1)
    {
        return NULL;
    }

    Node *temp = new Node(v[idx]);
    temp->left = preorder(v);
    temp->right = preorder(v);

    return temp;
}

void preorderTrav(Node *root)
{
    if (root == NULL)
    {
        cout << -1 << " ";
        return;
    }
    cout << root->data << " ";
    preorderTrav(root->left);
    preorderTrav(root->right);
}

void levelOrderTrav(Node *root)
{
    queue<Node *> q;
    if (root == NULL)
        return;
    q.push(root);
    q.push(NULL);
    Node *curr;
    while (!q.empty())
    {
        curr = q.front();
        q.pop();
        if (curr == NULL)
        {
            cout << endl;
            if (!q.empty())
                q.push(curr);
            continue;
        }
        cout << curr->data << " ";
        if (curr->left)
            q.push(curr->left);
        if (curr->right)
            q.push(curr->right);
    }
}

void heightofBT(Node *root)
{
    if (root == NULL)
    {
        cout << "0" << endl;
        return;
    }
    int h = 0;
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    Node *curr;
    while (!q.empty())
    {
        curr = q.front();
        q.pop();
        if (curr == NULL)
        {
            h++;
            // cout<<endl;
            if (!q.empty())
                q.push(curr);
            continue;
        }
        // cout<<curr->data<<" ";
        if (curr->left)
            q.push(curr->left);
        if (curr->right)
            q.push(curr->right);
    }
    cout << "Height:" << h << endl;
}

int heightRec(Node *root)
{
    if (root == NULL)
        return 0;
    int leftHeight = heightRec(root->left);
    int rightHeight = heightRec(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int maxPath(Node *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 0;
    int leftHeight = maxPath(root->left);
    int rightHeight = maxPath(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int diameterPath(Node*root){
    if(root==NULL)
        return 0;
    if(root->left==NULL&&root->right==NULL){
        return 0;
    }
    int rootDia=0;
    if(root->left){
        rootDia+= maxPath(root->left)+1;
    }
    if(root->right){
        rootDia+= maxPath(root->right)+1;
    }

    int leftDia = diameterPath(root->left);
    int rightDia = diameterPath(root->right);

    return max(rootDia,max(leftDia,rightDia));

}
int diameter(Node *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    int rootDia = heightRec(root->left) + heightRec(root->right) + 1;
    int leftDia = diameter(root->left);
    int rightDia = diameter(root->right);
    return max(rootDia, max(leftDia, rightDia));
}

int main()
{
    // vector<int>v={1,2,4,-1,-1,5,-1,6,-1,7,-1,-1,3,-1,-1};
    // vector<int>v = {1,2,3,-1,-1,4,-1,-1,5,-1,6,-1,-1};
    // vector<int> v = {1, 2, 4, -1, -1, 5, -1, 7, -1, 8, -1, 9, -1, -1, 3, -1, 6, -1, -1};
    vector<int>v={1,-1,-1};
    Node *root = preorder(v);
    // preorderTrav(root);
    levelOrderTrav(root);
    heightofBT(root);
    cout << "Recursive Height:" << heightRec(root) << endl;
    cout << "diameter:" << diameter(root) << endl;
    cout<< "maxPath:"<<maxPath(root)<<endl;
    cout<<"DiameterPath:"<<diameterPath(root)<<endl;
}