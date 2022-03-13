#ifndef AVLTREE_H
#define AVLTREE_H
#include "BinarySearchTree.h"

template <typename T>
class AVLTree : public BinarySearchTree<T>
{

public:
	AVLTree();
	AVLTree(const AVLTree<T>& copy);
	AVLTree(AVLTree<T>&& move) noexcept;
	AVLTree<T>& operator=(const AVLTree<T>& copy);
	AVLTree<T>& operator=(AVLTree<T>&& copy) noexcept;
	~AVLTree();
	void Insert(T data) override;
	void Traverse(void(*display)(T& data));
	void Delete(T data) override;
private:

	void InsertAVL(TreeNode<T>*& root, T data, bool& taller);
	TreeNode<T>* RotateRight(TreeNode<T>*& root);
	TreeNode<T>* RotateLeft(TreeNode<T>*& root);
	void LeftBalance(TreeNode<T>*& root, bool& taller);
	void RightBalance(TreeNode<T>*& root, bool& taller);
	void AVLDelete(TreeNode<T>*& root, T data, bool& shorter, bool& success);
	void DeleteRightBalance(TreeNode<T>*& root, bool& shorter);
	void DeleteLeftBalance(TreeNode<T>*& root, bool& shorter);
	void AVLTraverse(void(*display)(T& data), TreeNode<T>* root);

};

/**********************************************************************
*AVLTree<T>::AVLTree()
*
*Purpose:	Create an object when default parameters are passed to it.
*Entry:		An object is being instantiated without specified parameters.
*Exit:		An AVLTree object with default values is constructed
*			and	instantiated.
***********************************************************************/
template <typename T>
AVLTree<T>::AVLTree()
{
	m_root = nullptr;
}

/**********************************************************************
*AVLTree<T>::AVLTree<T>(const AVLTree<T> & copy)
*
*Purpose:	Copies the contents of one AVLTree object into a newly
*			instantiated AVLTree object.
*Entry:		One object has been created, and another is being instantiated
*			upon entry. The object being copied will have its contents
*			copied over via a deep copy into the newly created object.
*Exit:		The new object contains all of the attributes of the object
*			on the right hand side (that was copied).
***********************************************************************/
template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& copy)
{
	*this = copy;
}

template <typename T>
AVLTree<T>::AVLTree(AVLTree<T>&& move) noexcept
{
	*this = copy;
}

/**********************************************************************
*AVLTree<T>::~AVLTree()
*
*Purpose:	Deallocates used memory and returns objects to a default state.
*Entry:		The program has reached the end of  main (return 0), and all
*			objects that have been instantiated are going to be purged.
*Exit:		Any object that allocated memory has given that memory back.
*			all other private data members are returned to a deault state.
***********************************************************************/
template <typename T>
AVLTree<T>::~AVLTree()
{}

/**********************************************************************
*AVLTree<T> & AVLTree<T>::operator=(const AVLTree<T> & rhs)
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
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& copy)
{
	if (this != &copy)
	{
		Purge();
		CopyTree(this->m_root, copy.m_root);
	}
	return *this;
}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree<T>&& move) noexcept
{
	if (this != &move)
	{
		Purge();
		CopyTree(this->m_root, move.m_root);
	}
	return *this;
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::Insert(TreeNode<T> *& root, T data, bool & taller)
*
*Purpose:	Inserts new data into the AVL Tree.
*Entry:		A AVL Tree object has been created and new data is being inserted
*			recursively based on its place in the BST. Depending on the
*			balance factors, there may been to be rotations conducted
*			to keep the tree balanced.
*Exit:		Once the data finds its place in the tree, it is allocated
*			into a node and added to the tree.
***********************************************************************/
template <typename T>
void AVLTree<T>::Insert(T data)
{
	bool taller;
	InsertAVL(m_root, data, taller);
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::Insert(TreeNode<T> *& root, T data, bool & taller)
*
*Purpose:	Inserts new data into the AVL Tree.
*Entry:		A AVL Tree object has been created and new data is being inserted
*			recursively based on its place in the BST. Depending on the
*			balance factors, there may been to be rotations conducted
*			to keep the tree balanced.
*Exit:		Once the data finds its place in the tree, it is allocated
*			into a node and added to the tree.
***********************************************************************/
template <typename T>
void AVLTree<T>::InsertAVL(TreeNode<T>*& root, T data, bool& taller)
{
	if (!root)
	{
		root = new TreeNode<T>(data);
		taller = true;
	}
	else if (data < root->m_data)
	{
		InsertAVL(root->m_left, data, taller);
		if (taller)
		{
			switch (root->m_balance_factor)
			{
			case LH:	// left heavy
			{
				LeftBalance(root, taller);
				break;
			}
			case EH:
			{
				root->m_balance_factor = LH;
				break;
			}
			case RH:
			{
				root->m_balance_factor = EH;
				taller = false;
				break;
			}
			}
		}
	}
	else
	{
		InsertAVL(root->m_right, data, taller);
		if (taller)
		{
			switch (root->m_balance_factor)
			{
			case LH:
			{
				root->m_balance_factor = EH;
				taller = false;
				break;
			}
			case EH:
			{
				root->m_balance_factor = RH;
				break;
			}
			case RH:
			{
				RightBalance(root, taller);
				break;
			}
			}
		}
	}
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::LeftBalance(TreeNode<T> *& root, bool & taller)
*
*Purpose:	The AVL Tree has Left Heavy. It must do an RR Rotation.
*Entry:
*Exit:		The tree is balanced again by the time it leaves this
*			function.
***********************************************************************/
template <typename T>
void AVLTree<T>::LeftBalance(TreeNode<T>*& root, bool& taller)
{
	TreeNode<T>* right;
	TreeNode<T>* left;

	left = root->m_left;
	switch (left->m_balance_factor)
	{
	case LH:
	{
		root->m_balance_factor = EH;
		left->m_balance_factor = EH;
		root = RotateRight(root);
		taller = false;
		break;
	}
	case EH:
	{
		throw Exception("ERROR: LeftBalance is not working properly.");
		break;
	}
	case RH:
	{
		right = left->m_right;
		switch (right->m_balance_factor)
		{
		case LH:
		{
			root->m_balance_factor = RH;
			left->m_balance_factor = EH;
			break;
		}
		case EH:
		{
			root->m_balance_factor = EH;
			left->m_balance_factor = EH;
			break;
		}
		case RH:
		{
			root->m_balance_factor = EH;
			left->m_balance_factor = LH;
			break;
		}
		}

		right->m_balance_factor = EH;
		root->m_left = RotateLeft(left);

		root = RotateRight(root);
		taller = false;
		break;
	}
	}
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::RightBalance(TreeNode<T> *& root, bool & taller)
*
*Purpose:	The AVL Tree has Right Heavy. It must do an RR Rotation.
*Entry:
*Exit:		The tree is balanced again by the time it leaves this
*			function.
***********************************************************************/
template <typename T>
void AVLTree<T>::RightBalance(TreeNode<T>*& root, bool& shorter)
{
	TreeNode<T>* right;
	TreeNode<T>* left;
	right = root->m_right;
	switch (right->m_balance_factor)
	{
	case LH:
	{
		left = right->m_left;

		switch (left->m_balance_factor)
		{
		case LH:
		{
			root->m_balance_factor = EH;
			right->m_balance_factor = RH;
			break;
		}
		case EH:
		{
			root->m_balance_factor = EH;
			right->m_balance_factor = EH;
			break;
		}
		case RH:
		{
			root->m_balance_factor = LH;
			right->m_balance_factor = EH;
			break;
		}
		}

		left->m_balance_factor = EH;
		root->m_right = RotateRight(right);

		root = RotateLeft(root);
		shorter = false;
		break;
	}
	case EH:
	{
		throw Exception("Right Balance is not working...");
		break;
	}
	case RH:
	{	root->m_balance_factor = EH;
	right->m_balance_factor = EH;
	root = RotateLeft(root);
	shorter = false;
	break;
	}
	}
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::RotateRight(TreeNode<T> *& root)
*
*Purpose:	Conducts the RR Rotation.
*Entry:		An AVL Tree, when out of balance to the left side, but
*			have an RR rotation done to restore balance to the tree.
*Exit:		The tree is balanced again by the time it leaves this
*			function.
***********************************************************************/
template <typename T>
TreeNode<T>* AVLTree<T>::RotateRight(TreeNode<T>*& root)
{
	TreeNode<T>* temp;
	temp = root->m_left;
	root->m_left = temp->m_right;
	temp->m_right = root;

	return temp;
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::RotateLeft(TreeNode<T> *& root)
*
*Purpose:	Conducts the LL Rotation.
*Entry:		An AVL Tree, when out of balance to the right side, but
*			have an LL rotation done to restore balance to the tree.
*Exit:		The tree is balanced again by the time it leaves this
*			function.
***********************************************************************/
template <typename T>
TreeNode<T>* AVLTree<T>::RotateLeft(TreeNode<T>*& root)
{
	TreeNode<T>* temp;
	temp = root->m_right;
	root->m_right = temp->m_left;
	temp->m_left = root;

	return temp;
}

/**********************************************************************
*void AVLTree<T>::Delete(T data)
*
*Purpose:	Deletes a node from the AVL Tree.
*Entry:		An AVL Tree object has been created and data is going to be
*			deleted from it.
*Exit:		If the data exists in the tree, the information will be
*			deleted from the tree.
***********************************************************************/
template <typename T>
void AVLTree<T>::Delete(T data)
{
	bool shorter = false;
	bool success = false;
	AVLDelete(m_root, data, shorter, success);
	if (!success)
		throw Exception("ERROR: Data not found.");
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::AVLDelete(TreeNode<T> *& root, bool & shorter, bool & success, T data)
*
*Purpose:	Deletes a node from the AVL Tree.
*Entry:		An AVL Tree object has been created and data is going to be
*			deleted from it. This is the private function called when
*			the user requests a particular node to be deleted. The data
*			will be sought for recursively.
*Exit:		If the data exists in the tree, the information will be
*			deleted from the tree, and the function will return an
*			appropriate success flag.
***********************************************************************/
template <typename T>
void AVLTree<T>::AVLDelete(TreeNode<T>*& root, T data, bool& shorter, bool& success)
{
	TreeNode<T>* todelete = nullptr;
	TreeNode<T>* exchange = nullptr;
	TreeNode<T>* newroot = nullptr;

	if (!root)
	{
		shorter = false;
		success = false;
	}
	else
	{
		if (data < root->m_data)
		{
			AVLDelete(root->m_left, data, shorter, success);
			if (shorter)
				DeleteRightBalance(root, shorter);
		}
		else if (data > root->m_data)
		{
			AVLDelete(root->m_right, data, shorter, success);
			if (shorter)
				DeleteLeftBalance(root, shorter);
		}
		else // data is equivalent
		{
			todelete = root;
			if (!root->m_right)
			{
				newroot = root->m_left;
				success = true;
				shorter = true;
				delete todelete;
				todelete = nullptr;
				root = newroot;
			}
			else
			{
				if (!root->m_left)
				{
					newroot = root->m_right;
					success = true;
					shorter = true;
					delete todelete;
					todelete = nullptr;
					root = newroot;
				}
				else
				{
					exchange = root->m_left;
					while (exchange->m_right)
						exchange = exchange->m_right;
					root->m_data = exchange->m_data;
					AVLDelete(root->m_left, exchange->m_data, shorter, success);
					if (shorter)
						DeleteRightBalance(root, shorter);
				}
			}
		}
	}
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::DeleteRightBalance(TreeNode<T> *& root, T data)
*
*Purpose:	Rebalances the tree using a rotation, either LL or RL depending
*			on what case the delete has created in the tree.
*Entry:		An AVL Tree object has been created and data is being deleted
*			from it.
*Exit:		The tree will be rebalanced.
***********************************************************************/
template <typename T>
void AVLTree<T>::DeleteRightBalance(TreeNode<T>*& root, bool& shorter)
{
	TreeNode<T>* right;
	TreeNode<T>* left;

	switch (root->m_balance_factor)
	{
	case LH:
	{
		root->m_balance_factor = EH;
		break;
	}
	case EH:
	{
		root->m_balance_factor = RH;
		shorter = false;
		break;
	}
	case RH:
	{
		right = root->m_right;
		if (right->m_balance_factor == LH)
		{
			left = right->m_left;
			switch (left->m_balance_factor)
			{
			case LH:
			{
				right->m_balance_factor = RH;
				root->m_balance_factor = EH;
				break;
			}
			case EH:
			{
				root->m_balance_factor = EH;
				right->m_balance_factor = EH;
				break;
			}
			case RH:
			{
				root->m_balance_factor = LH;
				right->m_balance_factor = EH;
				break;
			}
			}
			left->m_balance_factor = EH;
			root->m_right = RotateRight(right);
			root = RotateLeft(root);
		}
		else
		{
			switch (right->m_balance_factor)
			{
			case LH:
			{}
			case RH:
			{
				root->m_balance_factor = EH;
				right->m_balance_factor = EH;
				break;
			}
			case EH:
			{
				root->m_balance_factor = RH;
				right->m_balance_factor = LH;
				shorter = false;
				break;
			}
			}
			root = RotateLeft(root);

		}
	}
	}
}

/**********************************************************************
*TreeNode<T> * AVLTree<T>::DeleteLeftBalance(TreeNode<T> *& root, T data)
*
*Purpose:	Rebalances the tree using a rotation, either LR or RR depending
*			on what case the delete has created in the tree.
*Entry:		An AVL Tree object has been created and data is being deleted
*			from it.
*Exit:		The tree will be rebalanced.
***********************************************************************/
template <typename T>
void AVLTree<T>::DeleteLeftBalance(TreeNode<T>*& root, bool& shorter)
{
	TreeNode<T>* right;
	TreeNode<T>* left;

	switch (root->m_balance_factor)
	{
	case RH:
	{
		root->m_balance_factor = EH;
		break;
	}
	case EH:
	{
		root->m_balance_factor = LH;
		shorter = false;
		break;
	}
	case LH:
	{
		left = root->m_left;
		if (left->m_balance_factor == RH)
		{
			right = left->m_right;
			switch (right->m_balance_factor)
			{
			case RH:
			{
				left->m_balance_factor = LH;
				root->m_balance_factor = EH;
				break;
			}
			case EH:
			{
				root->m_balance_factor = EH;
				left->m_balance_factor = EH;
				break;
			}
			case LH:
			{
				root->m_balance_factor = RH;
				left->m_balance_factor = EH;
				break;
			}
			}
			right->m_balance_factor = EH;
			root->m_left = RotateLeft(left);
			root = RotateRight(root);
		}
		else
		{
			switch (left->m_balance_factor)
			{
			case RH:
			{}
			case LH:
			{
				root->m_balance_factor = EH;
				left->m_balance_factor = EH;
				break;
			}
			case EH:
			{
				root->m_balance_factor = LH;
				left->m_balance_factor = RH;
				shorter = false;
				break;
			}
			}
			root = RotateRight(root);
		}
	}
	}
}

/**********************************************************************
*void AVLTree<T>::Traverse(void (*display)(T & data))
*
*Purpose:	Traverses through and displays the AVL tree.
*Entry:		The user wants to see a traversal of the tree.
*Exit:		The tree will be displayed to the user.
***********************************************************************/
template <typename T>
void AVLTree<T>::Traverse(void(*display)(T& data))
{
	AVLTraverse(display, m_root);
}

/**********************************************************************
*void AVLTree<T>::AVLTraverse(void (*display)(T & data))
*
*Purpose:	Uses an In Order Traversal to display the tree to the user.
*Entry:		The function is being recursively called to display each
*			node in the AVL Tree.
*Exit:		The node's data is displayed to the user with each recursive
*			pass.
***********************************************************************/
template <typename T>
void AVLTree<T>::AVLTraverse(void(*display)(T& data), TreeNode<T>* root)
{
	if (root != nullptr)
	{
		AVLTraverse(display, root->m_left);
		display(root->m_data);
		AVLTraverse(display, root->m_right);
	}
}

#endif