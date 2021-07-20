#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
struct Tree
{
	char value;
	Tree *left;
	Tree *right;
};
vector<Tree *> forest;
vector<Tree *> st;
void build_tree()
{
	char ch;
	while ((ch = getchar()) != EOF && ch != '\n')
	{
		while (ch == ' ')
		{
			ch = getchar();
		}
		Tree *temp = new Tree({ch, nullptr, nullptr});
		if (ch == ')')
		{
			while (st.back()->value != '(')
			{
				st.back()->right = forest.back();
				if (st.back()->value != '!')
				{
					forest.pop_back();
					st.back()->left = forest.back();
				}
				forest.pop_back();
				forest.push_back(st.back());
				st.pop_back();
			}
			st.pop_back();
		}
		else if (ch == '&' || ch == '|')
		{
			while (!st.empty() && st.back()->value != '(')
			{
				st.back()->right = forest.back();
				if (st.back()->value != '!')
				{
					forest.pop_back();
					st.back()->left = forest.back();
				}
				forest.pop_back();
				forest.push_back(st.back());
				st.pop_back();
			}
			st.push_back(temp);
		}
		else if (ch == '=')
		{
			while (!st.empty() && st.back()->value != '(' &&
				   st.back()->value != '&' && st.back()->value != '|')
			{
				st.back()->right = forest.back();
				if (st.back()->value != '!')
				{
					forest.pop_back();
					st.back()->left = forest.back();
				}
				forest.pop_back();
				forest.push_back(st.back());
				st.pop_back();
			}
			st.push_back(temp);
		}
		else if (ch == '>')
		{
			while (!st.empty() && st.back()->value == '=' && st.back()->value == '!')
			{
				st.back()->right = forest.back();
				if (st.back()->value != '!')
				{
					forest.pop_back();
					st.back()->left = forest.back();
				}
				forest.pop_back();
				forest.push_back(st.back());
				st.pop_back();
			}
			st.push_back(temp);
		}
		else if (ch == '!')
		{
			while (!st.empty() && st.back()->value == '!')
			{
				st.back()->right = forest.back();
				forest.pop_back();
				forest.push_back(st.back());
				st.pop_back();
			}
			st.push_back(temp);
		}
		else if (ch == '(')
		{
			st.push_back(temp);
		}
		else
		{
			forest.push_back(temp);
		}
	}
	while (!st.empty())
	{
		st.back()->right = forest.back();
		if (st.back()->value != '!')
		{
			forest.pop_back();
			st.back()->left = forest.back();
		}
		forest.pop_back();
		forest.push_back(st.back());
		st.pop_back();
	}
}
void dfs(Tree *cur = forest.back(), int h = 0)
{
	for (int i = 0; i < h - 1; i++)
	{
		printf("%s", "    ");
	}
	if (h != 0)
	{
		printf("%s", " ---");
	}
	printf("%c\n", cur->value);
	if (cur->left != nullptr)
	{
		dfs(cur->left, h + 1);
	}
	if (cur->right != nullptr)
	{
		dfs(cur->right, h + 1);
	}
}
unordered_map<char, bool> sigma;
void get_sigma()
{
	char ch;
	while ((ch = getchar()) != EOF && ch != '\n')
	{
		while (ch == ' ')
		{
			ch = getchar();
		}
		scanf("%d", &sigma[ch]);
	}
}
bool calculate(Tree *cur = forest.back())
{
	bool l, r;
	if (cur->left != nullptr)
	{
		l = calculate(cur->left);
	}
	if (cur->right != nullptr)
	{
		r = calculate(cur->right);
	}
	if (cur->value == '&')
	{
		return l && r;
	}
	if (cur->value == '|')
	{
		return l || r;
	}
	if (cur->value == '!')
	{
		return !r;
	}
	if (cur->value == '>')
	{
		return !l || r;
	}
	if (cur->value == '=')
	{
		return l == r;
	}
	return sigma[cur->value];
}
int main()
{
	build_tree();
	dfs();
	get_sigma();
	printf("%d", calculate());
}