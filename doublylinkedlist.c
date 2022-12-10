#include <stdio.h>

struct list_node
{
    struct list_node *prev;
    struct list_node *next;
};

struct string_item
{
    struct list_node node;
    const char *string;
};

struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }

    item->prev = tail;
    item->next = NULL;

    return item;
}

void remove_from_head(struct string_item *item)
{
    if (item == NULL)

        return;

    if (item->node.next == NULL)
    {
        free(item);
        return;
    }

    struct string_item *newHead = item->node.next;
    newHead->node.prev = NULL;
    *item = *newHead;
}

void insert_after_item(struct list_node *item, char *newvalue, char *oldvalue)
{
    struct string_item *temphead = item;
    struct string_item *newitem = string_item_new(newvalue);
    struct string_item *item_next;

    while (temphead->node.next != NULL)
    {
        temphead = temphead->node.next;

        if (temphead->string == oldvalue)
        {
            item_next = temphead->node.next;
            temphead->node.next = newitem;
            newitem->node.prev = temphead;
            newitem->node.next = item_next;
            item_next->node.prev = newitem;
        }
    }
}

void insert_before_item(struct string_item *item, char *newvalue, char *oldvalue)
{
    struct string_item *temphead = item; // testa
    struct string_item *newitem = string_item_new(newvalue);
    struct string_item *item_prev;

    while (temphead->node.next != NULL)
    {
        temphead = temphead->node.next;
        if (temphead->string == oldvalue)
        {

            item_prev = temphead->node.prev;
            item_prev->node.next = newitem;
            newitem->node.prev = item_prev;
            newitem->node.next = temphead;
            temphead->node.prev = newitem;
        }
    }
}
void swap(struct string_item *node1, struct string_item *node2)
{
    char *string = node1->string;
    node1->string = node2->string;
    node2->string = string;
}

void Shuffling(struct string_item *head)
{
    struct string_item *temp = head;
    struct string_item *next = temp->node.next;
    while (next)
    {

        swap(temp, next);
        temp = next;
        next = temp->node.next;
    }
}

#define NODO struct list_node *

int main()
{
    struct string_item *list = NULL;

    list_append((NODO *)&list, (NODO)string_item_new("Hello World"));
    list_append((NODO *)&list, (NODO)string_item_new("ciao"));
    list_append((NODO *)&list, (NODO)string_item_new("mondo"));
    list_append((NODO *)&list, (NODO)string_item_new("flowers"));
    list_append((NODO *)&list, (NODO)string_item_new("last item"));
    struct string_item *string_item = list;
    remove_from_head(string_item);
    insert_after_item(string_item, "first ciao  ", "ciao");
    insert_before_item(string_item, "after ciao", "ciao");

    Shuffling(string_item);
    while (string_item)
    {

        printf("MAIN %d:", string_item);
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    return 0;
}