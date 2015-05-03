#include "MovieTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
    std::ifstream io;
    MovieTree tree, yearTree, ratingTree, priceTree;
    std::string title;
    int year, rating, price;

    if (argv[1] != NULL) {
        io.open(argv[1]);

        if (!io.good()) {
            std::cout << "Error opening file\n";
            io.close();
            return 0;
        }

        std::string line, word;

        while (!io.eof()) {
            getline(io, line);
            std::istringstream ss(line);

            if (ss.str() == "") {
                continue;
            }

            getline(ss, word, ',');
            title = word;
            std::cout<<title<<std::endl;

            getline(ss, word, ',');
            std::istringstream y(word);
            y >> year;

            getline(ss, word, ',');
            std::istringstream r(word);
            r >> rating;

            getline(ss, word, ',');
            std::istringstream p(word);
            p >> price;

            tree.addMovie(title, year, rating, price, 't');
            yearTree.addMovie(title, year, rating, price, 'y');
            ratingTree.addMovie(title, year, rating, price, 'r');
            priceTree.addMovie(title, year, rating, price, 'p');
        }

        io.close();
    }

    while (true) {
        std::cout << "========MAIN MENU========\n";
        std::cout << "1. Add Movie\n";
        std::cout << "2. Delete Movie\n";
        std::cout << "3. Find Movie\n";
        std::cout << "4. Count Movies\n";
        std::cout << "5. List by Title\n";
        std::cout << "6. List by Year\n";
        std::cout << "7. List by Rating\n";
        std::cout << "8. List by Price\n";
        std::cout << "9. Print Inventory\n";
        std::cout << "0. Quit\n";

        int selection;
        std::cin >> selection;

        switch (selection) {
        case 1:
            //Add Movie
            std::cout << "Title: ";
            std::cin.ignore();
            getline(std::cin, title);
            std::cout << "Year: ";
            std::cin >> year;
            std::cout << "Rating: ";
            std::cin >> rating;
            std::cout << "Price: $";
            std::cin >> price;
            tree.addMovie(title, year, rating, price, 't');
            yearTree.addMovie(title, year, rating, price, 'y');
            ratingTree.addMovie(title, year, rating, price, 'r');
            priceTree.addMovie(title, year, rating, price, 'p');
            break;
        case 2:
            //Delete Movie
            std::cout << "Title: ";
            std::cin.ignore();
            getline(std::cin, title);
            if (tree.deleteMovie(title)) {
                yearTree.deleteMovie(title);
                ratingTree.deleteMovie(title);
                priceTree.deleteMovie(title);
                std::cout << "Movie deleted successfully\n";
            } else {
                std::cout << "Movie not found\n";
            }
            break;
        case 3:
            //Find Movie
            std::cout << "Title: ";
            std::cin.ignore();
            getline(std::cin, title);
            if (!tree.findMovie(title)) {
                std::cout << "Movie not found\n";
            }
            break;
        case 4:
            //Count Movies
            std::cout << "The tree has " << tree.countMovies() << " movies.\n";
            break;
        case 5:
            //List by Title
            std::cout << "======LIST BY TITLE======\n";
            std::cout << "1. Ascending Order\n";
            std::cout << "2. Descending Order\n";
            std::cin >> selection;
            switch (selection) {
            case 1:
                tree.traversePreOrder('t');
                break;
            case 2:
                tree.traversePostOrder('t');
                break;
            default:
                std::cout << "Invalid selection\n";
                break;
            }
            break;
        case 6:
            //List by Year
            std::cout << "=======LIST BY YEAR======\n";
            std::cout << "1. Ascending Order\n";
            std::cout << "2. Descending Order\n";
            std::cin >> selection;
            switch (selection) {
            case 1:
                yearTree.traversePreOrder('y');
                break;
            case 2:
                yearTree.traversePostOrder('y');
                break;
            default:
                std::cout << "Invalid selection\n";
                break;
            }
            break;
        case 7:
            //List by Rating
            std::cout << "======LIST BY RATING=====\n";
            std::cout << "1. Ascending Order\n";
            std::cout << "2. Descending Order\n";
            std::cin >> selection;
            switch (selection) {
            case 1:
                ratingTree.traversePreOrder('r');
                break;
            case 2:
                ratingTree.traversePostOrder('r');
                break;
            default:
                std::cout << "Invalid selection\n";
                break;
            }
            break;
        case 8:
            //List by Price
            std::cout << "======LIST BY PRICE======\n";
            std::cout << "1. Ascending Order\n";
            std::cout << "2. Descending Order\n";
            std::cin >> selection;
            switch (selection) {
            case 1:
                priceTree.traversePreOrder('p');
                break;
            case 2:
                priceTree.traversePostOrder('p');
                break;
            default:
                std::cout << "Invalid selection\n";
                break;
            }
            break;
        case 9:
            //Print Inventory
            tree.printInventory();
            break;
        case 0:
            //Quit
            return 0;
            break;
        default:
            std::cout << "Invalid selection\n";
            break;
        }
    }

    return 0;
}
