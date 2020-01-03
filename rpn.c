/* Name: Neel Prasad Narvankar
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "token.h"
#include "hash.h"

/* Local Function Declarations (that you need to finish implementing) */
static int read_file(char *filename, char *line);
static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok);

/* Pre-Written Local Function Declarations */
static void print_header(char *filename, int step);
static void print_step_header(int step);
static void print_step_footer(Symtab *symtab, Stack_head *stack);
static void print_step_output(int val);

/* Defines the largest line that can be read from a file */
#define MAX_LINE_LEN 255

/* This has been written for you.
 * Main function to run your program (written for you).
 * 1) Opens the file using the passed in filename. (your function)
 * -- If the file is not found (ie. fopen returns NULL), then exit(-1);
 * 2) Reads one line from the file.
 * -- The programs will all only be one line in size.
 * -- That line may be up to MAX_LINE_LEN long.
 * 3) Closes the file.
 * 4) Calls token_read_line(line, strlen(line))
 * -- This parses the line and prepares the tokens to be ready to get.
 * 5) While there are tokens remaining to parse: token_has_next() != 0
 * -- a) Get the next token: token_get_next()
 * 6) Parse the token (your function)
 * 7) Print out all of the relevant information
 */
int rpn(Stack_head *stack, Symtab *symtab, char *filename) {
  int step = 0; /* Used to track the program steps */
  int ret = 0;
  char line[MAX_LINE_LEN];
  Token *tok = NULL;

  /* Complete the read_file function that is defined later in this file. */
  ret = read_file(filename, line);
  if(ret != 0) {
    printf("Error: Cannot Read File %s.  Exiting\n", filename);
    exit(-1);
  }

  /* Pass the line into the tokenizer to initialize that system */
  token_read_line(line, strlen(line));

  /* Prints out the nice program output header */
  print_header(filename, step);

  /* Iterate through all tokens */
  while(token_has_next()) {
    /* Begin the next step of execution and print out the step header */
    step++; /* Begin the next step of execution */
    print_step_header(step);

    /* Get the next token */
    tok = token_get_next();
    /* Complete the implementation of this function later in this file. */
    ret = parse_token(symtab, stack, tok);
    if(ret != 0) {
      printf("Critical Error in Parsing.  Exiting Program!\n");
      exit(-1);
    }

    /* Prints out the end of step information */
    print_step_footer(symtab, stack);
  }

  return 0;
}

/* (IMPLEMENT THIS FUNCTION)
 * Local function to open a file or exit.
 * Follow the Directions in the Project Documentation for this Function
 * Open filename, read its contents (up to MAX_LINE_LEN) into line, then
 *   close the file and return 0.
 * On any file error, return -1.
 */

/*This function is used to open an file to which the input for RPN calculator needs to be read from*/
static int read_file(char *filename, char *line) {
  /* Implement This Function */             
  FILE *fp = fopen(filename, "r");                 /*We first create an FILE pointer and point it to the opened file with the read parameter*/
  if(fp ==NULL){
    return -1;                                      /*If the file is not opened the pointer returns -1  and the program returns an error*/
  }

   fgets(line, MAX_LINE_LEN, fp);     /*Read each line from the file upto the Max_length */
   if (line == NULL)
   {
     return -1;
   }
  
  fclose(fp);                         /*Close the opened file and return 0 on success*/
 
  return 0;
}

/* (IMPLEMENT THIS FUNCTION)
 * Parses the Token to implement the rpn calculator features
 * Follow the Directions in the Project Documentation for this Function
 * You may implement this how you like, but many small functions would be good!
 * If the token you are passed in is NULL, return -1.
 * If there are any memory errors, return -1.
 */
static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok) {
  /* Implement This Function */
  /*This function is used to let the program know what is the type of the incoming token and perfrom actions on it according ot its type*/
 if(tok == NULL){
  return -1;
 }                              /*Check if the token does not have a NULL if it is NULL then exit the program
                                  else check its type and perform actions accordingly*/

else{
                                                      /*We use an chain of ifs to check what is the type of the token*/
 if (tok->type == TYPE_VALUE)                     /*if token has a type value push it on top of the stack*/
 {
   stack_push(stack, tok);
   return 0;
 }


if(tok->type == TYPE_OPERATOR){                     //If token has type operator we check which operator it is (+ - * /) and then 
Token *tok1 = NULL;                                 // pop the top two tokens from the stack and apply the operation on it  
Token *tok2 = NULL;
if(tok->oper == OPERATOR_PLUS ){
         tok1 = stack_pop(stack);
         tok2 = stack_pop(stack);
         int tok3;
            

         if((tok2->type == TYPE_VARIABLE) && (tok1->type == TYPE_VARIABLE)){  // The two tokens which are popped of can be of the type variable we check for that here
                      Symbol *sym1 = NULL;              // if the poppped tokens are variables we create two new variables of type symbol and set it as NULL
                      Symbol *sym2 = NULL;
                      sym1 = hash_get(symtab, tok1->variable);    //Use hash_get() to get the token from the symbol table and assign it to the new variable of type symbol
                      sym2 = hash_get(symtab, tok2->variable);
                      if (sym2 == NULL || sym1 == NULL)
                      {
                        return -1;
                      }
                      tok2->value = sym2->val;                          
                      tok1->value = sym1->val;
                      tok3 = (tok2->value) + (tok1->value);       // Do the operation which is required and store the value in tok3
                      Token *tok =token_create_value(tok3);       // use the token_create_value() to create a token with the new value      
                      stack_push(stack, tok);                     // push this answer which was obtained from above step and push it on two the stack
                  return 0;
                      token_free(tok1);                             // free the tokens used and the symbols created
                      token_free(tok2);
                      symbol_free(sym2);
                      symbol_free(sym1);

                  } 
                
          tok3 = tok2->value + tok1->value;     // if we reach here it means that the tokens popped of the stack were not variables 
          Token *tok =token_create_value(tok3);   // we perform normal operations on the values and store it in a new token
          stack_push(stack, tok);                     // push this token with the answer on top of the stack
          token_free(tok1);
          token_free(tok2);
          return 0;     
      }

if(tok->oper == OPERATOR_MINUS ){       // The logic remains the same as operation PLUS we only do substraction or MINUS in this case
         tok1 = stack_pop(stack);
         tok2 = stack_pop(stack);
         int tok3;

           if((tok2->type == TYPE_VARIABLE) && (tok1->type == TYPE_VARIABLE)){
                      Symbol *sym1 = NULL;
                      Symbol *sym2 = NULL;
                      sym1 = hash_get(symtab, tok1->variable);
                      sym2 = hash_get(symtab, tok2->variable);
                      tok2->value = sym2->val;
                      tok1->value = sym1->val;
                      tok3 = (tok2->value) - (tok1->value);
                      Token *tok =token_create_value(tok3);
                      stack_push(stack, tok);
                      token_free(tok1);
                      token_free(tok2);
                      symbol_free(sym2);
                      symbol_free(sym1);
                  return 0;

                  }

             
                
                
                

         tok3 = tok2->value - tok1->value;        // The logic remains the same as operation PLUS we only do substraction or MINUS in this case  
         Token *tok =token_create_value(tok3);
         stack_push(stack, tok);
         token_free(tok1);
         token_free(tok2);
         return 0;
        }

if(tok->oper == OPERATOR_MULT ){      // The logic remains the same as operation PLUS we only do Multiplication in this case
          tok1 = stack_pop(stack);
          tok2 = stack_pop(stack);
         int tok3;

            if((tok2->type == TYPE_VARIABLE) && (tok1->type == TYPE_VARIABLE)){
                      Symbol *sym1 = NULL;
                      Symbol *sym2 = NULL;
                      sym1 = hash_get(symtab, tok1->variable);
                      sym2 = hash_get(symtab, tok2->variable);
                      tok2->value = sym2->val;
                      tok1->value = sym1->val;
                      tok3 = (tok2->value) * (tok1->value);
                      Token *tok =token_create_value(tok3);
                      stack_push(stack, tok);
                      token_free(tok1);
                      token_free(tok2);
                      symbol_free(sym2);
                      symbol_free(sym1);
                  return 0;

                  }
                
             
                
               

          tok3 = tok2->value * tok1->value;  // The logic remains the same as operation PLUS we only do Multiplication in this case
          Token *tok = token_create_value(tok3);
          stack_push(stack, tok);
          token_free(tok1);
          token_free(tok2);
          return 0;
      }

if(tok->oper == OPERATOR_DIV ){     // The logic remains the same as operation PLUS we only do Division in this case
        tok1 = stack_pop(stack);
        tok2 = stack_pop(stack);
         int tok3;
         if((tok2->type == TYPE_VARIABLE) && (tok1->type == TYPE_VARIABLE)){
                      Symbol *sym1 = NULL;
                      Symbol *sym2 = NULL;
                      sym1 = hash_get(symtab, tok1->variable);
                      sym2 = hash_get(symtab, tok2->variable);
                      tok2->value = sym2->val;
                      tok1->value = sym1->val;
                      tok3 = (tok2->value) / (tok1->value);
                      Token *tok =token_create_value(tok3);
                      stack_push(stack, tok);
                      token_free(tok1);
                      token_free(tok2);
                      symbol_free(sym2);
                      symbol_free(sym1);
                  return 0;

                  }

               if(tok2->type == TYPE_VARIABLE){
                  Symbol *sym = NULL;
                  sym =hash_get(symtab, tok2->variable);
                      if(sym == NULL){
                        return -1;
                        }
                  tok2->value = sym->val;
                  tok3 = (tok2->value) / (tok1->value);
                  Token *tok =token_create_value(tok3);
                  stack_push(stack, tok);
                  token_free(tok1);
                  token_free(tok2);
                  symbol_free(sym);
                  return 0;
                }
                
                  
                
          tok3 = (tok2->value) / (tok1->value);  
          Token *tok =token_create_value(tok3);
          stack_push(stack, tok);
          token_free(tok1);
          token_free(tok2);
          return 0;
      }
}


if(tok->type == TYPE_PRINT){    //This part checks if the token we get next has the type if PRINT

 Token *tok = stack_pop(stack);               // if the token is print we pop the top most token from the stack and store it in a Variable of type Token
 if(tok->type == TYPE_VARIABLE){              // The token popped can be of type variable

    Symbol *sym = NULL;                       //we create an variable of type Symbol  
    sym =hash_get(symtab, tok->variable);     // we use the hash_get() to get the value of the variable from the symbol table
    print_step_output(sym->val);                // Then use the prin_step_output() to print the value of the variable
    return 0;
 }

 print_step_output(tok->value);         //If the function reaches here that means the token is a normal value
 return 0;                              // we just print the value and return 0 on success
}

if(tok->type == TYPE_VARIABLE){

stack_push(stack,tok);
return 0;
}

if(tok->type == TYPE_ASSIGNMENT ){      // This part check to see if the next token we get is of the type ASSIGNMERT
Token *tok1 = NULL;                 // create two variables of Type TOKEN
Token *tok2 = NULL;
  tok1 = stack_pop(stack);              //pop two values from the top of the stack and assign the values to the new token
  tok2 = stack_pop(stack);
  hash_put(symtab, tok2->variable, tok1->value);    // use the hash_put() to put the values in the symbol table.
return 0;

}

}
return -1;

}

/* This has been written for you.
 * Prints out the main output header
 */
static void print_header(char *filename, int step) {
  printf("######### Beginning Program (%s) ###########\n", filename);
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step);
  token_print_remaining();
  printf("o-------------------\n");
}

/* This has been written for you.
 * Prints out the information at the top of each step
 */
static void print_step_header(int step) {
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step++);

}

/* This has been written for you.
 * Prints out the output value (print token) nicely
 */
static void print_step_output(int val) {
  printf("|-----Program Output\n");
  printf("| %d\n", val);
}

/* This has been written for you.
 * Prints out the information at the bottom of each step
 */
static void print_step_footer(Symtab *symtab, Stack_head *stack) {
  hash_print_symtab(symtab);
  stack_print(stack);
  token_print_remaining();
  printf("o-------------------\n");
}
