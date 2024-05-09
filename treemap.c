#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>   
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
    //new->lower_than = lower_than;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode* newNodo = createTreeNode(key,value);
    if(tree->root==NULL)
    {
        tree->root=newNodo;
    }
    else
    {
        TreeNode* aux=tree->root;
        while(true)
            {
                if(tree->lower_than(key,aux->pair->key))
                {
                    if(aux->left==NULL)
                    {
                        aux->left=newNodo;
                        newNodo->parent=aux;
                        tree->current = newNodo;
                        break;
                    }
                    else{
                            aux = aux->left;
                            tree->current = newNodo;
                        }
                }
                else if(tree->lower_than(aux->pair->key,key))
                {
                    if(aux->right==NULL)
                    {
                        aux->right=newNodo;
                        newNodo->parent=aux;
                        tree->current = newNodo;
                        break;
                    }
                    else{
                        aux = aux->right;
                        tree->current = newNodo;
                    }
                }
                else {
                    free(newNodo);
                    break;
                }
            }
    }
    
}

TreeNode * minimum(TreeNode * x){
    if(x==NULL) return NULL;
    while(x->left!=NULL)
        {
            x=x->left;
        }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* temp = tree->root;
    while(temp != NULL)
        {
            if(is_equal(tree,temp->pair->key,key))
            {
                tree->current = temp;
                return temp->pair;
            }
            else
            {
                if(tree->lower_than(key,temp->pair->key) == 1)
                {
                    temp = temp->left;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
