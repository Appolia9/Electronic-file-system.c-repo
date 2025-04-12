#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define CLS system("cls")


#define max_lengh_str 100
#define MAXL 100
#define MAXR 50

typedef struct MUSIC{
    int id;
    char* name_of_the_song;
    char* performer;
    char* name_of_the_album;
    int numer_in_top;
    double profit;
    double rating;
    char** feets;
    int feets_count;
    struct MUSIC *prev;
    struct MUSIC *next;
}song;

typedef struct first_sh{
    int cnt;
    song *first;
    song *last;
}head;

head* make_head(){

    head* ph;

    ph = (head*)malloc(sizeof(head));
    if(ph){
        ph->cnt = 0;
        ph->first = NULL;
        ph->last = NULL;
    }
    return ph;

}

song* filling(head* h, char* s1, char sep){
    int len = strlen(s1);
    int i, j = 0,  k = 1;
    char* n ;
    song* struc;

    n = (char*)malloc(sizeof(char)*(len+1));

    struc = (song*)malloc(sizeof(song));
    struc->name_of_the_song = (char*)malloc(sizeof(char)*100);
    struc->performer = (char*)malloc(sizeof(char)*100);
    struc->name_of_the_album = (char*)malloc(sizeof(char)*100);
    struc->feets = (char**)malloc(sizeof(char*));
    struc->feets_count = 0;


    for(i = 0; i<= len; i++){
        if(s1[i] == sep || i == len){
            n[i - j] = '\0'; 
            switch(k)
            {
            case 1:
                strcpy(struc->name_of_the_song, n);
                break;
            case 2:
                strcpy(struc->performer, n);
                break;
            case 3:
                strcpy(struc->name_of_the_album, n);
                break;
            case 4:
                struc->numer_in_top = atoi(n);
                break;
            case 5:
                struc->profit = atof(n);
                break;
            case 6:
                struc->rating = atof(n);
                break;
           case 7:
                struc->feets[struc->feets_count] = (char*)malloc(sizeof(char)*(strlen(n)+1));
                strcpy(struc->feets[struc->feets_count],n);
                printf("%s", struc->feets[0]);
                struc->feets_count++;
                break;
            default:
                struc->feets = (char**)realloc(struc->feets, (struc->feets_count + 1) * sizeof(char*));
                struc->feets[struc->feets_count] = (char*)malloc((strlen(n)+1)*sizeof(char));
                strcpy(struc->feets[struc->feets_count],n);
                struc->feets_count++;
                break;
            }
           
            k++;
            j = i + 1;
            continue;
        }
        n[i-j] = s1[i];
    }
    free(n);
    
    return struc;

}

void insert_after(head *h, song* prev, song* current){
    prev->next = current;
    current ->prev = prev;
    current->next = h->first;
    h->first->prev = current;

    h->last = current;
    h-> cnt++;
}


int delete_by_id(head *h, int s_id){
    int i, flag = 0;
    song *q;
    if(h->last->id < s_id){
        printf("No such id\n");
        return -1;
    }
    if (s_id >= h->last->id/2){
        q = h->last;
        for(i = 0; i< h->cnt/2+2; i++){
            if(q->id == s_id){
                flag = 1;
                break;
            }
            q = q->prev;
        }
    }
    else{
        q = h->first;
        for(i = 0; i<h->last->id/2+2; i++){
            if(q->id == s_id){
                flag = 1;
                break;
            }
            q = q->next;
        }
    }
    if(flag == 0){
        printf("No such elem\n");
        return -1;
    }

    if(s_id == 1){
        q->next->prev = NULL;
        h->first = q->next;
    }
    if(s_id == h->last->id){
        q->prev->next = NULL;
        h->last = q->prev;
    }
    else{
        q->prev->next = q->next;
        q->next->prev = q->prev;
    }
    h->cnt--;
    free(q);
    printf("Element was deleted\n");
    return 2;

}

int delete_by_field(head *h, char *s1, char *s2){
    int i;
    int res = 0;
    int s_len, j;
    char *mas[] = {"name of the song","performer","name of the album","numer in top","profit","rating","feets"};
    song *elem;

    for(i = 0; i<7; i++){
        if(strcmp(mas[i],s1)==0){
            break;
        }
    }

    if(i==7){
        printf("\nNo such field\n");
        return -1;
    }

    elem = h->first;
    for(j = 0; j<h->cnt;j++){
        switch (i)
        {
            case 0:
                if(strcmp(elem->name_of_the_song, s2) == 0){
                    res = 1;
                }
                break;
            case 1:
                if(strcmp(elem->performer, s2) == 0){
                    res = 1;
                }
                break;
            case 2:
                if(strcmp(elem->name_of_the_album, s2) == 0){
                    res = 1;
                }
                break;
            case 3:
                if(atoi(s2)==elem->numer_in_top){
                    res = 1;
                }
            case 4:
                if(atof(s2)==elem->profit){
                    res = 1;
                }
                break;
            case 5:
                if(atof(s2)==elem->rating){
                    res = 1;
                }
                break;
            default:
                for(int k = 0; k<elem->feets_count;k++){
                    if(strcmp(elem->feets[k], s2) == 0){
                    res = 1;
                    k = elem->feets_count;
                    }
                }
            break;
        }
        if(res == 1){
            if(elem == h->first){
                elem->next->prev = NULL;
                h->first = elem->next;
            }
            if(elem == h->last){
                    elem->prev->next = NULL;
                    h->last = elem->prev;
            }
            else{
                elem->prev->next = elem->next;
                elem->next->prev = elem->prev;
            }
            h->cnt--;
            printf("Element was deleted\n");
            res = 0;
        }
        elem = elem->next;
    }
    return res;
}

int edit(head *h, song* elem){
    int i;
    char s2[max_lengh_str];
    int s_len;
    char *mas[] = {"name of the song","performer","name of the album","numer in top","profit","rating","feets"};

    printf("Enter field: ");
    fgets(s2,max_lengh_str,stdin);
    s_len = strlen(s2);
    s2[s_len-1] = '\0';

    for(i = 0; i<7; i++){
        if(strcmp(mas[i],s2)==0){
            break;
        }
    }
    if(i==7){
        printf("\nNo such field\n");
        return -1;
    }

    printf("Enter:\n");
    fgets(s2,max_lengh_str,stdin);
    s_len = strlen(s2);
    s2[s_len-1] = '\0';

    switch(i){
        case 0:
            strcpy(elem->name_of_the_song,s2);
        break;
        case 1:
            strcpy(elem->performer,s2);
        break;
        case 2:
            strcpy(elem->name_of_the_album,s2);
        break;
        case 3:
            elem->numer_in_top = atoi(s2);
        break;
        case 4:
            elem->profit = atof(s2);
        break;
        case 5:
            elem->rating = atof(s2);
        break;
        default:
        break;
    }
    printf("Elem was edited\n");
    
    return 1;
}


int search(head *h){
    int i,j,l,len_p,res = 0, flag = 0;
    char s2[max_lengh_str];
    int s_len;
    char *mas[] = {"name of the song","performer","name of the album","numer in top","profit","rating","feets"};
    song *q;

    printf("Enter parametr to search: ");
    fgets(s2,max_lengh_str,stdin);
    s_len = strlen(s2);
    s2[s_len-1] = '\0';

    for(i = 0; i<7; i++){
        if(strcmp(mas[i],s2)==0){
            break;
        }
    }
    if(i==7){
        printf("\nNo such field\n");
        return -1;
    }

    printf("Enter:\n");
    fgets(s2,max_lengh_str,stdin);
    s_len = strlen(s2);
    s2[s_len-1] = '\0';
    s_len = strlen(s2);
    q = h->first;
    for(j = 0;j<h->cnt;j++){
        switch(i){
            case 0:
                l = 0;
                len_p = strlen(q->name_of_the_song);
                if(len_p >= s_len){
                    while(tolower(q->name_of_the_song[l]) == s2[l]){
                        l++;
                    }
                    if(l == s_len){
                        res = 1;
                    }
                }
            break;
            case 1:
                l = 0;
                len_p = strlen(q->performer);
                if(len_p >= s_len){
                    while(tolower(q->performer[l]) == s2[l]){
                        l++;
                    }
                    if(l == s_len){
                        res = 1;
                    }
                }
            break;
            case 2:
                l = 0;
                len_p = strlen(q->name_of_the_album);
                if(len_p >= s_len){
                    while(tolower(q->name_of_the_album[l]) == s2[l]){
                        l++;
                    }
                    if(l == s_len){
                        res = 1;
                    }
                }
            break;
            case 3:
                if(atoi(s2)==q->numer_in_top){
                    res = 1;
                }
            break;
            case 4:
                if(atof(s2)==q->profit){
                    res = 1;
                }
            break;
            case 5:
                if(atof(s2)==q->rating){
                    res = 1;
                }
            break;
            default:
                for(int d= 0; d<q->feets_count;d++){
                    l = 0;
                    len_p = strlen(q->feets[d]);
                    if(len_p >= s_len){
                        while(tolower(q->feets[d][l]) == s2[l]){
                            l++;
                        }
                        if(l == s_len){
                            res = 1;
                            break;
                        }
                    }
                }
            break;
        }
        if(res == 1){
            if(i == 0){
                printf("|%4s |%20s |%20s |%20s | %6s  |%20s |%6s |%10s\n","id", "Name of the song","Performer","Name of the album","numer","profit","rating","feets");
                printf("+-----+---------------------+---------------------+---------------------+---------+---------------------+-------+--------------\n");
            }
            printf("|%4d |%20s |%20s |%20s | %6d  |%20.2f |%6.2f | ", 
            q->id, q->name_of_the_song, q->performer, q->name_of_the_album, q->numer_in_top, q->profit, q->rating);
            for(int j = 0; j<q->feets_count; j++){
                printf("%s  ", q->feets[j]);
            }
            printf("\n");
            flag = 1;
        }
        q = q->next;
        res = 0;
    }
    return flag;
}

// int sort(head *h){
//     int i,j,s_len;
//     char s2[max_lengh_str];
//     char *mas[] = {"name of the song","performer","name of the album","numer in top","profit","rating","feets"};
//     song* current;
//     song* q;

//     printf("Enter parametr to sorting: ");
//     fgets(s2,max_lengh_str,stdin);
//     s_len = strlen(s2);
//     s2[s_len-1] = '\0';

//     for(i = 0; i<7; i++){
//         if(strcmp(mas[i],s2)==0){
//             break;
//         }
//     }
//     if(i==7){
//         printf("\nNo such field\n");
//         return -1;
//     }

//     current = h->first->next;
//     q = current->prev;
//     for(i = 1; i<h->cnt;i++){
//         //q = current->prev;
//         for(j = i;j>0;j--){
//             if(current->numer_in_top<q->numer_in_top){
//                 if(q->prev==NULL){
//                     // q->next=current->next;                    
//                     // current->prev = NULL;
//                     // current->next->prev = q;
//                     // h->first = current;

//                     q->next=current->next; 
//                     current->next = q;
//                     current->next->prev = q;
//                     current->prev = NULL;
//                 }
//                 if(current->next == NULL){
//                     q->prev->next = current;
//                     current->next = q;
//                     current->prev = q->prev;
//                     q->prev = current;
//                     q->next = NULL; 
//                 }else{
//                 // q->next=current->next;
//                 // current->prev = q->prev;
//                 // q->prev->next = current;
//                 // current->next->prev = q;

//                     current->prev = q->prev;
//                     q->next = current->next;
//                     current->next->prev= q;
//                     q->prev->next = current;
//                     current->next = q;
//                     q->prev = current;
//                 }
    
//                 q = current->prev;
//             }
//             else{
//                 j = 0;
//             }
            
//         }
//         q = current->prev;
//         current = current->next;


//     }
//     return 1;

// }

int sort_1(head *h){
    int i,j,s_len;
    char s2[max_lengh_str];
    char *mas[] = {"name of the song","performer","name of the album","numer in top","profit","rating","feets"};
    song* current;
    song* q;

    printf("Enter parametr to sorting: ");
    fgets(s2,max_lengh_str,stdin);
    s_len = strlen(s2);
    s2[s_len-1] = '\0';

    for(i = 0; i<7; i++){
        if(strcmp(mas[i],s2)==0){
            break;
        }
    }
    if(i==7){
        printf("\nNo such field\n");
        return -1;
    }

    current = h->first;
    for(i = 0;i<h->cnt;i++){

    }

    
    return 1;

}

void wr_to_f(FILE *f, head *h){
    song* q;
    int i, j;
    q = h->first;
    for(i = 0; i<h->cnt; i++){
        fprintf(f, "%4d; ", q->id);
        fprintf(f,"%s;  ", q->name_of_the_song);
        fprintf(f,"%s;  ", q->performer);
        fprintf(f,"%s;  ",q->name_of_the_album);
        fprintf(f, "%d;  ",q->numer_in_top);
        fprintf(f, "%10.2f;  ", q->profit);
        fprintf(f, "%6.2f;  ", q->rating);
        for(j = 0; j<q->feets_count; j++){
            fprintf(f, "%s  ", q->feets[j]);
        }
        fprintf(f,"\n");
        q = q->next;
    }
}

void res_print(head* struc, int k_st, int flag) {
    int i, n = 0;
    song* q = struc->first;

    if(flag == 0){
        printf("\nInitial array:\n");
    }
    else if(flag == 1){
        printf("\nThe head of the list was moved\n");
        printf("\nResult:\n");
    }
    else{
        printf("\nThe head of the list remained in the same place\n");
        printf("\nResult:\n");
    }

    for(i = 0; i<k_st; i++){
        if(i == 0){
            printf("|%4s |%20s |%20s |%20s | %6s  |%20s |%6s |%10s\n","id", "Name of the song","Performer","Name of the album","numer","profit","rating","feets");
            printf("+-----+---------------------+---------------------+---------------------+---------+---------------------+-------+--------------\n");
        }
        printf("|%4d |%20s |%20s |%20s | %6d  |%20.2f |%6.2f | ", 
        q->id, q->name_of_the_song, q->performer, q->name_of_the_album, q->numer_in_top, q->profit, q->rating);
        for(int j = 0; j<q->feets_count; j++){
            printf("%s  ", q->feets[j]);
        }
        printf("\n");
        q = q->next;
    }
}

void switch_structs(head *ph,song *pr)
{
    song *m,*k;
/*m - Variable pointer to next element after pr;
k - Variable pointer to the next element after m;*/
    if (pr==ph->first)
    {
        if (ph->cnt==2)
        {
            ph->first=pr->next;
            ph->last=pr;
            ph->first->prev=NULL;
            ph->first->next=ph->last;
            ph->last->next=NULL;
            ph->last->prev=ph->first;
        }
        else
        {
            k=pr->next->next;
            m=pr->next;
            m->prev=NULL;
            ph->first=m;
            ph->first->next=pr;
            ph->first->next->next=k;
            ph->first->next->next->prev=pr;
            ph->first->next->prev=m;
        }
    }
    else
    {
        if (pr->next==ph->last)
        {
            m=pr->next;
            pr->prev->next=m;
            m->prev=pr->prev;
            pr->prev=m;
            pr->next=NULL;
            m->next=pr;
            ph->last=pr;
        }
        else
        {
            m=pr->next;
            m->next->prev=pr;
            pr->prev->next=m;
            m->prev=pr->prev;
            m->prev=pr->prev;
            pr->prev=m;
            pr->next=m->next;
            m->next=pr;
        }
    }
}


void sort(head *ph)
{
    song *pr;/*Current element*/
    char s1[MAXR],s2[MAXR]; /*Arrays for storing lowercase strings*/
    int c; /*Selected sort number;*/
    printf("\nWhich structure field do you want to sort by??\n");
    printf("Enter: 1-to sort by name\n       2-to sort by performer\n       3-to sort by number in top\n       4-to sort by rating\n");
    scanf("%i",&c);
    while (c<1 || c>4)
    {
        printf("Try again,please\n");
        printf("Enter: 1-to sort by name\n       2-to sort by performer\n       3-to sort by number in top\n       4-to sort by rating\n");
        scanf("%i",&c);
    }
    if (c==1)
    {
        for (int i=0;i<ph->cnt-1;i++)
        {
            pr=ph->first;
            for (int z=0;z<ph->cnt-i-1;z++)
            {
                for (int w=0;w<strlen(pr->name_of_the_song);w++)
                    s1[w]=tolower(pr->name_of_the_song[w]);
                s1[strlen(s1)-1]='\0';
                for (int w=0;w<strlen(pr->next->name_of_the_song);w++)
                    s2[w]=tolower(pr->next->name_of_the_song[w]);
                s2[strlen(s2)-1]='\0';
                if (strcmp(s1,s2)>0)
                    switch_structs(ph,pr);
                else
                    if (pr->next) pr=pr->next;
            }
        }
    }
    if (c==2)
    {
        for (int i=0;i<ph->cnt-1;i++)
        {
            pr=ph->first;
            for (int z=0;z<ph->cnt-i-1;z++)
            {
                for (int w=0;w<strlen(pr->performer);w++)
                    s1[w]=tolower(pr->performer[w]);
                s1[strlen(s1)-1]='\0';
                for (int w=0;w<strlen(pr->next->performer);w++)
                    s2[w]=tolower(pr->next->performer[w]);
                s2[strlen(s2)-1]='\0';
                if (strcmp(s1,s2)>0)
                    switch_structs(ph,pr);
                else
                    if (pr->next) pr=pr->next;
            }
        }
    }
    if (c==3)
    {
        for (int i=0;i<ph->cnt-1;i++)
        {
            pr=ph->first;
            for (int z=0;z<ph->cnt-i-1;z++)
            {
                if (pr->numer_in_top > pr->next->numer_in_top)
                    switch_structs(ph,pr);
                else
                    if (pr->next) pr=pr->next;
            }
        }
    }
    if (c==4)
    {
        for (int i=0;i<ph->cnt-1;i++)
        {
            pr=ph->first;
            for (int z=0;z<ph->cnt-i-1;z++)
            {
                if (pr->rating > pr->next->rating)
                    switch_structs(ph,pr);
                else
                    if (pr->next) pr=pr->next;
            }
        }
    }

}

int main(){
    FILE *df;
    FILE *rf;
    int n, s_len, i,j,l;
    int flag = 0;
    int m_id = 1, d;
    int t;
    char *search_str[max_lengh_str];
    char s1[max_lengh_str];
    char s2[max_lengh_str];
    char *mas[] = {"name of the song","performer","name of the album","numer in top","profit","rating","feets"};
    char t1[3];
    song* current;
    song* pre_c;
    head*  h;
    song *q;


    current = (song*)malloc(sizeof(song));
    pre_c = (song*)malloc(sizeof(song));
    


    h = (head*)malloc(sizeof(head));
    h = make_head();

    
    df = fopen("music.txt", "r");


    if (df!=0){
        n =0;
        while(fgets(s1, max_lengh_str, df)!= NULL){
            n++;
        }

        rewind(df);

        for(i = 0; i<n; i++){
            fgets(s1, max_lengh_str, df);
            s_len = strlen(s1);
            s1[s_len-1] = '\0';
            current = filling(h, s1,';');
            current->id = m_id;
            m_id++;
            if(i == 0){
                h->first = current;
                h->last = current;
                h->cnt = 1;
                current->prev = current;
                current->next = current;
                pre_c = current;
                continue;  
            }
            if(i!=n-1){
                insert_after(h,pre_c,current);
                pre_c = current;
            }

        }
    }
    else{
        printf("Error opening the file");
    }
    CLS;

    // printf("To start enter 's'\n");
    // t = getchar();
    printf("Menu:\n");
    printf("0 - Informaion\n");
    printf("1 - Card file output\n");
    printf("2 - Add the cards about song\n");
    printf("3 - Editing\n");
    printf("4 - Delete the card\n");
    printf("5 - Search for cards by parameter\n");
    printf("6 - Sorting the card file by parameter\n");
    printf("-1 - Exit\n");

    //t = getchar();
    // fgets(t1, 3, stdin);
    // s_len = strlen(t1);
    // t1[s_len-1] = '\0';

    while(1){
            scanf("%d",&t);
            while(getchar()!= '\n'); 
            if(t == 0){
                printf("Menu:\n");
                printf("0 - Informaion\n");
                printf("1 - Card file output\n");
                printf("2 - Add the cards about song\n");
                printf("3 - Editing\n");
                printf("4 - Delete the card\n");
                printf("5 - Search for cards by parameter\n");
                printf("6 - Sorting the card file by parameter\n");
                printf("q - Exit\n");
            }
            else if(t == 1){
                res_print(h,h->cnt,flag);
            }
            else if(t == 2){
                printf("Enter the cards\n");
                printf("To finish, enter 0\n");

                fgets(s1, max_lengh_str, stdin);
                s1[strcspn(s1, "\n")] = '\0';
                while(strcmp(s1, "0") != 0){
                    current = filling(h,s1,';');
                    current->id = n;
                    insert_after(h,pre_c,current);   
                    pre_c = current;                    
                    n++;
                    fgets(s1, max_lengh_str, stdin);
                    s1[strcspn(s1, "\n")] = '\0';
                }
            }
            else if(t == 3){
                flag = 0;
                printf("Enter elem id to editing\n");
                scanf("%d", &d);
                while(getchar()!='\n');
                q = h->first;
                for(i = 0; i<h->cnt;i++){
                    if(q->id==d){
                        i = h->cnt;
                        flag = 1;
                        q = q->prev;
                    }
                    q = q->next;
                }
                if(flag!=1){
                    printf("No such elem id\n");
                }
                else{
                    edit(h,q);
                }
                flag = 0;

            }
            else if(t == 4){
                printf("Enter 1 - delete by id, 2 - delete by field\n");
                t = getchar();
                if(t == '2'){
                    printf("Enter field: ");
                    getchar();
                    fgets(s1,max_lengh_str,stdin);
                    s_len = strlen(s1);
                    s1[s_len-1] = '\0';

                    printf("Enter: ");
                    fgets(s2,max_lengh_str,stdin);
                    s_len = strlen(s2);
                    s2[s_len-1] = '\0';

                    flag = delete_by_field(h,s1,s2);
                    printf("End\n");
                }else if(t == '1'){
                    printf("To stop enter 0\n");
                    printf("Enter elem id to delete:\n");            
                    scanf("%d", &d);
                    while(getchar()!='\n');
                    while(d!= 0){
                        flag = delete_by_id(h, d);
                        printf("Enter elem id to delete:\n");  
                        scanf("%d", &d);
                        while(getchar()!='\n');
                    }
                }else{
                    printf("No such command\n");
                }
            }
            else if(t == 5){
                flag = 0;
                flag = search(h);
                if(flag != 1){
                    printf("No such elem\n");
                }
            }
            else if(t == 6){
                sort(h);
                printf("Completed\n");
            }
            else if (t == -1){
                break;
            }
            else{
                printf("No such command");
            }
    }
        

    rf = fopen("res_music.txt", "w");
    wr_to_f(rf,h);
    fclose(rf);

    //res_print(h,h->cnt,flag);


    return 0;
    
}