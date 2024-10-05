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

int test_list_search(kysdk_skiplist *list)
{
    for (int i = 0; i < 5; i ++)
    {
        int target = random() % 50 + 1;
        kysdk_listdata data = kysdk_skiplist_search(list, target);
        printf("Searching for %d, data is %d\n", target, data.num);

        kysdk_skiplist_node *curnode = list->children[0];
        short finded = 0;
        while (curnode)
        {
            if (curnode->key == target)
            {
                finded = 1;
                break;
            }
            curnode = curnode->next[0];
        }
        
        if (finded && data.num == -1)
        {
            printf("Skiplist search test failed.\n");
            return -1;
        }
    }

    printf("Skiplist search test pass.\n");

    return 0;
}

int main()
{
    kysdk_skiplist *list = kysdk_create_skiplist();

    kysdk_skiplist_setmaxlevels(list, 5);
    
    srand(time(NULL));
    for (int i = 0; i < 20; i ++)
    {
        int num = random() % 50 + 1;
        kysdk_listdata data;
        data.num = i;
        kysdk_skiplist_insert(list, num, data);
        printf("[%d] %d has been insert.\n", i, num);
        sleep(1);
    }
    
    print_list(list);

    int res = test_list_search(list);

    kysdk_destroy_skiplist(list);

    return res;
}