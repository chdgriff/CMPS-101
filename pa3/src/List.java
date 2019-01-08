// List.java - Doubly linked list ADT
// Chris Griffis <chdgriff>
// pa3 05/11/18
import java.lang.StringBuffer;

@SuppressWarnings("overrides")
public class List {
  // Node object
  private class Node {
    // Fields
    private Object data;
    private Node next;
    private Node previous;

    // Constructor
    private Node(Object data) {
      this.data =  data;
      this.next = null;
      this.previous = null;
    }

    // toString() overrides Object's toString()
    public String toString() {
      return data.toString();
    }
  }

  // Fields
  private Node front;
  private Node back;
  private Node cursor;

  private int length;
  private int cursorIndex;

  // Constructor
  public List() {
    front = null;
    back = null;
    cursor = null;
    length = 0;
    cursorIndex = -1;
  }

  // Access Functions

  // Returns number of elements in List
  public int length() {
    return length;
  }

  // Returns index of cursor element if defined
  // Else returns -1
  public int index() {
    return cursorIndex;
  }

  // Returns front element
  // Pre: length() > 0
  public Object front() {
    if (length() == 0)
      throw new RuntimeException("List.java error: Can't call front() on empty list");

    return front.data;
  }

  // Returns back element
  // Pre: length() > 0
  public Object back() {
    if (length() == 0)
      throw new RuntimeException("List.java error: Can't call back() on empty list");

    return back.data;
  }

  // Returns cursor element
  // Pre: length() > 0, index() >= 0
  public Object get() {
    if (length() == 0)
      throw new RuntimeException("List.java error: Can't call get() on empty list");

    if (index() == -1)
      throw new RuntimeException("List.java error: Can't call get() when cursor isn't defined");

    return cursor.data;
  }

  // Returns true if this.List and L are the same
  // Cursor location doesn't matter
  public boolean equals(Object x) {
    List L;
    Node n1, n2;
    
    L = (List) x;
    if (length() != L.length()) return false;
    
    n1 = front;
    n2 = L.front;
    while (n1 != null && n2 != null) {
      if (!n1.data.equals(n2.data)) return false;
      n1 = n1.next;
      n2 = n2.next;
    }
    return true;
  }

  // Manipulation procedures

  // Resets this.List to empty state
  public void clear() {
    front = null;
    back = null;
    cursor = null;
    length = 0;
    cursorIndex = -1;
  }

  // Places cursor under front element
  public void moveFront() {
    if (length > 0) {
      cursor = front;
      cursorIndex = 0;
    }
  }

  // Places cursor under back element
  public void moveBack() {
    if (length > 0) {
      cursor = back;
      cursorIndex = length()-1;
    }
  }

  // Moves cursor one step toward front
  // If cursor is at front cursor becomes undefined
  // If cursor is undefined nothing happens
  public void movePrev() {
    if (cursor != null) cursor = cursor.previous;
    cursorIndex--;
  }

  // Moves cursor one step toward back
  // If cursor is at back cursor becomes undefined
  // If cursor is undefined nothing happens
  public void moveNext() {
    if (cursor != null) {
      cursor = cursor.next;
      cursorIndex++;

      if (cursor == null) cursorIndex = -1;
    }
  }

  // Inserts new element into front of this.List
  public void prepend(Object data) {
    Node N;
    
    N = new Node(data);

    if (length() == 0) {
      front = N;
      back = front;
    }
    else {
      front.previous = N;
      N.next = front;
      front = N;
    }
    if (index() > -1) cursorIndex++;
    length++;
  }

  // Inserts new element into back of this.List
  public void append(Object data) {
    Node N;
    
    N = new Node(data);
    if (length() == 0) {
      back = N;
      front = back;
    }
    else {
      back.next = N;
      N.previous = back;
      back = N;
    }
    length++;
  }

  // Inserts new element before cursor
  // Pre: length() > 0, index() >= 0;
  public void insertBefore(Object data) {
    if (length() == 0) {
      throw new RuntimeException("List.java error: can't call insertBefore() on empty List");
    }
    if (index() == -1) {
      throw new RuntimeException("List.java error: Can't call insertBefore() when cursor isn't defined");
    }

    if (cursor == front) { // if cursor is at front
      prepend(data);
    }
    else {
      Node N;
      
      N = new Node(data);
      N.next = cursor;
      N.previous = cursor.previous;
      cursor.previous.next = N;
      cursor.previous = N;
      length++;
      cursorIndex++;
    }
  }

  // Inserts new element after cursor
  // Pre: length() > 0, index() >= 0;
  public void insertAfter(Object data) {
    if (length() == 0) {
      throw new RuntimeException("List.java error: can't call insertAfter() on empty List");
    }
    if (index() == -1) {
      throw new RuntimeException("List.java error: Can't call insertAfter() when cursor isn't defined");
    }

    if (cursor == back) {
      append(data);
    }
    else {
      Node N;
      N = new Node(data);
      N.next = cursor.next;
      N.previous = cursor;
      cursor.next.previous = N;
      cursor.next = N;
      length++;
    }
  }

  // Deletes front element
  // Pre: length() > 0
  public void deleteFront() {
    if (length() == 0) {
      throw new RuntimeException("List.java error: can't call deleteFront() on empty List");
    }
    if (length() == 1) {
      clear();
    }
    else {
      front = front.next;
      front.previous = null;
      length--;

      if (index() >= 0) {
        cursorIndex--;
        if (index() == -1) cursor = null;
      }
    }
  }

  // Deletes back element
  // Pre: length() > 0
  public void deleteBack() {
    if (length() == 0) {
      throw new RuntimeException("List.java error: can't call deleteBack() on empty List");
    }

    if (back == front) {
      clear();
    }
    else {
      back = back.previous;
      back.next = null;
      length--;

      if (index() == length()) {
        cursor = null;
        cursorIndex = -1;
      }
    }
  }

  // Deletes cursor element, making cursor undefined
  // Pre: length() > 0, index() >= 0
  public void delete() {
    if (length() == 0) {
      throw new RuntimeException("List.java error: can't call delete() on empty List");
    }
    if (index() == -1) {
      throw new RuntimeException("List.java error: can't call delete() when cursor is undefined");
    }

    if (cursor == front) { // If cursor is front
      deleteFront();
    }
    else if (cursor == back) { // If cursor is back
      deleteBack();
    }
    else { // If cursor is in between two nodes
      cursor.previous.next = cursor.next;
      cursor.next.previous = cursor.previous;
      cursorIndex = -1;
      cursor = null;
      length--;
    }
  }

  // Other methods

  public String toString() {
    StringBuffer sb;
    Node N;
    
    sb = new StringBuffer();
    N = front;
    for (int i = 0; i < length(); i++) {
      if (i != 0) sb.append(" ");
      sb.append(N);
      N = N.next;
    }
    return sb.toString();
  }

}