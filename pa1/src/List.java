// List.java - Doubly linked list ADT
// Chris Griffis <chdgriff>
// pa1
import java.lang.StringBuffer;

public class List {
  // Node object
  private class Node {
    // Fields
    private int data;
    private Node next;
    private Node previous;
		
 		 // Constructor
  		private Node(int data) {
  		  this.data =  data;
  			 this.next = null;
  			 this.previous = null;
  		}
  		
  		// toString() overrides Object's toString()
    public String toString() {
  		  return Integer.toString(data);
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
  public int front() {
    if (length() == 0) {
      throw new RuntimeException("List.java error: Can't call front() on empty list");
    }
    return front.data;
  }
  
  // Returns back element
  // Pre: length() > 0
  public int back() {
    if (length() == 0) {
      throw new RuntimeException("List.java error: Can't call back() on empty list");
    }
    return back.data;
  }
  
  // Returns cursor element
  // Pre: length() > 0, index() >= 0
  public int get() {
    if (length() == 0) {
      throw new RuntimeException("List.java error: Can't call get() on empty list");
    }
    if (index() == -1) {
      throw new RuntimeException("List.java error: Can't call get() when cursor isn't defined");
    }
    return cursor.data;
  }
  
  // Returns true if this.List and L are the same
  // Cursor location doesn't matter
  public boolean equals(List L) {
    if (length() != L.length()) return false;
    Node n1 = front;
    Node n2 = L.front;
    while (n1 != null && n2 != null) {
      if (n1.data != n2.data) return false;
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
    cursor = front;
    cursorIndex = 0;
  }
  
  // Places cursor under back element
  public void moveBack() {
    cursor = back;
    cursorIndex = length()-1;
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
    if (cursor != null) cursor = cursor.next;
    cursorIndex++;
    
    if (index() == length()) {
      cursorIndex = -1;
    }
  }
  
  // Inserts new element into front of this.List
  public void prepend(int data) {
    Node n = new Node(data);
    
    if (length() == 0) {
      front = n;
      back = front;
    }
    else {
      front.previous = n;
      n.next = front;
      front = n;
    }
    if (index() > -1) cursorIndex++;
    length++;
  }
  
  // Inserts new element into back of this.List
  public void append(int data) {
    Node n = new Node(data);
    
    if (length() == 0) {
      back = n;
      front = back;
    }
    else {
      back.next = n;
      n.previous = back;
      back = n;
    }
    length++;
  }
  
  // Inserts new element before cursor
  // Pre: length() > 0, index() >= 0;
  public void insertBefore(int data) {
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
      Node n = new Node(data);
      n.next = cursor;
      n.previous = cursor.previous;
      cursor.previous.next = n;
      cursor.previous = n;
      length++;
      cursorIndex++;
    }
  }
  
  // Inserts new element after cursor
  // Pre: length() > 0, index() >= 0;
  public void insertAfter(int data) {
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
      Node n = new Node(data);
      n.next = cursor.next;
      n.previous = cursor;
      cursor.next.previous = n;
      cursor.next = n;
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
    StringBuffer s = new StringBuffer();
    Node n = front;
    for (int i = 0; i < length(); i++) {
      if (i != 0) s.append(" ");
      s.append(n);
      n = n.next;
    }
    return s.toString();
  }
  
  // Returns new list with same integer sequence
  public List copy() {
    List l = new List();
    Node n = front;
    for (int i = 0; i < length(); i++) {
      l.append(n.data);
      n = n.next;
    }
    
    return l;
  }

  // Returns concats this List to L
  // Cursor is undefined
  public List concat(List L) {
    List n = new List();
    
    moveFront();
    while (cursor != null) {
      n.append(get());
      moveNext();
    }
    
    L.moveFront();
    while (L.cursor != null) {
      n.append(L.get());
      L.moveNext();
    }
    
    return n;
  }
}
