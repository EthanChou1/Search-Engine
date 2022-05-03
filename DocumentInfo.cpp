//
// Created by Ethan on 4/5/2022.
//

/*  The DocumentInfo.cpp file contains the implementations for the methods defined in DocumentInfo.h.
 */
#include "DocumentInfo.h"

/**
 * Copy constructor for DocumentInfo object
 * @param id document id
 * @param title document title
 * @param name names within the document
 * @param org organizations within the document
 * @param text document text
 * @param publishDate date the document was published
 */
DocumentInfo::DocumentInfo(const string& id, const string& title, const vector<string>& name, const vector<string>& org, const string& text, const string& publishDate) {
    this->id = id;
    this->title = title;
    this->name = name;
    this->text = text;
    this->org = org;
    this->publishDate = publishDate;
    wordCount = 0;
}

/**
 * Overloaded equality operator
 * @param doc second document to compare
 * @return true if the documents are equal, false if not
 */
bool DocumentInfo::operator==(DocumentInfo &doc) {
    return id.compare(doc.id) == 0;
}
