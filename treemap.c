#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
  Pair *pair;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
};

struct TreeMap {
  TreeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) {
  TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));
  if (new == NULL) {
    return NULL;
  }
  new->current = new->root = NULL;
  new->lower_than = lower_than;

  return new;
}
// done
// done
void insertTreeMap(TreeMap *tree, void *key, void *value) {
  TreeNode *new;

  if (tree->root == NULL) {
    new = createTreeNode(key, value);
    tree->root = new;
    return;
  }

  tree->current = tree->root;

  // loop check
  while (tree->current != NULL) {
    if (is_equal(tree, key, tree->current->pair->key) == 1) {
      return;
    }
    if (tree->lower_than(key, tree->current->pair->key) == 1) {
      if (tree->current->left == NULL) {
        new = createTreeNode(key, value);
        tree->current->left = new;
        new->parent = tree->current;
        tree->current = tree->current->left;
        return;
      }
      tree->current = tree->current->left;
    } else {
      if (tree->current->right == NULL) {
        new = createTreeNode(key, value);
        tree->current->right = new;
        new->parent = tree->current;
        tree->current = tree->current->right;
        return;
      }
      tree->current = tree->current->right;
    }
  }
}
// done
// done
TreeNode *minimum(TreeNode *t) {
  TreeNode *current = t;
  while (current != NULL) {
    if (current->left == NULL) {
      return current;
    } else {
      current = current->left;
    }
  }
  return NULL;
}


void removeNode(TreeMap *tree, TreeNode *node) {
  TreeNode *pparent = node->parent;
  if (node->left == NULL && node->right == NULL) {
    if (pparent->left == node) {
      pparent->left = NULL;
    } else {
      pparent->right = NULL;
    }
  } else if (node->left == NULL || node->right == NULL) {
    TreeNode *hijo;
    if (node->left != NULL) {
      hijo = node->left;
    } else {
      hijo = node->right;
    }
    if (pparent->right == node) {
      pparent->right = hijo;
    } else {
      pparent->left = hijo;
    }
    hijo->parent = pparent;
  } else {
    if (node->right != NULL || node->left != NULL) {
      TreeNode *min = minimum(node->right);
      node->pair->key = min->pair->key;
      node->pair->value = min->pair->value;
      removeNode(tree, min);
    }
  }
}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;
  if (searchTreeMap(tree, key) == NULL) {
    return;
  }
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) {
  tree->current = tree->root;
  while (tree->current != NULL) {
    if (is_equal(tree, key, tree->current->pair->key) == 1)
      break;

    if (tree->lower_than(key, tree->current->pair->key) == 1) {
      tree->current = tree->current->left;

    } else {
      tree->current = tree->current->right;
    }
  }
  if (tree->current == NULL)
    return NULL;

  return tree->current->pair;
}

Pair *upperBound(TreeMap *tree, void *key) {
  TreeNode *nodo_actual = tree->root;
  TreeNode *node_ubi = NULL;

  while (nodo_actual != NULL) {

    if (tree->lower_than(nodo_actual->pair->key, key) == 0 &&
        tree->lower_than(key, nodo_actual->pair->key) == 0) {
      return nodo_actual->pair;
    }

    else if (tree->lower_than(nodo_actual->pair->key, key) == 0 &&
             tree->lower_than(key, nodo_actual->pair->key) == 1)

    {
      node_ubi = nodo_actual;
      nodo_actual = nodo_actual->left;
    } else {
      nodo_actual = nodo_actual->right;
    }
  }
  if (node_ubi != NULL) {

    return node_ubi->pair;
  }
  return NULL;
}

Pair *firstTreeMap(TreeMap *tree) {
  tree->current = minimum(tree->root);
  if (tree->current == NULL)
    return NULL;
  return tree->current->pair;
}

Pair *nextTreeMap(TreeMap *tree) {
  // falta retornanr nodo
  TreeNode *aux = tree->current;
  if (aux->right != NULL) {
    aux = minimum(aux->right);
  }

  if (aux == NULL)
    return NULL;
  tree->current = aux;
  return aux->pair;
}
