#include <stdio.h>
#include <stdlib.h>

struct dict{
    struct dict* left, *right;
    char word[10], meaning[30];
}*Root = NULL;

typedef struct dict dictionary;

void Search();
void insert(dictionary *);
void view(dictionary *);
int check(char[], char[]);

int check(char a[], char b[]){
    int i , j, c;
    for(i = 0, j= 0; a[i] != '\0' && b[j] != '\0'; i++, j++){
        if(a[i] > b[j]){
            c = 1;
            break;
        }else if(a[i] < b[j]){
            c = -1;
            break;
        }else{
            c = 0;
        }
    }

    if( c== 1){
        return 1;
    }else if(c == -1){
        return -1;
    }else{
        return 0;
    }
}


void Search(){
    char w[10];
    dictionary *ptr;
    int flag = 0;
    ptr = Root;
    printf("\nEnter the word :");
    scanf("%s", w);

    while(ptr != NULL && flag == 0){
        if(check(w, ptr->word) == 1){
            ptr = ptr->right;
        }else if(check(w, ptr->word) == -1){
            ptr = ptr->left;
        }else{
            flag = 1;
            printf("\nMeaning: %s", ptr->meaning);
            break;
        }
    }

    if(flag == 0 && ptr == NULL){
        printf("\nWord not found.");
    }
}

void insert(dictionary*temp){
    dictionary *ptr, *par;
    int flag = 0;
    ptr = Root;

    if(Root == NULL){
        Root = temp;
    }else{
        while(ptr != NULL && flag == 0){
            if(check(temp->word, ptr->word) == 1){
                par = ptr;
                ptr = ptr->right;
            }else if(check(temp->word, ptr->word) == -1){
                par = ptr;
                ptr = ptr->left;
            }else{
                flag = 1;
                printf("\nWord already exists!!\n");
                break;
            }
        }
    }
    
    if(flag == 0){
        if(check(par -> word , temp -> word) == 1){
            par -> left = temp;
        }else if(check(par -> word , temp-> word) == -1){
            par -> right = temp;
        }
    }
}

void view(dictionary *ptr){
    if(Root == NULL){
        printf("\nEmpty Dictionary\n");
    }else{
        if(ptr != NULL){
            view(ptr->left);
            printf("\nWord: %s", ptr-> word);
            printf("\nMeaning: %s", ptr -> meaning);
            view(ptr->right);
        }
    }
}

int main(int argc, char const *argv[]){
    int ch;
    dictionary *temp;
    while(ch != 4){
        printf("\n1. Search\n2. Insert\n3. View\n4. Quit\nYour choice please... ");
        scanf("%d", &ch);
        switch(ch){
            case 1: Search();break;
            case 2: 
            temp=(dictionary *)malloc(sizeof(dictionary));
            temp->left = NULL;
            temp->right = NULL;
            printf("\nInsert Word: ");
            scanf("%s", temp-> word);
            printf("\nInsert meaning: ");
            scanf("%s", temp-> meaning);

            insert(temp);break;

            case 3: view(Root);break;
            case 4: exit(0);
        }
    }


    return 0;
}

