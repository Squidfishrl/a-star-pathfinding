#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct node_t{

    int row;
    int column;
    struct node_t* up;
    struct node_t* down;
    struct node_t* left;
    struct node_t* right;

    int type;  //-1 = path // 0 = endpoint // 1 = start point //  2 = passable // 3 = not passable
    int fCost;
    int hCost;
    int gCost;
    struct node_t* previous;
};


struct matrix_t{
    struct node_t* headNode;
    int rows;
    int columns;
};

struct node_t* init_node(int row, int column, struct node_t* up, struct node_t* down, struct node_t* left, struct node_t* right, int type);
struct matrix_t* create_matrix(int rows, int columns);
void print_matrix(struct matrix_t* matrix);
void free_matrix(struct matrix_t* matrix);
void validate_matrix(struct matrix_t* matrix);  // will crash on error


// int main(){

//     struct matrix_t* matrix = create_matrix(10, 10);
//     // print_matrix(matrix);
//     // validate_matrix(matrix);
//     print_matrix(matrix);
//     free_matrix(matrix);

//     return 0;
// }


struct node_t* init_node(int row, int column, struct node_t* up, struct node_t* down, struct node_t* left, struct node_t* right, int type){

    struct node_t* initNode = (struct node_t*)malloc(sizeof(struct node_t));
    initNode->row = row;
    initNode->column = column;
    initNode->left = left;
    initNode->right = right;
    initNode->up = up;
    initNode->down = down;
    initNode->type = type;

    initNode->previous = NULL;

    return initNode;
}


struct matrix_t* create_matrix(int rows, int columns){
    struct node_t* headNode = init_node(0, 0, NULL, NULL, NULL, NULL, 2);
    struct node_t* tempNode1 = headNode;
    struct node_t* tempNode2 = headNode;
    char nodeType;

    srand(time(NULL));

    for(int column = 0; column < columns; column++){

        for(int row = 1; row < rows; row++){
            nodeType = rand();
            if(nodeType%3 == 0){
              nodeType=3;
            }else{
              nodeType=2;
            }
            printf("%d ", nodeType);
            if(column == 0){
                tempNode1->up = init_node(row, column, NULL, tempNode1, NULL, NULL, nodeType);
            }else{
                tempNode1->up = init_node(row, column, NULL, tempNode1, tempNode1->left->up, NULL, nodeType);
                tempNode1->left->up->right = tempNode1->up;
            }

            tempNode1 = tempNode1->up;

        }

        tempNode2->right = init_node(0, column+1, NULL, NULL, tempNode2, NULL, nodeType);
        tempNode2 = tempNode2->right;
        tempNode1 = tempNode2;

    }

    struct matrix_t* matrix = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    matrix->headNode = headNode;
    matrix->rows = rows;
    matrix->columns = columns;
    return matrix;
}


void print_matrix(struct matrix_t* matrix){

    struct node_t* iterNode2 = matrix->headNode;


    // for(int row = 0; row < matrix->rows; row++){
    //     iterNode2 = iterNode2->up;
    // }

    struct node_t* iterNode1 = iterNode2;

    for(int row = 0; row < matrix->rows; row++){

        for(int column = 0; column < matrix->columns; column++){
            // printf("%d %d  ", iterNode2->row, iterNode2->column);
            // randomly generate
            if(iterNode2->type == 2){
                printf("x ");
            }else if(iterNode2->type == 1){
                printf("A ");
            }else if(iterNode2->type == 0){
                printf("B ");
            }else if(iterNode2->type == -1){
                printf("- ");
            }else if(iterNode2->type == 3){
                printf("0 ");
            }
            iterNode2 = iterNode2->right;
        }
        printf("\n");
        iterNode1 = iterNode1->up;
        iterNode2 = iterNode1;
    }

    printf("\n\n");
}


void free_matrix(struct matrix_t* matrix){

    struct node_t* iterNode2 = matrix->headNode;
    struct node_t* iterNode1 = iterNode2;
    struct node_t* holdNode;

    for(int row = 0; row <= matrix->rows; row++){

        iterNode1 = iterNode1->up;
        for(int column = 0; column < matrix->columns; column++){
            holdNode = iterNode2->right;
            free(iterNode2);
            iterNode2 = holdNode;
        }
        free(iterNode2);
        if(iterNode1 == NULL){
            break;
        }else{
            iterNode2 = iterNode1;
        }

    }
    free(matrix);
}


void validate_matrix(struct matrix_t* matrix){

    struct node_t* iterNode2 = matrix->headNode;
    struct node_t* iterNode1 = iterNode2;

    for(int row = 0; row < matrix->rows; row++){

        for(int column = 0; column < matrix->columns; column++){

            iterNode2->up = iterNode2->up;
            iterNode2->down = iterNode2->down;
            iterNode2->left = iterNode2->left;
            iterNode2->right = iterNode2->right;

            iterNode2 = iterNode2->right;
        }
        printf("\n");
        iterNode1 = iterNode1->up;
        iterNode2 = iterNode1;
    }

}
