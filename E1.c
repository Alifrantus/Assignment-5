#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 10

//Khởi tạo struct
struct student 
{
    char fname[100];
    char lname[100];
    int year;
    int age;
};

//Khởi tạo dữ liệu
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

//Hàm so sánh tên
int compare_fname(const void* a, const void* b)
{
    struct student* sa = (struct student*)a;
    struct student* sb = (struct student*)b;
    return strcmp(sa -> fname, sb -> fname);
}

//Hàm so sánh họ
int compare_lname (const void* a, const void* b)
{
    struct student* sa = (struct student*)a;
    struct student* sb = (struct student*)b;
    return strcmp(sa -> lname, sb -> lname);
}

//Hàm lưu lại thay đổi về dữ liệu
void apply(struct student* sarr, int nrec, void (*fp)(void* prec, void* arg), void* arg)
{
    int i = 0;
    for(i = 0; i < nrec; i++)
    {
        fp(&sarr[i], arg);
    }
}

//Hàm in ra dữ liệu về học sinh
void printrec(void* prec, void* arg)
{
    struct student* pstud = (struct student*)prec;
    printf("%-20s %-20s %2d %2d\n", pstud -> fname, pstud -> lname, pstud -> year, pstud -> age);
}

//Hàm so sánh và in ra kết quả khi học sinh có số tuổi lớn hơn số tuổi so sánh
void isolder(void* prec, void* arg)
{
    int* age = (int*)arg;
    struct student* pstud = (struct student*)prec;
    if(pstud -> age < *age)
        return;
    else 
        printf("%-20s %-20s %2d %2d\n", pstud -> fname, pstud -> lname, pstud -> year, pstud -> age);
}

//Hàm main
int main()
{
    //Khởi tạo dữ liệu ban đầu
    int nstudents = sizeof(class)/sizeof(struct student);
    int age;

    //In ra danh sách sinh viên trước khi chỉnh sửa
    puts("----------------");
    puts("Initiate");
    puts("----------------");
    apply(class, nstudents, printrec, NULL);

    //Sắp xếp học sinh theo tên
    puts("----------------");
    puts("Sort by first name");
    puts("----------------");
    qsort(class, nstudents, sizeof(struct student), compare_fname);
    apply(class, nstudents, printrec, NULL);

    //Sắp xếp học sinh theo họ
    puts("----------------");
    puts("Sort by last name");
    puts("----------------");
    qsort(class, nstudents, sizeof(struct student), compare_lname);
    apply(class, nstudents, printrec, NULL);

    //Sắp xếp học sinh theo tuổi (20 tuổi)
    puts("---------------");
    puts("Sort by age 20");
    puts("----------------");
    age = 20;
    apply(class, nstudents, isolder, &age);
    
    return 0;
}