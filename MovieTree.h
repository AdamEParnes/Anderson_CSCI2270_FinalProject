#ifndef MOVIE_TREE_H
#define MOVIE_TREE_H

#include <string>

struct Movie {
    std::string title;
    int year;
    int rating;
    int price;

    Movie *parent;
    Movie *left;
    Movie *right;

    bool isRed;

    Movie(std::string t, int y, int r, int p)
    {
        title = t;
        year = y;
        rating = r;
        price = p;
    }
};

class MovieTree {
private:
    Movie *root;
    Movie *nil;
    Movie *searchTree(Movie*, std::string);
    void deleteMovie(Movie*);
    int countMovie(Movie*);
    void fixUpAdd(Movie*);
    void fixUpDelete(Movie*);
    void transplant(Movie*, Movie*);
    void rotateLeft(Movie*);
    void rotateRight(Movie*);
    void traversePreOrderTitle(Movie*);
    void traversePreOrderYear(Movie*);
    void traversePreOrderRating(Movie*);
    void traversePreOrderPrice(Movie*);
    void traversePostOrderTitle(Movie*);
    void traversePostOrderYear(Movie*);
    void traversePostOrderRating(Movie*);
    void traversePostOrderPrice(Movie*);
    void printInventory(Movie*);
    void deleteTree(Movie*);
public:
    MovieTree();
    virtual ~MovieTree();
    void addMovieByTitle(std::string, int, int, int);
    void addMovieByYear(std::string, int, int, int);
    void addMovieByRating(std::string, int, int, int);
    void addMovieByPrice(std::string, int, int, int);
    bool deleteMovie(std::string);
    bool findMovie(std::string);
    int countMovies();
    void traversePreOrder(char);
    void traversePostOrder(char);
    void printInventory();
};

#endif
