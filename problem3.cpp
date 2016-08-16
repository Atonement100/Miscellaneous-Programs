#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

struct node {
	std::string value;
	node* left;
	node* right;

	node(std::string val) {
		value = val;
		left = NULL;
		right = NULL;
	}
};

node* buildTree(std::vector<std::string> post, std::vector<std::string> in, int postStart, int postEnd, int inStart, int inEnd) {
	if (postStart > postEnd || inStart > inEnd) { return NULL; } //return null if size == 0;

	node* root = new node(post[postEnd]);
	//int pos = std::find(in.begin(), in.end(), post[postEnd]) - in.begin();
	int pos = 0;
	for (int i = 0; i < in.size(); i++) {
		if (in[i] == root->value) { 
			pos = i; 
			break; 
		} 
	}
	root->left = buildTree(post, in, postStart, postStart + pos - inStart - 1, inStart, pos - 1);
	root->right = buildTree(post, in, postStart + pos - inStart, postEnd - 1, pos + 1, inEnd);
	return root;
}

int levelorder(node* root) {
	node* temp;
	std::queue<node*> loqueue;
	loqueue.push(root);
	while (!loqueue.empty()) {
		temp = loqueue.front();
		std::cout << temp->value << " ";
		if (temp->left) {
			loqueue.push(temp->left);
		}
		if (temp->right) {
			loqueue.push(temp->right);
		}
		loqueue.pop();
	}

	return 0;
}


int main()
{
	int size, root = 0;
	std::string line;

	std::cin >> size;
	if (size == 0) { return 0; }
	std::vector<std::string> post(size), in(size), pre(0);
	for (unsigned int i = 0; i < post.size(); i++) {
		std::cin >> post[i];
	}
	for (unsigned int i = 0; i < post.size(); i++) {
		std::cin >> in[i];
	}

	node* tree = buildTree(post, in, 0, size - 1, 0, size - 1);
	levelorder(tree);

	return 0;
}

