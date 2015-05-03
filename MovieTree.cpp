#include "MovieTree.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

MovieTree::MovieTree()
{
    nil = new Movie("nil", -1, -1, -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
}

MovieTree::~MovieTree()
{
    deleteMovie(root);
}

/*
void MovieTree::addMovieByTitle(std::string, int, int, int)

Description:
Adds a movie to the tree using the movie's title as the
attribute being sorted.

Example:
MovieTree tree;
tree.addMovieByTitle("Back to the Future", 1985, 96, 5);

Precondition:
The ends of the tree are nil.

Postcondition:
Movie added to the tree in correct position.
*/
void MovieTree::addMovie(std::string title, int year, int rating, int price, char mode)
{
    Movie *newMovie = new Movie(title, year, rating, price);

    if (root == nil) {
        newMovie->parent = nil;
        newMovie->left = nil;
        newMovie->right = nil;
        root = newMovie;
    } else {
        Movie *p = root;
        Movie *m = newMovie;

        while (p != nil) {
            if (nodeComparison(mode, m, p) == true) {
                if (p->left != nil) {
                    p = p->left;
                } else {
                    p->left = m;
                    break;
                }
            } else {
                if (p->right != nil) {
                    p = p->right;
                } else {
                    p->right = m;
                    break;
                }
            }
        }

        m->parent = p;
        m->left = nil;
        m->right = nil;
    }

    fixUpAdd(newMovie);
}

/*
bool MovieTree::nodeComparison(char mode, Movie *m, Movie *p)

Description:
Compares one value of node m to the corresponding value of p.

Example:
Movie *m, *p;
char mode = 't';
nodeComparison(mode, m, p);

Precondition:
Both nodes are not nil and have values for title, year,
rating or price.

Postcondition:
Returns true if the value of m is lower than the value of p.
Returns false otherwise.
*/
bool MovieTree::nodeComparison(char mode, Movie *m, Movie *p)
{
    bool goLeft = false;

    switch (mode) {
    case 't':
        if (strcmp((p->title).c_str(), (m->title).c_str()) > 0) {
            goLeft = true;
        }
        break;
    case 'y':
        if (p->year > m->year) {
            goLeft = true;
        }
        break;
    case 'r':
        if (p->rating > m->rating) {
            goLeft = true;
        }
        break;
    case 'p':
        if (p->price > m->price) {
            goLeft = true;
        }
        break;
    default:
        break;
    }

    return goLeft;
}

/*
bool MovieTree::deleteMovie(std::string)

Description:
Deletes a movie from the tree.

Example:
MovieTree tree;
tree.deleteMovie("Back to the Future");

Precondition:
The ends of the tree are nil. Movies are organized in the red-black
tree correctly.

Postcondition:
Memory used by the movie is freed. The tree is rearranged as
necessary. Returns true if the movie is found.
*/
bool MovieTree::deleteMovie(std::string title)
{
    Movie *m = searchTree(root, title);

    if (m != nil) {
        deleteMovie(m);
        return true;
    } else {
        return false;
    }
}

/*
bool MovieTree::findMovie(std::string)

Description:
Searches the tree for a specific movie by title, and prints the year,
rating, and price if found.

Example:
MovieTree tree;
tree.findMovie("Back to the Future");

Precondition:
The ends of the tree are nil. Movies are organized in the red-black
tree correctly.

Postcondition:
Returns true and displays year, rating, and price if the movie is found.
*/
bool MovieTree::findMovie(std::string title)
{
    Movie *m = searchTree(root, title);

    if (m != nil) {
        std::cout << "Year: " << m->year << std::endl;
        std::cout << "Rating: " << m->rating << std::endl;
        std::cout << "Price: $" << m->price << std::endl;
        return true;
    } else {
        return false;
    }
}

/*
int MovieTree::countMovies()

Description:
Calls a private, recursive method to count the number of movies in the tree.

Example:
MovieTree tree;
tree.countMovies();

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Returns the number of movies in the tree.
*/
int MovieTree::countMovies()
{
    if (root == nil) {
        return 0;
    }

    return countMovie(root);
}

/*
void MovieTree::traversePreOrder(char)

Description:
Calls the private pre-order traversal method corresponding to the mode given
in the char parameter.

Example:
MovieTree tree;
tree.traversePreOrder('t');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The movies in the tree are printed out in ascending order according to the
selected mode.
*/
void MovieTree::traversePreOrder(char mode)
{
    if (root == nil) {
        std::cout << "Tree is empty\n";
        return;
    }

    switch (mode) {
    case 't':
        traversePreOrderTitle(root);
        break;
    case 'y':
        traversePreOrderYear(root);
        break;
    case 'r':
        traversePreOrderRating(root);
        break;
    case 'p':
        traversePreOrderPrice(root);
        break;
    default:
        break;
    }
}

/*
void MovieTree::traversePostOrder(char)

Description:
Calls the private post-order traversal method corresponding to the mode given
in the char parameter.

Example:
MovieTree tree;
tree.traversePostOrder('t');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The movies in the tree are printed out in descending order according to the
selected mode.
*/
void MovieTree::traversePostOrder(char mode)
{
    if (root == nil) {
        std::cout << "Tree is empty\n";
        return;
    }

    switch (mode) {
    case 't':
        traversePostOrderTitle(root);
        break;
    case 'y':
        traversePostOrderYear(root);
        break;
    case 'r':
        traversePostOrderRating(root);
        break;
    case 'p':
        traversePostOrderPrice(root);
        break;
    default:
        break;
    }
}

/*
void MovieTree::printInventory()

Description:
Prints the title, year, rating, and price of each movie in the tree.

Example:
MovieTree tree;
tree.printInventory();

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the title, year, rating, and price of each movie in the tree.
*/
void MovieTree::printInventory()
{
    printInventory(root);
}

/*
Movie *MovieTree::searchTree(Movie*, std::string)

Description:
Private, recursive method used by findMovie and deleteMovie to return the
memory address of a specific movie.

Example:
MovieTree tree;
tree.findMovie("Back to the Future");
tree.deleteMovie("Back to the Future");

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Returns the matching movie's address, or continues searching through the
given movie's children.
*/
Movie *MovieTree::searchTree(Movie *m, std::string title)
{
    if (m == nil || m->title == title) {
        return m;
    } else if (strcmp((m->title).c_str(), title.c_str()) > 0) {
        return searchTree(m->left, title);
    } else {
        return searchTree(m->right, title);
    }
}

/*
Movie *MovieTree::deleteMovie(Movie*)

Description:
Private function used by deleteMovie to delete a movie.

Example:
MovieTree tree;
tree.deleteMovie("Back to the Future");

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The movie will be deleted from the tree, and the tree will be rebalanced.
*/
void MovieTree::deleteMovie(Movie *z)
{
    Movie *x = nil;
    Movie *y = z;

    bool wasRed = y->isRed;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = z->right;

        while (y->left != nil) {
            y = y->left;
        }

        wasRed = y->isRed;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isRed = z->isRed;
    }

    if (!wasRed) {
        fixUpDelete(x);
    }
}

/*
int MovieTree::countMovie(Movie*)

Description:
Private, recursive method used to count the number of movies in the tree.

Example:
MovieTree tree;
tree.countMovies();

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Returns the number of movies that branch from the movie given.
*/
int MovieTree::countMovie(Movie *m)
{
    if (m == nil) {
        return 0;
    }

    return 1 + countMovie(m->left) + countMovie(m->right);
}

/*
void MovieTree::fixUpAdd(Movie*)

Description:
Private method used to balance the tree after adding a movie.

Example:
MovieTree tree;
tree.addMoviebyTitle("Back to the Future", 1985, 96, 5);

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The tree will be balanced.
*/
void MovieTree::fixUpAdd(Movie *x)
{
    x->isRed = true;

    while (x != root && x->parent->isRed) {
        if (x->parent == x->parent->parent->left) {
            Movie *y = x->parent->parent->right;

            if (y->isRed) {
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    rotateLeft(x);
                }

                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rotateRight(x->parent->parent);
            }
        } else {
            Movie *y = x->parent->parent->left;

            if (y->isRed) {
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }

                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rotateLeft(x->parent->parent);
            }
        }
    }

    root->isRed = false;
}

/*
void MovieTree::fixUpDelete(Movie*)

Description:
Private method used to balance the tree after deleting a movie.

Example:
MovieTree tree;
tree.deleteMovie("Back to the Future");

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The tree will be balanced.
*/
void MovieTree::fixUpDelete(Movie *x)
{
    while (x != root && !(x->isRed)) {
        if (x == x->parent->left) {
            Movie *w = x->parent->right;

            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                rotateLeft(x->parent);
                w = x->parent->right;
            }

            if (!(w->left->isRed) && !(w->right->isRed)) {
                w->isRed = true;
                x = x->parent;
            } else {
                if (!(w->right->isRed)) {
                    w->left->isRed = false;
                    w->isRed = true;
                    rotateRight(w);
                    w = x->parent->right;
                }

                w->isRed = x->parent->isRed;
                w->parent->isRed = false;
                w->right->isRed = false;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Movie *w = x->parent->left;

            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                rotateRight(x->parent);
                w = x->parent->left;
            }

            if (!(w->right->isRed) && !(w->left->isRed)) {
                w->isRed = true;
                x = x->parent;
            } else {
                if (!(w->left->isRed)) {
                    w->right->isRed = false;
                    w->isRed = true;
                    rotateLeft(w);
                    w = x->parent->left;
                }

                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->left->isRed = false;
                rotateRight(x->parent);
                x = root;
            }
        }
    }

    x->isRed = false;
}

/*
void MovieTree::transplant(Movie*, Movie*)

Description:
Private method called in the private deleteMovie method to balance the tree.

Example:
MovieTree tree;
tree.deleteMovie("Back to the Future");

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The given movies will be transplanted, and the tree will remain balanced.
*/
void MovieTree::transplant(Movie *u, Movie *v)
{
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

/*
void MovieTree::rotateLeft(Movie*)

Description:
Private method called in fixUpAdd and fixUpDelete to balance the tree after
adding or deleting a movie.

Example:
MovieTree tree;
tree.addMovieByTitle("Back to the Future", 1985, 96, 5);
tree.deleteMovie("Back to the Future");

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The tree is rotated left at the given movie.
*/
void MovieTree::rotateLeft(Movie *x)
{
    Movie *y = x->right;

    x->right = y->left;

    if (y->left != nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nil) {
        root = y;
    } else {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    }

    y->left = x;
    x->parent = y;
}

/*
void MovieTree::rotateRight(Movie*)

Description:
Private method called in fixUpAdd and fixUpDelete to balance the tree after
adding or deleting a movie.

Example:
MovieTree tree;
tree.addMovieByTitle("Back to the Future", 1985, 96, 5);
tree.deleteMovie("Back to the Future");

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
The tree is rotated right at the given movie.
*/
void MovieTree::rotateRight(Movie *y)
{
    Movie *x = y->left;

    y->left = x->right;

    if (x->right != nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nil) {
        root = x;
    } else {
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    }

    x->right = y;
    y->parent = x;
}

/*
void MovieTree::traversePreOrderTitle(Movie*)

Description:
Private, recursive function called by traversePreOrder that prints the movies
in the tree according to title in ascending order.

Example:
MovieTree tree;
tree.traversePreOrder('t');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the titles of each movie in ascending order.
*/
void MovieTree::traversePreOrderTitle(Movie *m)
{
    if (m->left != nil) {
        traversePreOrderTitle(m->left);
    }

    std::cout << m->title << std::endl;

    if (m->right != nil) {
        traversePreOrderTitle(m->right);
    }
}

/*
void MovieTree::traversePreOrderYear(Movie*)

Description:
Private, recursive function called by traversePreOrder that prints the movies
in the tree according to year in ascending order.

Example:
MovieTree tree;
tree.traversePreOrder('y');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the year of each movie in ascending order.
*/
void MovieTree::traversePreOrderYear(Movie *m)
{
    if (m->left != nil) {
        traversePreOrderYear(m->left);
    }

    std::cout << m->year << " - " << m->title << std::endl;

    if (m->right != nil) {
        traversePreOrderYear(m->right);
    }
}

/*
void MovieTree::traversePreOrderRating(Movie*)

Description:
Private, recursive function called by traversePreOrder that prints the movies
in the tree according to rating in ascending order.

Example:
MovieTree tree;
tree.traversePreOrder('r');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the rating of each movie in ascending order.
*/
void MovieTree::traversePreOrderRating(Movie *m)
{
    if (m->left != nil) {
        traversePreOrderRating(m->left);
    }

    std::cout << m->rating << " - " << m->title << std::endl;

    if (m->right != nil) {
        traversePreOrderRating(m->right);
    }
}

/*
void MovieTree::traversePreOrderPrice(Movie*)

Description:
Private, recursive function called by traversePreOrder that prints the movies
in the tree according to price in ascending order.

Example:
MovieTree tree;
tree.traversePreOrder('p');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the price of each movie in ascending order.
*/
void MovieTree::traversePreOrderPrice(Movie *m)
{
    if (m->left != nil) {
        traversePreOrderPrice(m->left);
    }

    std::cout << "$" << m->price << " - " << m->title << std::endl;

    if (m->right != nil) {
        traversePreOrderPrice(m->right);
    }
}

/*
void MovieTree::traversePostOrderTitle(Movie*)

Description:
Private, recursive function called by traversePostOrder that prints the movies
in the tree according to title in descending order.

Example:
MovieTree tree;
tree.traversePreOrder('t');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the title of each movie in descending order.
*/
void MovieTree::traversePostOrderTitle(Movie *m)
{
    if (m->right != nil) {
        traversePostOrderTitle(m->right);
    }

    std::cout << m->title << std::endl;

    if (m->left != nil) {
        traversePostOrderTitle(m->left);
    }
}

/*
void MovieTree::traversePostOrderYear(Movie*)

Description:
Private, recursive function called by traversePostOrder that prints the movies
in the tree according to year in descending order.

Example:
MovieTree tree;
tree.traversePreOrder('y');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the year of each movie in descending order.
*/
void MovieTree::traversePostOrderYear(Movie *m)
{
    if (m->right != nil) {
        traversePostOrderYear(m->right);
    }

    std::cout << m->year << " - " << m->title << std::endl;

    if (m->left != nil) {
        traversePostOrderYear(m->left);
    }
}

/*
void MovieTree::traversePostOrderRating(Movie*)

Description:
Private, recursive function called by traversePostOrder that prints the movies
in the tree according to rating in descending order.

Example:
MovieTree tree;
tree.traversePreOrder('r');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the rating of each movie in descending order.
*/
void MovieTree::traversePostOrderRating(Movie *m)
{
    if (m->right != nil) {
        traversePostOrderRating(m->right);
    }

    std::cout << m->rating << " - " << m->title << std::endl;

    if (m->left != nil) {
        traversePostOrderRating(m->left);
    }
}

/*
void MovieTree::traversePostOrderPrice(Movie*)

Description:
Private, recursive function called by traversePostOrder that prints the movies
in the tree according to price in descending order.

Example:
MovieTree tree;
tree.traversePreOrder('p');

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
Prints the price of each movie in descending order.
*/
void MovieTree::traversePostOrderPrice(Movie *m)
{
    if (m->right != nil) {
        traversePostOrderPrice(m->right);
    }

    std::cout << "$" << m->price << " - " << m->title << std::endl;

    if (m->left != nil) {
        traversePostOrderPrice(m->left);
    }
}

/*
void MovieTree::printInventory(Movie*)

Description:
Private, recursive method called by the public printInventory method to
print the movies in the tree with title, year, rating, and price.

Example:
MovieTree tree;
tree.printInventory();

Precondition:
The ends of the tree are nil. The tree is arranged correctly.

Postcondition:
All information for every movie is printed to console. If the tree is empty,
"Tree is empty" will be printed.
*/
void MovieTree::printInventory(Movie *m)
{
    if (root == nil) {
        std::cout << "Tree is empty\n";
        return;
    }

    if (m->left != nil) {
        printInventory(m->left);
    }

    std::cout << m->title << " (" << m->year << ")\n";
    std::cout << "rating: " << m->rating << "\n";
    std::cout << "price: $" << m->price << std::endl;

    if (m->right != nil) {
        printInventory(m->right);
    }
}

/*
void MovieTree::deleteTree(Movie*)

Description:
Private, recursive function called in the destructor to properly deallocate
memory used by the tree.

Precondition:
The ends of the tree are nil.

Postcondition:
Each movie in the tree is deleted, using post-order traversal.
*/
void MovieTree::deleteTree(Movie *m)
{
    if (m == nil) {
        return;
    }

    if (m->left != nil) {
        deleteTree(m->left);
    }

    if (m->right != nil) {
        deleteTree(m->right);
    }

    delete m;
}
