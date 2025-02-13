/* Copyright (C) 2005-2024, UNIGINE. All rights reserved.
*
* This file is a part of the UNIGINE 2 SDK.
*
* Your use and / or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the UNIGINE License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the UNIGINE License Agreement is available by contacting
* UNIGINE. at http://unigine.com/
*/

#pragma once

#include <UnigineVector.h>

namespace Unigine
{

template <typename Key, typename Data>
class Tree
{
public:
	using NodeType = Data;
	template<typename IteratorType>
	class IteratorTemplate
	{
	private:
		friend class Tree<Key, Data>;
	public:
		using KeyType = Key;
		using DataType = Data;

		UNIGINE_INLINE IteratorTemplate()
			: node(nullptr)
		{}
		UNIGINE_INLINE IteratorTemplate(NodeType *node)
			: node(node)
		{}
		UNIGINE_INLINE IteratorTemplate(const IteratorTemplate &it)
			: node(it.node)
		{}

		UNIGINE_INLINE IteratorTemplate &operator=(const IteratorTemplate &it) { node = it.node; return *this; }

		template<typename T>
		UNIGINE_INLINE bool operator!=(const IteratorTemplate<T> &o) const { return node != o.get(); }
		template<typename T>
		UNIGINE_INLINE bool operator==(const IteratorTemplate<T> &o) const { return node == o.get(); }

		UNIGINE_INLINE IteratorType &operator*() const { return *node; }
		UNIGINE_INLINE IteratorType *operator->() const { return node; }
		UNIGINE_INLINE IteratorType *get() const { return node; }

		IteratorTemplate &operator++() { next(); return *this; }
		IteratorTemplate &operator--() { prev(); return *this; }
		IteratorTemplate operator++(int) { IteratorTemplate it = *this; next(); return it; }
		IteratorTemplate operator--(int) { IteratorTemplate it = *this; prev(); return it; }

		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = IteratorType;
		using pointer = IteratorType *;
		using reference = IteratorType &;

	private:
		void next()
		{
			if (node->right)
			{
				node = node->right;
				while (node->left)
					node = node->left;
			} else
			{
				NodeType *p = node->parent;
				while (p && node == p->right)
				{
					node = p;
					p = p->parent;
				}
				if (p == nullptr || node->right != p)
					node = p;
			}
		}
		void prev()
		{
			if (node->left)
			{
				node = node->left;
				while (node->right)
					node = node->right;
			} else
			{
				NodeType *p = node->parent;
				while (p && node == p->left)
				{
					node = p;
					p = p->parent;
				}
				if (p == nullptr || node->left != p)
					node = p;
			}
		}

		NodeType *node;
	};

	using Iterator = IteratorTemplate<NodeType>;
	using ConstIterator = IteratorTemplate<const NodeType>;

	using iterator = Iterator;
	using const_iterator = ConstIterator;

public:

	Tree()
		: length(0)
		, root(nullptr)
	{
	}

	~Tree() { delete root; }

	void swap(Tree &o)
	{
		if (root == o.root)
			return;
		int i = length;
		length = o.length;
		o.length = i;
		NodeType *n = root;
		root = o.root;
		o.root = n;
	}

	UNIGINE_INLINE Iterator begin() { return Iterator(get_begin()); }
	UNIGINE_INLINE Iterator back() { return Iterator(get_back()); }
	UNIGINE_INLINE Iterator end() { return Iterator(nullptr); }

	UNIGINE_INLINE ConstIterator begin() const { return ConstIterator(get_begin()); }
	UNIGINE_INLINE ConstIterator cbegin() const { return ConstIterator(get_begin()); }
	UNIGINE_INLINE ConstIterator back() const { return ConstIterator(get_back()); }
	UNIGINE_INLINE ConstIterator end() const { return ConstIterator(nullptr); }
	UNIGINE_INLINE ConstIterator cend() const { return ConstIterator(nullptr); }

	UNIGINE_INLINE int size() const { return length; }
	UNIGINE_INLINE size_t getMemoryUsage() const
	{
		size_t ret = 0;
		ret += sizeof(length);
		ret += sizeof(NodeType *);
		ret += length * sizeof(NodeType);
		return ret;
	}
	UNIGINE_INLINE bool empty() const { return (length == 0); }
	UNIGINE_INLINE void clear()
	{
		length = 0;
		delete root;
		root = nullptr;
	}

	template <class T>
	UNIGINE_INLINE Iterator find(const T &key) { return Iterator(do_find(key)); }
	template <class T>
	UNIGINE_INLINE ConstIterator find(const T &key) const { return ConstIterator(do_find(key)); }

	template<class T>
	UNIGINE_INLINE Iterator lowerBound(const T &key) { return do_lower_bound(key); }

	template<class T>
	UNIGINE_INLINE ConstIterator lowerBound(const T &key) const { return do_lower_bound(key); }

	template<class T>
	UNIGINE_INLINE Iterator upperBound(const T &key) { return do_upper_bound(key); }

	template<class T>
	UNIGINE_INLINE ConstIterator upperBound(const T &key) const { return do_upper_bound(key); }

	UNIGINE_INLINE bool remove(const Key &key)
	{
		NodeType *node = do_remove(key);
		bool ret = node != nullptr;
		delete node;
		return ret;
	}
	template<typename IteratorType>
	UNIGINE_INLINE bool remove(const IteratorTemplate<IteratorType> &it) {
		NodeType *node = do_remove(it.node);
		bool ret = node != nullptr;
		delete node;
		return ret;
	}

	UNIGINE_INLINE bool erase(const Key &key) { return remove(key); }
	template<typename IteratorType>
	UNIGINE_INLINE IteratorTemplate<IteratorType> erase(const IteratorTemplate<IteratorType> &it)
	{
		auto ret = it; ++ret;
		remove(it);
		return ret;
	}

	template <class T>
	UNIGINE_INLINE bool contains(const T &key) const
	{
		NodeType *node = root;
		while (node && (node->key == key) == 0)
			node = node->dirs[key < node->key];
		return node != nullptr;
	}

	UNIGINE_INLINE Vector<Key> keys() const {
		Vector<Key> keys;
		getKeys(keys);
		return keys;
	}

	UNIGINE_INLINE void getKeys(Vector<Key> &keys) const {
		keys.allocate(keys.size() + length);
		ConstIterator end_it = end();
		for (ConstIterator it = begin(); it != end_it; ++it)
			keys.appendFast(it->key);
	}

protected:
	UNIGINE_INLINE NodeType *get_begin() const
	{
		if (root)
		{
			NodeType *node = root;
			while (node->left)
				node = node->left;
			return node;
		}
		return nullptr;
	}
	UNIGINE_INLINE NodeType *get_back() const
	{
		if (root)
		{
			NodeType *node = root;
			while (node->right)
				node = node->right;
			return node;
		}
		return nullptr;
	}
	void copy_proc(NodeType *&dest_root, NodeType *&dest_parent, const NodeType *src_root)
	{
		if (src_root == nullptr)
			return;
		length++;
		dest_root = new NodeType(*src_root);
		dest_root->parent = dest_parent;
		dest_root->balance = src_root->balance;

		copy_proc(dest_root->left, dest_root, src_root->left);
		copy_proc(dest_root->right, dest_root, src_root->right);
	}

	template<typename T>
	UNIGINE_INLINE NodeType *do_find(const T &key) const
	{
		NodeType *node = root;
		while (node && (node->key == key) == 0)
			node = node->dirs[key < node->key];
		return node;
	}

	template<typename T>
	UNIGINE_INLINE NodeType *do_lower_bound(const T &key) const
	{
		NodeType *node = root;
		NodeType *last_node = nullptr;
		while (node)
		{
			if (node->key < key)
			{
				node = node->right;
			}
			else
			{
				last_node = node;
				node = node->left;
			}
		}
		return last_node;
	}

	template<typename T>
	UNIGINE_INLINE NodeType *do_upper_bound(const T &key) const
	{
		NodeType *node = root;
		NodeType *last_node = nullptr;
		while (node)
		{
			if (key < node->key)
			{
				last_node = node;
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}
		return last_node;
	}

	NodeType *&do_find_node(const Key &key, NodeType *&parent)
	{
		if (root == nullptr)
			return root;

		NodeType *node = root;
		int dir = -1;
		while (node && (node->key == key) == 0)
		{
			parent = node;
			node = node->dirs[dir = (key < node->key)];
		}
		return node == root ? root : parent->dirs[dir];
	}

	template<typename T>
	NodeType *do_append(T &&key)
	{
		NodeType *parent = nullptr;
		NodeType *&finded_node = do_find_node(key, parent);
		if (finded_node == nullptr)
		{
			NodeType *new_node = new NodeType(std::forward<T>(key), parent);
			finded_node = new_node;
			if (parent)
				rebalance_insert(new_node);
			++length;
			return new_node;
		}
		return finded_node;
	}

	NodeType *do_append_node(NodeType *new_node)
	{
		NodeType *parent = nullptr;
		NodeType *&finded_node = do_find_node(new_node->key, parent);
		if (finded_node == nullptr)
		{
			new_node->parent = parent;
			finded_node = new_node;
			if (parent)
				rebalance_insert(new_node);
			++length;
			return new_node;
		}
		assert(0 && "Tree::do_append_node: key already exists");
		delete new_node;
		return nullptr;
	}

	NodeType *do_remove(const Key &key) { return root == nullptr ? nullptr : do_remove(do_find(key)); }

	NodeType *do_remove(NodeType *node)
	{
		if (root == nullptr)
			return nullptr;
		if (node == nullptr)
			return nullptr;
		length--;

		NodeType *parent = node->parent;
		NodeType *target = node->parent;
		NodeType *child;
		bool left = false;
		if (node->left == nullptr)
			child = node->right;
		else if (node->right == nullptr)
			child = node->left;
		else
		{
			target = node->right;
			while (target->left)
				target = target->left;

			if (parent)
				parent->dirs[parent->left == node] = target;
			else
				root = target;

			child = target->right;
			NodeType *targe_parent = target->parent;
			target->parent = parent;
			target->left = node->left;
			node->left->parent = target;
			target->balance = node->balance;

			left = targe_parent != node;
			if (left)
			{
				if (child)
					child->parent = targe_parent;
				targe_parent->left = child;
				target->right = node->right;
				node->right->parent = target;
				target = targe_parent;
			}

			if (root)
				rebalance_remove(target, left);
			node->parent = node->left = node->right = nullptr;
			return node;
		}

		if (parent)
		{
			left = parent->left == node;
			parent->dirs[left] = child;
		} else
			root = child;

		if (child)
			child->parent = parent;

		if (root)
			rebalance_remove(target, left);
		node->parent = node->left = node->right = nullptr;
		return node;
	}

	UNIGINE_INLINE void rotate_left(NodeType *n)
	{
		NodeType *parent = n->parent;
		NodeType *right = n->right;
		n->right = right->left;
		if (n->right)
			n->right->parent = n;

		n->parent = right;
		right->left = n;
		right->parent = parent;
		if (parent == nullptr)
		{
			root = right;
			return;
		}
		parent->dirs[parent->left == n] = right;
	}

	UNIGINE_INLINE void rotate_right(NodeType *n)
	{
		NodeType *parent = n->parent;
		NodeType *left = n->left;
		n->left = left->right;
		if (n->left)
			n->left->parent = n;

		n->parent = left;
		left->right = n;
		left->parent = parent;
		if (parent == nullptr)
		{
			root = left;
			return;
		}
		parent->dirs[parent->left == n] = left;
	}

	UNIGINE_INLINE void rotate_left_right(NodeType *parent)
	{
		rotate_left(parent->left);
		rotate_right(parent);
	}

	UNIGINE_INLINE void rotate_right_left(NodeType *parent)
	{
		rotate_right(parent->right);
		rotate_left(parent);
	}

	void rebalance_insert(NodeType *node)
	{
		NodeType *parent = node;
		do
		{
			node = parent;
			parent = parent->parent;
			if (parent->left == node)
			{
				parent->balance--;
				if (parent->balance == 0)
					return;
				if (parent->balance == -1)
					continue;

				if (node->balance == -1)
				{
					node->balance = parent->balance = 0;
					rotate_right(parent);
					return;
				}

				NodeType *child = node->right;
				parent->balance = node->balance = 0;
				if (child->balance == -1) parent->balance = 1;
				else if (child->balance == 1) node->balance = -1;
				child->balance = 0;

				rotate_left_right(parent);
				return;
			} else
			{
				parent->balance++;
				if (parent->balance == 0)
					return;
				if (parent->balance == 1)
					continue;

				if (node->balance == 1)
				{
					node->balance = parent->balance = 0;
					rotate_left(parent);
					return;
				}

				NodeType *child = node->left;
				parent->balance = node->balance = 0;
				if (child->balance == 1) parent->balance = -1;
				else if (child->balance == -1) node->balance = 1;
				child->balance = 0;

				rotate_right_left(parent);
				return;
			}
		} while (parent->parent);
	}

	void rebalance_remove(NodeType *node, bool left)
	{
		for (NodeType *parent; node; node = parent)
		{
			parent = node->parent;
			if (left)
			{
				node->balance++;
				if (node->balance == 1)
					break;
				if (parent && parent->right == node)
					left = false;
				if (node->balance == 0)
					continue;

				NodeType *child = node->right;

				if (child->balance == 0)
				{
					node->balance = 1;
					child->balance = -1;
					rotate_left(node);
					break;
				}
				if (child->balance == 1)
				{
					node->balance = child->balance = 0;
					rotate_left(node);
					continue;
				}

				NodeType *child_left = child->left;
				node->balance = child->balance = 0;
				if (child_left->balance == 1)
					node->balance = -1;
				else if (child_left->balance == -1)
					child->balance = 1;

				child_left->balance = 0;

				rotate_right_left(node);
			} else
			{
				node->balance--;
				if (node->balance == -1)
					break;
				if (parent && parent->left == node)
					left = true;
				if (node->balance == 0)
					continue;

				NodeType *child = node->left;
				if (child->balance == 0)
				{
					node->balance = -1;
					child->balance = 1;
					rotate_right(node);
					break;
				}

				if (child->balance == -1)
				{
					node->balance = child->balance = 0;
					rotate_right(node);
					continue;
				}

				NodeType *child_right = child->right;
				node->balance = child->balance = 0;
				if (child_right->balance == -1)
					node->balance = 1;
				else if (child_right->balance == 1)
					child->balance = -1;

				child_right->balance = 0;

				rotate_left_right(node);
			}
		}
	}

	int length;
	NodeType *root;
};

}
