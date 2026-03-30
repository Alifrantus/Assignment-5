#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 10

struct student 
{
    char fname[100];
    char lname[100];
    int year;
    int age;
};

struct student class[] = 
{
    "Sean", "Penn", 2, 21,
    "Sean", "Connery", 4, 25,
    "Angelina", "Jolie", 3, 22,
    "Meryl", "Streep", 4, 29,
    "Robin", "Williams", 3,32,
    "Bill", "Gates", 3, 17,
    "Jodie", "Foster", 4, 25,
    "John", "Travolta", 1, 17,
    "Issac", "Newton", 2, 19,
    "Sarah", "Palin", 2, 19
};

int compare_fname(const void* a, const void* b)
{
    struct student* sa = (struct student*)a;
    struct student* sb = (struct student*)b;
    return strcmp(sa -> fname, sb -> fname);
}

int compare_lname (const void* a, const void* b)
{
    struct student* sa = (struct student*)a;
    struct student* sb = (struct student*)b;
    return strcmp(sa -> lname, sb -> lname);
}

void apply(struct student* sarr, int nrec, void (*fp)(void* prec, void* arg), void* arg)
{
    int i = 0;
    for(i = 0; i < nrec; i++)
    {
        fp(&sarr[i], arg);
    }
}

void printrec(void* prec, void* arg)
{
    struct student* pstud = (struct student*)prec;
    printf("%-20s %-20s %2d %2d\n", pstud -> fname, pstud -> lname, pstud -> year, pstud -> age);
}

void isolder(void* prec, void* arg)
{
    int* age = (int*)arg;
    struct student* pstud = (struct student*)prec;
    if(pstud -> age < *age)
        return;
    else 
        printf("%-20s %-20s %2d %2d\n", pstud -> fname, pstud -> lname, pstud -> year, pstud -> age);
}

int main()
{
    int nstudents = sizeof(class)/sizeof(struct student);
    int age;

    puts("----------------");
    puts("Initiate");
    puts("----------------");
    apply(class, nstudents, printrec, NULL);

    puts("----------------");
    puts("Sort by first name");
    puts("----------------");
    qsort(class, nstudents, sizeof(struct student), compare_fname);
    apply(class, nstudents, printrec, NULL);

    puts("----------------");
    puts("Sort by last name");
    puts("----------------");
    qsort(class, nstudents, sizeof(struct student), compare_lname);
    apply(class, nstudents, printrec, NULL);


    puts("---------------");
    puts("Sort by age 20");
    puts("----------------");
    age = 20;
    apply(class, nstudents, isolder, &age);
    
    return 0;
}