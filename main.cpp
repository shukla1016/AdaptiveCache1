#include <iostream>
#include <sqlite3.h>
#include "database_handler.h"
#include "splay_tree.h"
#include <string.h>

using namespace std;

int main() {
    system("clear");
    system("tput setab 4");
    cout << "Adaptive Cache Implementation using Splay tree" << endl;
    cout << "Parth Shukla 206124020" << endl;
    cout << "Raushan Mehta 206124026" << endl;
    int n;
    cout << "Enter any key to start!" << endl;
    cin >> n;
    system("clear");
    const double alpha = 0.5; // For score calculation
    const int max_cache_size = 3; // Maximum cache size
    static long long int time = 0;

    DatabaseHandler db("data.db");
    SplayTree cache(alpha, max_cache_size);

    int choice, key;
    while (true) {
        std::cout << "1. Search\n2. Insert\n3. Delete\n4. Display Cache\n5. Exit\nEnter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
            {
                system("clear");
                std::cout << "Enter key to search: ";
                std::cin >> key;
                
                if (cache.search(key, ++time)) {
                    std::cout << "Found: " << key << " with value: " << db.getValue(key) << std::endl;
                } else {
                    std::cout << "Not found in cache! Checking database...\n";
                    std::string value = db.getValue(key);
                    if (!value.empty()) {
                        cache.insert(key, time);
                        std::cout << "Found in database: " << key << " with value: " << value << std::endl;
                    } else {
                        std::cout << "Not found in database!" << std::endl;
                    }
                }
                break;
            }

            case 2:
            {
                system("clear");
                std::cout << "Enter key to insert: " << std::endl;
                std::cin >> key;
                std::string value;
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                db.insertRecord(key, value);
                break;
            }

            case 3:
                system("clear");
                std::cout << "Enter key to delete: ";
                std::cin >> key;
                db.deleteRecord(key);
                cache.remove(key);
                cache.current_size--;
                std::cout << "Deleted: " << key << std::endl;
                break;

            case 4:
                system("clear");
                if(cache.current_size == 0)
                    cout << "Empty\n" << endl;
                else
                {
                    std::cout << "Current cache keys:\n";
                    cache.print();
                }
                break;

            case 5:
                system("clear");
                return 0;

            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    }
}
