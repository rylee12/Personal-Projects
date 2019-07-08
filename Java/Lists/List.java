// Ryan K Lee
// Title: List.java
// Description: This file contains the class definition of a List ADT. It contains the
// necessary constructors and functions needed to create, manipulate, maintain, and delete
// a List ADT.

class List{
	private class Node{
		int data;
		Node next;
		Node prev;

		// Constructor
		Node(int data){
			this.data = data;
			next = null;
			prev = null;
		}

		public String toString() {
			return String.valueOf(data);
		}
	}

	// Fields
	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int index;

	// List()
	//
	// Preconditions: none
	List(){
		front = back = null;
		cursor = null;
		length = 0;
		index = -1;
	}

    //Access Functions

    // length()
    // Returns the number of elements in this list
    // Preconditions: none
    int length(){
        return length;
    }

    // index()
    // If cursor is defined, returns the index of the cursor element, otherwise returns -1
    // Preconditions: none
    int index(){
        if (cursor != null){
            return index;
        }
        else{
            index = -1;
            return -1;
        }
    }

    // front()
    // Returns front element
    // Preconditions: length() > 0
    int front(){
        if (this.length <= 0){
            throw new RuntimeException("Error: the list is empty");
        }
        return front.data;
    }

    // back()
    // Returns back element
    // Preconditions: length() > 0
    int back(){
        if (this.length <= 0){
            throw new RuntimeException("Error: the list is empty");
        }
        return back.data;
    }

    // get()
    // Returns cursor element
    // Preconditions: length() > 0 and index() >= 0
    int get(){
        if (this.length <= 0){
            throw new RuntimeException("Error: the list is empty");
        }
        if (this.index() < 0){
            throw new RuntimeException("Error: the cursor is undefined");
        }
        return cursor.data;
    }

    // equals()
    // Returns true if and only if this List and L are the same integer sequence
    // Preconditions: None
    boolean equals(List L){
    	Node N, M;
        N = this.front;
        M = L.front;
            if (this.length() != L.length()){
                return false;
            }
            else{
                while (N != null && M != null){
                    if (N.data != M.data)
                        return false;
                    N = N.next;
                    M = M.next;
                }
                return true;
            }
    }

    //Manipulation procedures

    // clear()
    // Resets this List to its original state i.e. deletes everything in the list
    // Preconditions: none
    void clear(){
        front = back = null;
        cursor = null;
        length = 0;
        index = -1;
    }

    // moveFront()
    // If List is non-empty, places cursor under the front element, otherwise does nothing
    // Preconditions: List is not empty i.e. length() > 0
    void moveFront(){
        if (this.length > 0){
            //System.out.println("Does this work?");
            cursor = front;
            index = 0;
        }
        else{
            return;
        }
    }

    // moveBack()
    // If List is non-empty, places cursor under the back element, otherwise does nothing
    // Preconditions: List is not empty i.e. length() > 0
    void moveBack(){
        if (this.length > 0){
            cursor = back;
            index = length - 1;
        }
        else{
            return;
        }
    }

    // movePrev()
    // If cursor is defined and not at front, moves cursor one step back. If cursor is defined and at front,
    // cursor becomes undefined. If cursor is undefined, does nothing.
    // Preconditions: cursor is defined i.e. cursor != null
    void movePrev(){
        if (cursor == null){
            return;
        }
        if (cursor == front){
            cursor = null;
            index = -1;
        }
        else{
            cursor = cursor.prev;
            index--;
        }
    }

    // moveNext()
    // If cursor is defined and not at back, moves cursor one step forward. If cursor is defined and at back,
    // cursor becomes undefined. If cursor is undefined does nothing.
    // Preconditions: cursor is defined i.e. cursor != null
    void moveNext(){
        if (cursor == null){
            return;
        }
        if (cursor == back){
            cursor = null;
            index = -1;
        }
        else{
            cursor = cursor.next;
            index++;
        }
    }

    // prepend()
    // Inserts new element before the front element
    // Preconditions: none
    void prepend(int data){
        Node N = new Node(data);
        if (this.length == 0)
                front = back = N;
        else{
            front.prev = N;
            N.next = front;
            front = N;
            if (this.index >= 0){
                if (cursor == back){
                    index = -1;
                }
                else{
                    index++;
                }
            }
        }
        length++;
    }

    // append()
    // Inserts new element after the back element
    // Preconditions: none
    void append(int data){
        Node N = new Node(data);
        if (this.length == 0)
            front = back = N;
        else{
            back.next = N;
            N.prev = back;
            back = N;
        }
        length++;
    }

    // insertBefore()
    // Inserts new element before cursor
    // Preconditions: length() > 0 and index() >= 0
    void insertBefore(int data){
        if (this.length <= 0)
            throw new RuntimeException("Error: empty list");
        if (this.index() < 0)
            throw new RuntimeException("Error: the cursor is undefined");
        Node N = new Node(data);
        if (cursor == front){
            N.next = front;
            front.prev = N;
            front = N;
        }
        else{
            N.next = cursor;
            N.prev = cursor.prev;
            (cursor.prev).next = N;
            cursor.prev = N;
        }
        length++;
        index++;
    }

    // insertAfter()
    // Inserts new element after cursor
    // Preconditions: length() > 0 and index() >= 0
    void insertAfter(int data){
        if (this.length <= 0)
            throw new RuntimeException("Error: empty list");
        if (this.index() < 0)
            throw new RuntimeException("Error: the cursor is undefined");
        Node N = new Node(data);
        if (cursor == back){
            N.prev = back;
            back.next = N;
            back = N;
        }
        else{
            N.prev = cursor;
            N.next = cursor.next;
            (cursor.next).prev = N;
            cursor.next = N;
        }
        length++;
    }

    void insertOrder(int data){
    	//Node N = new Node(data);
    	Node M;
    	moveFront();
    	while (this.index() >= 0){
    		M = cursor;
    		if (data <= M.data)
    			break;
    		moveNext();
    	}
    	if (this.index() == -1){
    		append(data);
    	}
    	else{
    		insertBefore(data);
    	}
    	length++;
    }

    // deleteFront()
    // Deletes the front element
    // Preconditions: length() > 0
    void deleteFront(){
        if (this.length <= 0)
            throw new RuntimeException("Error: the list is empty");
        if (this.length > 1){
            front = front.next;
            front.prev = null;
            if (this.index == 0 || this.index == -1){
                index = -1;
            }
            else{
                index--;
            }
        }
        else{
            front = back = null;
            index = -1;
        }
        length--;
    }

    // deleteBack()
    // Deletes the back element
    // Preconditions: length() > 0
    void deleteBack(){
        if (this.length <= 0)
            throw new RuntimeException("Error: the list is empty");
        if (this.length > 1){
            back = back.prev;
            back.next = null;
            if (this.index == this.length - 1){
                index = -1;
            }
        }
        else{
            front = back = null;
            index = -1;
        }
        length--;
    }

    // delete()
    // Deletes the cursor element, making the cursor undefined
    // Preconditions: length() > 0 and index() >= 0
    void delete(){
        if (this.length <= 0)
            throw new RuntimeException("Error: the list is empty");
        if (this.index() < 0)
            throw new RuntimeException("Error: the cursor is undefined");
        Node N;
        if (cursor == front){
            front = front.next;
            front.prev = null;
            cursor = null;
            index = -1;
        }
        else if (cursor == back){
            back = back.prev;
            back.next = null;
            cursor = null;
            index = -1;
        }
        else{
            (cursor.prev).next = cursor.next;
            (cursor.next).prev = cursor.prev;
            cursor.next = null;
            cursor.prev = null;
            cursor = null;
            index = -1;
        }
        length--;
    }

    // Other methods

    // toString()
    // Overrides Object's toString method. Returns a String representation of this List consisting of a space
    // separated sequence of integers, with front on left
    // Preconditions: none
    public String toString(){
        StringBuffer s = new StringBuffer();
        Node N = front;
        while (N != null){
            s.append(N.toString());
            s.append(" ");
            N = N.next;
        }
        return new String(s);
    }

    // copy()
    // Returns a new List representing the same integer sequence as this List. The cursor in the new List
    // is undefined. This List is unchanged.
    // Preconditions: none
    List copy(){
        List L = new List();
        Node N, M;
        if (this.length > 0){
            N = this.front;
            M = new Node(N.data);
            L.front = M;
            L.length++;
            N = N.next;
            while (N != null){
                M.next = new Node(N.data);
                (M.next).prev = M;
                M = M.next;
                L.length++;
                N = N.next;
            }
        }
        return L;
    }

}