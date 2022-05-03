//
// Created by ethan on 4/5/2022.
//
/*  The parseDocument.cpp file contains the implementations for the methods defined in parseDocument.h.
 */

#include "parseDocument.h"
#include <string>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include <filesystem>
#include "DocumentInfo.h"
#include <fstream>
#include <future>
namespace fs = std::filesystem;
//https://en.cppreference.com/w/cpp/experimental/fs/directory_iterator for parsing directory
/**
 * Extracts the names, titles, organizations, text, people, etc. of each json document
 * @param nameDirectory the directory of the desired file
 */
parseDocument::parseDocument(const string& nameDirectory) {
    chrono::time_point<chrono::high_resolution_clock> start, end;
    //Starts timer
    start = chrono::high_resolution_clock::now();
    cout << "Starting parse...." << endl;
    for (const auto & entry : fs::recursive_directory_iterator(nameDirectory)){
        if(entry.path().extension().string() != ".json"){
            continue;
        }
        ifstream file(entry.path().c_str());
//        cout << entry.path().c_str() << endl;     For Debugging
        string jsonFile((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        rapidjson::Document readDocument;
        readDocument.Parse(jsonFile.c_str());
        rapidjson::Value &id = readDocument["uuid"];
        rapidjson::Value &title = readDocument["title"];
        rapidjson::Value &body = readDocument["text"];
        rapidjson::Value  &date = readDocument["published"];
        vector<string> names;
        vector<string> orgs;
        const rapidjson::Value& persons = readDocument["entities"]["persons"];
        for (auto &a : readDocument["entities"]["persons"].GetArray())
        {
            names.emplace_back(a["name"].GetString());
        }
        for (auto &a : readDocument["entities"]["organizations"].GetArray())
        {
            orgs.emplace_back(a["name"].GetString());
        }
        DocumentInfo doc(id.GetString(), title.GetString(), names, orgs, body.GetString(), date.GetString());
        documents.push_back(doc);
    }
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> time_in_seconds = end - start;
    cout << fixed << "Parsed in " << time_in_seconds.count() << " seconds." << endl;
}

/**
 * Does the same extraction as the method above again -- use for eventual user interface loop
 * @param nameDirectory the directory of the desired file
 */
void parseDocument::parseAgain(const string& nameDirectory) {
    documents.clear();
    chrono::time_point<chrono::high_resolution_clock> start, end;
    //Starts timer
    start = chrono::high_resolution_clock::now();
    cout << "Starting parse...." << endl;
    for (const auto & entry : fs::recursive_directory_iterator(nameDirectory)){
        if(entry.path().extension().string() != ".json"){
            continue;
        }
        ifstream file(entry.path().c_str());
        string jsonFile((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        rapidjson::Document readDocument;
        readDocument.Parse(jsonFile.c_str());
        rapidjson::Value &id = readDocument["uuid"];
        rapidjson::Value &title = readDocument["title"];
        rapidjson::Value &body = readDocument["text"];
        rapidjson::Value  &date = readDocument["published"];
        vector<string> names;
        vector<string> orgs;
        const rapidjson::Value& persons = readDocument["entities"]["persons"];
        for (auto &a : readDocument["entities"]["persons"].GetArray())
        {
            names.emplace_back(a["name"].GetString());
        }
        for (auto &a : readDocument["entities"]["organizations"].GetArray())
        {
            orgs.emplace_back(a["name"].GetString());
        }
        DocumentInfo doc(id.GetString(), title.GetString(), names, orgs, body.GetString(), date.GetString());
        documents.push_back(doc);
    }
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> time_in_seconds = end - start;
    cout << fixed << "Parsed in " << time_in_seconds.count() << " seconds." << endl;
}
