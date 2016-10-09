#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode
{
    int data;
    struct BinaryTreeNode* lChild;
    struct BinaryTreeNode* rChild;
}BinTreeNode;

int createBinTree(BinTreeNode** node)
{
    int input = 0;
    scanf("%d", &input);

    if (input == -1)
    {
        *node = NULL;
        return 0;
    }

    *node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (node == NULL)
    {
        printf("malloc failed\n");
        return 0;
    }

    (*node)->data = input;
    printf("Please input %d's left child:\n", input);
    createBinTree(&((*node)->lChild));
    printf("Please input %d's right child:\n", input);
    createBinTree(&((*node)->rChild));

    return 0;
}

int preOrderAccessBinTree(BinTreeNode* node)
{
    if (node == NULL)
    {
        return 0;
    }

    printf("%d ", node->data);
    preOrderAccessBinTree(node->lChild);
    preOrderAccessBinTree(node->rChild);

    return 0;
}

int middleOrderAccessBinTree(BinTreeNode* node)
{
    if (node == NULL)
    {
        return 0;
    }

    middleOrderAccessBinTree(node->lChild);
    printf("%d ", node->data);
    middleOrderAccessBinTree(node->rChild);

    return 0;
}

int postOrderAccessBinTree(BinTreeNode* node)
{
    if (node == NULL)
    {
        return 0;
    }

    printf("%d ", node->data);
    postOrderAccessBinTree(node->lChild);
    postOrderAccessBinTree(node->rChild);

    return 0;
}

int deepOfTree(BinTreeNode* node)
{
    if (node == NULL)
    {
        return 0;
    }

    int leftDeep = deepOfTree(node->lChild);
    int rightDeep = deepOfTree(node->rChild);
    return ((leftDeep >= rightDeep) ? (leftDeep + 1) : (rightDeep + 1));
}

int countNodeNumber(BinTreeNode* node)
{
    static int nodeNumber;
    if (node != NULL)
    {
        nodeNumber++;
        countNodeNumber(node->lChild);
        countNodeNumber(node->rChild);
    }

    return nodeNumber;
}

int main(int argc, const char* argv[])
{
    BinTreeNode* node;
    int num = 0, deep = 0;

    printf("Please input an integer for root node, -1 means no need to create this node\n");
    createBinTree(&node);

    printf("\npre order access bin tree\n");
    preOrderAccessBinTree(node); 

    printf("\nmiddle order access bin tree\n");
    middleOrderAccessBinTree(node);

    printf("\npost order access bin tree\n");
    postOrderAccessBinTree(node);

    deep = deepOfTree(node);
    printf("\ndeep of bin tree is %d\n", deep);

    num = countNodeNumber(node);
    printf("number of node in bin tree is %d\n", num);

    return 0;
}
