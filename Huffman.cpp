#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class node
{
	node* left;
	node* right;
	node* predecessor;
	int frequency;
	
public:
	int ID;
	string code;
	node(int freq=0)
	{
		ID = 1;
		code = "";
		node* left=nullptr;
		node* right= nullptr;
		node* predecessor= nullptr;
		frequency= freq;
	}
	
	

	void setleft(node* x)
	{
		left = x;
	}
	void setright(node* x)
	{
		right = x;
	}
	void setpredecessor(node* x)
	{
		predecessor = x;
	}
	void setfreq(int x)
	{
		frequency = x;
	}
	int getfreq()
	{
		return frequency;
	}
	node* getLeft()
	{
		return left;
	}
	node* getRight()
	{
		return right;
	}
	node* getPredecessor()
	{
		return predecessor;
	}
	virtual ~node(){}

};
class leaf : public node
{
	char Character;

public:
	leaf(int freq=0, char C='.')
		:node::node(freq)
	{
		Character = C;
		ID = 2;
	}
	void setChar(char c)
	{
		Character = c;
	}
	char getChar()
	{
		return Character;
	}
	virtual ~leaf(){}

};
void getCodes(node* top, vector<node*> &leafs, string x)
{
	if (top == nullptr)
	{
		return;
	}
	if (top->getPredecessor() != nullptr)
	{
		top->code += top->getPredecessor()->code + x;
	}
	if (top->ID == 2)
	{
		leafs.push_back(top);
	}
		getCodes(top->getLeft(), leafs, "0");
		getCodes(top->getRight(), leafs, "1");

}

void sort(vector<node*> &leafs)
{
	for (int x = 0; x < leafs.size(); x++)
	{
		for (int j = 0; j <leafs.size() - x -1; j++)
			if (leafs[j]->getfreq() > leafs[j + 1]->getfreq())
			{
				swap(leafs[j], leafs[j + 1]);
			}
	}

}
void sortChars(vector<node*>& leafs)
{

	for (int x = 0; x < leafs.size(); x++)
	{
		for (int j = 0; j < leafs.size()-x-1; j++)
			if (dynamic_cast<leaf*>(leafs[j])->getChar() > dynamic_cast<leaf*>(leafs[j+1])->getChar())
			{
				swap(leafs[j], leafs[j + 1]);
			}
	}
}
void minHeap(vector<node*> &leafs)
{
	while (leafs.size() != 1)
	{
		node* Node = new node();
		Node->setleft(leafs[0]);
		Node->setright(leafs[1]);
		leafs[0]->setpredecessor(Node);
		leafs[1]->setpredecessor(Node);
		Node->setfreq(leafs[0]->getfreq() + leafs[1]->getfreq());
		leafs.erase(leafs.begin());
		leafs[0] = Node;
		sort(leafs);
	}
}
int main()
{
	ifstream file;
	file.open("freq.txt");
	string line;
	
	vector<string> charvec;
	vector<int> intvec;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector<string> result;
			istringstream iss(line);
			for (string line; iss >> line; )
			{
				result.push_back(line);
			}
			charvec.push_back(result[0]);
			intvec.push_back(stoi(result[1]));
		}
		file.close();
	}
	vector<node*> leafs;
	for (int i = 0; i < intvec.size(); i++)
	{
		leaf* Leaf = new leaf();
		char* char_arr;
		string str_obj = charvec[i];
		char_arr = &str_obj[0];
		Leaf->setfreq(intvec[i]);
		Leaf->setChar(*char_arr);
		leafs.push_back(Leaf);
	}
	sort(leafs);
	minHeap(leafs);
	getCodes(leafs[0], leafs, "");
	leafs.erase(leafs.begin());
	sortChars(leafs);
	//write to file
	ofstream output;
	output.open("codetable.txt");
	for (int i = 0; i < leafs.size(); i++)
	{
		output << dynamic_cast<leaf*>(leafs[i])->getChar() << " " << leafs[i]->code << endl;
	}
	output.close();
	return 0;
}