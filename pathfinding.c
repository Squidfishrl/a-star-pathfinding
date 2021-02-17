#include "matrix.h"


struct node_t* find_node_by_type(int type, struct matrix_t *matrix);  // assuming type is unique, else finds first node with type
unsigned int calc_node_distance(struct node_t* nodeA, struct node_t* nodeB);
int calc_fCost(struct node_t* targetNode, struct node_t* startNode, struct node_t* destNode, char applyValuesBool);
struct node_t* A_star_search(struct matrix_t* matrix);
char p_exists_in_arr(struct node_t* node, struct node_t* nodeArr[], int arrSize);
char is_empty_list(struct node_t *arr[], int size);


    int main()
{

    struct matrix_t* matrix = create_matrix(10, 10);
    struct node_t *endingNode = matrix->headNode->up;
    struct node_t* startingNode = matrix->headNode->up->up->right->right->right->up->up->right;

    startingNode->type = 1;
    endingNode->type = 0;
    print_matrix(matrix);
    // printf("\n %d", calc_node_distance(startingNode, endingNode));

    A_star_search(matrix);

    print_matrix(matrix);
    return 0;
}

struct node_t* A_star_search(struct matrix_t* matrix){

    struct node_t* startingNode = find_node_by_type(1, matrix);
    struct node_t* destNode = find_node_by_type(0, matrix);
    struct node_t* currentNode;
    int tempOpenIndex, closedNodesCount;
    int matrixSize = matrix->columns * matrix->rows;

    struct node_t* open[matrixSize];  // nodes to be evaluated
    struct node_t* closed[matrixSize]; // nodes already evaluated
    struct node_t* nodeNeighbour[4];

    for(int i = 0; i < matrixSize; i++){
        open[i] = NULL;
        closed[i] = NULL;
    }

    open[0] = startingNode;
    closedNodesCount = 0;
    do{

        // find node with lowest f cost
        tempOpenIndex = 0;
        calc_fCost(open[0], startingNode, destNode, 1);

        for(int i = 1; i<matrixSize; i++){
            if(open[i] != NULL){

                if(open[i]->fCost == 0){
                    calc_fCost(open[i], startingNode, destNode, 1);
                }

                if(open[tempOpenIndex]->fCost > open[i]->fCost){
                    tempOpenIndex = i;
                }else if(open[tempOpenIndex]->fCost == open[i]->fCost){
                    if(open[tempOpenIndex]->hCost > open[i]->hCost){
                        tempOpenIndex = i;
                    }
                }
            }
       }

 

        currentNode = open[tempOpenIndex];

       // remove node from open and put in closed

        open[tempOpenIndex] = NULL;
        closed[closedNodesCount] = currentNode;
        closedNodesCount++;

        if(currentNode->hCost == 0){
            printf("found path \n");
            currentNode = currentNode->previous;
            while(currentNode->previous != NULL){
                currentNode->type = -1;
                currentNode = currentNode->previous;

                
            }
            return NULL;
        }

        nodeNeighbour[0] = currentNode->up;
        nodeNeighbour[1] = currentNode->down;
        nodeNeighbour[2] = currentNode->left;
        nodeNeighbour[3] = currentNode->right;

        for(int i = 0; i<4; i++){

            if (nodeNeighbour[i] == NULL || nodeNeighbour[i]->type == 3 || p_exists_in_arr(nodeNeighbour[i], closed, matrixSize))
            {
                continue;
            }

            if (!p_exists_in_arr(nodeNeighbour[i], open, matrixSize) || calc_fCost(nodeNeighbour[i], startingNode, destNode, 0) < nodeNeighbour[i]->fCost){
                
                nodeNeighbour[i]->previous = currentNode;
                calc_fCost(nodeNeighbour[i], startingNode, destNode, 1);

                if (!p_exists_in_arr(nodeNeighbour[i], open, matrixSize)){
                    // add to open
                    for (int b = 0; b < matrixSize; b++){
                        if (open[b] == NULL)
                        {
                            open[b] = nodeNeighbour[i];
                            break;
                        }
                    }
                }
            }
        }

    }while(!is_empty_list(open, matrixSize));
    printf("didn't find path");
    return NULL;
}


struct node_t* find_node_by_type(int type, struct matrix_t* matrix){

    struct node_t *iterNode2 = matrix->headNode;
    struct node_t *iterNode1 = iterNode2;

    for (int row = 0; row < matrix->rows; row++){

        for (int column = 0; column < matrix->columns; column++){

            if (iterNode2->type == type){
                return iterNode2;
            }

            iterNode2 = iterNode2->right;
        }
        iterNode1 = iterNode1->up;
        iterNode2 = iterNode1;
    }

    return NULL;
}


unsigned int calc_node_distance(struct node_t *nodeA, struct node_t *nodeB){
    int horizontalDistance = nodeA->row - nodeB->row;
    int verticalDistance= nodeA->column - nodeB->column;
  
    if(horizontalDistance < 0){
        horizontalDistance *= -1;
    }

    if(verticalDistance < 0){
        verticalDistance *= -1;
    }

    return verticalDistance + horizontalDistance;
}

int calc_fCost(struct node_t *targetNode, struct node_t *startNode, struct node_t *destNode, char applyValuesBool){
    int gCost;
    int hCost = calc_node_distance(targetNode, destNode);
    if(targetNode->previous == NULL){
        gCost = calc_node_distance(targetNode, startNode);
    }else{
        gCost = targetNode->previous->gCost + 1;
    }

    int fCost = gCost + hCost;

    if(applyValuesBool){
        targetNode->gCost = gCost;
        targetNode->hCost = hCost;
        targetNode->fCost = fCost;
    }
    return fCost;
}

char p_exists_in_arr(struct node_t *node, struct node_t *nodeArr[], int arrSize){

    char exists = 0;

    for(int i = 0; i < arrSize; i++){
        if(nodeArr[i] == NULL){
           continue;
        }
        if (node->row == nodeArr[i]->row && node->column == nodeArr[i]->column){
            exists = 1;
            break;
        }
    }

    return exists;
}

char is_empty_list(struct node_t* arr[], int size){
    char isEmpty = 1;

    for(int i = 0; i<size; i++){
        if(arr[i] != NULL){
            isEmpty = 0;
            break;
        }
    }

    return isEmpty;
}