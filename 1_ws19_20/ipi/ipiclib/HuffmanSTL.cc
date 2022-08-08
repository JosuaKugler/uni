#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std; // import namespace std

// There are no general binary trees in the STL.
// But we do not use much of this structure anyhow...
struct node {
  struct node *left;
  struct node *right;
  char symbol;
  int weight;
  node (char c, int i) {  // leaf constructor
    symbol = c;
    weight = i;
    left = right = 0;
  }
  node (node* l, node *r) { // internal node constructor
    symbol = 0;
    weight = l->weight + r->weight;
    left = l;
    right = r;
  }
  bool isleaf() {return symbol!=0;}
  bool operator> (const node &a) const {
    return weight > a.weight;
  }
};

// construct the Huffman trie for this message
node* huffman_trie (string message) {
  // count multiplicities
  map<char,int> cmap;
  for (string::iterator i=message.begin(); i!=message.end(); i++)
    if (cmap.find(*i)!=cmap.end())
      cmap[*i]++;
    else
      cmap[*i]=1;
    
  // generate leaves with multiplicities
  priority_queue<node, vector<node>, greater<node> > q;
  for (map<char,int>::iterator i=cmap.begin(); i!=cmap.end(); i++)
    q.push(node(i->first,i->second));
    
  // build Huffman tree (trie)
  while (q.size()>1)
    {
      node *left = new node(q.top());
      q.pop();
      node *right = new node(q.top());
      q.pop();
      q.push(node(left, right));
    }
  return new node(q.top());
}
    
// recursive filling of the encoding table 'code'
void fill_encoding_table (string s, node *i,
                          map<char,string>& code) {
  if (i->isleaf())
    code[i->symbol]=s;
  else
    {
      fill_encoding_table (s+"0", i->left, code);
      fill_encoding_table (s+"1", i->right, code);
    }
}

// encoding
string encode (map<char,string> code, string& message) {
  string encoded = "";
  for (string::iterator i=message.begin(); i!=message.end(); i++)
    encoded += code[*i];
  return encoded;
}

// decoding
string decode (node* trie, string& encoded) {
  string decoded = "";
  node* node = trie;
  for (string::iterator i=encoded.begin(); i!=encoded.end(); i++)
    {
      if (!node->isleaf())
	node = (*i=='0') ? node->left : node->right;
      if (node->isleaf())
        {
	  decoded.push_back(node->symbol);
	  node = trie;
        }
    }
  return decoded;
}

int main () {
  string message = "ABRACADABRASIMSALABIM";
    
  // generate Huffman trie
  node* trie = huffman_trie(message);

  // generate and show encoding table
  map<char,string> table;
  fill_encoding_table ("", trie, table);
  for (map<char,string>::iterator i=table.begin(); i!=table.end(); i++)
    cout << i->first << " " << i->second << endl;

  // encode and decode
  string encoded = encode(table, message);
  cout << "Encoded: " << encoded <<
    " [" << encoded.size() << " Bits]" << endl ;
  cout << "Decoded: " << decode(trie, encoded) << endl;

  // the trie is not deleted here ...
}
