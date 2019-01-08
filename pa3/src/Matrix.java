// Matrix.java - Contains matrix format of Entry objects and various operations
// Chris Griffis <chdgriff>
// pa3 05/11/18
import java.lang.StringBuffer;

@SuppressWarnings("overrides")
public class Matrix {
  
  // private
  
  private class Entry {
    private int column;
    private double value;
    
    // Constructor
    Entry(int column, double value) {
      this.column = column;
      this.value = value;
    }
    
    public boolean equals(Object x) {
      Entry E = (Entry) x;
      if (column != E.column) return false;
      if (value != E.value) return false;
      
      return true;
    }
    
    public String toString() {
      return "(" + Integer.toString(column) + ", " + Double.toString(value) + ")";
    }
  }
  
  
  private List[] matrix;
  private int nnz;
  
  private static double dot(List P, List Q) {
    double j1, j2, sum;
    sum = 0;
    P.moveFront();
    Q.moveFront();
    while (P.index() != -1 && Q.index() != -1) { // Loops through columns of each matrix concurrently
      j1 = ((Entry) P.get()).column; // column0
      j2 = ((Entry) Q.get()).column; // column1
      
      if (j1 < j2) {
        P.moveNext();
      }
      else if (j2 < j1) {
        Q.moveNext();
      }
      else { // if needed to be mult
        sum += ((Entry) P.get()).value * ((Entry) Q.get()).value;
        P.moveNext();
        Q.moveNext();
      }
    }
      return sum;
  }
  
  // returns a new Matrix of this.matrix and M.matrix combined where M.matrix * x
  // x is either +1 or -1
  private Matrix combine(Matrix M, int x) {
    Matrix N; 
    int j1, j2;
    double combinedVal;
    
    if (matrix == M.matrix) {
      if (x > 0) return scalarMult(2);
      else return new Matrix(getSize());
    }
    
    N = new Matrix(getSize());
    for (int i = 0; i < N.getSize(); i++) { // Loops through each row
      matrix[i].moveFront();
      M.matrix[i].moveFront();
      while (matrix[i].index() != -1 || M.matrix[i].index() != -1) { // Loops through columns of each matrix concurrently
        if (matrix[i].index() == -1) { // if matrix0 is empty
          while (M.matrix[i].index() != -1) { // Loop through rest of matrix1
            N.matrix[i].append(new Entry(((Entry) M.matrix[i].get()).column, x*((Entry) M.matrix[i].get()).value));
            N.nnz++;
            M.matrix[i].moveNext();
          }
        }
        else if (M.matrix[i].index() == -1) { // if matrix1 is empty
          while (matrix[i].index() != -1) { // Loop through rest of matrix0
            N.matrix[i].append(new Entry(((Entry) matrix[i].get()).column, ((Entry) matrix[i].get()).value));
            N.nnz++;
            matrix[i].moveNext();
          }
        }
        else {
          j1 = ((Entry) matrix[i].get()).column; // column0
          j2 = ((Entry) M.matrix[i].get()).column; // column1
          
          if (j1 < j2) { // if data
            N.matrix[i].append(new Entry(j1, ((Entry) matrix[i].get()).value));
            N.nnz++;
            matrix[i].moveNext();
          }
          else if (j2 < j1) {
            N.matrix[i].append(new Entry(j2, x*((Entry) M.matrix[i].get()).value));
            N.nnz++;
            M.matrix[i].moveNext();
          }
          else { // if needed to be combined
            combinedVal = ((Entry) matrix[i].get()).value + x*((Entry) M.matrix[i].get()).value;
            if (combinedVal != 0) { // if zero
              N.matrix[i].append(new Entry(j1, combinedVal));
              N.nnz++;
            }
            matrix[i].moveNext();
            M.matrix[i].moveNext();
          }
        }
      }
    }
    return N;
  }
  
  
  //Constructor
  //Makes a new n x n zero Matrix. pre: n>=1
  Matrix(int n) {
    if (!(n >= 1))
      throw new RuntimeException("Matrix Error: matrix must be created with n >= 1");
    
    matrix = new List[n];
    
    for (int i = 0; i < n; i++) matrix[i] = new List();
    nnz = 0;
  }
  
  //Access functions
  //Returns n, the number of rows and columns of this Matrix
  int getSize() {
    return matrix.length;
  }
  
  //Returns the number of non-zero entries in this Matrix
  int getNNZ() {
    return nnz;
  }
 
  //overrides Object's equals() method
  public boolean equals(Object x) {
    Matrix M = (Matrix) x;
    if (getSize() != M.getSize()) return false;
    if (nnz != M.nnz) return false;
    
    for (int i = 0; i < getSize(); i++) {
      if (!(matrix[i].equals(M.matrix[i]))) return false;
    }
    return true;
  }
  
  //Manipulation procedures
  //sets this Matrix to the zero state
  void makeZero() {
    for (int i = 0; i < getSize(); i++) {
      matrix[i].clear();
    }
    nnz = 0;
  }
  
  // returns a new Matrix having the same entries as this Matrix
  Matrix copy() {
    Matrix M = new Matrix(getSize());
    for (int i = 0; i < getSize(); i++) {
      matrix[i].moveFront();
      while (matrix[i].index() != -1) {
        M.matrix[i].append(matrix[i].get());
        matrix[i].moveNext();
      }
    }
    M.nnz = nnz;
    return M;
  }
  
  //changes ith row, jth column of this Matrix to x
  // pre: 1<=i<=getSize(), 1<=j<=getSize()
  void changeEntry(int i, int j, double x) {
    Entry E = new Entry(j, x);
    i--;
    if (matrix[i].length() == 0) {
      if (x != 0) {
       matrix[i].prepend(E);
       nnz++;
      }
    }
    else {
      matrix[i].moveFront(); 
      
      while (matrix[i].index() != -1) {
        if (j == ((Entry) matrix[i].get()).column) {
          if (x == 0) nnz--;
          else matrix[i].insertBefore(E);
          
          matrix[i].delete();
          return;
        }
        else if (j < ((Entry) matrix[i].get()).column) {
           if (x != 0) {
             matrix[i].insertBefore(E);
             nnz++;
           }
           return;
        }
        else matrix[i].moveNext();
      }

      if (x != 0) {
        matrix[i].append(E);
        nnz++;
      }
    }
      
    
    
  }
     
  //returns a new Matrix that is the scalar product of this Matrix with x 
  Matrix scalarMult(double x) {
    Matrix M = new Matrix(getSize());
    for (int i = 0; i < getSize(); i++) {
      matrix[i].moveFront();
      while (matrix[i].index() != -1) {
        M.matrix[i].append(new Entry(((Entry) matrix[i].get()).column, ((Entry) matrix[i].get()).value*x));
        M.nnz++;
        matrix[i].moveNext();
      }
    }
    return M;
  }
  
 
  //returns a new Matrix that is the sum of this Matrix with M
  // pre: getSize()==M.getSize()
  Matrix add(Matrix M) {
    if (getSize() != M.getSize())
      throw new RuntimeException("Matrix Error: the sizes of both matrices don't match in add()\n");
    return combine(M, 1);
  }
     
  //returns a new Matrix that is the difference of this Matrix with M
  // pre: getSize()==M.getSize()
  Matrix sub(Matrix M) {
    if (getSize() != M.getSize())
      throw new RuntimeException("Matrix Error: the sizes of both matrices don't match in sub()\n");
    return combine(M, -1);
  }
  
  
  //returns a new Matrix that is the transpose of this Matrix
  Matrix transpose() {
    Matrix N = new Matrix(getSize());
    for (int i = 0; i < getSize(); i++) {
      matrix[i].moveFront();
      while (matrix[i].index() != -1) {
        N.changeEntry(((Entry) matrix[i].get()).column, i+1, ((Entry) matrix[i].get()).value);
        matrix[i].moveNext();
      }
    }
    return N;
  }
  
  // returns a new Matrix that is the product of this Matrix with M
  // pre: getSize()==M.getSize()
  Matrix mult(Matrix M) {
    if (getSize() != M.getSize())
      throw new RuntimeException("Matrix Error: the sizes of both matrices don't match in mult()\n");
    
    Matrix N;
    double multVal;
    
    N = new Matrix(getSize());
    M = M.transpose();
    for (int i = 0; i < getSize(); i++) {
      for (int j = 0; j < M.getSize(); j++) {
        multVal = dot(matrix[i], M.matrix[j]);
        if (multVal != 0) {
          N.matrix[i].append(new Entry(j+1, multVal));
          N.nnz++;
        }
      }
    }
    return N;
  }
  
  //Other functions
  //overrides Object's toString() method
  public String toString() {
    StringBuffer sb = new StringBuffer();
    for (int i = 0; i < getSize(); i++) {
      if (matrix[i].length() != 0) {
        sb.append("\n" + (i+1) + ": " + matrix[i]);
      }
    }
    
    return sb.toString();
  }
}
