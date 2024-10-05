#include <skip_linklist.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

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

int test_list_order(kysdk_skiplist *list)
{
    kysdk_skiplist_node *node = list->children[0];
    while (node)
    {
        if (node->next[0])
        {
            if (node->key > node->next[0]->key)
            {
                printf("Skiplist order test failed.\n");
                return -1;
            }
        }
        node = node->next[0];
    }

    printf("Skiplist order test pass.\n");

    return 0;
}

int main()
{
    kysdk_skiplist *list = kysdk_create_skiplist();

    kysdk_skiplist_setmaxlevels(list, 5);
    
    srand(time(NULL));
    for (int i = 0; i < 100; i ++)
    {
        int num = random() % 500 + 1;
        kysdk_skiplist_insert(list, num, (kysdk_listdata)i);
        printf("%d has been insert.\n", num);
        sleep(1);
    }
    
    print_list(list);

    int res = test_list_order(list);

    kysdk_destroy_skiplist(list);

    return res;
}