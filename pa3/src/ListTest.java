// ListTest.java - Test List ADT
// Chris Griffis <chdgriff>
// pa3

public class ListTest {
  public static void main(String[] args) {
    List L;
    
    
    L =  new List();
    
    
    L.append(0);
    L.prepend(1);
    
    L.moveFront();
    
    L.insertAfter(2);
    L.moveNext();
    L.insertBefore(3);
    
    L.moveBack();
    L.movePrev();
    L.delete();
    
    L.deleteFront();
    L.deleteBack();
    
    System.out.println("L:");
    System.out.println(L);
    
    System.out.println("\nLength = " + L.length());
    System.out.println("\nIndex = " + L.index());
    System.out.println("Front = " + L.front());
    System.out.println("Back = " + L.back());
    
    
    
  }
}
