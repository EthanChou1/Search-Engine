//
// Created by ethan on 4/5/2022.
//

/*  The invertIndex class is a custom class used to store references from each element to be indexed to the
 *  corresponding document(s) in which those elements exist.
 *
 *  invertIndex.h is used for the functions definitions of the class.
 */

#ifndef INC_22S_FINAL_PROJ_INVERTINDEX_H
#define INC_22S_FINAL_PROJ_INVERTINDEX_H
#pragma once
#include "parseDocument.h"
#include "porter2_stemmer.h"
#include "sstream"
#include <fstream>
#include <string.h>
#include "DSHashTable.h"
class invertIndex {
    friend class searchQuery;
private:
    parseDocument docParser;
    DSAVLTree<string, vector<DocumentInfo*>> indexWord;
//    DSAVLTree<string, vector<DocumentInfo*>> indexPeople;
//   DSAVLTree<string, vector<DocumentInfo*>> indexOrg;
//    DSAVLTree<string, int> stopWords;
    DSHashTable<int> stopWords;
    DSHashTable<vector<DocumentInfo*>> indexPeople;
    DSHashTable<vector<DocumentInfo*>> indexOrg;
    int totalWords;
    int totalPersons;
    int totalOrgs;
    double averageWordCount;
public:
    void createIndex();
    void createStopWordIndex();
    invertIndex(const string& nameDirectory);
    void searchSingleWord(vector<DocumentInfo*>& list, string word);
    void searchQueryAnd(vector<DocumentInfo*>& list, string word, bool secondRun);
    void searchQueryOr(vector<DocumentInfo*>& list, string word);
    void searchQueryNot(vector<DocumentInfo*>& list, string word);
    void searchQueryPerson(vector<DocumentInfo*>& list, string word);
    void searchQueryOrg(vector<DocumentInfo*>& list, string word);
    void deleteIndex();
    void repopulate();
    vector<DSAVLNode<string, vector<DocumentInfo *>>> mostPopularWords();
    void relevancyCalc(vector<DocumentInfo*>& list, vector<string>& wordList);
};


#endif //INC_22S_FINAL_PROJ_INVERTINDEX_H
