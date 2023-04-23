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
// done

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

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) { return NULL; }

Pair *upperBound(TreeMap *tree, void *key) { return NULL; }

Pair *firstTreeMap(TreeMap *tree) { return NULL; }

Pair *nextTreeMap(TreeMap *tree) {}
