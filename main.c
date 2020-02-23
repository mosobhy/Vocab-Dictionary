#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#define N 27
#define MAX 512

// defining the node representation.
typedef struct Node
{
    //Word exist;
    bool is_word;
    char arabic[MAX];
    struct Node *children[N];
}
Node;

Node *root = NULL;

// helpers functions prototypes.
Node *create();
int Index(char c);
bool unload_(Node *ptr);
bool load(FILE *fpe, FILE *fpa);
int check(const char *word, char *arr);
bool unload(void);


int main()
{
    // open the file and pass it to be loaded.
    FILE *fpe = fopen("English.txt", "r");
    if (!fpe)
    {
        printf("file could not be opened\n");
        return 1;
    }

    FILE *fpa = fopen("Spanish.txt", "r");
    if (!fpe)
    {
        printf("Arabic file could not be opened\n");
        return 2;
    }

    // pass the file pointer to the load function.
    bool loaded = load(fpe, fpa);
    if (!loaded)
    {
        printf("file not loaded\n");
        return 3;
    }

    char *input = (char *)malloc(sizeof(char));
    printf("ENGLISH: ");
    scanf("%s", input);

    // pass the input to the check function to search.
    char meaning[MAX];
    int returned = check(input, meaning);
   if (returned == 3)
    {
        printf("WRONG SPELLING\n");
        return 4;
    }

    // display the output.
    printf("Spanish: %s\n", meaning);

    return 0;
}

// declaring the function that allocate a new node and return a pointer to it.
Node *create()
{
    // allocate space for the new node
    Node *newnode = (Node *)malloc(sizeof(Node));

    // initialize its fields to the state values.
    newnode->is_word = false;
    //newnode->arabic = NULL;

    for(int i = 0; i < N; i++)
    {
        newnode->children[i] = NULL;
    }

    return newnode;
}

// declaring the function that returns the index of a char.( just lowercase )
int Index(char c)
{
    int apostrophe = 0;
    if (isalpha(c))
    {
        if (islower(c))
            return c - 'a';
        else
            return c - 'A';
    }
    else if (c == '\'')
    {
        apostrophe = 26;
    }

    return apostrophe;
}

// declaring the load function that loads the dataset into the TRIE.
bool load(FILE *fpe, FILE *fpa)
{
    // initialize the root pointer.
    root = create();
    if (root == NULL)
    {
        unload();
        return false;
    }

    // declaring the traversing pointer (we use it to keep track of the current pos)
    Node *ptr = root;

    // declare the buffer to hold the line from the arabic file and initialize it.
    char Ara_word[MAX] = "";

    // get a string from the Arabic file to insert it into the node after loading the English word..
    fgets(Ara_word, MAX, fpa);

    // get a single character at each iteration and store it in the TRIE.
    for(char c = fgetc(fpe); c != EOF; c = fgetc(fpe))
    {
        if (c != '\n')
        {
            // indexing the chars of the buffer.
            int INDEX = Index(c);

            if (ptr->children[INDEX] == NULL)
            {
                // assign the root children to the new malloced node.
                ptr->children[INDEX] = create();
            }
            // advance the ptr to pointe at the next node.
            ptr = ptr->children[INDEX];
        }
        else
        {
            // mark as a word.
            ptr->is_word = true;

            // assign the last node to the arabic word.
            strcpy(ptr->arabic, Ara_word);

            // get to the first node again.
            ptr = root;

            // get another word from the arabic file.
            fgets(Ara_word, MAX, fpa);
        }
    }

    // close the file.
    fclose(fpe);
    fclose(fpa);

    return true;

}

// it copys the Arabic word into an array we pass it from the main (holding the Arabic meaning)
// case insensitivity ==> upper or lower case letter is allowed.
// string should only contains letters and apostrophe.
int check(const char *word, char *arr)
{
    Node *ptr = root;

    // iterate over the word.
    for(int i = 0, n = strlen(word); i <= n; i++)
    {
        // assign the index of the current char order.
        int INDEX = Index(word[i]);

        if (word[i] == '\0')
        {
            // check if the word in the dictionary or not.
            if (ptr->is_word == true)
            {
                // assign the output to the Arabic word.
                // copy the output to the array passed from the main.
                strcpy(arr, ptr->arabic);
                return 1;
            }
            else
                return 2;
        }
        // wrong spelling.
        if (ptr->children[INDEX] == NULL)
            return 3;

        // forward the pointer to the next value(node).
        ptr = ptr->children[INDEX];
    }

    return 4;
}

// unload the dictionary from the memory, return true or false.
bool unload_(Node *ptr)
{
    // iterate over each element in the children array.
    for(int i = 0; i < N; i++)
    {
        // check if its not null. start again.
        if (ptr->children[i] != NULL)
        {
            unload_(ptr->children[i]);
        }
    }
    // free the node.
    free(ptr);

    return true;
}

bool unload(void)
{
    if (unload_(root))
        return true;

    return false;
}


