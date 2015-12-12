#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * This function will create a new list, initialize its fields and return a pointer to that list.
 */
LIST *create_list()
{	
	LIST *list = malloc(sizeof(LIST));
	list->head = NULL;
	list->size = 0;
	return list;
}

/**
 * This function will create a node from the given data and return a pointer to that node.
 */
NODE *create_node(int data)
{
	NODE *node = malloc(sizeof(NODE));
	node->data = data;
	node->next = NULL;
	return node;
}

/**
 * This function will add a node with the given data to the head of the linked list.
 */
void push_front(LIST *llist, int data)
{
	NODE *newnode = create_node(data);
	newnode->next = llist->head;
	llist->head = newnode;
	llist->size++;
	return;
}

/**
 * Removes the last node from the tail of the linked list and returns the data from the removed node to the user.
 * If the list is empty, return -1.
 */
int pop_back(LIST *llist)
{
	NODE *current = llist->head;
	NODE *pre = NULL;
	if (current != NULL) {
		while (current->next != NULL) {
			pre = current;
			current = current->next;
		}
		if (pre != NULL) {
			int ret = current->data;
			free(pre->next);
			pre->next = NULL;
			llist->size--;
			return ret;
		} else {
			int ret = current->data;
			free(llist->head);
			llist->head = NULL;
			llist->size--;
			return ret;
		}
	}
	return -1;
}

/**
 * All memory used in the linked list that was allocated from the heap should be freed. This includes the linked 
 * list struct and all of the node structs in the linked list.
 */
void destroy(LIST *llist)
{
	NODE *current = llist->head;
	while (current != NULL) {
		NODE *pre = current;
		current = current->next;
		free(pre);
	}
	free(llist);
    return;
}

/** 
 * This function will print out the entire linked list in order. It will traverse the list starting at the head 
 * and go node by node till it reaches to the tail. At each node, it will print out the node's data followed by
 * ", ". (This does mean that the last node in the list will also be followed by a ", "). If the list is empty, 
 * print "empty".
 */
void print_list(LIST *llist)
{
	NODE *current = llist->head;
	if (current == NULL) {
		printf("empty");
		return;
	}
	while (current != NULL) {
		printf("%d, ", current->data);
		current = current->next;
	}
	return;
}
