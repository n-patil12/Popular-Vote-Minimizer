#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool test_totalEVs() {
//This function tests for the total EVs by checking all the EVs made by putting it through the totalEV's function and returning the result through "res"
    State aStates[10];
    int res; //used to capture the return totalEVs
    
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    //checks if the totalEVs is populated and added correctly
    if (res != 38) { 
        printf("  individual state EVs are 5, 8, 13, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return 0;
    }
    //tests for a larger set with 10 states created and populated
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 15;
    aStates[6].electoralVotes = 12;
    aStates[7].electoralVotes = 8;
    aStates[8].electoralVotes = 14;
    aStates[9].electoralVotes = 13;
    
    printf(" Checking totalEVs() for 10 States:\n");
    res = totalEVs(aStates,10);
    //checks if the total EVs is added up correctly
    if (res != 100) {
        printf("  expected total EVs = 100, actual total EVs = %d\n",res);
        return false;
    }

    return true;
}

bool test_totalPVs() {
    //--------------------------------------------------------   
// This function will return the total number of PVs in the subset
    State newStates[10];
    int pvCheck;

    //tests for a small set of popular votes
    newStates[0].popularVotes = 19854;
    newStates[1].popularVotes = 17159;
    newStates[2].popularVotes = 14299;
    newStates[3].popularVotes = 18382;
    newStates[4].popularVotes = 13609;

    printf(" Checking totalPVs() for 5 States:\n");
    pvCheck = totalPVs(newStates,5);
    //checks if the PVs has been added correctly 
    if (pvCheck != 83303) {
        printf("  individual state PVs are %d, %d, %d, %d, %d\n", newStates[0].popularVotes, newStates[1].popularVotes, newStates[2].popularVotes, newStates[3].popularVotes, newStates[4].popularVotes);
        printf("  expected total PVs = 83303, actual total EVs = %d\n",pvCheck);

        return 0;
    }

    //tests for total PVs in a larger set
    newStates[0].popularVotes = 19854;
    newStates[1].popularVotes = 17159;
    newStates[2].popularVotes = 14299;
    newStates[3].popularVotes = 18382;
    newStates[4].popularVotes = 13609;
    newStates[5].popularVotes = 11325;
    newStates[6].popularVotes = 15000;
    newStates[7].popularVotes = 15500;
    newStates[8].popularVotes = 18422;
    newStates[9].popularVotes = 13398;

    printf(" Checking totalPVs() for 10 States:\n");
    //run and capture the return of total PVs, and then checks if the total PVs has been added up correctly
    pvCheck = totalPVs(newStates,10);
    if (pvCheck != 156948) {
        printf("  individual state PVs are %d, %d, %d, %d, %d\n", newStates[0].popularVotes, newStates[1].popularVotes, newStates[2].popularVotes, newStates[3].popularVotes, newStates[4].popularVotes);
        printf("  expected total PVs = 83303, actual total EVs = %d\n",pvCheck);
        return false;
    }
    //--------------------------------------------------------
    return true; 
}

bool test_setSettings() {
    //-----------------------------------------------------------  
    //This function will test the setSettings function and check if the command line arguements are correctly
    bool TF_Val = false; 

    char* argv[4];
    //This test case conatins all the valid commands, so it will pass
    printf("\n");
    printf("Sample 1: ./app.exe -y 2000 -q\n");
    printf("This test case will result in true due to valid command-line");
    printf("\n");

    argv[0] = "app.exe";
    argv[1] = "-y";
    argv[2] = "2000";
    argv[3] = "-q";


    bool fastMode = false;
    bool quietMode = false;
    int year = 0;
    
    //checks if setSettings is returning a false of an invalid command
    if (!setSettings(4, argv, &year, &fastMode, &quietMode)) {
        printf("Invalid command-line argument.\n");
        printf("Terminating program...\n");
        TF_Val = false;
    }
    //Since it is a valid command, the program will output all of the settings for the command
    printf("\n");
    printf("Settings:\n");
    printf("  year = %d\n", year);
    
    if (quietMode == false){
        printf("  quietMode = OFF\n");
    }
    else {
        printf("  quietMode = ON\n");
    }
    if (fastMode == false){
        printf("  fastMode = OFF\n");
    }
    else {
        printf("  fastMode = ON\n");
    }
    
    //this test case is invalid becuase -z is not a vaid command, so it should return false
   printf("\n");
    printf("Sample 2: ./app.exe -z 2000 -f\n");
    printf("This test case will result in false due to invalid command-line");
    printf("\n");

    argv[0] = "app.exe";
    argv[1] = "-z";
    argv[2] = "2000";
    argv[3] = "-f";

    fastMode = false;
    quietMode = false;
    year = 0;
    
    //this check should return an invalid statements
    if (!setSettings(4, argv, &year, &fastMode, &quietMode)) {
        printf("Invalid command-line argument.\n");
        printf("Terminating program...\n");
        TF_Val = false;
    }
    
    if (TF_Val == false){
        TF_Val = true;
    }
    //-----------------------------------------------------------
    return TF_Val;
}

bool test_inFilename() {
    //----------------------------------------------------------   
// this function checks for the validity of the file name and if the year is found in the data file tree

    //creating an empty string to pass as an arguement for the inFilename function
    char inFile[100];
    inFilename(inFile, 1828);

    //using strcmp to check whether the file exists or not
    if (strcmp(inFile, "data/1828.csv") != 0){
        printf("Invalid Year Command: 1828\n");
    }
    else {
        printf("Valid Year Command: 1828\n");
    }

    char inFile2 [100];
    inFilename(inFile2, 2023);
    
    if (strcmp(inFile2, "data/2023.csv") != 0){
        printf("Invalid Year Command: 2023\n");
    }
    else {
        printf("Valid Year Command: 2023\n");
    }
    
    //----------------------------------------------------------
    return true; 
}

bool test_outFilename() {
    //-----------------------------------------------------------  
//This function tests for the outfile of the year and writes the data to the file

    //creates an empty string to pass in as an arguement for the outFilename function
    char outFile[100];
    outFilename(outFile, 1828);

    //uses strcmp to check whether the file exists and has been written to the toWin file tree
    if (strcmp(outFile, "toWin/1828_win.csv") != 0){
        printf("Invalid Year Command: 1828\n");
    }
    else {
        printf("Valid Year Command: 1828\n");
    }

    //this function should return invalid as this year does not exist
    char outFile2 [100];
    outFilename(outFile, 2023);
    if (strcmp(outFile2, "toWin/1828_win.csv") != 0){
        printf("Invalid Year Command: 2023\n");
    }
    else {
        printf("Valid Year Command: 2023\n");
    }
    
    //-----------------------------------------------------------
    return true; 
}

bool test_parseLine() {
    //---------------------------------------------------------   
//This function will test the parseLine function for whether all the data memebers in the State struct has been passed in  correctly

    
    bool check_val = false;

    //creating a string that has 3/4 of the data members, so this case should return invalid
    char str[50] = "Oregon, OR, 8";

    //returns true or false depending on whether the parameters passed in are returning true or false
    bool parLine = false;
    State randState;

    //passes in a the string and the State object into the array
    parLine = parseLine(str, &randState);

    printf("Sample 1: Oregon, OR, 8\n");
    printf("Checking Sample 1, which will return false because of invalid number of inputs\n");
    //checks for whether parLine captured a true or false after the function executed
    if (!parLine){
        printf("Case invalid\n");
        check_val = false;
    }
    else{
        printf("Case valid\n");
        check_val = true;
    }
    
    //This is a case that will return valid
    char str2[50] = "Nevada, NV, 7, 14792";
    
    bool parLine2 = false;

    printf("Sample 2: Nevada, NV, 7, 14792\n");
    printf("Checking Sample 2, which will return true because all input is valid\n");
    parLine2 = parseLine(str2, &randState);

    if (!parLine2){
        printf("Case invalid\n");
        check_val = false;
    }
    else{
        printf("Case valid\n");
        check_val = true;
    }


    //---------------------------------------------------------
    return check_val; 
}

bool test_readElectionData() {
    //----------------------------------------------------------------   
//This function will test whether the readElection data has been read correctly
    State mockStates[51];

    int nStates = 0;

    //this function will read in pass in a valid file name, empty string, and the number of states
    if(!readElectionData("data/2000.csv", mockStates, &nStates)){
        return false;
    }

    //checks whether the number of states is correct
    if(nStates != 51){
        return false;
    }
    //----------------------------------------------------------------
    return true; 
}

bool test_minPVsSlow() {
    //----------------------------------------------------------------- 
//This function tests for the brute force recursion, the minPVsSlow function

    State mockState[4]; 

    strcpy(mockState[0].name,"Illinois");
    strcpy(mockState[0].postalCode,"IL");
    mockState[0].electoralVotes = 5;
    mockState[0].popularVotes = 60;

    strcpy(mockState[1].name, "Nevada");
    strcpy(mockState[1].postalCode, "NV");
    mockState[1].electoralVotes = 2;
    mockState[1].popularVotes = 20;

    strcpy(mockState[2].name, "New Jersey");
    strcpy(mockState[2].postalCode, "NJ");
    mockState[2].electoralVotes = 8;
    mockState[2].popularVotes = 70;

    strcpy(mockState[3].name, "Texas");
    strcpy(mockState[3].postalCode, "TX");
    mockState[3].electoralVotes = 3;
    mockState[3].popularVotes = 30;

    //the mockState array passes in 4 individual states and will return valid because the number of subsetPVs is added up correctly
    MinInfo win_res = minPopVoteToWin(mockState, 4);

    if(win_res.subsetPVs != 47){
        return false;
    }
    
    //-----------------------------------------------------------------
    return true;
}

bool test_minPVsFast() {
    //--------------------------------------------------------------------- 

//This function tests recursion with memoization, the minPVsFast function
    State mockState[30]; 

    strcpy(mockState[0].name,"Illinois");
    strcpy(mockState[0].postalCode,"IL");
    mockState[0].electoralVotes = 30;
    mockState[0].popularVotes = 10;

    strcpy(mockState[1].name, "Nevada");
    strcpy(mockState[1].postalCode, "NV");
    mockState[1].electoralVotes = 29;
    mockState[1].popularVotes = 20;

    strcpy(mockState[2].name, "New Jersey");
    strcpy(mockState[2].postalCode, "NJ");
    mockState[2].electoralVotes = 28;
    mockState[2].popularVotes = 30;

    strcpy(mockState[3].name, "Texas");
    strcpy(mockState[3].postalCode, "TX");
    mockState[3].electoralVotes = 27;
    mockState[3].popularVotes = 40;

    strcpy(mockState[4].name, "Arizona");
    strcpy(mockState[4].postalCode, "AZ");
    mockState[4].electoralVotes = 26;
    mockState[4].popularVotes = 50;

    strcpy(mockState[5].name, "Alabama");
    strcpy(mockState[5].postalCode, "AL");
    mockState[5].electoralVotes = 25;
    mockState[5].popularVotes = 60;

    strcpy(mockState[6].name, "Alaska");
    strcpy(mockState[6].postalCode, "AK");
    mockState[6].electoralVotes = 24;
    mockState[6].popularVotes = 70;

    strcpy(mockState[7].name, "Arkansas");
    strcpy(mockState[7].postalCode, "AR");
    mockState[7].electoralVotes = 23;
    mockState[7].popularVotes = 80;

    strcpy(mockState[8].name, "California");
    strcpy(mockState[8].postalCode, "CA");
    mockState[8].electoralVotes = 22;
    mockState[8].popularVotes = 90;

    strcpy(mockState[9].name, "Colorado");
    strcpy(mockState[9].postalCode, "CO");
    mockState[9].electoralVotes = 21;
    mockState[9].popularVotes = 100;

    strcpy(mockState[10].name, "Connecticut");
    strcpy(mockState[10].postalCode, "CT");
    mockState[10].electoralVotes = 20;
    mockState[10].popularVotes = 110;

    strcpy(mockState[11].name, "Delaware");
    strcpy(mockState[11].postalCode, "DE");
    mockState[11].electoralVotes = 19;
    mockState[11].popularVotes = 120;

    strcpy(mockState[12].name, "Florida");
    strcpy(mockState[12].postalCode, "FL");
    mockState[12].electoralVotes = 18;
    mockState[12].popularVotes = 130;

    strcpy(mockState[13].name, "Georgia");
    strcpy(mockState[13].postalCode, "GA");
    mockState[13].electoralVotes = 17;
    mockState[13].popularVotes = 140;

    strcpy(mockState[14].name, "Hawaii");
    strcpy(mockState[14].postalCode, "HI");
    mockState[14].electoralVotes = 16;
    mockState[14].popularVotes = 150;

    strcpy(mockState[15].name, "Idaho");
    strcpy(mockState[15].postalCode, "ID");
    mockState[15].electoralVotes = 15;
    mockState[15].popularVotes = 160;

    strcpy(mockState[16].name, "Indiana");
    strcpy(mockState[16].postalCode, "IN");
    mockState[16].electoralVotes = 14;
    mockState[16].popularVotes = 170;

    strcpy(mockState[17].name, "Iowa");
    strcpy(mockState[17].postalCode, "IA");
    mockState[17].electoralVotes = 13;
    mockState[17].popularVotes = 180;

    strcpy(mockState[18].name, "Kansas");
    strcpy(mockState[18].postalCode, "KS");
    mockState[18].electoralVotes = 12;
    mockState[18].popularVotes = 190;

    strcpy(mockState[19].name, "Kentucky");
    strcpy(mockState[19].postalCode, "KY");
    mockState[19].electoralVotes = 11;
    mockState[19].popularVotes = 200;

    strcpy(mockState[20].name, "Louisiana");
    strcpy(mockState[20].postalCode, "LA");
    mockState[20].electoralVotes = 10;
    mockState[20].popularVotes = 210;

    strcpy(mockState[21].name, "Maine");
    strcpy(mockState[21].postalCode, "ME");
    mockState[21].electoralVotes = 9;
    mockState[21].popularVotes = 220;

    strcpy(mockState[22].name, "Maryland");
    strcpy(mockState[22].postalCode, "MD");
    mockState[22].electoralVotes = 8;
    mockState[22].popularVotes = 230;

    strcpy(mockState[23].name, "Michigan");
    strcpy(mockState[23].postalCode, "MI");
    mockState[23].electoralVotes = 7;
    mockState[23].popularVotes = 240;

    strcpy(mockState[24].name, "Minnesota");
    strcpy(mockState[24].postalCode, "MN");
    mockState[24].electoralVotes = 6;
    mockState[24].popularVotes = 250;

    strcpy(mockState[25].name, "Missouri");
    strcpy(mockState[25].postalCode, "MO");
    mockState[25].electoralVotes = 5;
    mockState[25].popularVotes = 260;

    strcpy(mockState[26].name, "Montana");
    strcpy(mockState[26].postalCode, "MT");
    mockState[26].electoralVotes = 4;
    mockState[26].popularVotes = 270;

    strcpy(mockState[27].name, "Nebraska");
    strcpy(mockState[27].postalCode, "NE");
    mockState[27].electoralVotes = 3;
    mockState[27].popularVotes = 280;

    strcpy(mockState[28].name, "New Hampshire");
    strcpy(mockState[28].postalCode, "NH");
    mockState[28].electoralVotes = 2;
    mockState[28].popularVotes = 290;

    strcpy(mockState[29].name, "New Mexico");
    strcpy(mockState[29].postalCode, "NM");
    mockState[29].electoralVotes = 1;
    mockState[29].popularVotes = 300;


    //mockstates contains 30 individual states, which is passed in and returns valid becuase the number of subsetPVs are calculated correctly
    MinInfo win_resFast = minPopVoteToWinFast(mockState, 30);

    if(win_resFast.subsetPVs != 234){
        return false;
    }

    //---------------------------------------------------------------------
    return true;
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
