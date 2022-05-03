//
// Created by Ethan on 4/5/2022.
//
/*  The SearchQuery class is a custom class used to serve as the menu-driven UI for the program. It allows the user to
 * search for various documents, look at statistics, etc.
 *
 *  SearchQuery.h is used for the functions definitions of the class.
 */


#ifndef INC_22S_FINAL_PROJ_SEARCHQUERY_H
#define INC_22S_FINAL_PROJ_SEARCHQUERY_H
#include "invertIndex.h"

class searchQuery {
public:
    searchQuery(const string& nameDirectory);
    static void asciiArt();
    static void stonks();
    static void viewStatistics(invertIndex& index,  vector<DSAVLNode<string, vector<DocumentInfo *>>>& list);
    static void menuOptions();
    static void clearIndex(invertIndex& index, vector<DSAVLNode<string, vector<DocumentInfo *>>>& popularWords);
    static void repopulateIndex(invertIndex& index, vector<DSAVLNode<string, vector<DocumentInfo *>>>& popularWords);
    static void searchIndex(invertIndex& index);
    static void displayDoc(vector<DocumentInfo*>& docList, bool sizeLimit);
};


#endif //INC_22S_FINAL_PROJ_SEARCHQUERY_H
