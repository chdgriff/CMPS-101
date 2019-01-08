// MatrixTest.java - self test of Matrix.java
// Chris Griffis <chdgriff>
// pa3 05/11/18
public class MatrixTest {
  public static void main(String[] args) {
    Matrix A;
    Matrix B;
    
    A = new Matrix(3);
    
    A.changeEntry(1, 1, 1);
    A.changeEntry(1, 2, 2);
    A.changeEntry(1, 3, 3);
    
    A.changeEntry(2, 2, 2);
    A.changeEntry(2, 1, 1);
    A.changeEntry(2, 3, 3);
    
    A.changeEntry(3, 3, 3);
    A.changeEntry(3, 1, 1);
    A.changeEntry(3, 2, 2);
    
  //  B = A.copy();
    
    A.changeEntry(2, 2, 0);
    System.out.println("A has " + A.getNNZ() + " non-zero entries:");
    System.out.println(A);
    
    B = A.scalarMult(2);
    
    System.out.println("\nB has " + B.getNNZ() + " non-zero entries:");
    System.out.println(B);
    
    System.out.println("\nA+A =");
    System.out.println(A.add(A));
    
    System.out.println("\nA+B =");
    System.out.println(A.add(B));
    
    System.out.println("\nA-A =");
    //System.out.println(A.sub(A));
    
    System.out.println("\nA-B =");
    System.out.println(A.sub(B));
    
    System.out.println("\nTranspose(A) =");
    System.out.println(A.transpose());
    
    System.out.println("\nA*A");
    System.out.println(A.mult(A));
    
    System.out.println("\nA*B");
    System.out.println(A.mult(B));
    
    A = new Matrix(10);
    A.changeEntry(1, 1, 4);
    A.changeEntry(1, 2, 2);
    A.changeEntry(1, 3, 0);
    A.changeEntry(2, 1, 2);
    A.changeEntry(3, 1, 0);
    A.changeEntry(2, 2, 2);
    A.changeEntry(3, 3, 0);
    
    System.out.println("A has " + A.getNNZ() + " non-zero entries:");
    System.out.println(A);
    
    B = A.scalarMult(-20);
    System.out.println("\nB has " + B.getNNZ() + " non-zero entries:");
    System.out.println(B);
  }
}
