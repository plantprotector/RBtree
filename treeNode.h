#ifndef TREE_NODE_H
#define TREE_NODE_H

#include<memory>
enum color {red, black};
template <class T>
class treeNode
{
    
    public:
    treeNode();
    treeNode(T data);
    std::shared_ptr<treeNode<T>> leftChild;
    std::shared_ptr<treeNode<T>> rightChild;
    std::weak_ptr<treeNode<T>> parent;
    T key;
    color cl;



};


template< class T >
treeNode<T>::treeNode()
{
    cl = black;

}

template< class T >
treeNode<T>::treeNode(T data)
{
    key = data;
    cl = red;

}



#endif
