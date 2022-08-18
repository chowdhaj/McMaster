#include <stdio.h>   // printf, scanf ..
#include <stdlib.h>  // malloc

struct node {
  int val;
  struct node *next; // pointer
};

// Time: O(n), Space: O(n)
struct node* reverseLinkedList(struct node *head) {
  struct node *h = head;
  int len = 0;
  while (h != NULL) {
    len++;
    h = h->next;
  }

  h = head;
  int arr[len];    // variable length array, since C99
  while (h != NULL) {
    arr[len - 1] = h->val;
    h = h->next;
    len--;
  }

  h = head;
  int idx = 0;
  while (h != NULL) {
    h->val = arr[idx];
    idx++;
    h = h->next;
  }

  return head;
}

// Time: O(n), Space: O(1)
struct node *reverseLinkedList_inPlace(struct node *head) {
  struct node *back = NULL;
  while (head != NULL) {
    struct node *cur = head->next;
    head->next = back;
    back = head;
    head = cur;
  }
  return back;
}

void printLinkedList(struct node *head) {
  printf("Printing Linked list: \n");
  while (head != NULL) {
    printf("%d ", head->val);
    head = head->next;
  }
  printf("\n");
}

void destroyLinkedList(struct node *head) {
  while (head) {
    struct node *n = head->next;
    free(head);    // deallocate memory
    head = n;
  }
}

int main() {
  struct node *prev = NULL;
  struct node *head = NULL;
  struct node *p = NULL;

  int n = 0, i = 0;
  printf("Number of elements: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    p = malloc(sizeof(struct node));   // alloc memory
    if (p == NULL) {
      fprintf(stderr, "malloc failed !\n");
      exit(-1);
    }
    scanf("%d", &(p->val));
    p->next = NULL;
    if (head == NULL) {
      head = p;
    } else {
      prev->next = p;
    }
    prev = p;
  }

  printLinkedList(head);
  destroyLinkedList(head);
  head = NULL;
  printLinkedList(head);   // Now the linked list is empty
  return 0;
}
