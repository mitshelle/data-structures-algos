#ifndef LINKED_L
#define LINKED_L
template <typename T>
class LL
{
  // contents of each node
  struct Node
  {
    T data;
    Node *prev;
    Node *next;
  };
  // Iterator class to allow access of each node in main
public:
  class Iterator // dis is class within a class so iterator is in the LL class
  {
  public:
    friend class LL;
    Iterator();
    Iterator(Node *);
    T operator*() const;
    const Iterator &operator++(int);
    const Iterator &operator--(int);
    bool operator==(const Iterator &) const;
    bool operator!=(const Iterator &) const;

  private:
    Node *current;
  };

  LL();
  LL(const LL<T> &);
  const LL<T> &operator=(const LL<T> &);
  ~LL();
  void headInsert(const T &);
  void tailInsert(const T &);
  Iterator begin() const;
  Iterator end() const;
  void swapNodes(Iterator &, Iterator &);
  void destroyList();
  bool isEmpty() const;

private:
  Node *head;
  Node *tail;
};

// default construct
template <typename T>
LL<T>::LL()
{
  // set to null
  head = nullptr;
  tail = nullptr;
}

// deep copy constructor
template <typename T>
LL<T>::LL(const LL<T> &copy)
{
  if (!copy.isEmpty())
  {
    // declared vars
    Node *originalL;
    Node *copyL;

    // allocate
    head = new Node;
    head->prev = nullptr;
    head->next = nullptr;

    // set original list to point to head of passed list
    originalL = copy.head;
    // copy list points to head
    copyL = head;
    // copy info set to original info
    copyL->data = originalL->data;
    copyL->prev = nullptr;
    // orignal points to nxt node
    originalL = originalL->next;
    head = copyL;

    // loop until next is null
    while (originalL != nullptr)
    {
      // allocate & set copy to nxt node & set prev
      copyL->next = new Node;
      copyL->next->prev = copyL;
      copyL = copyL->next;

      // set copy to original data
      copyL->data = originalL->data;
      // set original to nxt node
      originalL = originalL->next;
    }

    // set to null once end
    copyL->next = nullptr;
    tail = head;

    // loop until tail points to null
    while (tail->next != nullptr)
    {
      // set last to nxt node
      tail = tail->next;
    }
  }
}

template <typename T>
const LL<T> &LL<T>::operator=(const LL<T> &rhs)
{
  if (!rhs.isEmpty())
  {
    // declared vars
    Node *originalL;
    Node *copyL;

    // deallocate first
    destroyList();

    // allocate
    head = new Node;
    head->prev = nullptr;
    head->next = nullptr;

    // set original list to point to head of passed list
    originalL = rhs.head;
    // copy list points to head
    copyL = head;
    // copy info set to original info
    copyL->data = originalL->data;
    copyL->prev = nullptr;
    // orignal points to nxt node
    originalL = originalL->next;

    // loop until next is null
    while (originalL != nullptr)
    {
      // allocate & set copy to nxt node & set to prev
      copyL->next = new Node;
      copyL->next->prev = copyL;
      copyL = copyL->next;

      // set copy to original data
      copyL->data = originalL->data;
      // set original to nxt node
      originalL = originalL->next;
    }

    // set to null once end
    copyL->next = nullptr;
    tail = head;

    // loop until tail points to null
    while (tail->next != nullptr)
    {
      // set last to nxt node
      tail = tail->next;
    }

    // return obj
    return *this;
  }
}

// destructor
template <typename T>
LL<T>::~LL()
{
  destroyList();
}

// default constructor
template <typename T>
LL<T>::Iterator::Iterator()
{
  // set
  current = nullptr;
}

// constructor to set
template <typename T>
LL<T>::Iterator::Iterator(Node *ptr)
{
  // set current to passed val
  current = ptr;
}

// return data of node that current is at
template <typename T>
T LL<T>::Iterator::operator*() const
{
  return current->data;
}

// move current pointer to right & return
template <typename T>
const typename LL<T>::Iterator &LL<T>::Iterator::operator++(int)
{
  // move to next node on right
  current = current->next;
  // return curr obj
  return *this;
}

// move current pointer to left
template <typename T>
const typename LL<T>::Iterator &LL<T>::Iterator::operator--(int)
{
  // move to node before on left
  current = current->prev;
  // return curr obj
  return *this;
}

// check if current & object passed's curr at same node
template <typename T>
bool LL<T>::Iterator::operator==(const Iterator &rhs) const
{
  // check if point to same node
  if (current == rhs.current)
  {
    return true;
  }
  // if not
  return false;
}

// check if current & object passed's not at same node
template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator &rhs) const
{
  // check if DO NOT point to same node
  if (current != rhs.current)
  {
    return true;
  }
  // if not
  return false;
}

// insert new node at end of list
template <typename T>
void LL<T>::tailInsert(const T &item)
{
  // declared vars
  Node *toInsert;
  // allocate
  toInsert = new Node;

  // set
  toInsert->data = item;
  toInsert->next = nullptr;
  toInsert->prev = tail;

  // check if last
  if (tail == nullptr)
  {
    head = toInsert;
    tail = toInsert;
  }
  else
  {
    // set to temp
    tail->next = toInsert;
    tail = toInsert;
  }
}

// insert new node at beginning of list
template <typename T>
void LL<T>::headInsert(const T &item)
{
  // declared vars
  Node *toInsert;
  // allocate
  toInsert = new Node;

  // set
  toInsert->data = item;
  toInsert->next = head;
  toInsert->prev = nullptr;

  // check if head
  if (head == nullptr)
  {
    head = toInsert;
    tail = toInsert;
  }
  else
  {
    // set to temp
    head->prev = toInsert;
    head = toInsert;
  }
}

// return iterator OBJ current that points to head
template <typename T>
typename LL<T>::Iterator LL<T>::begin() const
{
  // declared vars
  LL<T>::Iterator temp;
  // set to head
  temp.current = this->head;
  // return whole object
  return temp;
}

// return iterator OBJ current that points to tail
template <typename T>
typename LL<T>::Iterator LL<T>::end() const
{
  // declared vars
  LL<T>::Iterator temp;
  // set to tail
  temp.current = this->tail;
  // return whole object
  return temp;
}

template <typename T>
void LL<T>::swapNodes(Iterator &it1, Iterator &it2)
{
  // declared vars
  Node *it1Left, *it2Right, *temp1, *temp2;

  // set
  temp1 = it1.current;    // points to addy of node that iterator obj points to
  temp2 = it2.current;    // points to addy of node that iterator obj points to
  it1Left = temp1->prev;  // points to node in front of it1
  it2Right = temp2->next; // points to node after of it2

  // check if head
  if (it1.current == head)
  {
    // temp1 prev point to temp2 & temp2 next to temp1
    temp2->next = temp1;
    temp1->prev = temp2;

    // set to null since head
    temp2->prev = nullptr;
    // node after it2
    temp1->next = it2Right;
    // temp1 now before what was on right of it2
    it2Right->prev = temp1;
    // set head pointer to temp2 now since in front
    head = temp2;
  }
  else if (it2.current == tail)
  { // tail case
    // temp1 prev point to temp2 & temp2 next to temp1
    temp2->next = temp1;
    temp1->prev = temp2;

    // set node before temp1 next to point to temp2 now
    it1Left->next = temp2;
    // set temp1 next null since it is tail
    temp1->next = nullptr;
    // set temp2 prev to point to node that was b4 temp1
    temp2->prev = it1Left;

    // set tail pointer to temp1 now since end
    tail = temp1;
  }
  else
  { // middle case
    // node b4 temp1 next now point to temp2 & temp2 prev point to node b4 temp1
    it1Left->next = temp2;
    temp2->prev = it1Left;

    // node after temp2 prev now point to temp1 & temp1 next point to node after
    // temp2
    it2Right->prev = temp1;
    temp1->next = it2Right;

    // temp1 prev point to temp2 & temp2 next to temp1
    temp2->next = temp1;
    temp1->prev = temp2;
  }

  it1.current = temp2;
  it2.current = temp1;
}

// MINE - deallocate linked list
template <typename T>
void LL<T>::destroyList()
{
  // declared vars
  Node *temp;

  // check if list is completely empty
  if (head == nullptr)
  {
    return;
  }

  // loop until head reaches tail,, end
  while (head != tail)
  {
    // get next node
    temp = head->next;
    // delete
    delete head;
    head = temp;
  }

  // delete
  delete head;

  // set
  head = nullptr;
  tail = nullptr;
}

// MINE - check if list is empty
template <class T>
bool LL<T>::isEmpty() const
{
  // if nothing in list
  if (head == nullptr)
  {
    return true;
  }

  return false;
}

#endif