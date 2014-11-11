07_HeapLab
==============

Implement a heap in C++

Requirements
------------

1. `add` and `remove` should be O(log n), except for `grow` which can be O(n)
2. Do not leak memory

Reading
=======
"Open Data Structures," Chapter 10, just the intro and section 1. http://opendatastructures.org/ods-cpp/10_Heaps.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. add and remove (without calling bubbleUp and trickleDown) run in constant time.  bubbleUp and trickleDown both run in O(log n) time because in the worst case
will iterate through the height of the tree.  so when add and remove call bubbleUp and trickleDown, their run times are O(1 + log n) which is just O(log n).
2. the destructor and grow methods both delete the backingArray when they need to.  And no other methods need to do any memory management.

#### 2. Exercises 10.1 and 10.2 from http://opendatastructures.org/ods-cpp/10_3_Discussion_Exercises.html
10.1)

add 7:

  7 becomes left node of 16
  7 and 16 swap
  7's new parent is 6 which is < 7 so we are done

add 3:

  3 becomes right node of 7
  3 and 7 swap, 6 is 3's new parent
  3 and 6 swap, 4 is 3's new parent
  3 and 4 swap, 3 is now at the root because it is the smallest in the tree

10.2)

#### 3. Exercise 10.4 from http://opendatastructures.org/ods-cpp/10_3_Discussion_Exercises.html

#### 4. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

TODO
