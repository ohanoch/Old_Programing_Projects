#include <iostream>

using namespace std;

class TreeNode{
public:
    // Pointer to the left child
    //  Initialised to nullptr (this syntax is a new C++11 feature)
    TreeNode* left = nullptr;
    // Pointer to the right child
    //  Initialised to nullptr (this syntax is a new C++11 feature)
    TreeNode* right = nullptr;

    // Value in the node
    int value;

    // Constructor, sets the value
    TreeNode(int v) : value(v) {}
    // Destructor, nifty trick to recursively delete all the nodes
    //  be careful though, when you delete just a single node, make
    //  sure that you set left and right = nullptr first
    ~TreeNode() {
        delete left;
        delete right;
    }
};

class Tree{
private:
    TreeNode* root = nullptr;

public:
    // These functions do the actual work
    void insert(int v, TreeNode* &subtree){
        if(subtree == nullptr){
           subtree = new TreeNode(v);
        }else if(v < subtree->value){
            insert(v, subtree->left);
        }else{
            insert(v, subtree->right);
        }
    }

    void preOrderTraversal(TreeNode* subtree) const{
		cout << subtree->value << " ";
		if (subtree->left!=nullptr)
		{
			preOrderTraversal(subtree->left);
		}
		if (subtree->right!=nullptr)
		{
			preOrderTraversal(subtree->right);
		}
    }

    void inOrderTraversal(TreeNode* subtree) const{
		if (subtree->left!=nullptr)
		{
			inOrderTraversal(subtree->left);
			cout << subtree->value << " ";
		}
		else
		{
			cout << subtree->value<< " ";
		}
		if (subtree->right!=nullptr)
		{
			inOrderTraversal(subtree->right);
//			if (subtree->left==nullptr)
//			{
//				cout << subtree->value << " ";
//			}
		}
    }

    void postOrderTraversal(TreeNode* subtree) const{
		if (subtree->left!=nullptr)
		{
			postOrderTraversal(subtree->left);
		}
		if (subtree->right!=nullptr)
		{
			postOrderTraversal(subtree->right);
		}
		cout << subtree->value << " ";

    }

    int min(TreeNode* subtree) const{
		if (subtree->left!=nullptr)
		{
			return min(subtree->left);
		}
		return subtree->value;
    }
    int max(TreeNode* subtree) const{
		if (subtree->right!=nullptr)
		{
			return max(subtree->right);
		}
		return subtree->value;
    }
    bool contains(int value, TreeNode* subtree) const{
		if (subtree->value==value)
		{
			return true;
		}
		if (subtree->value<value)
		{
			if (subtree->right!=nullptr)
			{
				return contains(value,subtree->right);
			}
		}
		if (subtree->value>value)
		{
			if (subtree->left!=nullptr)
			{
				return contains(value,subtree->left);
			}
		}
		return false;

    }
    void remove(int value, TreeNode* &subtree){
//cout <<"aaaaa\t"<<subtree->value<<endl;
		if (subtree->value==value)
		{
//cout <<"bbbbbbbb"<<endl;
			if (subtree->right==nullptr && subtree->left==nullptr)
			{
				subtree=nullptr;
			}
			else
			{
				if (subtree->right==nullptr)
				{
					TreeNode* temp=subtree->left;
					subtree->left=nullptr;
					delete subtree;
					subtree=temp;
				}
				else if (subtree->left==nullptr)
				{
					TreeNode* temp=subtree->right;
					subtree->right=nullptr;
					delete subtree;
					subtree=temp;
				}
				else
				{
					subtree->value=min(subtree->right);
					remove (min(subtree->right),subtree->right);
				}
			}
//cout <<"cccccccc"<<endl;
		}
		else if (subtree->value<value)
		{
//cout <<"ddddddddd"<<endl;
			remove(value,subtree->right);
		}
		else
		{
//cout <<"eeeeeee"<<endl;
			remove(value,subtree->left);
		}
		
    }

    void insert(int value){
        insert(value, root);
    }

    void preOrderTraversal(){
        preOrderTraversal(root);
        cout << endl;
    }
    void inOrderTraversal(){
        inOrderTraversal(root);
        cout << endl;
    }
    void postOrderTraversal(){
        postOrderTraversal(root);
        cout << endl;
    }
    int min(){
        return min(root);
    }
    int max(){
        return max(root);
    }
    bool contains(int value){
        return contains(value, root);
    }
    void remove(int value){
        remove(value, root);
    }
    ~Tree(){
        // This ends up deleting all the nodes recursively.
        delete root;
    }
};

int main(){
    Tree t;
    int value;
    // Sample code to read and construct the tree.
    while(cin >> value && value != -1){
        t.insert(value);
    }

    // Do some stuff...
	while(cin >> value && value != -1){
        t.remove(value);
		t.preOrderTraversal();
		t.inOrderTraversal();
		t.postOrderTraversal();
    }

/*	while(cin >> value && value != -1){
        if(t.contains(value))
		{
			cout<<"true" <<endl;
		}
		else
		{
			cout<<"false" <<endl;
		}
    }

	cout << t.min()<<endl;
	cout << t.max()<<endl;
	t.preOrderTraversal();
	cout <<endl;
	t.inOrderTraversal();
	cout <<endl;
	t.postOrderTraversal();
	cout <<endl<<"remove2"<<endl;
	t.remove(2);
	cout<< "removed2"<<endl;
	t.preOrderTraversal();
	t.insert(2);
	t.remove(3);
	cout<< "remove3"<<endl;
	t.preOrderTraversal();
	t.insert(3);
	t.remove(5);
	cout<< "remove5"<<endl;
	t.preOrderTraversal();
	t.insert(5);
*/
}
