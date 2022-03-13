#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <queue>
using std::queue;
#include "TreeNode.h"
#include "Exception.h"

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& copy);
	BinarySearchTree(BinarySearchTree<T>&& move) noexcept;
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& copy);
	BinarySearchTree<T>& operator=(BinarySearchTree<T>&& move) noexcept;
	virtual ~BinarySearchTree();

	virtual void Insert(T data);
	bool FindNode(T data);
	void Purge();
	int Height();
	virtual void BreadthFirstTraversal(void(*visit)(T& data));
	virtual void InOrderTraversal(void(*visit)(T& data));
	virtual void PreOrderTraversal(void(*visit)(T& data));
	virtual void PostOrderTraversal(void(*visit)(T& data));
	virtual void Delete(T data);
protected:
	virtual void CopyTree(TreeNode<T>*& newtree, TreeNode<T>* oldtree);
	TreeNode<T>* Insert(TreeNode<T>*& root, T data);
	void Purge(TreeNode<T>* node);
	void DeleteFromTree(TreeNode<T>*& node);
	int Height(TreeNode<T>* node);
	void BreadthFirstTraversal(TreeNode<T>* root, void(*visit)(T& data));
	void InOrderTraversal(TreeNode<T>* root, void(*visit)(T& data));
	void PreOrderTraversal(TreeNode<T>* root, void(*visit)(T& data));
	void PostOrderTraversal(TreeNode<T>* root, void(*visit)(T& data));
	TreeNode<T>* m_root;

};

//everything that isn't breadth first errors by missing out on some of the first values. WHY. WHY, WHY.

/**********************************************************************
*BinarySearchTree<T>::BinarySearchTree()
*
*Purpose:	Create a default object when no parameters are passed.
*Entry:		An object is being instantiated without specified parameters.
*Exit:		A BinarySearchTree object with default values is constructed
*			and	instantiated.
***********************************************************************/
template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{}

/**********************************************************************
*BinarySearchTreeedList<T>::BinarySearchTree<T>(const BinarySearchTree<T> & copy)
*
*Purpose:	Copies the contents of one BinarySearchTree object into a newly
*			instantiated BinarySearchTree object.
*Entry:		One object has been created, and another is being instantiated
*			upon entry. The object being copied will have its contents
*			copied over into the newly created object.
*Exit:		The new object contains all of the attributes of the object
*			on the right hand side (that was copied).
***********************************************************************/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& copy)
{
	*this = copy;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& move) noexcept
{
	*this = move;
}

/**********************************************************************
*BinarySearchTree<T> & BinarySearchTree<T>::operator=(const BinarySearchTree<T> & copy)
*
*Purpose:	Assigns one object's attributes and data to another object's.
*Entry:		Two objects that have already been instantiated are set equal
*			to one another. The object on the right of the = sign is the
*			object whose data is being copied over to the object on the
*			left of the = sign.
*Exit:		The right object's attributes and data have been copied over
*			to the left object's. Whatever old information has been
*			deleted and re-initialized.
***********************************************************************/
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& copy)
{
	if (this != &copy)
	{
		Purge();
		CopyTree(this->m_root, copy.m_root);
	}
	return *this;
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& move) noexcept
{
	if (this != &move)
	{
		Purge();
		CopyTree(this->m_root, move.m_root);
	}
	return *this;
}

/**********************************************************************
*void BinarySearchTree<T>::CopyTree(TreeNode<T> *& newtree, TreeNode<T> * oldtree)
*
*Purpose:	Copies the tree to a new tree.
*Entry:		The copy constructor is being called and the previous tree
*			needs to be copied.
*Exit:		The tree has been copied and is changed via pointer-reference.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::CopyTree(TreeNode<T>*& newtree, TreeNode<T>* oldtree)
{
	if (oldtree == nullptr)
		newtree = nullptr;
	else
	{
		newtree = new TreeNode<T>(oldtree->m_data);
		CopyTree(newtree->m_left, oldtree->m_left);
		CopyTree(newtree->m_right, oldtree->m_right);
	}
}

/**********************************************************************
*BinarySearchTree<T>::~BinarySearchTree()
*
*Purpose:	Deallocates used memory and returns objects to a default state.
*Entry:		The program has reached the end of  main (return 0), and all
*			objects that have been instantiated are going to be purged.
*Exit:		Any object that allocated memory has given that memory back.
*			all other private data members are returned to a deault state.
***********************************************************************/
template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	Purge();
}

/**********************************************************************
*void BinarySearchTree<T>::Insert(T data)
*
*Purpose:	Inserts new data into the BST.
*Entry:		A BST object has been created and new data is being inserted.
*Exit:		The data has been turned into a node and has been inserted
*			into the BST.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::Insert(T data)
{
	Insert(m_root, data);
}

/**********************************************************************
*void BinarySearchTree<T>::Insert(TreeNode<T> *& root, T data)
*
*Purpose:	Inserts new data into the BST.
*Entry:		A BST object has been created and new data is being inserted
*			recursively based on its place in the BST.
*Exit:		Once the data finds its place in the tree, it is allocated
*			into a node and added to the tree.
***********************************************************************/
template <typename T>
TreeNode<T>* BinarySearchTree<T>::Insert(TreeNode<T>*& root, T data)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>(data);
	}
	else if (root->m_data < data) //if 20 less than 15, go right
		root->m_right = Insert(root->m_right, data);
	else
		root->m_left = Insert(root->m_left, data);

	return root;

}

/**********************************************************************
*bool BinarySearchTree<T>::FindNode(T data)
*
*Purpose:	Finds the data passed as a parameter in a BST.
*Entry:		Partiuclar data is being requested to be found in the tree.
*Exit:		This function is called recursively once the data is found.
*			If found, the data will be deleted from the BST. If the data
*			is found, a boolean returns 'true'. Else, the data is not
*			in the BST.
***********************************************************************/
template <typename T>
bool BinarySearchTree<T>::FindNode(T data)
{
	bool found = false;
	if (m_root == nullptr)
		throw Exception("ERROR: The tree is empty.");
	else
	{
		TreeNode<T>* current = m_root;
		TreeNode<T>* prev = m_root;
		while (current != nullptr && !found)
		{
			if (current->m_data == data)
				found = true;
			else
			{
				prev = current;
				if (current->m_data > data)
					current = current->m_left;
				else
					current = current->m_right;
			}
		}
		if (found)
		{
			if (current->m_data == m_root->m_data)
				DeleteFromTree(m_root);
			else if (prev->m_data > data)
				DeleteFromTree(prev->m_left);
			else
				DeleteFromTree(prev->m_right);
		}
		else
			throw Exception("ERROR: Node not found.");
	}
	return found;
}

/**********************************************************************
*void BinarySearchTree<T>::Delete(T data)
*
*Purpose:	Deletes a node from the BST.
*Entry:		A BST object has been created and data is going to be deleted
*			from it.
*Exit:		If the data exists in the tree, the information will be
*			deleted from the tree.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::Delete(T data)
{
	bool found = FindNode(data);
}

/**********************************************************************
*void BinarySearchTree<T>::DeleteFromTree()
*
*Purpose:	Deletes a node from the BST.
*Entry:		A BST object has been created and data is being deleted.
*Exit:		The data has been found thorugh the FindNode function and
*			is not being deleted from the tree. Based on how many
*			children the node has, certain steps need to be taken to
*			reassure the tree is still connected and still a BST.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::DeleteFromTree(TreeNode<T>*& node)
{
	// 4 CASES:
	//	leaf node
	//	right node
	//	left node
	//  two children
	TreeNode<T>* current = node;
	TreeNode<T>* prev = nullptr;
	if (node == nullptr)
		throw Exception("ERROR: Node not found.");
	else if (node->m_left == nullptr && node->m_right == nullptr)
		node = nullptr;
	else if (node->m_left == nullptr)
		node = node->m_right;
	else if (node->m_right == nullptr)
		node = node->m_left;
	else
	{
		current = node->m_left;
		while (current->m_right != nullptr)
		{
			prev = current;
			current = current->m_right;
		}
		node->m_data = current->m_data;
		if (prev == nullptr)
			node->m_left = current->m_left;
		else
			prev->m_right = current->m_left;
	}
	delete current;
	current = nullptr;
}

/**********************************************************************
*void BinarySearchTree<T>::Purge()
*
*Purpose:	Deallocates all memory used in the BST.
*Entry:		A BST has been created and now requires all nodes to be
*			deallocated and all data members returned to their original
*			values.
*Exit:		The nodes have been deleted and the root is nullptr again.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::Purge()
{
	Purge(m_root);
	m_root = nullptr;
}

/**********************************************************************
*void BinarySearchTree<T>::Purge(TreeNode<T> * node)
*
*Purpose:	Traverses through the BST to deallocate all used memory.
*Entry:		A BST has been created and now requires all nodes to be
*			deallocated and all data members returned to their original
*			values.
*Exit:		A node has been deleted, and will recursively call this function
*			until the node is finds is nullptr.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::Purge(TreeNode<T>* node)
{
	if (node != nullptr)
	{
		Purge(node->m_left);
		Purge(node->m_right);
		delete node;
		node = nullptr;
	}
}

/**********************************************************************
*int BinarySearchTree<T>::Height()
*
*Purpose:	Returns the height of the BST.
*Entry:		The height of the BST has been requested by the user.
*Exit:		The height of the BST is returned.
***********************************************************************/
template <typename T>
int BinarySearchTree<T>::Height()
{
	return Height(m_root);
}

/**********************************************************************
*int BinarySearchTree<T>::Height(TreeNode<T> * node)
*
*Purpose:	Calculates the height of the BST.
*Entry:		The current node's height is calculated.
*Exit:		The final height of the BST is returned after recursively
*			calculating the height of every node and finding the largest
*			height.
***********************************************************************/
template <typename T>
int BinarySearchTree<T>::Height(TreeNode<T>* node)
{
	if (node == nullptr)
		return -1;
	int l_height = Height(node->m_left);
	int r_height = Height(node->m_right);

	if (l_height > r_height)
		return l_height + 1;
	else
		return r_height + 1;
}

/**********************************************************************
*void BinarySearchTree<T>::BreadthFirstTraversal(void (*visit)(T & data))
*
*Purpose:	Conducts a Breadth First Traversal.
*Entry:		The user has requested a Breadth First Traversal on the BST.
*Exit:		A display of all nodes is presented to the user.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::BreadthFirstTraversal(void(*visit)(T& data))
{
	BreadthFirstTraversal(m_root, visit);
}

/**********************************************************************
*void BinarySearchTree<T>::BreadthFirstTraversal(TreeNode<T> * node, void (*visit)(T & data))
*
*Purpose:	Conducts a Breadth First Traversal.
*Entry:		A BST has been created and will visit the current node and
*			display its data value back to the user.
*Exit:		A display of all nodes' data will be displayed to the user
*			and will be completed once the recursive calls find the last
*			leaf node. .
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::BreadthFirstTraversal(TreeNode<T>* root, void(*visit)(T& data))
{
	queue<TreeNode<T>*> q;
	TreeNode<T>* current = root;

	if (current != nullptr)
	{
		q.push(current);
		while (!q.empty())
		{
			current = q.front();
			q.pop();
			visit(current->m_data);

			if (current->m_left != nullptr)
				q.push(current->m_left);
			if (current->m_right != nullptr)
				q.push(current->m_right);
		}
	}
	else
		throw Exception("ERROR: Nothing in the tree.");
}

/**********************************************************************
*void BinarySearchTree<T>::InOrderTraversal(void (*visit)(T & data))
*
*Purpose:	Conducts an In Order Traversal.
*Entry:		The user has requested an In Order Traversal on the BST.
*Exit:		A display of all nodes is presented to the user.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::InOrderTraversal(void(*visit)(T& data))
{
	InOrderTraversal(m_root, visit);
}

/**********************************************************************
*void BinarySearchTree<T>::InOrderTraversal(TreeNode<T> * node, void (*visit)(T & data))
*
*Purpose:	Conducts an In Order Traversal.
*Entry:		A BST has been created and will visit the current node and
*			display its data value back to the user.
*Exit:		A display of all nodes' data will be displayed to the user
*			and will be completed once the recursive calls find the last
*			leaf node. .
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::InOrderTraversal(TreeNode<T>* root, void(*visit)(T& data))
{
	queue<TreeNode<T>*> q;
	TreeNode<T>* current = root;

	if (root != nullptr)
	{
		//current = q.front();

		InOrderTraversal(current->m_left, visit);
		visit(root->m_data);

		InOrderTraversal(current->m_right, visit);
		//INTERESTING, left notices the values!!!!!!!! HOW DO I MOVE THE ROOT OVER THERE TO PRINT THEM
				//Nodes are missing from even post/pre order, flat out missing values, why?
	}
}

/**********************************************************************
*void BinarySearchTree<T>::PreOrderTraversal(void (*visit)(T & data))
*
*Purpose:	Conducts a Pre Order Traversal.
*Entry:		The user has requested a Pre Order Traversal on the BST.
*Exit:		A display of all nodes is presented to the user.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::PreOrderTraversal(void(*visit)(T& data))
{
	PreOrderTraversal(m_root, visit);
}

/**********************************************************************
*void BinarySearchTree<T>::PreOrderTraversal(TreeNode<T> * node, void (*visit)(T & data))
*
*Purpose:	Conducts a Pre Order Traversal.
*Entry:		A BST has been created and will visit the current node and
*			display its data value back to the user.
*Exit:		A display of all nodes' data will be displayed to the user
*			and will be completed once the recursive calls find the last
*			leaf node. .
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::PreOrderTraversal(TreeNode<T>* root, void(*visit)(T& data))
{
	if (root != nullptr)
	{
		visit(root->m_data);

		PreOrderTraversal(root->m_left, visit); //SHOULD BE LEFT!

		PreOrderTraversal(root->m_right, visit);
	}
}

/**********************************************************************
*void BinarySearchTree<T>::PostOrderTraversal(void (*visit)(T & data))
*
*Purpose:	Conducts a Post Order Traversal.
*Entry:		The user has requested a Post Order Traversal on the BST.
*Exit:		A display of all nodes is presented to the user.
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::PostOrderTraversal(void(*visit)(T& data))
{
	PostOrderTraversal(m_root, visit);
}

/**********************************************************************
*void BinarySearchTree<T>::PostOrderTraversal(TreeNode<T> * node, void (*visit)(T & data))
*
*Purpose:	Conducts a Post Order Traversal.
*Entry:		A BST has been created and will visit the current node and
*			display its data value back to the user.
*Exit:		A display of all nodes' data will be displayed to the user
*			and will be completed once the recursive calls find the last
*			leaf node. .
***********************************************************************/
template <typename T>
void BinarySearchTree<T>::PostOrderTraversal(TreeNode<T>* root, void(*visit)(T& data))
{
	if (root != nullptr)
	{
		PostOrderTraversal(root->m_left, visit); //SHOULD BE LEFT!
		PostOrderTraversal(root->m_right, visit);
		visit(root->m_data);
	}
}

#endif