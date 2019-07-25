// Ryan K Lee
// Title: ListClient.java
// Description: Client/test file for the List ADT

public class ListClient{
   public static void main(String[] args){
      List A = new List();
      List B = new List();
      List C = new List();
      
      for (int i=1; i<=20; i++){
         A.append(i);
         B.prepend(i);
      }

      for (int i = 0; i <= 30; i = i + 3){
      	 C.append(i);
      }
      
      System.out.println(A);
      System.out.println(B);
      System.out.println(C);
      
      for (A.moveFront(); A.index() >= 0; A.moveNext()){
         System.out.print(A.get() + " ");
      }
      System.out.println();
      
      for (B.moveBack(); B.index() >= 0; B.movePrev()){
         System.out.print(B.get() + " ");
      }
      System.out.println();
      
      List D = A.copy();
      System.out.println(A.equals(B));
      System.out.println(B.equals(D));
      System.out.println(D.equals(A));
      
      A.moveFront();
      for (int i = 0; i < 5; i++) A.moveNext(); // at index 5
      A.insertBefore(-1);                  		// at index 6
      for (int i = 0; i < 9; i++) A.moveNext(); // at index 15
      A.insertAfter(-2);
      for (int i = 0; i < 5; i++) A.movePrev(); // at index 10
      A.delete();
      System.out.println(A);
      System.out.println(A.length());
      A.clear();
      System.out.println(A.length());

      C.insertOrder(0);
      C.insertOrder(100);
      C.insertOrder(14);
      System.out.println(C);
      System.out.println(C.length());
   }
}

// Output of this program:
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
// 0 3 6 9 12 15 18 21 24 27 30 
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// false
// false
// true
// 1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
// 21
// 0
