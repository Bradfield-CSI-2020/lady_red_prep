#include <stdio.h>
#include <strings.h>
#include <stddef.h>

#include "util.c"
int getword(char* buf);
char * dupstr(char *word);

struct tnode {
    char * word;
    int count;
    struct tnode *left;
    struct tnode *right;
} *root;


struct tnode *count(struct tnode *node, char* word){
    void * malloc(size_t size);

    if (node == NULL) {
        // allocate new tnode
        node = (struct tnode *) malloc(sizeof(struct tnode));
        node->count = 0;
        node->word = dupstr(word);
        node->left = node->right = NULL;
    }
    int comp = strcmp(node->word, word);
    if (comp==0){
        node->count++;
    } else if (comp > 0) {
        node->left = count(node->left, word);
    } else if (comp < 0) {
        node->right = count(node->right, word);
    }
    return node;
}
char *dupstr(char *word) {
    char *w, *newstr;
    w = word;
    while(*w++);
    w = newstr = (char *)malloc(w-word+1);
    while((*w++=*word++));
    return newstr;
}

void print_tree(struct tnode * root, int spacer) {
    if (root == NULL) 
        return;
    
    print_tree(root->left, spacer+1);
    for(int i=0;i<spacer; i++) printf("  ");
    printf("%s \t%d\n", root->word, root->count);
    print_tree(root->right, spacer +1);
}

int find_depth(struct tnode * root){
    if (root == NULL){
        return 0;
    }
    int a = find_depth(root->left);
    int b = find_depth(root->right);
    return 1 + ((a>b) ? a : b);
}
int count_nodes(struct tnode * root){
    if (root == NULL){
        return 0;
    }
    int a = count_nodes(root->left);
    int b = count_nodes(root->right);
    return 1 + a + b;
}

double pow(double base, double exp) {
    double ans = 1;
    while (exp--)
        ans = ans * base;
    return ans;
}
int main(){
    char buf[100];
    while (getword(buf)) {
       printf("%s\n", buf);
       root = count(root, buf);
    }
   print_tree(root, 0);
   int depth, nodenum;
   printf("Tree depth: %d\n", (depth = find_depth(root)));
   printf("Tree nodes: %d\n", (nodenum = count_nodes(root)));
   double possible_nodes=pow(2, depth)-1;
   printf("Tree density: %d/%1.0f = %f\n", nodenum, possible_nodes, nodenum/possible_nodes);

   return 0;
}