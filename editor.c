//Gowtham Vuppala

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//All the named constants
#define COM_SIZE 4
#define MAX_SIZE 10
#define T 1
#define F 0
#define MAX_INPUT 15

typedef struct node {
    int count;
    char symbol[MAX_SIZE];
    struct node* next;
} NODE, *PNODE;

PNODE head, tail = NULL;

//Prototypes for functions
void pr1();
void ins(char []);
void pst();
void sort();
void del(char []);
void fde(int );
void pcr(int , int );
void ppr(char []);
void psu(char []);

int main(void) {
    //All needed variables
    char input[MAX_INPUT];
    char command[COM_SIZE];
    char word[MAX_SIZE];
    int val, v1, v2;
    
    //Ask for a command
    printf("Command? "); fflush(stdout);
    fgets(input, MAX_INPUT - 1, stdin);
    strncpy(command ,input, COM_SIZE - 1);
    
    sscanf(input, "%s %s", command, word);
    //While the command is not end, process the command
    while(strcmp(command, "end") != 0){
        if (strcmp(command, "ins") == 0){
            sscanf(input, "%s %s", command, word);
            ins(word);
        }
        else if (strcmp(command, "pr1") == 0){
            pr1();
        }
        else if (strcmp(command, "pst") == 0){
            pst();
        }
        else if (strcmp(command, "del") == 0){
            sscanf(input, "%s %s", command, word);
            del(word);
        }
        else if (strcmp(command, "fde") == 0){
            sscanf(input, "%s %d", command, &val);
            fde(val);
        }
        else if (strcmp(command, "pcr") == 0){
            sscanf(input, "%s %d %d", command, &v1, &v2);
            pcr(v1, v2);
        }
        else if (strcmp(command, "ppr") == 0){
            sscanf(input, "%s %s", command, word);
            ppr(word);
        }
        else if (strcmp(command, "psu") == 0){
            sscanf(input, "%s %s", command, word);
            psu(word);
        }
        
        // Keep asking until the user types end
        printf("Command? "); fflush(stdout);
        fgets(input, MAX_INPUT - 1, stdin);
        strncpy(command ,input, COM_SIZE - 1);
    }
    
    return 0;
}

/* This method creates and inserts a node in the linked list pointed by 
 * head.
 * @param word : The symbol of the node
 */
void ins(char *word){
     PNODE temp, currentPtr;
     int inserted = F;
     //If malloc returns null, exit the program
     if ((temp = malloc(sizeof(PNODE))) == NULL) {
        printf("Node allocation failed. \n"); fflush(stdout);
         exit(1); /* Stop program */
    }
    currentPtr= malloc(sizeof(PNODE));
    strcpy(temp -> symbol, word); 
    temp->next = NULL;
    temp->count = 1;
    //If the list is empty, create one, else add the node at the end
    if (head == NULL) {
         head = tail = temp;
    }
    else { 
        currentPtr = head;
        //If the node of same symbol is already present, increment the count
        while (currentPtr != NULL){
            if (strcmp(currentPtr->symbol, temp->symbol) == 0){
                currentPtr->count += 1;
                inserted = T;
            }
            currentPtr = currentPtr->next;
        }
        //If its a new symbol, add the node at the end
        if(inserted == F){
            tail->next = temp;
            tail = tail->next;
        }
        //Make sure to sort the list in non-increasing order
        sort();
    }
}

/*
 * This method prints the list from left to right
 */
void pr1() {
    PNODE temp = head;
    //If the list isn't empty, print the list
    if (temp == NULL) {
        printf("List is empty.\n"); fflush(stdout);
    }
    else {
        while (temp != NULL) {
        printf("%s %5d\n", temp-> symbol, temp->count); fflush(stdout);
        temp = temp->next;
    }
    }
   } 
 
/*
 * This method prints out all the statistics of the list
 */
void pst(){
     PNODE temp = head;
     int nodes = 0;
     double avg = 0;
     int maxCount, minCount;
     // find the maximum and minimum count
     if (temp == NULL){
         printf("List is Empty!\n");
     }
     else{
         maxCount = minCount = temp->count;
         // Make dure to keep track of no. of nodes
         nodes++;
         avg += temp->count;
         for (temp = temp->next; temp != NULL; temp = temp->next){
             
            if (temp->count > maxCount)
                maxCount = temp->count;
            else if (temp->count < minCount)
                minCount = temp->count;
            nodes++;
            avg += temp->count;
        }
        //Print all the statistics
        printf("No. of nodes = %d\n", nodes); fflush(stdout);
        printf("Max. count = %d\n", maxCount); fflush(stdout);
        printf("Min. count = %d\n", minCount); fflush(stdout);
        printf("Avg. count = %.1f\n", avg/nodes); fflush(stdout);
    }
 }
 
 /*
 * This method sorts the list in non-increasing order from left to right
 * using insertion sort.
 */
 void sort(){
     PNODE temp;
     PNODE list;
     PNODE swap;
     // For all the n elements, loop n^2 times
      for (list = head; list->next != NULL; list = list->next){
        for (swap = list->next; swap != NULL; swap = swap->next){
            if (list->count < swap->count){
                if ((temp = malloc(sizeof(PNODE))) == NULL) {
                    printf("Node allocation failed. \n");
                     exit(1); /* Stop program */
                }
                //Swap the current largest count with list using temp for storing list
                strcpy(temp->symbol, list->symbol); temp->count = list->count;
                strcpy(list->symbol, swap->symbol); list->count = swap->count;
                strcpy(swap->symbol, temp->symbol); swap->count = temp->count;
            }
        }
    }
 }
 
 /*
 * This method deletes a node from the list
 */
 void del(char *word){
     PNODE temp;
     //Make sure to remove the node only if count is zero
     if (strcmp(word, head->symbol) == 0){
         head->count -= 1;
         if (head->count == 0){
            temp = head;
            head = head->next;
            //Free temp
            free(temp);
            //Return from function
            return;
         }
         else{
             //Make sure to re-sort the list
             sort();
             return;
         }
     }
     else {
       PNODE temp1 = head;
       PNODE delNode;
       while (temp1 != NULL){
         if (strcmp(word, temp1->symbol) == 0){
           delNode = temp1;
           delNode->count -= 1;
       }
        temp1 = temp1->next;
       }
       if (delNode->count == 0){
        PNODE prevPtr = head;
        while(prevPtr->next != NULL && (strcmp(word, prevPtr->next->symbol) != 0))
          prevPtr = prevPtr->next;
        if(prevPtr->next == NULL){
            return;
        }
            prevPtr->next = prevPtr->next->next;
            free(delNode);
            return;
      }
      else{
        sort();
        return;
      }
   }
 }
 
 /*
  * This method deletes all the nodes with count less than or equal 
  * to n
  * @param val : The value of count
  */
 void fde(int val){
     if (head->count == val){
         head = NULL;
     }
     else{
         PNODE prev = head;
         PNODE temp = head->next;
         while (temp != NULL){
            // Remove all the nodes with count<=val 
            if (temp->count == val){
                temp->next = NULL;
                prev->next = NULL;
                tail = prev;
                return;
            } 
            temp = temp->next;
            prev = prev->next;
         }
         
     }
 }
 /*
  * This methos prints all the elements in the node with count in range
  * of v1 and v2.
  * @v1 : the starting bound of count
  * @v2 : the ending bound of count
  */
 void pcr(int v1, int v2){
    PNODE temp = head;
    // If the list isn't empty, print the symbols between count v1 and v2 
    if (temp == NULL) {
       printf("List is empty.\n"); fflush(stdout);
    }
    else {
        while (temp != NULL) {
        if (temp->count >= v1 && temp->count <= v2){    
          printf("%s %5d\n", temp-> symbol, temp->count); fflush(stdout);
        }
         temp = temp->next;
    }
  }
 }

/*
 * This method prints all the nodes in the list which starts with the given 
 * input.
 * @param word: The word with which the symbol should start
 */ 
void ppr(char *word){
    PNODE temp = head;
    //If the list isn't empty, see which symbols start with the given word
    if (temp == NULL) {
       printf("List is empty.\n"); fflush(stdout);
    }
    else {
        while (temp != NULL) {
        if ((strncmp(temp->symbol, word, strlen(word))) == 0){    
          printf("%s %5d\n", temp->symbol, temp->count); fflush(stdout);
        }
         temp = temp->next;
    }
  }
}

/*
 * This method prints all the nodes in the list which ends with the given 
 * input.
 * @param word: The word with which the symbol should end
 */
void psu(char *word){
    PNODE temp = head;
    //If the list isn't empty, see which symbols end with the given word
    if (temp == NULL) {
       printf("List is empty.\n"); fflush(stdout);
    }
    else {
        while (temp != NULL) {
        if ((strlen(temp->symbol) >= strlen(word)) && 
        (strcmp(temp->symbol + (strlen(temp->symbol) - strlen(word)), word)) == 0){    
          printf("%s %5d\n", temp->symbol, temp->count); fflush(stdout);
        }
         temp = temp->next;
    }
  }
}
  
 
