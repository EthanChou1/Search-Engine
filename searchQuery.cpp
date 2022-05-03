//
// Created by Ethan on 4/5/2022.
//
/*  The SearchQuery.cpp file contains the implementations for the methods defined in SearchQuery.h.
 */

#include "searchQuery.h"

/**
 * Main menu of search engine, allows the user to do all of the searching options, statistics, etc.
 * @param nameDirectory the file directory that the dataset is in
 */
searchQuery::searchQuery(const string &nameDirectory){

    invertIndex index(nameDirectory);
    //Gets most popular words after indexing
    vector<DSAVLNode<string, vector<DocumentInfo *>>> popularWords = index.mostPopularWords();
    bool keepGoing = true;
    stonks();
    cout << endl << "2022 Data $tructure$ $tonk$ $earch Engine" << endl;
    do {
        string option;
        menuOptions();
        cin >> option;
        cout << endl;
        if(option == "CLEAR")
        {
            clearIndex(index, popularWords);
        }
        else if(option == "INDEX")
        {
            repopulateIndex(index, popularWords);
        }
        else if(option == "SEARCH")
        {
            searchIndex(index);
        }
        else if(option == "STATISTICS")
        {
            viewStatistics(index, popularWords);
        }
        else if(option == "QUIT")
        {
            cout << "Have a nice day!" << endl;
            keepGoing = false;
        }
        else
        {
            cout << "Invalid input, please try again." << endl;
            cout << "Returning to menu...." << endl;
            cout << endl;
        }
    }while(keepGoing);
}

/**
 * Lists the different options to pick in the main menu
 */
void searchQuery::menuOptions() {

    cout << "What would you like to do?" << endl;
    cout << "To Clear Index type: CLEAR" << endl;
    cout << "To Repopulate Index type: INDEX" << endl;
    cout << "To Search type: SEARCH" << endl;
    cout << "To See Statistics type: STATISTICS" << endl;
    cout << "To Quit type: QUIT" << endl;
    cout << "Option: ";
}

/**
 * Deletes the index
 * @param index index to be deleted
 * @param popularWords list of popular words to be cleared
 */
void searchQuery::clearIndex(invertIndex &index, vector<DSAVLNode<string, vector<DocumentInfo *>>>& popularWords) {
    cout << "Are you sure that you would like to delete the Index? type: YES or NO: ";
    cin.ignore();
    string parseOption;
    getline(cin, parseOption);
    cout << endl;
    if(parseOption == "YES")
    {
        cout << "Clearing index..." << endl;
        index.deleteIndex();
        //Clears most poplar word list
        vector<DSAVLNode<string, vector<DocumentInfo *>>> empty;
        popularWords = empty;
        cout << "Index has been cleared" << endl;
        cout << endl;
    }
    else if(parseOption == "NO")
    {
        cout << "———————————No Deleting?————————————" << endl;
        asciiArt();
        cout << endl;
    }
}

/**
 * Re-indexes the search engine
 * @param index to be repopulated
 * @param popularWords to find top 25 most popular words
 */
void searchQuery::repopulateIndex(invertIndex &index, vector<DSAVLNode<string, vector<DocumentInfo *>>>& popularWords) {
    cout << "Would you like to repopulate the Index? type: YES or NO: ";
    cin.ignore();
    string parseOptionTwo;
    getline(cin, parseOptionTwo);
    cout << endl;
    if(parseOptionTwo == "YES")
    {
        index.repopulate();
        popularWords = index.mostPopularWords();
    }
    else if(parseOptionTwo == "NO")
    {
        cout << "——————————No Repopulating?—————————" << endl;
        asciiArt();
        cout << endl;
    }
}

/**
 * Gets a query, searches the documents for the words/terms of the query, and displays the 15 most relevant documents of
 * the query
 * @param index index of documents to search within
 */
void searchQuery::searchIndex(invertIndex &index) {
    cout << "Enter search query: ";
    string query;
    cin.ignore();
    getline(cin, query);
    vector<string> wordVector;
    //Vector to store found documents into
    cout << "Query: " << query << endl;
    stringstream stream(query);
    string word;
    //Store search results
    vector<DocumentInfo*> docList;
    vector<string> wordList;
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();
    while(getline(stream, word, ' '))
    {
        wordVector.push_back(word);
    }
    //"toggles" which search function to use
    bool useAnd = false;
    bool useOr = false;
    bool useNot = false;
    bool usePerson = false;
    bool useOrg = false;
    bool singleSearch = false;
    int AndCounter = 0;
    bool secondRun = false;
    for(int i = 0; i < wordVector.size(); i++)
    {
        if(wordVector.size() == 1)
        {
            singleSearch = true;
        }
        if(wordVector.at(i) == "AND")
        {
            useAnd = true;
            useOr = false;
            useNot = false;
            usePerson = false;
            useOrg = false;
        }
        else if(wordVector.at(i) == "OR")
        {
            useOr = true;
            useAnd = false;
            useNot = false;
            usePerson = false;
            useOrg = false;
        }
        else if(wordVector.at(i) == "NOT")
        {
            useNot = true;
            useOr = false;
            useAnd = false;
            usePerson = false;
            useOrg = false;
        }
        else if(wordVector.at(i) == "PERSON")
        {
            usePerson = true;
            useOr = false;
            useNot = false;
            useAnd = false;
            useOrg = false;
        }
        else if(wordVector.at(i) == "ORG")
        {
            useOrg = true;
            useOr = false;
            useNot = false;
            usePerson = false;
            useAnd = false;
        }
        else;
        if(useAnd)
        {
            //Skips the boolean query
            if(wordVector.at(i) != "AND" && AndCounter == 0)
            {
                index.searchQueryAnd(docList, wordVector.at(i), secondRun);
                wordList.push_back(wordVector.at(i));
                AndCounter++;
            }
            else if(wordVector.at(i) != "AND" && AndCounter != 0)
            {
                secondRun = true;
                wordList.push_back(wordVector.at(i));
                index.searchQueryAnd(docList, wordVector.at(i), secondRun);
            }
        }
        else if(useOr)
        {
            //Skips the boolean query
            if(wordVector.at(i) != "OR")
            {
                index.searchQueryOr(docList, wordVector.at(i));
                wordList.push_back(wordVector.at(i));
            }
        }
        else if(useNot)
        {
            //Skips the boolean query
            if(wordVector.at(i) != "NOT")
            {
                index.searchQueryNot(docList, wordVector.at(i));
                wordList.push_back(wordVector.at(i));
            }
        }
        //Uses same process as AND
        else if(usePerson)
        {
            //Skips the boolean query
            if(wordVector.at(i) != "PERSON")
            {
                index.searchQueryPerson(docList, wordVector.at(i));
                wordList.push_back(wordVector.at(i));
            }
        }
        //Uses same process as AND
        else if(useOrg)
        {
            //Skips the boolean query
            if(wordVector.at(i) != "ORG")
            {
                index.searchQueryOrg(docList, wordVector.at(i));
                wordList.push_back(wordVector.at(i));
            }
        }
        //One word search
        else if(singleSearch)
        {
            index.searchSingleWord(docList ,wordVector.at(i));
            wordList.push_back(wordVector.at(i));
        }
        //No BOOLEAN operator at the front, but has one later
        else
        {
            index.searchSingleWord(docList ,wordVector.at(i));
            wordList.push_back(wordVector.at(i));
        }
    }
    index.relevancyCalc(docList, wordList);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> time_in_seconds = end - start;
    cout << "Query Time: " << time_in_seconds.count() << " seconds." << endl;
    //If size is less than 15, set size to true
    bool size = false;
    if(docList.size() > 15)
    {
        size = true;
        if(docList.empty())
        {
            cout << "No documents could be displayed." << endl;
        }
        else
        {
            displayDoc(docList, size);
        }
    }
    else
    {
        if(docList.empty())
        {
            cout << "No documents could be displayed." << endl;
        }
        else
        {
            displayDoc(docList, size);
        }
    }
    if(docList.empty())
    {
        cout << "No documents found." << endl;
        cout << "—————————No Documents?—————————" << endl;
        asciiArt();
        cout << endl;
    }
}

/**
 * Displays the full text of the document and creates a user menu to read and re-read
 * documents if needed
 * @param docList the list of documents to pick a document to read from
 * @param sizeLimit to see if there are fifteen documents or not
 */
void searchQuery::displayDoc(vector<DocumentInfo *>& docList, bool sizeLimit) {
    bool readDocLoop = true;
    cout << "Total Documents: " << docList.size() << endl;
    cout << endl;
    //loop to re-read documents
    do {
        if(sizeLimit)
        {
            //Displays first 15 docs
            cout << "Top 15 most relevant documents list: " << endl;
            for(int i = 0; i < 15; i++)
            {
                cout << i << ". Document ID: " << docList[i]->id << " | Document Title: " << docList[i]->title << " | Publish Date: " << docList[i]->publishDate << endl;
            }
        }
        else
        {
            //If less than 15, display all docs
            cout << "Document List: " << endl;
            for(int i = 0; i < docList.size(); i++)
            {
                cout << i << ". Document ID: " << docList[i]->id << " | Document Title: " << docList[i]->title << " | Publish Date: " << docList[i]->publishDate << endl;
            }
        }
        cout << endl;
        cout << "Would you like to read a document? Type YES or NO: ";
        string readDoc;
        cin >> readDoc;
        cout << endl;
        if(readDoc == "YES")
        {
            cout << "Which Document would you like to read? Type a number between 0 and " << docList.size() - 1<< ": ";
            int docNumber;
            cin >> docNumber;
            cout << endl;
            if(docNumber > docList.size() - 1)
            {
                cout << "Invalid Number" << endl;
            }
            else if(docNumber >= 0 && docNumber < docList.size())
            {
                //Displays information
                cout << "Document ID: " << docList[docNumber]->id << endl;
                cout << "Document Title: " << docList[docNumber]->title << endl;
                cout << "Document Publish Date: " << docList[docNumber]->publishDate << endl;
                cout << "Document Word Count: " << docList[docNumber]->wordCount << endl;
                cout << "Document People: ";
                //If there are no people, display no people
                for(int i = 0; i < docList[docNumber]->name.size(); i++)
                {
                    if(i < docList[docNumber]->name.size() - 1)
                    {
                        cout << docList[docNumber]->name[i] << ", ";
                    }
                    else
                    {
                        cout << docList[docNumber]->name[i] << endl;
                    }
                }
                if(docList[docNumber]->name.size() == 0)
                {
                    cout << "No people listed in this document." << endl;
                }
                //If there are no organizations, display no orgs
                cout << "Document Organizations: ";
                for(int i = 0; i < docList[docNumber]->org.size(); i++)
                {
                    if(i < docList[docNumber]->org.size() - 1)
                    {
                        cout << docList[docNumber]->org[i] << ", ";
                    }
                    else
                    {
                        cout << docList[docNumber]->org[i] << endl;
                    }
                }
                if(docList[docNumber]->org.size() == 0)
                {
                    cout << "No organizations listed in this document." << endl;
                }
                cout << "Document Text: " << docList[docNumber]->text << endl;
                cout << endl;
            }
        }
        else if(readDoc == "NO")
        {
            cout << "————————————No Reading?————————————" << endl;
            asciiArt();
            cout << endl;
            readDocLoop = false;
        }
        else
        {
            cout << "Invalid input, please try again." << endl;
        }
    }while(readDocLoop);
}

/**
 * Displays the statistics collected during indexing
 * @param index index to get the statistics from
 * @param list top 25 most popular words to display
 */
void searchQuery::viewStatistics(invertIndex& index, vector<DSAVLNode<string, vector<DocumentInfo *>>>& list) {
    cout << "Statistics: " << endl;
    cout << "\tTotal number of unique words: " << index.totalWords << endl;
    cout << "\tTotal articles parsed: " << index.docParser.documents.size() << endl;
    cout << "\tAverage word count per document: " << index.averageWordCount << endl;
    cout << "\tTotal number of unique organizations: " << index.totalOrgs << endl;
    cout << "\tTotal number of unique persons: " << index.totalPersons << endl;
    cout << "\tTop 25 Most Popular Words: " << endl;
    //Checks if list is empty
    if(list.empty())
    {
        cout << "\tThere are no words in the word index for popularity display." << endl;
    }
    else
    {
        for(int i = 0; i < list.size(); i++)
        {
            cout << "\t" << list[i].getKey() << " " << list[i].getValue().size() << endl;
        }
    }
    cout << endl;
}

/**
 * Easter egg ascii art for when the user picks "NO" for certain choices
 */
void searchQuery::asciiArt() {
    cout << " ⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝" << endl;
    cout << "⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫" << endl;
    cout << "⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏" << endl;
    cout << "⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀" << endl;
    cout << "⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "———————————————————————————————————" << endl;
}

/**
 * Title screen ascii art
 */
void searchQuery::stonks()
{
    cout << "⠀⠀⠀⠀⠀⢀⠤⠐⠒⠀⠀⠀⠒⠒⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            "⠀⠀⠀⡠⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            "⠀⠀⡔⠁⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠈⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            "⠀⢰⠀⠀⠀⠀⠀⠀⠀⣾⠀⠀⠔⠒⠢⠀⠀⠀⢼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            "⠀⡆⠀⠀⠀⠀⠀⠀⠀⠸⣆⠀⠀⠙⠀⠀⠠⠐⠚⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            "⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀⡄⢠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀\n"
            "⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⣀⣀⡠⡌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⢄⣲⣬⣶⣿⣿⡇⡇⠀\n"
            "⠀⠀⠆⠀⠀⠀⠀⠀⠀⠀⠘⡆⠀⠀⢀⣀⡀⢠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⢴⣾⣶⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀\n"
            "⠀⠀⢸⠀⠀⠀⠀⠠⢄⠀⠀⢣⠀⠀⠑⠒⠂⡌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⡇⠀\n"
            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠤⡀⠑⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣡⣿⣿⣿⣿⣿⣿⣿⣇⠀\n"
            "⠀⠀⢀⡄⠀⠀⠀⠀⠀⠀⠀⠈⢑⠖⠒⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⣴⣿⣿⣿⡟⠁⠈⠛⠿⣿⠀\n"
            "⠀⣰⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢈⣾⣿⣿⣿⠏⠀⠀⠀⠀⠀⠈⠀\n"
            "⠈⣿⣿⣿⣿⣷⡤⣀⡀⠀⠀⢀⠎⣦⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⣢⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀\n"
            "⠀⠘⣿⣿⣿⣿⣿⣄⠈⢒⣤⡎⠀⢸⣿⣿⣿⣷⣶⣤⣄⣀⢠⣽⣿⠿⠿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
            "⠀⠀⠹⣿⣿⣿⣿⣿⣾⠛⠉⣿⣦⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡗⣰⣿⠀ ⠀⣿⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀\n"
            "⠀⠀⡰⠋⠉⠉⠉⣿⠉⠀⠀⠉⢹⡿⠋⠉⠉⠉⢿⣿⠉⠉⠋⠉⠉⠻⣿⠀⠀⣿⠞⠉⢉⣿⠚⠉⠉⠉⣿⠀\n"
            "⠀⠀⢧⠀⠈⠛⠿⣟⢻⠀⠀⣿⣿⠁⠀⣾⣿⣧⠀⠘⣿⠀⠀⣾⣿⠀⠀⣿⠀⠀⠋⠀⢰⣿⣿⡀⠀⠛⠻⣟⠀\n"
            "⠀⠀⡞⠿⠶⠄⠀⢸⢸⠀⠀⠿⢿⡄⠀⠻⠿⠇⠀⣸⣿⠀⠀⣿⣿⠀⠀⣿⠀⠀⣶⡀⠈⢻⣿⠿⠶⠆⠀⢸⡇\n"
            "⠀⠀⠧⢤⣤⣤⠴⠋⠈⠦⣤⣤⠼⠙⠦⢤⣤⠶⠋⠹⠤⠤⠿⠿ ⠤⠿⠤⠿⠳⠤ ⠤⠽⢤⣤⣤⠴⠟⠀" << endl;
}


