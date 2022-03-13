#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
class BinarySearchTree;

template <typename T>
class TreeNode
{
	friend class BinarySearchTree<T>;
public:
	TreeNode();
	TreeNode(T data);
	TreeNode(const TreeNode<T>& copy);
	TreeNode(TreeNode<T>&& move) noexcept;
	TreeNode<T>& operator=(const TreeNode<T>& copy);
	TreeNode<T>& operator=(TreeNode<T>&& move) noexcept;
	~TreeNode();

private:
	TreeNode<T>* m_left;
	TreeNode<T>* m_right;
	T m_data;
};

template <typename T>
TreeNode<T>::TreeNode() : m_left(nullptr), m_right(nullptr), m_data(0)
{

}

template <typename T>
TreeNode<T>::TreeNode(T data)
	:m_left(nullptr), m_right(nullptr), m_data(data)
{

}

template <typename T>
TreeNode<T>::TreeNode(const TreeNode<T>& copy)
{

}

template <typename T>
TreeNode<T>::TreeNode(TreeNode<T>&& move) noexcept
{
	this = move; //*this????
}

template <typename T>
TreeNode<T>::~TreeNode()
{}

template <typename T>
TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>& copy)
{

}
template <typename T>
TreeNode<T>& TreeNode<T>::operator=(TreeNode<T>&& move) noexcept
{
	this = move;
}

#endif
