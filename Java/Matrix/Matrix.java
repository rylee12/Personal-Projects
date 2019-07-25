/*
 * Ryan Lee
 * Title: Matrix.java
 * Description:
 */

 class Matrix{
        private class Entry{
          int num;
          double data;

          Entry(int num, double data){
                this.num = num;
                this.data = data;
          }

          public String toString(){
                return "(" + String.valueOf(num) + ", " + String.valueOf(data) + ") ";
          }

          public boolean equals(Object x){
                boolean eq = false;
                Entry that;
                if (x instanceof Entry){
                  that = (Entry) x;
                  if (this.num == that.num && this.data == that.data){
                        eq = true;
                  }
                }
                return eq;
          }
        }

        //Fields
        private int n;
        private List[] array;

        // Constructor
        // Matrix()
        // Makes a new n x n zero Matrix
        // Pre: n >= 1
        Matrix(int n){
          if (n < 1){
                throw new RuntimeException("Invalid size for the matrix");
          }
          this.n = n;
          array = new List[n+1];
          for (int x = 1; x <= n; x++){
                array[x] = new List();
          }
        }

        // Access functions

        // getSize()
        // Returns n, the number of rows and columns of this Matrix
        int getSize(){
          return n;
        }

        // getNNZ()
        // Returns the number of non-zero entries in this Matrix
        int getNNZ(){
          int count = 0;
          List L;
          for (int i = 1; i <= n; i++){
                L = array[i];
                count += L.length();
          }
          return count;
        }

        // equals()
        // determines if the object x is equal to the matrix
        // Note: overrides Object's equals() method
        public boolean equals(Object x){
          Matrix that;
          if (x instanceof Matrix){
                that = (Matrix) x;
                List L, H;
                Entry E, T;
                if (this.getSize() != that.getSize()){
                  return false;
                }

                for (int i = 1; i <= n; i++){
                  L = this.array[i];
                  H = that.array[i];
                  if (L.length() != H.length()){
                        return false;
                  }
                  L.moveFront();
                  H.moveFront();
                  while (L.index() != -1){
                        E = (Entry) L.get();
                        T = (Entry) H.get();
                        //System.out.println(i + ": " + E.data + " = " + T.data + " ; " + E.num + " = " + T.num);
                        if (!(E.equals(T))){
                          return false;
                        }
                        L.moveNext();
                        H.moveNext();
                  }
                }
          }
          return true;
        }

        // Manipulation procedures

        // makeZero()
        // sets this Matrix to the zero state
        void makeZero(){
          for (int i = 1; i <= n; i++){
                array[i].clear();
          }
        }

        // copy()
        // returns a new Matrix having the same entries as this Matrix
        Matrix copy(){
          Matrix M = this;
          Matrix copy = new Matrix(M.getSize());
          List L;
          Entry E;
          for (int i = 1; i <= M.getSize(); i++){
                L = this.array[i];
                L.moveFront();
                while (L.index() != -1){
                  E = (Entry) L.get();
                  copy.changeEntry(i, E.num, E.data);
                  L.moveNext();
                }
          }
          return copy;
        }

        // 4 base cases:
        // 0 -> 0 do nothing
        // 0 -> # insert
        // # -> 0 delete
        // # -> # change
        // Note: A tricky case is where when x != 0, but new entry must come before the entry
        // changeEntry()
        // changes ith row, jth column of this Matrix to x
        // Pre: 1 <= i <= getSize(), 1 <= j <= getSize()
        void changeEntry(int i, int j, double x){
          if (i <= 0 || i >= getSize() + 1){
                throw new RuntimeException("Index out of bounds");
          }
          if (j <= 0 || j >= getSize() + 1){
                throw new RuntimeException("Index out of bounds");
          }
          List L = array[i];
          L.moveFront();
          Entry E;
          Entry T = new Entry(j, x);
          int k = 1;
          if (L.length() == 0 && x != 0)  //Used only when it's empty
                L.append(T);
          else{
                if (x != 0){
                  while (L.index() != -1){
                        E = (Entry) L.get();
                        if (E.num < j){
                          L.moveNext();
                        }
                        else if (E.num == j){
                          L.insertAfter(T);
                          L.delete();
                          return;
                        }
                        else{
                          L.insertBefore(T);
                          return;
                        }
                  }
                  if (L.index() == -1){
                        L.append(T);
                        return;
                  }
                }
                else{
                  while (L.index() != -1){
                        E = (Entry) L.get();
                        if (E.num < j){
                          L.moveNext();
                        }
                        else if (E.num == j){
                          if (L.length() == 1){
                                L.clear();
                                return;
                          }
                          L.delete();
                          return;
                        }
                        else{
                          return;
                        }
                  }
                }
          }
        }

        // scalarMult()
        // returns a new Matrix that is the scalar product of this Matrix with x
        Matrix scalarMult(double x){
          List L;
          Entry E;
          Matrix result = new Matrix(n);
          for (int i = 1; i <= n; i++){
                L = this.array[i];
                L.moveFront();
                while (L.index() != -1){
                  E = (Entry) L.get();
                  result.changeEntry(i, E.num, E.data * x);
                  L.moveNext();
                }
          }
          return result;
        }

        // add()
        // returns a new Matrix that is the sum of this Matrix with M
        // Pre: getSize() == M.getSize()
        Matrix add(Matrix M){
          if (n != M.getSize()){
                throw new RuntimeException("Dimensions don't match");
          }
          Matrix result = new Matrix(n);
          List L, R;
          List S = new List();
          Entry A;
          for (int i = 1; i <= n; i++){
                L = this.array[i];
                R = M.array[i];
                listAdd(L, R, S);
                S.moveFront();
                //System.out.println(i);
                while (S.index() != -1){
                  A = (Entry) S.get();
                  //System.out.println(A.num);
                  //System.out.println(A.data);
                  result.changeEntry(i, A.num, A.data);
                  S.moveNext();
                }
                S.clear();
          }
          return result;
        }

        // sub()
        // returns a new Matrix that is the difference of this Matrix with M
        // Pre: getSize() == M.getSize()
        Matrix sub(Matrix M){
          if (n != M.getSize()){
                throw new RuntimeException("Dimensions don't match");
          }
          Matrix result = new Matrix(n);
          List L, R;
          List S = new List();
          Entry A;
          for (int i = 1; i <= n; i++){
                L = this.array[i];
                R = M.array[i];
                listSub(L, R, S);
                S.moveFront();
                while (S.index() != -1){
                  A = (Entry) S.get();
                  result.changeEntry(i, A.num, A.data);
                  S.moveNext();
                }
                S.clear();
          }
          return result;
        }

        // transpose()
        // returns a new Matrix that is the transpose of this Matrix
        Matrix transpose(){
          Matrix result = new Matrix(n);
          List L;
          Entry E;
          for (int i = 1; i <= n; i++){
                L = this.array[i];
                L.moveFront();
                while (L.index() != -1){
                  E = (Entry) L.get();
                  result.changeEntry(E.num, i, E.data);
                  L.moveNext();
                }
          }
          return result;
        }

        // mult()
        // returns a new Matrix that is the product of this Matrix with M
        // Pre: getSize() == M.getSize()
        Matrix mult(Matrix M){
          if (n != M.getSize()){
                throw new RuntimeException("Dimensions don't match");
          }
          Matrix result = new Matrix(n);
          Matrix T = M.transpose();
          List L, R;
          double sum;
          for (int i = 1; i <= n; i++){
                L = this.array[i];
                //L.moveFront();
                //R.moveFront();
                for (int j = 1; j <= n; j++){
                  R = T.array[j];
                  sum = dot(L, R);
                  if (sum != 0)
                        result.changeEntry(i, j, sum);
                }
          }
          return result;
        }

        // Other functions
        // Why all my code so messy??

        // toString()
        // overrides Object's toString() method
        public String toString(){
          StringBuffer sb = new StringBuffer();
          List L;
          Entry E;
          for (int i = 1; i <= n; i++){
                L = array[i];
                L.moveFront();
                if (L.length() > 0){
                  sb.append(i + ": ");
                }
                while (L.index() != -1){
                  E = (Entry) L.get();
                  sb.append(E.toString());
                  sb.append(" ");
                  L.moveNext();
                }
                if (L.length() > 0){
                  //sb.prepend(i + ": ");
                  sb.append("\n");
                }
          }
          return new String(sb);
        }

        // dot()
        // Helper function for mult(); use with transpose()
        private static double dot(List L, List R){
          double sum = 0.0;
          Entry A, B;
          L.moveFront();
          R.moveFront();
          while (L.index() != -1 && R.index() != -1){
                A = (Entry) L.get();
                B = (Entry) R.get();
                if (A.num == B.num){
                  sum += (A.data * B.data);
                  L.moveNext();
                  R.moveNext();
                }
                else if (A.num > B.num){
                  R.moveNext();
                }
                else{
                  L.moveNext();
                }
          }
          return sum;
        }

        // listAdd
        // helper function for add()
        private void listAdd(List L, List R, List S){
          Entry A, B, C;
          L.moveFront();
          R.moveFront();
          boolean eq = L.equals(R);
          while (L.index() != -1 && R.index() != -1){
                A = (Entry) L.get();
                B = (Entry) R.get();
                if (A.num == B.num){
                  C = new Entry(A.num, A.data + B.data);
                  //double p = A.data + B.data;
                  //System.out.println("A.data = " + A.data);
                  //System.out.println("B.data = " + B.data);
                  //System.out.println(A.num + ", " + p);
                  S.append(C);
                  L.moveNext();
                  if (!eq)      //If both lists are the same
                        R.moveNext();
                }
                else if (A.num > B.num){
                  S.append(B);
                  R.moveNext();
                }
                else{
                  S.append(A);
                  L.moveNext();
                }
          }
          if (L.index() != -1){
                while (L.index() != -1){
                  A = (Entry) L.get();
                  S.append(A);
                  L.moveNext();
                }
          }
          else{
                while (R.index() != -1){
                  B = (Entry) R.get();
                  S.append(B);
                  R.moveNext();
                }
          }
        }

        // listSub
        // helper function for sub()
        private void listSub(List L, List R, List S){
          Entry A, B, C;
          L.moveFront();
          R.moveFront();
          //boolean eq = L.equals(R);
          while (L.index() != -1 && R.index() != -1){
                A = (Entry) L.get();
                B = (Entry) R.get();
                if (A.num == B.num){
                  //System.out.println((A.data - B.data));
                  C = new Entry(A.num, A.data - B.data);
                  S.append(C);
                  L.moveNext();
                  R.moveNext();
                }
                else if (A.num > B.num){
                  C = new Entry(B.num, -1 * B.data);
                  S.append(C);
                  R.moveNext();
                }
                else{
                  C = new Entry(A.num, A.data);
                  S.append(C);
                  L.moveNext();
                }
          }
          if (L.index() != -1){
                while (L.index() != -1){
                  A = (Entry) L.get();
                  C = new Entry(A.num, A.data);
                  S.append(C);
                  L.moveNext();
                }
          }
          else{
                while (R.index() != -1){
                  B = (Entry) R.get();
                  C = new Entry(B.num, -1 * B.data);
                  S.append(C);
                  R.moveNext();
                }
          }
        }
}
