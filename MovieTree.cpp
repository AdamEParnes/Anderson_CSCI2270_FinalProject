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

void MovieTree::addMovieByTitle(std::string title, int year, int rating, int price)
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
            if (strcmp((p->title).c_str(), (m->title).c_str()) > 0) {
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

void MovieTree::addMovieByYear(std::string title, int year, int rating, int price)
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
            if (p->year > m->year) {
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

void MovieTree::addMovieByRating(std::string title, int year, int rating, int price)
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
            if (p->rating > m->rating) {
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

void MovieTree::addMovieByPrice(std::string title, int year, int rating, int price)
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
            if (p->price > m->price) {
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

int MovieTree::countMovies()
{
    return countMovie(root);
}

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

void MovieTree::printInventory()
{
    printInventory(root);
}

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

int MovieTree::countMovie(Movie *m)
{
    if (m == nil) {
        return 0;
    }

    return 1 + countMovie(m->left) + countMovie(m->right);
}

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
