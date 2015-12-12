#include "list.h"
#include <stdio.h>

//HONGRUI ZHENG

// Test your list code here! Make sure you test all the cases!
int main()
{
	LIST* llist = create_list();

	push_front(llist, 1);
	push_front(llist, 2);
	push_front(llist, 3);
	push_front(llist, 4);
	push_front(llist, 5);
	push_front(llist, 6);
	push_front(llist, 7);
	push_front(llist, 8);
	push_front(llist, 9);
	push_front(llist, 10);
	printf("size of the list: %d\n",llist->size);
	printf("head of the list: %d\n",llist->head->data);
	print_list(llist);
	printf("\n");
	printf("pop one from the back: %d\n", pop_back(llist));
	printf("size of the list: %d\n",llist->size);
	printf("head of the list: %d\n",llist->head->data);
	print_list(llist);
	printf("\n");
	for (int i = llist->size; i > 1; i--) {
		printf("popin':%d\n", pop_back(llist));
	}
	printf("size of the list: %d\n",llist->size);
	printf("head of the list: %d\n",llist->head->data);
	print_list(llist);
	printf("\n");

	printf("last one: %d\n", pop_back(llist));
	printf("size of the list: %d\n",llist->size);
	//printf("head of the list: %d\n",llist->head);
	print_list(llist);
	printf("\n");

	LIST* llist2 = create_list();
	destroy(llist2);

	destroy(llist);
	
	return 0;
}
