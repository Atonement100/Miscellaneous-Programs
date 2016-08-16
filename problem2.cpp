#include <iostream>
#include <string>
#include <vector>
#include <queue>

struct node {
	std::string value;
	node* left;
	node* right;

	node() {
		value = "null";
		left = NULL;
		right = NULL;
	}
};

int levelorder(std::vector<std::string> values, std::vector<int> left, std::vector<int> right, int root) {
	int temp;
	std::queue<int> loqueue;
	loqueue.push(root);
	while (!loqueue.empty()) {
		temp = loqueue.front();
		std::cout << values[temp] << " ";
		if (left[temp] != -1) { loqueue.push(left[temp]); }
		if (right[temp] != -1) { loqueue.push(right[temp]); }
		loqueue.pop();
	}
	return 0;
}

int postorder(std::vector<std::string> values, std::vector<int> left, std::vector<int> right, int root) {
	if (left[root] != -1) { postorder(values, left, right, left[root]); }
	if (right[root] != -1) { postorder(values, left, right, right[root]); }
	std::cout << values[root] << " ";
	return 0;
}

int inorder(std::vector<std::string> values, std::vector<int> left, std::vector<int> right, int root) {
	if (left[root] != -1) { inorder(values, left, right, left[root]); }
	std::cout << values[root] << " ";
	if (right[root] != -1) { inorder(values, left, right, right[root]); }
	return 0;
}

int preorder(std::vector<std::string> values, std::vector<int> left, std::vector<int> right, int root) {
	std::cout << values[root] << " ";
	if (left[root] != -1) { preorder(values, left, right, left[root]); }
	if (right[root] != -1) { preorder(values, left, right, right[root]); }
	return 0;
}

int main()
{
	int size, l, r, root = 0;
	std::string line;

	std::cin >> size;
	if (size == 0) { return 0; }
	std::vector<std::string> values(size, "");
	std::vector<int> left(size, -1), right(size, -1);
	std::vector<bool> pointedAt(size, false);

	for (unsigned int i = 0; i < values.size(); i++) {
		std::cin >> values[i] >> l >> r;
		if (l != -1) {
			pointedAt[l] = true;
			left[i] = l;

			if (pointedAt[l] == true && root == l) {
				while (pointedAt[root]) {
					root++;
				}
			}
		}
		if (r != -1) {
			pointedAt[r] = true;
			right[i] = r;

			if (pointedAt[r] == true && root == r) {
				while (pointedAt[root]) {
					root++;
				}
			}
		}

	}

	/*
	postorder(values, left, right, root);
	std::cout << std::endl;
	inorder(values, left, right, root);
	std::cout << std::endl;
	preorder(values, left, right, root);
	std::cout << std::endl << std::endl;
	*/ 
	levelorder(values, left, right, root);

	return 0;
}

