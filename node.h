typedef struct _Node {
   int time;
   int minimum;
   int status;
   int x;
   int y;
   struct _Node *prev;
   struct _Node *up;
   struct _Node *down;
   struct _Node *left;
   struct _Node *right;
} Node;

