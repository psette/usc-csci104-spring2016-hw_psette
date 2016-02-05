Node* merge(Node*& first, Node*& second) {
	if (first == NULL || second == NULL) return first == NULL ? second : first;
	if (first -> value < second -> value) first -> next = merge(first -> next, second);
	else second -> next = merge(second -> next, first);
	return first -> value < second -> value ? first : second;
}
/*
The first if statement will return second if first = NULL and first if second = NULL
The second if statement compares if the first value is larger than the second.
If it is, it will set the pointer to next, as a recursion call to merge of the next pointer
and the second pointer. The function will return the node with a larger value.
EXAMPLE:

Linked List first(values) = 1 -> 4 -> 5
Linked List second(values) = 0 -> 2 -> 3
merge(1,0) comopares and sees that the value of first is larger than the second.
Since it is not, it will then set 0 -> next as the return of merge(2,1).

Merge(2,1) will compare 2 and 1 to see which is larger. It will then set 
1 -> next as the return of merge(4,2). 

Merge(4,2) will compare 4 and 2 to see which is larger. It will then set 
2 -> next as the return of merge(3,4).

Merge(3,4) will compare 3 and 4 to see which is larger. It will then set 
3 -> next as the return of merge(NULL,4).

At this point first = NULL so merge(NULL,4) will return 4 ( which has a next pointer to 5 )
So it will go back to merge(3,4) where 3 -> next = 4 and return 3.

This will go back to merge(4,2) where 2 -> next = 3 and return 2.

This will go back to merge(2,1) where 1 -> next = 2 and return 1.

This will go back to the initial call, merge (1,0) where 0 -> next = 1.
At this point the linked list looks like 0 -> 1 -> 2 -> 3 -> 4 -> 5.
*/