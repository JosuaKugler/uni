#include<set>
#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

const int m = 2;    // B-tree of order m
const int a = m;    // minimal number of keys
const int b = 2*m;  // maximal number of keys

template<class T>
struct Node {
  // data
  vector<T> keys;
  vector<Node *> children;
  Node* parent;
  // interface
  Node (Node* p) {parent = p;}
  bool is_leaf() {return children.size()==0;}
  Node* root () { return (parent==0) ? this : parent->root(); }
  Node* find_node (T item);
  int find_pos (T item);
  bool equals_item (int pos, T item);
} ;

// finds first position i such that keys[i]>=item
template<class T>
int Node<T>::find_pos (T item)
{
  int i = 0;
  while ((i<keys.size())&&(keys[i]<item)) i++;
  return i;
}

// checks if the key at position pos contains item
template<class T>
bool Node<T>::equals_item (int pos, T item) {
  return (pos<keys.size()) && !(item<keys[pos]);
}

// finds the node in which the item should be stored
template<class T>
Node<T>* Node<T>::find_node (T item) {
  if (is_leaf()) return this;
  int pos = find_pos(item);
  if (equals_item(pos, item))
    return this;
  else
    return children[pos]->find_node(item);
}

template<class VEC> 
VEC subseq (VEC vec, int start, int end)
{
  int size = (vec.size()==0) ? 0 : end-start;
  VEC result(size);
  for (int i = 0; i<size; i++)
    result[i] = vec[i+start];
  return result;
}

// if necessary, split the node.  Returns 0 or a new root
template<class T>
Node<T>* balance (Node<T>* node)
{
  int n = node->keys.size();
  if (n<=b) return 0;
  T median = node->keys[a];
  // create a new node
  Node<T>* node2 = new Node<T>(node->parent);
  node2->keys = subseq(node->keys, a+1,
		       node->keys.size());
  node2->children = subseq(node->children, a+1,
			   node->children.size());
  for (int i=0; i<node2->children.size(); i++)
    node2->children[i]->parent = node2;
  // handle node
  node->keys = subseq(node->keys, 0, a);
  node->children = subseq(node->children, 0, a+1);

  Node<T>* parent = node->parent;
  if (parent==0)  // split the root!
    {
      Node<T>* root = new Node<T>(0);
      root->keys.push_back(median);
      root->children.push_back(node);
      root->children.push_back(node2);
      node->parent = root;
      node2->parent = root;
      return root;
    }
  // otherwise: insert in parent
  int pos=0;
  while (parent->children[pos]!=node) pos++;
  parent->keys.insert(parent->keys.begin()+pos, median);
  parent->children.insert(parent->children.begin()+pos+1, node2);
  // recursive call;
  return balance(parent);
}

template<class T>
void show (Node<T> *node)
{
  cout << node << ": ";
  if (node->children.size()>0)
    {
      cout << node->children[0];
      for (int i=0; i<node->keys.size(); i++)
	cout << " |" << node->keys[i] << "| "
	     << node->children[i+1];
    }
  else
    for (int i=0; i<node->keys.size(); i++)
      cout << node->keys[i] << " ";
  cout << endl;
  for (int i=0; i<node->children.size(); i++)
    show(node->children[i]);
}

// we could work with a root pointer, but for later use it is
// better to wrap it into a class

template<class T>
class abTree {
public:
  abTree () {root = new Node<T>(0);}
  void insert (T item);
  bool find (T item);
  void show () { ::show(root); }
private:
  Node<T> *root;
};

template<class T>
void abTree<T>::insert (T item) {
  Node<T>* node = root->find_node(item);
  int i=node->find_pos(item);
  if (node->equals_item(i,item))
    node->keys[i] = item;
  else
    {
      node->keys.insert(node->keys.begin()+i, item);
      Node<T>* new_root = balance(node);
      if (new_root) root = new_root;
    }
}

template<class T>
bool abTree<T>::find (T item) {
  Node<T>* node = root->find_node(item);
  int i=node->find_pos(item);
  return node->equals_item(i, item);
}

int main ()
{
  abTree<int> tree;
  // insertion demo
  for (int i=0; i<5; i++) {
    tree.insert(i);
    tree.show();
  }
  // testing insertion and retrieval
  int n = 10;
  for (int i=0; i<n; i++)
    tree.insert(i*i);
  cout << endl;
  tree.show();
  for (int i=0; i<2*n; i++)
    cout << i << " " << tree.find(i) << endl;
  // performance test
  //abTree<int> set;
  set<int> set;  // should be faster
  int nn = 1000000;
  for (int i=0; i<nn; i++)
    set.insert(i*i);
  for (int i=0; i<nn; i++)
    set.find(i*i);
}
