#include<bits/stdc++.h>
#include<vector>
using namespace std;

class Node {
    public:
    int data;
    Node*left,*right;

    Node(int data){
        this->data = data;
        left=right=NULL;
    }
};
static int idx = -1;
Node*preorder(vector<int>v){
    idx++;
    if(v[idx]==-1){
        return NULL;
    }

    Node*temp = new Node(v[idx]);
    temp->left = preorder(v);
    temp->right = preorder(v);

    return temp;
}

void preorderTrav(Node*root){
    if(root==NULL){
        cout<<-1<<" ";
        return;
    }
    cout<<root->data<<" ";
    preorderTrav(root->left);
    preorderTrav(root->right);

}

void levelOrderTrav(Node*root){
    queue<Node*>q;
    if(root==NULL)
        return ;
    q.push(root);
    q.push(NULL);
    Node*curr;
    while(!q.empty()){
        curr = q.front();
        q.pop();
        if(curr==NULL){
            cout<<endl;
            if(!q.empty())
                q.push(curr);
            continue;
        }
        cout<<curr->data<<" ";
        if(curr->left)
            q.push(curr->left);
        if(curr->right)
            q.push(curr->right);
    }
}



int main(){
    vector<int>v={1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    Node * root = preorder(v);
    // preorderTrav(root);
    levelOrderTrav(root);
}