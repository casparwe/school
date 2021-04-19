

#### What did you learn from this assignment?

I did this lab last year but didnt finish it completely so it was a while since i made it.
But from what i remember the new thing learnt in this lab was mostly to use templates (when i did the course this was the fourth lab and we had already dealt with operators and everything, and i already knew c so memory management was nothing new).

#### What was hardest to implement in this assignment?

the hardest thing was understanding that defining the methods for a class/struct with a template has to be done in the same file as the class/struct, that took alot of time.

#### How many methods/functions have you implemented?

14 methods and no functions


#### How many methods/functions have you tested?

all

#### Describe and motivate how your implementation of operator= works

it copies all attributes of the matrix to the right into the matrix to the left, deletes m_vec for the matrix to the left, makes a copy of m_vec from the matrix to the right and assigns it to the matrix to the left. It basically makes a new matrix identical to the one on the right and assigns it to the one on the left so that modifying a copied matrix does not change the contents of the copied-from matrix.

#### When do you need to resize in your code?

when adding or removing rows or columns

#### Why do you need to implement a const-version of the accessor operator?

if you want a read only access tool

#### Is it possible to call std::sort() to sort your matrix using begin() and end()?

yes

#### What other kind of iterators, besides random access iterators, are there in C++?

input, output, forward, bidirectional
