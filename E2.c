#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUCKETS 1000
#define MULTIPLIER 31
#define MAX_LEN 100

//Khởi tạo struct
struct wordrec
{
    char* word;
    unsigned long count;
    struct wordrec* next;
};

//Cấp bộ nhớ cho node mới của wordrec
struct wordrec* walloc(const char* str)
{
    struct wordrec* p=(struct wordrec*)malloc(sizeof(struct wordrec));
    if(p!=NULL)
    {
        p->count=0;
        p->word=strdup(str); //Tạo ra chuỗi copy.
        p->next=NULL;
    }
    return p;
}

//Khởi tạo hash bucket.
struct wordrec* table[MAX_BUCKETS];

//Tạo ra chuỗi hash cho ký tự.
unsigned long hashstring(const char* str)
{
    unsigned long hash=0;
    while(*str)
    {
        hash=hash*MULTIPLIER+*str;
        str++;
    }
    return hash%MAX_BUCKETS;
}

//Hàm để tính chuỗi hash, vào bucket của chuỗi hash và tìm bằng strcmp, 
//trả lại pointer nếu tìm thấy từ đó. Nếu không tìm thấy
//sẽ tạo ra một node mới và đẩy lên đầu hash index.
struct wordrec* lookup(const char* str, int create)
{
    unsigned long hash=hashstring(str);
    struct wordrec* wp=table[hash];
    struct wordrec* curr=NULL;
    for(curr=wp; curr!=NULL; curr=curr->next)
        if(strcmp(curr->word, str)==0) /* found */
        {
            return curr;
        }
    if(create)
    {
        curr=(struct wordrec*)malloc(sizeof(struct wordrec));
        curr->word=strdup(str);
        curr->count=0;
        curr->next=table[hash];
        table[hash]=curr;
    }
    return curr;
}

//Hàm giải phóng bộ nhớ đã cấp
void cleartable()
{
    struct wordrec* wp=NULL, *p=NULL;
    int i=0;
    for(i=0; i<MAX_BUCKETS; i++)
    {
        wp=table[i];
        while(wp)
        {
            p=wp;
            wp=wp->next;
            free(p->word);
            free(p);
        }
    }
}

//Hàm main
int main(int argc, char* argv[])
{
    FILE* fp=fopen("book.txt", "r"); //Đọc dữ liệu từ file book.txt 
    char word[1024];
    struct wordrec* wp=NULL;
    int i=0;

    //Bắt table bắt đầu với dữ liệu NULL
    memset(table, 0, sizeof(table));

    //Đọc từ đầu vào
    while(1)
    {
        if(fscanf(fp, "%s", word)!=1)
            break;
        wp=lookup(word, 1); //Tìm và tạo nếu không tồn tại
        wp->count++;
    }
    fclose(fp);

    //Hàm in ra tất cả các từ mà có tần xuất > 1000
    for(i=0; i<MAX_BUCKETS; i++)
    {
        for(wp=table[i]; wp!=NULL; wp=wp->next)
        {
            if(wp->count>1000)
            {
                printf("%s-->%ld\n", wp->word, wp->count);
            }
        }
    }

    cleartable();
    return 0;
}