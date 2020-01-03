/* 
 * Name: Neel Prasad Narvankar
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "stack.h"

/* (IMPLEMENT THIS FUNCTION)
 * Create a new Stack_head struct on the Heap and return a pointer to it.
 * Follow the Directions in the Project Documentation for this Function
 * On any malloc errors, return NULL
 */
Stack_head *stack_initialize() {
  /* Implement this function */
       Stack_head *head = malloc(sizeof(Stack_head));   // Create a new head and assign memory on the heap by using  malloc 
       if(head == NULL){ 
        return NULL;                                    //if not assigned memory then return NULL and exit
       }
       else{
       head->count = 0;                             // set the count of the head to zero and top to NULL
       head->top = NULL; 
       return head;
}
}

/* (IMPLEMENT THIS FUNCTION)
 * Destroy a stack.
 * Follow the Directions in the Project Documentation for this Function
 * If head is NULL, you can just return.
 */
void stack_destroy(Stack_head *head) {
  Node *rep = NULL;

  if(head == NULL){                     
    return;
  }

  if(head->count == 1){               //If there is just one node in the stack free that node

    node_free(head->top);

  }

else{
 while(head->top!=NULL){                      // else free everything untill we reach NULL
 rep = head->top;
 head->top = head->top->next;
 token_free(head->top->tok);            
 node_free(rep);
 return;
}
}

free(head);                       //free head
}

/* (IMPLEMENT THIS FUNCTION)
 * Push a new Token on to the Stack.
 * Follow the Directions in the Project Documentation for this Function
 * On any malloc errors, return -1.
 * If there are no errors, return 0.
 */
int stack_push(Stack_head *stack, Token *tok) {
  /* Implement this function */
  Node *node = NULL;                        // Create a new variabel of the type Node 
  node = node_create(tok);                 // use the node_create() to create a new node for tok passed in the function
  if(node== NULL){                        // if the new node is not created properly return -1.
    return -1;
  }
  
else{                                      //if the new node is created successfuly insert the node on the stack
  node->next = stack->top;                //the new node always gose on the top of the stack. stack follows FirstInLastOut
  stack->top = node;                     //make this node the new top of the stack
  stack->count++;                       //increase the count of the stack and return 0 on success.
  return 0;
}

    return -1;
}

/* (IMPLEMENT THIS FUNCTION)
 * Pop a Token off of the Stack.
 * Follow the Directions in the Project Documentation for this Function
 * If the stack was empty, return NULL.
 */
Token *stack_pop(Stack_head *stack) {
  /* Implement this function */
  Node *temp = NULL;                                  // create a new variable of the type Node this is the node which we will pop

  if(stack == NULL || (stack->top) == NULL){            // if the sta
    return NULL;
  }

  
      Token *temp_node = NULL;

  
   
    if(stack->count >= 1){                            
      temp = stack->top;                                // point the node to the top of the stack
      stack->top= stack->top->next;                     // point the top of the stack to the next node on the stack
      stack->count--;                                    // decrease the count of the stack 
      temp_node = temp->tok;                      // store the value of the node in another variable 
      node_free(temp);
      return temp_node;                                       // return the node .

    }

  
  return NULL;
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the token in the stack node on the top of the stack
 * Follow the Directions in the Project Documentation for this Function
 * If the stack is NULL, return NULL.
 * If the stack is empty, return NULL.
 */
Token *stack_peek(Stack_head *stack) {
  /* Implement this function */
  if(stack == NULL || (stack->top) == NULL){
    return NULL;
  }

else{                                       // see what is the top of the node

  return stack->top->tok;                   // return the top token on the stack
    }
  return NULL;
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the number of nodes in the stack.
 * Follow the Directions in the Project Documentation for this Function
 * If stack is NULL, return -1.
 * Return 1 if the stack is empty or 0 otherwise.
 */
int stack_is_empty(Stack_head *stack) {
  /* Implement this function */
  if(stack == NULL){                    // check if the stack is empty or not
    return -1;
  }

  if(stack->count==0){

    return 1;                                     // if the stack count is zero we return it is empty
    }

  else{
  return stack->count;                // if the stack is not empty return the no of nodes on the stack by returning stack->count
    }
}

/* These two functions are written for you.
 * It recurses the stack and prints out the tokens in reverse order
 * eg. top->2->4->1->8 will print at Stack: 8 1 4 2
 * eg. stack_push(5) will then print Stack: 8 1 4 2 5
 */

/* This is implemented for you.
 * Recursive print. (Local function)
 * Base Case: node == NULL, return
 * Recursive Case: call print_node(node->next, print_data), then print node.
 */
static void print_node(Node *node) {
  if(node == NULL) {
    return;
  }
  token_print(node->tok);
  print_node(node->next);
  return;
}

/* This is implemented for you.
 * Setup function for the recursive calls.  Starts printing with stack->top
 */
void stack_print(Stack_head *stack) {
  if(stack == NULL) {
    return;
  }
  printf("|-----Program Stack\n");
  printf("| ");
  print_node(stack->top);
  printf("\n");
  return;
}
