#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *li = malloc(sizeof(struct list_head));

    if (!li) {
        return NULL;
    }

    li->next = li;
    li->prev = li;

    return li;
}

/* Free all storage used by queue */
void q_free(struct list_head *head) {}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_node;

    new_node = (element_t *) malloc(sizeof(element_t));
    list_add(&new_node->list, head);

    new_node->value = (char *) malloc(strlen(s) + 1);
    memcpy(new_node->value, s, strlen(s) + 1);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_node;

    new_node = (element_t *) malloc(sizeof(element_t));
    list_add_tail(&new_node->list, head);

    new_node->value = (char *) malloc(strlen(s) + 1);
    memcpy(new_node->value, s, strlen(s) + 1);

    return true;
}

/* Remove an element from head of queue */
/**
 * q_remove_head() - Remove the element from head of queue
 * @head: header of queue
 * @sp: string would be inserted
 * @bufsize: size of the string
 *
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 *
 * NOTE: "remove" is different from "delete"
 * The space used by the list element and the string should not be freed.
 * The only thing "remove" need to do is unlink it.
 *
 * Reference:
 * https://english.stackexchange.com/questions/52508/difference-between-delete-and-remove
 *
 * Return: the pointer to element, %NULL if queue is NULL or empty.
 */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || !q_size(head))
        return NULL;

    element_t *tmp = container_of(head->next, element_t, list);
    list_del(head->next);

    if (sp) {
        memcpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    return tmp;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || !q_size(head))
        return NULL;

    element_t *rm_node = container_of(head->prev, element_t, list);
    list_del(head->prev);

    if (sp) {
        memcpy(sp, rm_node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    return rm_node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return -1;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head) {
        len++;
    }

    return len;
}

/* Delete the middle node in queue */
/**
 * q_delete_mid() - Delete the middle node in queue
 * @head: header of queue
 *
 * The middle node of a linked list of size n is the
 * ⌊n / 2⌋th node from the start using 0-based indexing.
 * If there're six elements, the third member should be returned.
 *
 * Reference:
 * https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
 *
 * Return: true for success, false if list is NULL or empty.
 */
bool q_delete_mid(struct list_head *head)
{
    if (!head || !q_size(head))
        return false;

    struct list_head *slow, *fast;
    // element_t *tmp_slow, *tmp_fast;

    for (slow = head->next, fast = head->next->next;
         fast != head && fast->next != head;
         slow = slow->next, fast = fast->next->next) {
        /* Debug: Print the fast & slow in each stage*/
        // if (slow!=head && fast!=head) {
        //     tmp_slow = container_of(slow, element_t, list);
        //     tmp_fast = container_of(fast, element_t, list);

        //     printf("slow: %s, fast: %s\n", tmp_slow->value, tmp_fast->value);
        //     printf("==========================\n");
        // }
    }

    list_del(slow);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
/**
 * q_swap() - Swap every two adjacent nodes
 * @head: header of queue
 *
 * Reference:
 * https://leetcode.com/problems/swap-nodes-in-pairs/
 */
void q_swap(struct list_head *head)
{
    if (!head || !q_size(head))
        return;

    struct list_head *a, *b;

    /* Note: after swapping, the position of a,b need to be noticed! */
    for (a = head->next, b = head->next->next; a != head && b != head;
         a = a->next, b = a->next) {
        b->next->prev = a;
        a->prev->next = b;
        b->prev = a->prev;
        a->next = b->next;
        b->next = a;
        a->prev = b;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    struct list_head *iter, *ptr;

    for (iter = head, ptr = head->prev; iter->next != ptr;
         iter = iter->next, ptr = head->prev) {
        list_del(ptr);
        list_add(ptr, iter);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
