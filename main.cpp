/*  Ethan Chou and Siddharth Bapat
 *  CS 2341
 *  Dr. Fontenot
 *  Deadline 5/3/22
 *  The program takes in a dataset of around 300,000 financial documents, parses and indexes them, and then allows the
 *  user to interact with these documents by searching up certain queries, looking at statistics, etc.
 */

#include <iostream>
#include "invertIndex.h"
#include "searchQuery.h"
using namespace std;

int main(int argc, char* argv[]) {
    searchQuery processor(argv[1]);
    return 0;
}
