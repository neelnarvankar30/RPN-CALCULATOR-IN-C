/*
 * Name:Neel Prasad Narvankar
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "hash.h"

/* (IMPLEMENT THIS FUNCTION)
 * In this function, you will create a new Symtab struct.
 * Follow the Directions in the Project Documentation for this Function
 * Return the pointer to the new symtab.
 * On any memory errors, return NULL
 */
Symtab *hash_initialize() {
  /* Implement this function */
  Symtab *sym = malloc(sizeof(Symtab)*1);         //Create a symtab variable and assign memory on the heap 
  Symbol **symtable = malloc(sizeof(Symbol *) * HASH_TABLE_INITIAL);    //Create a new table of type Symbol and assign memory on heap
  if (sym == NULL)                                                    //This will be the array of pointers 
  {
    return NULL;
  }
  

  for(int i = 0; i < HASH_TABLE_INITIAL; i++)   //Initialize each index to NULL by using for loop and going through each index.
    {
    symtable[i] = NULL;
    }
  sym->size = 0;                                          //set size to zero and capacity to max hash_table_capacity.
  sym->capacity = HASH_TABLE_INITIAL;
  sym->table = symtable;                      //point the symtab to the symbol table created


  return sym;                   //Return sym on success.
  
}

/* (IMPLEMENT THIS FUNCTION)
 * Destroy your Symbol Table.
 * Follow the Directions in the Project Documentation for this Function
 * Return on any memory errors.
 */
void hash_destroy(Symtab *symtab) {
  /* Implement this function */                   //check if the symtab is NULL, if yes return NULL.
  if(symtab == NULL){
      return;

    }
    
      Symbol *walker = NULL;                            //we use walker and reaper to traverse through the entire table and free
      Symbol *reaper = NULL;

  for (int i = 0; i < symtab->capacity; i++)  //start freeing symbols in a loop.
    {
      if(symtab->table[i]!=NULL){
    
      walker = symtab->table[i];            //point walker and reaper to i position of symtab.
      reaper = symtab->table[i];           //  move the walker forward and repear follows walker and frees the node one by one
        while(walker != NULL){
            walker = walker->next;
            symbol_free(reaper);
            reaper = walker;
          }
        }
    }
free(symtab);  
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the capacity of the table inside of symtab.
 * If symtab is NULL, return -1;
 */
int hash_get_capacity(Symtab *symtab) {
  /* Implement this function */
  if(symtab == NULL){
   return -1;
    }                                                       // return the symtab capacity.

    return symtab->capacity;    
}

/* (IMPLEMENT THIS FUNCTION)
 * Return the number of used indexes in the table (size) inside of symtab.
 * If symtab is NULL, return -1;
 */
int hash_get_size(Symtab *symtab) {
  /* Implement this function */
 
  if(symtab == NULL){
   return -1;
    }

    return symtab->size;                    //return the size of the symtab
}

/* (IMPLEMENT THIS FUNCTION)
 * Adds a new Symbol to the symtab via Hashing.
 * Follow the Directions in the Project Documentation for this Function
 * If symtab is NULL, there are any malloc errors, or if any rehash fails, return -1;
 * Otherwise, return 0;
 */
int hash_put(Symtab *symtab, char *var, int val) {
  /* Implement this function */
  if (symtab == NULL)                                             
    {
        return -1;  
    }

    long hashvr = hash_code(var);                         // calculate the hashcode and the index the sameway we did in hash get to put the symbol in the correct index
    int index = ((hashvr) % (symtab->capacity));
    Symbol *temp  = symbol_create(var,val);
    Symbol *walker = symtab->table[index];
    Symbol *put = symtab->table[index];

              double load = ((double)symtab->size)/((double)symtab->capacity);    //check for the load of the tabe 
   
  
            while(walker != NULL){                          // check if there already exists an variable and change the value of that variable if there
            if(strcmp(var, walker->variable) == 0)
            {
                walker->val = val;                              // travel the entire linkedlist and see if the variable is there and change the value
                                                        // if success update.
            }
            
              walker = walker->next;
        }
    

          
    if (put == NULL){                       // check if the index obtained is NULL or NOT if it is NULL insert the symbol at that index
        symtab->table[index]  = temp;
        (symtab->size)++ ;  
                      //incerase the size of symtab
    }

    else{                               //if the index obtained is occupied then traverse the linked-list and insert it at the end of it
        while(put->next != NULL)
        {
            put = put->next;
        }
        put->next = temp;
        (symtab->size)++;  
                               // increase the size of the symtab
    }


             
              if(load >= 2.0) {                                   // if the load is greater than 2.0 call the rehash function and double the size of the smymtab->capacity.
              hash_rehash(symtab, 2*symtab->capacity);    //call the rehash function with double the capacity of the original.
               }

               

  return 0;
}

/* (IMPLEMENT THIS FUNCTION)
 * Gets the Symbol for a variable in the Hash Table.
 * Follow the Directions in the Project Documentation for this Function
 * On any NULL symtab or memory errors, return NULL
 */
Symbol *hash_get(Symtab *symtab, char *var) {
  /* Implement this function */
  if (symtab == NULL)                   // Check if symtab is NULL, if yes Return NULL
  {                       
  return NULL; 
  } 
long hashvr = hash_code(var);                       // calculate the index from where we want to get the value of the variable
int index = ((hashvr) % (symtab->capacity));        // we calculate the index by taking the mod of the hashvr with symtab->capacity


if(symtab == NULL){
  return NULL;
      }


 Symbol *temp = symtab->table[index];         // make a new temp variable of type symbol and point to the index
 
 if (temp->next == NULL)                      // check if the index has a linked list if not copy the symbol and return  
 {
 Symbol *sym_temp = symbol_copy(temp);
 
 return sym_temp;  
 }

 if(temp->next != NULL){                    // if the index has a linked-list traverse the entire list until we find the symbol to be returned
   while(temp != NULL){                    // when we find the symbol copy it and return it 
            if(strcmp(var, temp->variable) == 0){
               Symbol *sym_temp = symbol_copy(temp);
 
                return sym_temp; 
              }
              temp = temp->next;
           }   
 }
return NULL;
}

/* (IMPLEMENT THIS FUNCTION)
 * Doubles the size of the Array in symtab and rehashes.
 * Follow the Directions in the Project Documentation for this Function
 * If there were any memory errors, set symtab->array to NULL
 * If symtab is NULL, return immediately.
 */
void hash_rehash(Symtab *symtab, int new_capacity) {
  /* Implement this function */
  if (symtab == NULL)
  {
    return;
  }
  long hashvr = 0;                                    // we create a new table of symbol pointers with double the capacity of the old table
  int index = 0; 
  Symbol **newtable = malloc(sizeof(Symbol *) * new_capacity);

  for(int i = 0; i < new_capacity; i++)
    {                                             //set all the index to NULL using a loop
    newtable[i] = NULL;
    }


    for (int i = 0; i < symtab->capacity; i++)        // we traveres the old table pointed by symtab
  {
    Symbol *top = symtab->table[i];                       // top points to the ith index
    while (top != NULL)                           //if top is not NULL get the variable form that index and get the hashcode
    {                                                      

      hashvr = hash_code(top->variable);
      index = hashvr % new_capacity;

      Symbol *new = newtable[index];                   // new symbol points to that index in new table where the symbol is to be inserted
      if (new == NULL)
      {
        newtable[index] = symbol_copy(top);     //copy the symbol from the old table and insert it in the new table 
      }
      else
      {
        while (new->next != NULL)             //see if the index has a linked list then for each value of the linked list
        {                                     // copy the symbol and insert it in the new table. 
          new = new->next;
        }
        new->next = symbol_copy(top);
      }
      top = top->next;
    }
  }


  for (int i = 0; i < symtab->capacity; i++)    // this loop frees the old table 
    {                                         
      if(symtab->table[i]!=NULL){                          // use walker follwed by reaper to free each symbol
    
    Symbol *walk = symtab->table[i];
      Symbol *reaper = symtab->table[i];
        
        while(walk != NULL){
            walk = walk->next;
            symbol_free(reaper);
            reaper = walk;
          }
        }
    }
    
  
    symtab->capacity = new_capacity;              //set the symtabcapacity to new capacity 
    symtab->table = newtable;                   // point the symtab to new table.
   

   if (symtab->table == NULL)
   {
      return;
   }

  return;
}

/* Implemented for you.
 * Provided function to print the symbol table */
void hash_print_symtab(Symtab *symtab) {
  if(symtab == NULL) {
    return;
  }
  printf("|-----Symbol Table [%d size/%d cap]\n", symtab->size, symtab->capacity);

  int i = 0;
  Symbol *walker = NULL;

  /* Iterate every index, looking for symbols to print */
  for(i = 0; i < symtab->capacity; i++) {
    walker = symtab->table[i];
    /* For each found linked list, print every symbol therein */
    while(walker != NULL) {
      printf("| %10s: %d \n", walker->variable, walker->val);
      walker = walker->next;
    }
  }
  return;
}

/* This function is written for you.
 * This computes the hash function for a String
 */
long hash_code(char *var) {
  long code = 0;
  int i;
  int size = strlen(var);

  for(i = 0; i < size; i++) {
    code = (code + var[i]);
    if(size == 1 || i < (size - 1)) {
      code *= 128;
    }
  }

  return code;
}
