/*
    This code was taken from: https://github.com/rtjk/drawBinaryTree

    MIT License

    Copyright (c) 2019 rtjk

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "displayTree.h"

void printSign(int n);

int *treeToArray(RedBlackNode *tree);
void recursiveTreeToArray(RedBlackNode *node, int x, int *absoluteData, int *dataSign);

int height(RedBlackNode *node);
int digits(int n);

void draw(RedBlackNode *tree)
{

    if (tree == NULL)
        printf("\n\nEMPTY TREE\n\n");

    else
    {

        printf("\n\n");

        int *arrayFromTree = treeToArray(tree);

        int h = height(tree);

        int l = pow(2, h + 1) - 1; // arraysLength

        int *a = &arrayFromTree[0]; // absoluteData
        int *s = &arrayFromTree[l]; // dataSign

        int i;

        int max = a[0]; // maxAbsoluteData

        for (i = 1; i < l; i++)
            if (a[i] > max)
                max = a[i];

        int d = digits(max); // digitsOfMaxAbsoluteData

        int negative = 0; // negativeData

        for (i = 0; i < l & !negative; i++)
            if (s[i] == 1)
                negative = 1;

        int r, gi; // row, digits of Data
        int j = 0;

        for (r = h + 1; r >= 1; r--)
        {

            for (int i = 0; i < pow(2, r - 1) - 1; i++)
            {
                for (int k = 0; k <= d; k++)
                    printf(" ");
                if (negative)
                    printf(" ");
            }

            for (int i = 0; i < pow(2, h - r + 1); i++, j++)
            {

                if (a[j] != -1)
                {
                    if (negative)
                    {
                        if (a[j] == 0)
                            printSign(0);
                        else
                            printSign(-s[j]);
                    }
                    gi = digits(a[j]);
                    for (int k = 0; k < (d - gi); k++)
                        printf("0");

                    /* Small modification to print the color of a node */
                    /* It's only colored red, otherwise left at the terminals default font color */
                    RedBlackNode *node = rb_search(tree, a[j]);
                    if (node && node->color == RB_RED)
                        printf(/* red */ "\033[31m" "%d" /* default */ "\033[0;39m", a[j]);
                    else
                        printf("%d", a[j]);
                }
                else
                {
                    if (negative)
                        printf("_");
                    for (int k = 0; k <= d; k++)
                        printf("_");
                }

                for (int j = 0; j < pow(2, r) - 1; j++)
                {
                    for (int k = 0; k <= d; k++)
                        printf(" ");
                    if (negative)
                        printf(" ");
                }
            }

            printf("\n\n");
        }

        /* Small modification, author had memory leaks :p */
        free(arrayFromTree);
    }
}

void printSign(int n)
{
    if (n == 0)
        printf("0");
    if (n > 0)
        printf("+");
    if (n < 0)
        printf("-");
}

int *treeToArray(RedBlackNode *tree)
{

    if (tree != NULL)
    {

        int maxNodes; // maximum possible number of nodes based on height
        maxNodes = pow(2, (height(tree)) + 1) - 1;

        // allocate
        int *arrayFromTree = malloc(2 * maxNodes * sizeof(int));

        // initialize
        int i;
        for (i = 0; i < 2 * maxNodes; i++)
            arrayFromTree[i] = -1;

        int *absoluteData = &arrayFromTree[0];	  // absoluteData[i] = Data if node is not null
                                                  // absoluteData[i] = -1 if node is null
        int *dataSign = &arrayFromTree[maxNodes]; // dataSign[i] = 1 if Data is negative
                                                  // dataSign[i] = -1 otherwise

        absoluteData[0] = abs(tree->data);
        if (tree->data < 0)
            dataSign[0] = 1;

        recursiveTreeToArray(tree, 0, absoluteData, dataSign);
        return arrayFromTree;
    }

    else
        return NULL;
}

void recursiveTreeToArray(RedBlackNode *node, int x, int *absoluteData,
                          int *dataSign)
{

    if (node == NULL)
        return;

    if (node->children[RB_LEFT] != NULL)
    {
        absoluteData[2 * x + 1] = abs(node->children[RB_LEFT]->data);
        if (node->children[RB_LEFT]->data < 0)
            dataSign[2 * x + 1] = 1;
    }

    if (node->children[RB_RIGHT] != NULL)
    {
        absoluteData[2 * x + 2] = abs(node->children[RB_RIGHT]->data);
        if (node->children[RB_RIGHT]->data < 0)
            dataSign[2 * x + 2] = 1;
    }

    recursiveTreeToArray(node->children[RB_LEFT], 2 * x + 1, absoluteData, dataSign);
    recursiveTreeToArray(node->children[RB_RIGHT], 2 * x + 2, absoluteData, dataSign);
}

int height(RedBlackNode *node)
{

    if (node == NULL)
        return -1;

    int leftHeight = height(node->children[RB_LEFT]);
    int rightHeight = height(node->children[RB_RIGHT]);
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    return rightHeight + 1;
}

int digits(int n)
{
    int d = 0;
    while (n >= 10)
    {
        n = n / 10;
        d++;
    }
    return d;
}
