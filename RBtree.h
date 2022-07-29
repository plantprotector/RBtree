#ifndef RBTREE_H
#define RBTREE_H

#include "treeNode.h"

template <class T>
class rbTree
{
    public:
    rbTree();
    rbTree(T rootData);

    void insertRBT(T data);
    void deleteRBT(T data);
    private:
    void setRoot(T root);
    std::shared_ptr<treeNode<T>> root();
    void insertFixTree(std::shared_ptr<treeNode<T>> current);
    void deleteFixTree(std::shared_ptr<treeNode<T>> current);
    void leftRotate(std::shared_ptr<treeNode<T>> current);
    void rightRotate(std::shared_ptr<treeNode<T>> current);
    std::shared_ptr<treeNode<T>> header;
    std::shared_ptr<treeNode<T>> nil;



};

template<class T>
rbTree<T>::rbTree()
{
    header = std::make_shared<treeNode<T>>();
    nil = std::make_shared<treeNode<T>>();
}

template<class T>
rbTree<T>::rbTree(T rootData)
{
    header = std::make_shared<treeNode<T>>();
    nil = std::make_shared<treeNode<T>>();
    setRoot(rootData);
}

template<class T>
void rbTree<T>::setRoot(T rootData)
{
    header->leftChild = std::make_shared<treeNode<T>>(rootData);
    header->leftChild->cl = black;
    header->leftChild->parent = header;
    header->leftChild->leftChild = nil;
    header->leftChild->rightChild = nil;
}

template<class T>
void rbTree<T>::insertRBT(T data){
    if(header->leftChild == nullptr){
        setRoot(data);
        return;
    }
    std::shared_ptr<treeNode<T>> t(root());
    bool fixed = false;
    while(t->key != data){
        if(data < t->key){
            if(t->leftChild == nil){
                t->leftChild = std::make_shared<treeNode<T> >(data);
                fixed = true;
                t->leftChild->parent = t;
                t->leftChild->leftChild = nil;
                t->leftChild->rightChild = nil;
            }else{
                t=t->leftChild;
            }
        }else{
            if(t->rightChild == nil){
                t->rightChild = std::make_shared<treeNode<T> >(data);
                fixed = true;
                t->rightChild->parent = t;
                t->rightChild->leftChild = nil;
                t->rightChild->rightChild = nil;
            }else{
                t=t->rightChild;
            }
        }
        
    }
    if(fixed)insertFixTree(t);


}
template<class T>
std::shared_ptr<treeNode<T>> rbTree<T>::root(){
    return header->leftChild;
}

template<class T>
void rbTree<T>::insertFixTree(std::shared_ptr<treeNode<T>> current){
    if(current == root()){
        current->cl = black;
        return;
    }
    if(current->parent.lock()->cl == black)return;
    auto parent = current->parent.lock();
    auto grandpa = parent->parent.lock();
    if(parent == grandpa->leftChild){
        auto uncle = grandpa->rightChild;
        if(uncle->cl == red){
            uncle->cl = black;
            parent->cl = black;
            grandpa->cl = red;
            insertFixTree(grandpa);
        }else if(current == parent->leftChild){
            parent->cl = black;
            grandpa->cl = red;
            rightRotate(grandpa);
        }else{
            leftRotate(parent);
            current->cl = black;
            grandpa->cl = red;
            rightRotate(grandpa);
        }
    }else{
        auto uncle = grandpa->leftChild;
        if(uncle->cl == red){
            uncle->cl = black;
            parent->cl = black;
            grandpa->cl = red;
            insertFixTree(grandpa);
        }else if(current == parent->rightChild){
            parent->cl = black;
            grandpa->cl = red;
            leftRotate(grandpa);
        }else{
            rightRotate(parent);
            current->cl = black;
            grandpa->cl = red;
            leftRotate(grandpa);
        }
    }

}

template<class T>
void rbTree<T>::deleteRBT(T data){
    auto deleteNode = root();
    while(deleteNode->key != data){
        if(deleteNode->key < data){
            deleteNode = deleteNode->rightChild;
        }else{
            deleteNode = deleteNode->leftChild;
        }
        if(deleteNode == nil) return;
    }
    auto y = deleteNode;
    if(y->leftChild != nil && y->rightChild != nil){
        y = y->rightChild;
        while(y->leftChild != nil){
            y = y->leftChild;
        }
        deleteNode->key = y->key;
    }
    decltype(y) x;
    if(y->leftChild != nil){
        x = y->leftChild;
    }else{
        x = y->rightChild;
    }

    x->parent = y->parent;

    if(y == y->parent.lock()->leftChild){
        y->parent.lock()->leftChild = x;
    }else{
        y->parent.lock()->rightChild = x;
    }

    if(y->cl == black){
        deleteFixTree(x);
    }


}

template<class T>
void rbTree<T>::deleteFixTree(std::shared_ptr<treeNode<T>> current){
    while(1){
        if(current == root()){
        return;
        }
        if(current->cl == red){
            current->cl = black;
            return;
        }
        auto parent = current->parent.lock();
        if(parent->leftChild == current){
            auto sibling = parent->rightChild;
            if(sibling->cl == red){
                parent->cl = red;
                sibling->cl = black;
                leftRotate(parent);
                continue;
            }else{
                if(sibling->leftChild->cl == black && sibling->rightChild->cl == black){
                    sibling->cl = red;
                    if(parent->cl == red){
                        parent->cl = black;
                        return;
                    }else{
                        current = parent;
                        continue;
                    }
                }else if(sibling->leftChild->cl == red && sibling->rightChild->cl == black){
                    sibling->cl = red;
                    sibling->leftChild->cl = black;
                    rightRotate(sibling);
                    continue;
                }else{
                    sibling->cl = parent->cl;
                    parent->cl = black;
                    sibling->rightChild->cl = black;
                    leftRotate(parent);
                    current = root();
                    current->cl = black;
                    return;
                }
            }
        }else if(parent->rightChild == current){
            auto sibling = parent->leftChild;
            if(sibling->cl == red){
                parent->cl = red;
                sibling->cl = black;
                rightRotate(parent);
                continue;
            }else{
                if(sibling->rightChild->cl == black && sibling->leftChild->cl == black){
                    sibling->cl = red;
                    if(parent->cl == red){
                        parent->cl = black;
                        return;
                    }else{
                        current = parent;
                        continue;
                    }
                }else if(sibling->rightChild->cl == red && sibling->leftChild->cl == black){
                    sibling->cl = red;
                    sibling->rightChild->cl = black;
                    leftRotate(sibling);
                    continue;
                }else{
                    sibling->cl = parent->cl;
                    parent->cl = black;
                    sibling->leftChild->cl = black;
                    rightRotate(parent);
                    current = root();
                    current->cl = black;
                    return;
                }
            }
        }
    }
    

}

template<class T>
void rbTree<T>::leftRotate(std::shared_ptr<treeNode<T>> current){
    auto y = current;
    auto x = y->rightChild;

    y->rightChild = x->leftChild;
    y->rightChild->parent = y;

    x->parent = y->parent;
    if(y == y->parent.lock()->leftChild){
        y->parent.lock()->leftChild = x;
    }else{
        y->parent.lock()->rightChild = x;
    }

    x->leftChild = y;
    y->parent = x;

}

template<class T>
void rbTree<T>::rightRotate(std::shared_ptr<treeNode<T>> current){
    auto y = current;
    auto x = y->leftChild;

    y->leftChild = x->rightChild;
    y->leftChild->parent = y;

    x->parent = y->parent;
    if(y == y->parent.lock()->leftChild){
        y->parent.lock()->leftChild = x;
    }else{
        y->parent.lock()->rightChild = x;
    }

    x->rightChild = y;
    y->parent = x;
}

#endif
