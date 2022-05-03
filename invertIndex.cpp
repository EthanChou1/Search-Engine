//
// Created by Ethan on 4/5/2022.
//

/*  The invertIndex.cpp file contains the implementations for the methods defined in invertIndex.h.
 */
#include "invertIndex.h"
#include <string.h>
/**
 * Pulls data from the documents and creates an index of words, people, and organizations
 * Also collects statistics such as total word count and average word count
 */
void invertIndex::createIndex() {
    //pointer to a vector of DocumentInfo pointers
    vector<DocumentInfo*>* temp;
    //Iterates through vector<DocumentInfo> for information
    for(int i = 0; i < docParser.documents.size(); i++)
    {
        //word counter
        int wordCount = 0;
        //https://stackoverflow.com/questions/5830868/c-stringstream-is-too-slow-how-to-speed-up
        //https://quick-adviser.com/why-is-stringstream-slow/
        //stringstream may be slow, so changed to strtok and testing
        //Changed stringstream to strtok
        //https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
        string str(docParser.documents.at(i).text);
        char const* const delim{" "};
        char *token;
        token = strtok( &str[0], delim);
        while(token != nullptr)
        {
            //Assigns char token to word
            string word = token;
            //Stems/Trims the word
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            //If avl tree of stop words does not have the word means it can be added
            if(!stopWords.search(word))
            {
                //adds to word count
                wordCount++;
                averageWordCount++;
                //temp point to word
                temp = indexWord.get(word);
                //If word doesn't exist in indexWord
                if(temp == nullptr)
                {
                    vector<DocumentInfo*> document;
                    //Inserts DocumentInfo to vector<DocumentInfo*> document;
                    document.push_back(&docParser.documents.at(i));
                    //Adds word and vector<DocumentInfo*> document to index AVL tree
                    indexWord.insert(word, document);
                    totalWords++;
                }
                else
                {
                    //Add new document to be associated with the word
                    temp->push_back(&docParser.documents.at(i));
                }
            }
            //If word is in the stop word avl tree
            else
            {
                //Move on to next
                token = strtok(nullptr, delim);
                continue;
            }
            token = strtok(nullptr, delim);
        }
        for(int j = 0; j < docParser.documents.at(i).name.size(); j++)
        {
            string name = docParser.documents.at(i).name.at(j);
            string str(name);
            char const* const delim{" "};
            char *token;
            token = strtok( &str[0], delim);
            while(token != nullptr) {
                //Assigns char token to word
                string word = token;
//                temp = indexPeople.get(word);
                Porter2Stemmer::trim(word);
                temp = indexPeople.search(word);
                if (temp == nullptr) {
                    vector<DocumentInfo *> document;
                    document.push_back(&docParser.documents.at(i));
                    indexPeople.insert(word, document);
                    totalPersons++;
                }
                else {
                    temp->push_back(&docParser.documents.at(i));
                }
                token = strtok(nullptr, delim);
            }
        }
        for(int k = 0; k < docParser.documents.at(i).org.size(); k++)
        {
            string org = docParser.documents.at(i).org.at(k);
            string str(org);
            char const* const delim{" "};
            char *token;
            token = strtok( &str[0], delim);
            while(token != nullptr) {
                //Assigns char token to word
                string word = token;
//                temp = indexOrg.get(word);
                Porter2Stemmer::trim(word);
                temp = indexOrg.search(word);
                if (temp == nullptr) {
                    vector<DocumentInfo *> document;
                    document.push_back(&docParser.documents.at(i));
                    indexOrg.insert(word, document);
                    totalOrgs++;
                }
                else {
                    temp->push_back(&docParser.documents.at(i));
                }
                token = strtok(nullptr, delim);
            }
        }
        //Assigns each document their word count
        docParser.documents.at(i).wordCount = wordCount;
        //Move on to next document
    }
    //Data for final demo output
    averageWordCount = averageWordCount / docParser.documents.size();
}

/**
 * Takes an array of stopwords, trims and stems them, and then inserts them into the related index
 */
void invertIndex::createStopWordIndex() {
 //   fstream stopFile("/home/ethanchou1/22s-final-project-cs2341searchengine2/stopwords.txt");
 //Temporarily stored stopwords into array because don't know if demo will allow other files to be accessed other than dataset
    string stopArray[636] =
            {"able", "about", "above", "abroad", "according", "accordingly", "across","actually", "adj", "after",
             "afterwards", "again", "against", "ago","ahead", "ain't", "all", "allow", "allows", "almost", "alone", "along", "alongside",
             "already", "also", "although", "always", "am", "amid", "amidst", "among", "amongst","an", "and", "another", "any",
             "anybody", "anyhow", "anyone", "anything", "anyways","anyway", "anywhere", "apart", "appear", "appreciate", "appropriate", "are", "aren't",
             "around", "as", "a's", "aside", "ask", "asking", "associated", "at", "available","away", "awfully", "back", "backward",
             "backwards", "be", "became", "because", "become","becomes", "becoming", "been", "before", "beforehand", "begin", "behind", "being", "believe",
             "below", "beside", "besides", "best", "better", "between", "beyond", "both", "brief","but", "by","came", "can", "cannot",
             "cant", "can't", "caption", "cause", "causes", "certain","certainly", "changes", "clearly", "c'mon", "co", "co.",
             "com", "come", "comes", "concerning","consequently", "consider", "considering", "contain", "containing",
             "contains", "corresponding", "could","couldn't", "course", "c's", "currently", "dare", "daren't",
             "definitely", "described", "despite", "did","didn't", "different", "directly", "do", "does", "doesn't", "doing", "done", "don't",
             "down", "downwards", "during", "each", "edu", "eg", "eight", "eighty", "either","else","elsewhere",
             "end","ending", "enough", "entirely", "especially", "et", "etc", "even", "ever", "evermore", "every", "everybody",
             "everyone", "everything", "everywhere", "ex", "exactly", "example", "except","fairly", "far", "farther", "few", "fewer",
             "fifth", "first", "five","followed", "following", "follows", "for", "forever", "former", "formerly", "forth",
             "forward", "found", "four" ,"from", "further", "furthermore", "get", "gets", "getting", "given", "gives", "go",
             "goes", "going", "gone", "got", "gotten", "greetings", "had", "hadn't", "half", "happens", "hardly", "has", "hasn't",
             "have", "haven't", "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein",
             "here's", "hereupon", "hers", "herself", "he's", "hi", "him" ,"himself", "his", "hither", "hopefully",
             "how", "howbeit", "however", "hundred", "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate", "in",
             "inasmuch", "inc", "inc.", "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into",
             "inward", "into", "inward", "is", "isn't", "it", "it'd", "it'll", "its", "it's", "itself", "i've", "just",
             "k", "keeps", "keeps", "kept", "know", "known", "knows", "last", "lately", "later", "latterly", "least",
             "less", "lest", "let's", "let", "like", "likely", "liked", "likewise", "little", "look", "looking", "looks", "low",
             "lower", "ltd", "made", "mainly", "make", "makes", "many", "may", "maybe", "mayn't", "me", "mean", "meantime", "meanwhile", "merely",
             "might", "might", "mightn't", "mine", "minus", "miss", "more", "moreover", "most", "mostly", "mr", "mrs",
             "much", "must", "mustn't", "my", "myself", "name", "namely", "nd", "near", "nearly", "necessary", "need",
             "needn't", "needs", "neither", "never", "neverf", "neverless", "nevertheless", "new", "next", "nine", "ninety",
             "no", "nobody", "non", "none", "nonetheless", "noone", "no-one", "nor", "normally", "not", "nothing", "notwithstanding",
             "novel", "nowhere", "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one",
             "ones", "one's", "only", "onto", "opposite", "or", "others", "other", "otherwise", "ought", "oughtn't", "our", "ours", "ourselves",
             "out", "outside", "over", "overall", "own", "particular", "particularly", "past", "per", "perhaps", "placed",
             "please", "plus", "possible", "presumably", "probably", "provided", "provides", "que", "quite", "qv", "rather",
             "rd", "re", "really", "reasonably", "recent", "recently", "regarding", "regardless", "regards", "relatively", "respectively",
             "right", "round", "said", "same", "saw", "say", "saying", "says", "second", "secondly", "see", "seeing", "seem", "seeming",
             "seems", "seen" ,"self", "selves", "sensible", "sent", "serious", "seriously", "seven", "several", "shall", "shan't",
             "she", "she'd", "she'll", "she's", "should", "shouldn't", "since", "since", "six", "so", "some", "somebody", "someday",
             "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon" ,"sorry", "specified", "specify",
             "specifying", "still" ,"sub", "such", "sup" ,"sure", "take", "taken", "taking", "tell", "tends", "th", "than",
             "thank", "thanks", "thanx", "that", "that'll", "thats", "that's", "that've", "the", "their", "theirs", "them",
             "themselves", "then", "thence", "there", "thereafter", "thereby", "there'd", "therefore", "therein", "there'll",
             "there're", "theres", "there's", "thereupon", "there've", "these", "they", "they'd", "they'll", "they're", "they've",
             "thing", "things", "think", "third", "thirty", "this", "thorough", "thoroughly", "those", "though", "three",
             "through", "throughout", "thru", "thus", "till", "to", "together", "too", "took", "toward", "towards", "tried",
             "tries", "truly", "try", "trying", "t's", "twice", "two", "un", "under", "underneath", "undoing", "unfortunately",
             "unless", "unlike", "unlikely", "until", "unto", "up", "upon", "upwards", "us", "use", "used", "useful", "uses",
             "using", "usually", "v", "value", "various", "versus", "very", "via", "viz", "vs", "want", "wants", "was",
             "wasn't", "way", "we", "we'd", "welcome", "well", "we'll", "went", "were", "we're", "weren't", "we've", "what",
             "whatever", "what'll", "what's", "what've", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "where's",
             "whereupon", "wherever", "whether", "which", "whichever", "while", "whilst", "whither", "who", "who'd", "whoever", "whole",
             "who'll", "whom", "whomever", "who's", "whose", "why", "will", "willing", "wish", "with", "within", "without", "wonder",
             "won't", "would", "wouldn't", "yes", "yet", "you", "you'd", "you'll", "your", "you're", "yours", "yourself", "yourselves",
             "you've", "zero"};
//    while(!stopFile.eof())
//    {
//        string stopWord;
//        getline(stopFile, stopWord);
//        Porter2Stemmer::trim(stopWord);
//        Porter2Stemmer::stem(stopWord);
//        stopWords.insert(stopWord, 1);
//    }
    for(auto & i : stopArray)
    {
        string stopWord;
        stopWord = i;
        Porter2Stemmer::trim(stopWord);
        Porter2Stemmer::stem(stopWord);
        stopWords.insert(stopWord, 1);
    }
}

/**
 * Indexes files from a certain directory and also times the process
 * @param nameDirectory the directory the files are contained within
 */
invertIndex::invertIndex(const string& nameDirectory) : docParser(nameDirectory), indexWord(), indexPeople(), indexOrg(), totalWords(), averageWordCount(){
    chrono::time_point<chrono::high_resolution_clock> start, end;
    //Starts timer
    start = chrono::high_resolution_clock::now();
    cout << "Starting index...." << endl;
    //Create avl tree of stop words
    createStopWordIndex();
    createIndex();
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> time_in_seconds = end - start;
    cout << fixed << "Indexed in " << time_in_seconds.count() << " seconds." << endl;
}

/**
 * Searches the index for a certain word and returns all of the documents which contain that word
 * @param list container of documents to store documents in
 * @param word selected word to search for
 */
void invertIndex::searchSingleWord(vector<DocumentInfo*>& list, string word) {
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    bool wordFound = true;
    //If word does not exist, quit program
    if(!indexWord.contains(word)){
        cout << "Word not found: " <<  word << endl;
        wordFound = false;
    }
    if(wordFound)
    {
        //Assigns vector<DocumentInfo*>*documents with vector of documents containing the search word
        vector<DocumentInfo*>*documents = indexWord.get(word);
        //Empty vector to have DocumentInfo pushed into
        for(int i = 0; i < documents->size(); i++)
        {
            bool inDocuments = false;
            //Iterates through temp vector
            for(int j = 0; j < list.size(); j++)
            {
                if(list[j] == documents->at(i))
                {
                    //If both temp and document are equal, means document is already in temp so don't add
                    inDocuments = true;
                    //Quit loop and move on
                    break;
                }
            }
            //If it isn't already in temp vector
            if(!inDocuments)
            {
                //Add to temp vector
                list.push_back(documents->at(i));
            }
        }
    }
}

/**
 * Clears all of the indices of words, people, orgs, etc. Also resets all stats to 0
 */
void invertIndex::deleteIndex() {
    indexWord.clear();
    indexPeople.clear();
    indexOrg.clear();
    totalWords = 0;
    totalPersons = 0;
    totalOrgs = 0;
    averageWordCount = 0;
}

/**
 * Re-indexes for the search engine
 */
void invertIndex::repopulate() {
    deleteIndex();
    chrono::time_point<chrono::high_resolution_clock> start, end;
    //Starts timer
    start = chrono::high_resolution_clock::now();
    cout << "Starting index...." << endl;
    createIndex();
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> time_in_seconds = end - start;
    cout << fixed << "Indexed in " << time_in_seconds.count() << " seconds." << endl;
    cout << endl;
}

/**
 * Method for AND operator for searching
 * @param list container of documents to store documents in
 * @param word selected word to search for
 * @param secondRun determines if should use existing vector or new vector
 */
void invertIndex::searchQueryAnd(vector<DocumentInfo *> &list, string word, bool secondRun) {
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    bool wordFound = true;
    //If word does not exist, quit program
    if(!indexWord.contains(word)){
        vector<DocumentInfo*> empty;
        list = empty;
        cout << "Word not found: " <<  word << endl;
        wordFound = false;
    }
    if(wordFound && secondRun == false)
    {
        //Assigns vector<DocumentInfo*>*documents with vector of documents containing the search word
        vector<DocumentInfo*>*documents = indexWord.get(word);
        //Empty vector to have DocumentInfo pushed into
        for(int i = 0; i < documents->size(); i++)
        {
            bool inDocuments = false;
            //Iterates through temp vector
            for(int j = 0; j < list.size(); j++)
            {
                if(list[j] == documents->at(i))
                {
                    inDocuments = true;
                    break;
                }
            }
            if(!inDocuments)
            {
                list.push_back(documents->at(i));
            }
        }
    }
    else if(wordFound && secondRun == true)
    {
        vector<DocumentInfo*>*documents = indexWord.get(word);
        //Empty vector to have DocumentInfo pushed into
        vector<DocumentInfo *> temp;
        for(int i = 0; i < documents->size(); i++)
        {
            bool inDocuments = false;
            //Iterates through temp vector
            for(int j = 0; j < temp.size(); j++)
            {
                if(temp[j] == documents->at(i))
                {
                    inDocuments = true;
                    break;
                }
            }
            if(!inDocuments)
            {
                //Add to temp vector
                temp.push_back(documents->at(i));
            }
        }
        vector<DocumentInfo *> tempTwo;
        for(int i = 0; i < list.size(); i++)
        {
            bool inDocuments = false;
            //Iterates through temp vector
            for(int j = 0; j < temp.size(); j++)
            {
                if(temp[j] == list.at(i))
                {
                    inDocuments = true;
                    break;
                }
            }
            if(inDocuments)
            {
                //Add to temp vector
                tempTwo.push_back(list.at(i));
            }
        }
        list = tempTwo;
    }
}

/**
 * Method for OR operator for search engine
 * @param list container of documents to store documents in
 * @param word selected word to search for
 */
void invertIndex::searchQueryOr(vector<DocumentInfo *> &list, string word) {
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    bool wordFound = true;
    //If word does not exist, quit program
    if(!indexWord.contains(word)){
        cout << "Word not found: " <<  word << endl;
        wordFound = false;
    }
    if(wordFound)
    {
        //Assigns vector<DocumentInfo*>*documents with vector of documents containing the search word
        vector<DocumentInfo*>*documents = indexWord.get(word);
        //Empty vector to have DocumentInfo pushed into
        for(int i = 0; i < documents->size(); i++)
        {
            bool inDocuments = false;
            //Iterates through temp vector
            for(int j = 0; j < list.size(); j++)
            {
                if(list[j] == documents->at(i))
                {
                    //If both temp and document are equal, means document is already in temp so don't add
                    inDocuments = true;
                    //Quit loop and move on
                    break;
                }
            }
            //If it isn't already in temp vector
            if(!inDocuments)
            {
                //Add to temp vector
                list.push_back(documents->at(i));
            }
        }
    }
}
/**
 * Method for NOT operator for search engine
 * @param list container of documents to store documents in
 * @param word selected word to not search for
 */
void invertIndex::searchQueryNot(vector<DocumentInfo*> &list, string word){
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    bool wordFound = true;
    //If word does not exist, quit program
    if(!indexWord.contains(word)){
        cout << "Word not found: " <<  word << endl;
        wordFound = false;
    }
    if(wordFound)
    {
        //Assigns vector<DocumentInfo*>*documents with vector of documents containing the search word
        vector<DocumentInfo*>*documents = indexWord.get(word);
        //Empty vector to have DocumentInfo pushed into
        vector<DocumentInfo *> tempTwo;
        for(int i = 0; i < list.size(); i++)
        {
            bool inDocuments = false;
            for(int j = 0; j < documents->size(); j++)
            {
                if(list[i] == documents->at(j))
                {
                    inDocuments = true;
                    break;
                }
            }
            if(!inDocuments)
            {
                tempTwo.push_back(list.at(i));
            }
        }
        list = tempTwo;
    }
}

/**
 * Method for PERSON operator for search engine
 * @param list container of documents to store documents in
 * @param word selected word to search for
 */
void invertIndex::searchQueryPerson(vector<DocumentInfo*> &list, string word){
    bool wordFound = true;
    //If word does not exist, quit program
//    if(!indexPeople.contains(word)){
//        cout << "Word not found: " <<  word << endl;
//        wordFound = false;
//    }
    Porter2Stemmer::trim(word);
    if(!indexPeople.search(word)){
        vector<DocumentInfo*> empty;
        list = empty;
        cout << "Word not found: " <<  word << endl;
        wordFound = false;
    }
    if(wordFound) {
//        vector<DocumentInfo *> *documents = indexPeople.get(word);
        vector<DocumentInfo *> *documents = indexPeople.search(word);
        //Empty vector to have DocumentInfo pushed into
        vector<DocumentInfo *> temp;
        for (int i = 0; i < documents->size(); i++) {
            bool inDocuments = false;
            //Iterates through temp vector
            for (int j = 0; j < temp.size(); j++) {
                if (temp[j] == documents->at(i)) {
                    inDocuments = true;
                    break;
                }
            }
            if (!inDocuments) {
                //Add to temp vector
                temp.push_back(documents->at(i));
            }
        }
        vector<DocumentInfo *> tempTwo;
        for (int i = 0; i < list.size(); i++) {
            bool inDocuments = false;
            //Iterates through temp vector
            for (int j = 0; j < temp.size(); j++) {
                if (temp[j] == list.at(i)) {
                    inDocuments = true;
                    break;
                }
            }
            if (inDocuments) {
                //Add to temp vector
                tempTwo.push_back(list.at(i));
            }
        }
        list = tempTwo;
    }
}

/**
 * Method for ORG operator for search engine
 * @param list container of documents to store documents in
 * @param word selected word to search for
 */
void invertIndex::searchQueryOrg(vector<DocumentInfo*> &list, string word)
{
    bool wordFound = true;
    //If word does not exist, quit program
//    if(!indexOrg.contains(word))
//    {
//        cout << "Word not found: " <<  word << endl;
//        wordFound = false;
//    }
    Porter2Stemmer::trim(word);
    if(!indexOrg.search(word))
    {
        vector<DocumentInfo*> empty;
        list = empty;
        cout << "Word not found: " <<  word << endl;
        wordFound = false;
    }
    if(wordFound)
    {
//        vector<DocumentInfo*> *documents = indexOrg.get(word);
        vector<DocumentInfo*> *documents = indexOrg.search(word);
        //Empty vector to have DocumentInfo pushed into
        vector<DocumentInfo*> temp;
        for (int i = 0; i < documents->size(); i++)
        {
            bool inDocuments = false;
            //Iterates through temp vector
            for (int j = 0; j < temp.size(); j++)
            {
                if (temp[j] == documents->at(i))
                {
                    inDocuments = true;
                    break;
                }
            }
            if (!inDocuments)
            {
                //Add to temp vector
                temp.push_back(documents->at(i));
            }
        }
        vector<DocumentInfo*> tempTwo;
        for (int i = 0; i < list.size(); i++)
        {
            bool inDocuments = false;
            //Iterates through temp vector
            for (int j = 0; j < temp.size(); j++)
            {
                if (temp[j] == list.at(i))
                {
                    inDocuments = true;
                    break;
                }
            }
            if (inDocuments)
            {
                //Add to temp vector
                tempTwo.push_back(list.at(i));
            }
        }
        list = tempTwo;
    }
}

/**
 * Iterates over a vector of DSAVLNodes created from getMostPopularWords() method in DSAVLTree
 * Finds the most popular word and outputs it, then deletes that node from the vector so that the next
 * most popular word can appear
 * @return list of most popular words
 */
vector<DSAVLNode<string, vector<DocumentInfo *>>> invertIndex::mostPopularWords() {
    vector<DSAVLNode<string, vector<DocumentInfo *>>> list = indexWord.getMostPopularWords();
    vector<DSAVLNode<string, vector<DocumentInfo *>>> temp;
    int count;
    int index;
    bool skipNull = false;
    for(int i = 0; i < 26; i++)
    {
        int tempNum = 0;
        for(int j = 0; j < list.size(); j++){
            count = list[j].getValue().size();
            if(count > tempNum)
            {
                //Gets highest value
                tempNum = count;
                index = j;
            }
            if(j == list.size() - 1 && !skipNull)
            {
                //Erases null character
                list.erase(list.begin() + index);
                skipNull = true;
            }
            if(j == list.size() - 1 && skipNull)
            {
                //Outputs most popular word, then removes it from index
//                cout << "\t" << list[index].getKey() << " " << list[index].getValue().size() << endl;
                temp.push_back(list[index]);
                list.erase(list.begin() + index);
            }
        }
    }
    return temp;
}

/**
 * Method for determining and ranking the relevancy of documents returned for a search query
 * @param list list of documents returned by a specific query
 * @param wordList the search query inputted by the user
 */
void invertIndex::relevancyCalc(vector<DocumentInfo*> &list, vector<string>& wordList) {
    vector<double> documentRelevancyScore;
    vector<DocumentInfo*> temp;
    documentRelevancyScore.reserve(list.size());
    //Assigns a score for each document
    for (int i = 0; i < list.size(); i++) {
        int counter = 0;
        std::vector<std::string> listOfWords = wordList;
        for(int j = 0; j < listOfWords.size(); j++){
            Porter2Stemmer::trim(listOfWords.at(j));
            Porter2Stemmer::stem(listOfWords.at(j));
        }
        //Term Frequency - Inverse Document Frequency calculator
        for(int j = 0; j < listOfWords.size(); j++){
            std::vector<DocumentInfo*> *documentsFromWord = indexWord.get(listOfWords.at(j));
            if(documentsFromWord != nullptr)
            {
                for(int k = 0; k < documentsFromWord->size(); k++){
                    if(documentsFromWord->at(k) == list.at(i)){
                        counter++;
                    }
                }
            }
            else
            {
                continue;
            }
        }
        double score = (double) counter / (double)list.at(i)->wordCount;
        //Adds score to vector
        documentRelevancyScore.push_back(score);
    }
    double score;
    int index;
    int size = list.size();
    //Iterates through size
    for(int k = 0; k < size; k++)
    {
        double tempNum = 0;
        //Iterates through vector of doubles score
        for(int j = 0; j < documentRelevancyScore.size(); j++){
            score = documentRelevancyScore[j];
            //Gets highest value
            if(score > tempNum)
            {
                tempNum = score;
                index = j;
            }
            if(j == documentRelevancyScore.size() - 1)
            {
                //Adds to temp vector
                temp.push_back(list.at(index));
                //Deletes from both documentRelevancyScore and list so that values won't get repeated and each index in both vectors
                //still correspond to each other
                documentRelevancyScore.erase(documentRelevancyScore.begin() + index);
                list.erase(list.begin() + index);
            }
        }
    }
    list = temp;
}

