//CS 211 - Project 4: Popular Vote Minimizer

//Author(s): Niharika Patil, starter code given by Dr. Ellen Kidane and Dr. Scott Reckinger

//Project Description: This project is looking at a certain pert of voting in the US, where each of the 50 states, plus DC, gets some number of electors in the Electoral College, and whoever they vote in becomes the next President. This project seeks to look at elector and popular votes through slow and fast recursion and memoization.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

//this function is developing the settings based on the command line arguements that the user provides
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    //------------------------------------------------   
    *fastMode = false;
    *quietMode = false;
    *year = 0;
    for (int i = 1; i < argc; i++){
        //checks if the user set either a "-y", "-q", or "-f"
        if (argv[i][0] == '-'){
            if (strcmp(argv[i], "-y") == 0){
                if ((atoi(argv[i+1]) < 1828) && (atoi(argv[i+1]) > 2020) || (atoi(argv[i+1]) % 4)){
                    *year = 0; // if the user enters no year
                }
                else {
                    *year = atoi(argv[i+1]); 

                }
                ++i;
            }

            //sets the quiet or fast mode if given in command line
            else if (strcmp(argv[i], "-q") == 0){
                *quietMode = true;
            }

            else if (strcmp(argv[i], "-f") == 0){
                *fastMode = true;
            }
            else{
                return false;
            }
            
        }
    }

    return true; 
}

//this function is setting the file name based on the year that the user gave, assuming user gave a valid year
void inFilename(char* filename, int year) {
    //------------------------------------------------   
    char fileFolder[100] = "";
    char strYear[20];
    sprintf(strYear, "%d", year); //changes the year to a string
    strcpy(fileFolder, strYear);
    strcat(fileFolder, ".csv");
    strcpy(filename, fileFolder); //puts all concatention into the file name
    //------------------------------------------------
    return;
}

//sets the file based on a valid year provided which all stats and data will be written to
void outFilename(char* filename, int year) {
    //------------------------------------------------   
    char fileFolder[100] = "toWin/";
    char strYear[20];
    sprintf(strYear, "%d", year); //changes the year to a string
    strcat(fileFolder, strYear);
    strcat(fileFolder, "_win.csv");
    strcpy(filename, fileFolder); //puts all concatention into the file name
    //------------------------------------------------
    return;
}

//this function parses through each line within a valid infile name, and updates all subitems within each state
bool parseLine(char* line, State* myState) {
    if (line[strlen(line) - 1] == '\n'){
        line[strlen(line) - 1] == '\0'; //changes newline character into null to parse uptill newline
    }

    int numOfCommas = 0;
    char strArr[50] = "";
    int counter = 0;
    
    //checks if there are 3 commas, meaning the line is valid to parse through
    for (int i = 0; i < strlen(line); i++){
        if (line[i] == ','){
            numOfCommas += 1;
        }
    }

    if (numOfCommas != 3){
        return false;
    }

    //uses strtok to parse through each section, with the comma being the delimiter
    char *temp_string = strtok(line,",");
    while(temp_string != NULL){
        //adds each section in the line that strtok goes until and adds onto the state's subitem
        if(counter == 0){ //state name
            strcpy((*myState).name,temp_string); 
        }
        else if(counter == 1){ //postal code
            strcpy((*myState).postalCode,temp_string); 
        }
        else if(counter == 2){ //electoral votes
            (*myState).electoralVotes = atoi(temp_string); 
        }
        else if(counter == 3){ //popular votes
            (*myState).popularVotes = atoi(temp_string);
        }
        counter++;
        temp_string = strtok(NULL,",");
    }
    return true;
}

//this function opens the file name and uses the parseLine function to read each line in the files
bool readElectionData(char* filename, State* allStates, int* nStates) {
    //-----------------------------------------------------
    *nStates = 0;   
    //reads each file in the given file
    FILE* filePtr = NULL; 
    filePtr = fopen(filename, "r");

    if(filePtr == NULL){
        return false;
    }

    char str[50];
    //goes through each line, calling parseLine each time that a line is read
    while ((!feof(filePtr)) && (fgets(str, 50, filePtr) != NULL)){
        parseLine(str, &(allStates[*nStates]));
        *nStates += 1; //increments the number of states that have been read
    }
    fclose(filePtr);
    return true; 
    //-----------------------------------------------------
}

//calculates the total electoral votes that was read from the file
int totalEVs(State* states, int szStates) {
    //----------------------------------------------   
   
    int totalElectoralVote = 0;
    for (int i = 0; i < szStates; i++){
        totalElectoralVote += (states[i]).electoralVotes;
    }
    //----------------------------------------------
    return totalElectoralVote; //total number electoral votes read
}

//similar to totalEVs, but this time, reads and calculates the total popular votes
int totalPVs(State* states, int szStates) {
    //--------------------------------------------------   
    int totalPopularVote = 0;
    for (int i = 0; i < szStates; i++){
        totalPopularVote += (states[i]).popularVotes;
    }
    //--------------------------------------------------
    return totalPopularVote; //total number popular votes read
}

//this function is a recursive function, which calculates the minimum popular votes with sufficient EV's needed to win
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    //----------------------------------------------   
    
    MinInfo include;
    MinInfo exclude;

    if (EVs <= 0){ //if electoral votes is 0 or negative, then it will not be calcuated
        include.szSomeStates = 0;
        include.subsetPVs = 0;
        include.sufficientEVs = true;
        return include;
    }

    //if the index is the same as the size of states
    if (start == szStates){
        include.szSomeStates = 0;
        include.subsetPVs = 0;
        include.sufficientEVs = false;
        return include;
    }

    //includes the states needed to be calculated
    include = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);

    //calculate the popular votes based on the index
    include.subsetPVs += ((states[start].popularVotes / 2) + 1);
    include.someStates[include.szSomeStates] = states[start];
    include.szSomeStates++;
    
    //excludes any states that exceed the calculation
    exclude = minPopVoteAtLeast(states, szStates, start + 1, EVs);
    if ((exclude.sufficientEVs == true) && (exclude.subsetPVs < include.subsetPVs)){ //checks if there are sufficient PVs and EVs
        return exclude;
    }else{
        return include;
    }
     
    //---------------------------------------------- 
    return include;
}



MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

//This function is the faster version of recursion using memoization to calculate PVs with sufficient EVs
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    //----------------------------------------------   
    
    MinInfo include;
    MinInfo exclude;

    if (EVs <= 0){
        include.szSomeStates = 0;
        include.subsetPVs = 0;
        include.sufficientEVs = true;
        return include;
    }
    if (start == szStates){
        include.szSomeStates = 0;
        include.subsetPVs = 0;
        include.sufficientEVs = false;
        return include;
    }

    //checks if the subsetPVs subitem value of that memo element is no longer -1, then it has already been calculated
    if (memo[start][EVs].subsetPVs != -1){
        return memo[start][EVs]; //adds into memo, an array of State struct containing all states from a file
    }
    

    //will check and return include and exclude if PVs have been met based on EVs
    include = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);

    include.subsetPVs += ((states[start].popularVotes / 2) + 1);
    include.someStates[include.szSomeStates] = states[start];
    include.szSomeStates++;
    
    exclude = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);
    if ((exclude.sufficientEVs == true) && (exclude.subsetPVs < include.subsetPVs)){
        memo[start][EVs] = exclude;
        return exclude;
    }else{
        memo[start][EVs] = include;
        return include;
    }
     
    //---------------------------------------------- 
    return memo[start][EVs];
    //---------------------------------------------- 
    
}

MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    
    //----------------------------------------------   
    //frees all allecated memory on heap to prevent memeory leaks 

    for (int i = 0; i < szStates + 1; i++){
        free(memo[i]);
    }
    free(memo);
    //---------------------------------------------- 

    return res;
}

//writes all stats and data calculated from past functions onto the toWin files, the out files
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    //-----------------------------------------------------   
    
    FILE* filePtr = NULL; 
    filePtr = fopen(filenameW, "w"); //file reads and adds writes to the file

    if(filePtr == NULL){ 
        return false;
    }

    //adds each specific data item to the outfile, including total EVs and PVs, sufficient EVs, and subset PVs calculated from task 7/8
    fprintf(filePtr, "%d, %d, %d, %d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);
    for (int i = toWin.szSomeStates - 1; i >= 0; i--){
        fprintf(filePtr, "%s, %s, %d, %d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, toWin.someStates[i].electoralVotes, ((toWin.someStates[i].popularVotes / 2) + 1));
    }
   
    fclose(filePtr);

    //-----------------------------------------------------
    return true;
}
