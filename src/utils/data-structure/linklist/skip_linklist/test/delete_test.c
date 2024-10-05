#include <skip_linklist.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define ARRAY_SIZE    20

int array[ARRAY_SIZE];
int del_flag[ARRAY_SIZE] = {0};

void print_list(kysdk_skiplist *list)
{
    for (int i = list->max_levels - 1; i >= 0; i --)
    {
        kysdk_skiplist_node *curnode = list->children[i];
        printf("Level[%d]: ", i);
        while (curnode)
        {
            printf("%d->", curnode->key);
            curnode = curnode->next[i];
        }
        printf("NULL\n");
    }
}

int test_list_delete(kysdk_skiplist *list)
{
    for (int i = 0; i < ARRAY_SIZE; i ++)
    {
        if (random() % 2)
        {
            del_flag[i] = 1;
            kysdk_skiplist_delete(list, array[i]);
            printf("Deleted %d\n", array[i]);
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i ++)
    {
        if (del_flag[i] && kysdk_skiplist_search(list, array[i]).num != -1)
        {
            printf("Skiplist delete test failed.\n");
            return -1;
        }
    }

    printf("Skiplist order test pass.\n");

    return 0;
}

int main()
{
    kysdk_skiplist *list = kysdk_create_skiplist();

    kysdk_skiplist_setmaxlevels(list, 5);
    
    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i ++)
    {
        array[i] = i;
        kysdk_skiplist_insert(list, i, (kysdk_listdata)i);
        printf("%d has been insert.\n", i);
        sleep(1);
    }
    
    print_list(list);

    int res = test_list_delete(list);

    print_list(list);

    kysdk_destroy_skiplist(list);

    return res;
}