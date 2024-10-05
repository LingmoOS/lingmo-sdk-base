#ifndef KYSDK_BASE_UTILS_SKIPLISK_H__
#define KYSDK_BASE_UTILS_SKIPLISK_H__


/** @defgroup 链表模块
  * @{
  */


/**
 * @file skip_linklist.h
 * @author liuyunhe (liuyunhe@lingmoos.cn)
 * @brief 时间复杂度:
 *          插入（平均）: O(log(n))
 *          删除（平均）: O(log(n))
 *          查找（平均）: O(log(n))
 *        空间复杂度:
 *          O(n)
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <listdata.h>

typedef struct _kysdk_skiplist_node{
    int key;
    kysdk_listdata data;

    struct _kysdk_skiplist_node **next;
}kysdk_skiplist_node;

typedef struct _kysdk_skiplist{
    unsigned int counts;    // 节点个数
    unsigned int max_levels;    // 最高层数

    kysdk_skiplist_node **children;
}kysdk_skiplist;

/**
 * @brief 创建跳表
 * 
 * @return kysdk_skiplist* 
 */
extern kysdk_skiplist* kysdk_create_skiplist();

/**
 * @brief 销毁跳表，并回收所有分配的内存；注意data.ptr指向的内存（若存在）不会被释放
 * 
 * @param list 
 */
extern void kysdk_destroy_skiplist(kysdk_skiplist *list);

/**
 * @brief 设置跳表最高层数，该选项必须在跳表为空时使用
 * 
 * @param list 
 * @param maxlevels 
 * @return int
 */
extern int kysdk_skiplist_setmaxlevels(kysdk_skiplist *list, unsigned int maxlevels);

/**
 * @brief 插入节点
 * 
 * @param list 
 * @param key 
 * @param data 
 * @return int， 成功插入返回0，失败返回-1
 */
extern int kysdk_skiplist_insert(kysdk_skiplist *list, int key, kysdk_listdata data);

/**
 * @brief 删除key值对应的节点
 * 
 * @param list 
 * @param key 
 * @return int, 成功删除返回0，失败返回-1
 */
extern int kysdk_skiplist_delete(kysdk_skiplist *list, int key);

/**
 * @brief 根据给定的key搜索data内容
 * 
 * @param list 
 * @param key 
 * @return kysdk_listdata， 当搜索的key不存在时，data.num值为-1
 */
extern kysdk_listdata kysdk_skiplist_search(kysdk_skiplist *list, int key);

#endif

/**
  * @}
  */