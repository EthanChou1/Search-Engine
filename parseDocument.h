//
// Created by ethan on 4/5/2022.
//

/*  The parseDocument class is a custom class used to extract important data from the desired dataset and put this data
 *  into the associated containers to hold the data
 *
 *  parseDocument.h is used for the functions definitions of the class.
 */

#ifndef INC_22S_FINAL_PROJ_PARSEDOCUMENT_H
#define INC_22S_FINAL_PROJ_PARSEDOCUMENT_H
#pragma once
#include "DSAVLTree.h"
#include "DocumentInfo.h"
#include <chrono>
#include <algorithm>
#include <fstream>
class parseDocument {
    friend class invertedIndex;

public:
    vector<DocumentInfo> documents;
    parseDocument(const string& nameDirectory);
    void parseAgain(const string& nameDirectory);
};


#endif //INC_22S_FINAL_PROJ_PARSEDOCUMENT_H
