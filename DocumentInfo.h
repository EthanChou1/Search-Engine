//
// Created by Ethan on 4/5/2022.
//
/*  The DocumentInfo class is a custom class used to serve as a container to store the various information related to the
 *  documents in the dataset
 *
 *  DocumentInfo.h is used for the functions definitions of the class.
 */

#ifndef INC_22S_FINAL_PROJ_DOCUMENTINFO_H
#define INC_22S_FINAL_PROJ_DOCUMENTINFO_H
#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class DocumentInfo {
public:
    string id;
    string title;
    vector<string> name;
    vector<string> org;
    string text;
    string publishDate;
    int wordCount;

    DocumentInfo(const string& id, const string& title, const vector<string>& name, const vector<string>& org, const string& text, const string& publishDate);
    bool operator==(DocumentInfo& doc);
};


#endif //INC_22S_FINAL_PROJ_DOCUMENTINFO_H
