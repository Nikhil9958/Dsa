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

int maxPath(Node *root) //counting edges
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 0;
    int leftHeight = maxPath(root->left);
    int rightHeight = maxPath(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int diameterPath(Node*root){ //counting diameter taking reference of edge
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

pair<int,int> optimizedDiameter(Node*root){
    if(root==NULL){
        return {0,0};
    }
    pair<int,int>leftP = optimizedDiameter(root->left);
    pair<int,int>rightP = optimizedDiameter(root->right);
    int rootDia = leftP.first + rightP.first + 1;
    int dia = max(rootDia,max(leftP.second,rightP.second));
    int height = max(leftP.first,rightP.first)+1;
    pair<int,int>ans = {height,dia};
    return ans;
}

vector<int>ans={};
vector<int> preorder(Node*root){
    if(root==NULL){
        ans.push_back(-1);
        return ans;
    }
    ans.push_back(root->data);
    preorder(root->left);
    preorder(root->right);
    return ans;
}

bool check2Vectors(vector<int>tree,vector<int>subTree){
        for(int i=0,j=0;i<tree.size();i++){
            if(tree[i]==subTree[j]){
                j++;
                if(j==subTree.size())
                    return true;
            }
        }
        return false;
}

void horizontalDist(Node*root,int level, map<int,Node*>&mp){
    if(root==NULL)
        return;
    if(mp.count(level)==0){
        mp[level] = root;
    }
    horizontalDist(root->left,level-1,mp);
    horizontalDist(root->right,level+1,mp);

    return;

}


int main()
{
    // vector<int>v={1,2,4,-1,-1,5,-1,6,-1,7,-1,-1,3,-1,-1};
    vector<int>v = {1,2,3,-1,-1,4,-1,-1,5,-1,6,-1,-1};
    // vector<int>v = {4,1,-1,-1,2,-1,-1};
    // vector<int> v = {1, 2, 4, -1, -1, 5, -1, 7, -1, 8, -1, 9, -1, -1, 3, -1, 6, -1, -1};
    // vector<int>v={1,-1,-1};
    Node *root = preorder(v);
    // preorderTrav(root);
    levelOrderTrav(root);
    heightofBT(root);
    cout << "Recursive Height:" << heightRec(root) << endl;
    cout << "diameter:" << diameter(root) << endl;
    cout<< "maxPath:"<<maxPath(root)<<endl;
    cout<<"DiameterPath:"<<diameterPath(root)<<endl;
    pair<int,int>HeightDiameter = optimizedDiameter(root);
    cout<<"OptimizedHeight:"<<HeightDiameter.first<<" "<<"OptimizedDia:"<<HeightDiameter.second<<endl;
    vector<int>buildedTree = preorder(root);
    // cout<<"Hello"<<endl;
    // for(int i=0;i<buildedTree.size();i++){
    //     cout<<buildedTree[i]<<" ";
    // }
    // cout<<endl;
    // vector<int>tree = {3,4, 1, -1, -1, 2, -1, -1,5,-1,-1 };
    // vector<int>subtree = {4, 1, -1, -1, 2,-1, -1 };
    // cout<<"Check2Vector:"<<check2Vectors(tree,subtree);

    map<int,Node*>mp;
    horizontalDist(root,0,mp);
    for(auto it:mp){
        cout<<it.first<<" "<<it.second->data<<endl;
    }
}