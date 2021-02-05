//
// Created by Selcuk on 13.11.2020.
//

#include <fstream>
#include "Deck.h"
#include "Reader.h"
#include "iostream"

using namespace std;


struct Command{
    string command_name;
    string cards[7][52];
};




Deck::Deck() {};
int Deck::board(string deck_file,string commands_file,string output_file ) {
    struct Command deck;
    struct Command pile;
    struct Command showing_pile;
    int line = 0;
    ofstream myfile;
    Reader reader;
    string condition;
    string upperboard[9][18]={{"@@@"},{"___"},{"___"},{"___"},{"       "},{"___"},{"___"},{"___"},{"___"}};
    deck = reader.changer(deck_file,0);
    int x=0;
    int y=0;
    int j=0;


    myfile.open (output_file);


    for(int i =0;i<7; i++){
        for (x;x<7;x++) {
            for (j; j < 52; j++) {
                if (deck.cards[0][j]==""){
                }
                else{
                    break;
                }
            }
            pile.cards[x][i]=deck.cards[0][j];
            deck.cards[0][j]="";
        }
        y+=1;
        x=y;
    }


    myfile << upperboard[0][0] << " ";
    for (int i = 1; i < 9; i++) {
        for (int j = 0; j < 18 ; j++) {
            if (upperboard[i][j]!="___"&&upperboard[i][j]!=""){
            }
            else{
                if (j==0){
                    myfile << upperboard[i][j] << " ";
                    break;
                }
                else{
                    myfile << upperboard[i][j - 1] << " ";
                    break;
                }
            }
        }
    }
    showing_pile=pile;
    myfile << endl;
    int k=0;
    for (int i=0; i < 7; i++) {
        if (k>0){
            for (int j=0;  j<k ; j++) {
                myfile << "      ";
            }
        }
        for(k;k<7;k++){
            int repeat=0;
            for ( repeat; repeat < 52 ; repeat++) {
                if (pile.cards[k][repeat]==""){
                    break;
                }
            }
            if (pile.cards[k][repeat-1]!=pile.cards[k][i]){
                showing_pile.cards[k][i] = "@@@";
                myfile << "@@@" << "   ";
            }
            else{
                myfile << pile.cards[k][i] << "   ";
            }
        }
        myfile << endl;
        k=i+1;
    }
    while (1){
        condition = reader.changer(commands_file,line).command_name;
        line+=1;
        myfile << condition << endl;
        myfile << endl << "****************************************" << endl << endl;
        if (condition=="open from stock"){
            int j=0;
            int edge;
            int l=0;
            for (j; j < 51; j++) {
                if (deck.cards[0][j]==""){
                }
                else{
                    break;
                }
            }
            if (51-j>=2){
                for (edge = 0; edge <18 ; edge++) {
                    if(upperboard[1][edge]=="___" && edge ==0){
                        break;
                    }
                    else if (upperboard[1][edge]==""){
                        break;
                    }
                }
                for ( l; l < 3  ; l) {
                    l+=1;
                    upperboard[l][edge]=deck.cards[0][j];
                    deck.cards[0][j]="";
                    j+=1;
                }
            }
            else if (51-j<2 && deck.cards[0][j]!=""){
                for (int l = 0; l < 52-j  ; l++) {
                    for (edge = 0; edge <18 ; edge++) {
                        if(upperboard[1][edge]=="___" && edge ==0){
                            break;
                        }
                        else if (upperboard[1][edge]==""){
                            break;
                        }
                    }
                    upperboard[l+1][edge]=deck.cards[0][j];
                    deck.cards[0][j]="";
                    j+=1;
                }

            }
            else if (51-j==0){
                int start=0;
                int end;
                for (end = 0; end < 18  ; end++){
                    if (upperboard[1][end]==""||upperboard[1][end]=="___"){
                        break;
                    }
                }
                for (int i = 0; i <=end ; i++) {
                    for (int j = 1; j < 4 ; j++) {
                        if (upperboard[j][i]!="")
                        {
                            deck.cards[0][start]=upperboard[j][i];
                            start+=1;
                            upperboard[j][i]="";
                        }
                    }

                }
            }
        }


//        MOVE TO FOUNDATION ..... KOMUTU

        else if (condition.substr(0,18)=="move to foundation"){
            int pile_number;
            string waste;
            string str=condition.substr(19,1);
            if (str=="p"){
                pile_number = stoi(condition.substr(24,1));
            }
            else if(str=="w"){
                waste = "waste";
            }
            if(waste=="waste"){
                int take;
                int put;
                int source_point=0;
                int destination_point=0;
                int can_do=0;
                for (int k = 3; k > 0 ; k--) {
                    for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                        if (upperboard[1][temp_j]!="___"&& upperboard[1][temp_j]!=""){
                        }
                        else{
                            if (temp_j==0){
                                take=temp_j;
                                break;
                            }
                            else{
                                take=temp_j-1;
                                break;
                            }
                        }
                    }
                    if (upperboard[k][take]!=""&&upperboard[k][take]!="___"){
                        can_do += 1;
                        if (can_do < 2){
                            if (upperboard[k][take].substr(0,1)=="H"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[5][temp_j]!="___" && upperboard[5][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (upperboard[k][take]!=""){
                                    source_point= stoi(upperboard[k][take].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[5][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[5][put]=upperboard[k][take];
                                    upperboard[k][take]="";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                            }
                            else if (upperboard[k][take].substr(0,1)=="D"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[6][temp_j]!="___" && upperboard[6][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (upperboard[k][take]!=""){
                                    source_point= stoi(upperboard[k][take].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[6][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[6][put]=upperboard[k][take];
                                    upperboard[k][take]="";

                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                            }
                            else if (upperboard[k][take].substr(0,1)=="S"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[7][temp_j]!="___" && upperboard[7][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (upperboard[k][take]!=""){
                                    source_point= stoi(upperboard[k][take].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[7][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[7][put]=upperboard[k][take];
                                    upperboard[k][take]="";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }

                            }
                            else if (upperboard[k][take].substr(0,1)=="C"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[8][temp_j]!="___" && upperboard[8][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (upperboard[k][take]!=""){
                                    source_point= stoi(upperboard[k][take].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[8][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[8][put]=upperboard[k][take];
                                    upperboard[k][take]="";

                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }

                            }
                        }
                    }
                }

            }
            else if (pile_number>=0){
                int edge;
                int put;
                int source_point=0;
                int destination_point=0;
                for (edge=0; edge < 52 ; edge++) {
                    if (pile.cards[pile_number][edge]==""){
                        if(edge!=0){
                            if (pile.cards[pile_number][edge-1].substr(0,1)=="H"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[5][temp_j]!="___" && upperboard[5][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (pile.cards[pile_number][edge-1]!=""&& showing_pile.cards[pile_number][edge-1]!="@@@"){
                                    source_point= stoi(pile.cards[pile_number][edge-1].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[5][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[5][put] =pile.cards[pile_number][edge-1];
                                    pile.cards[pile_number][edge-1]="";
                                    showing_pile.cards[pile_number][edge-1] = "   ";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }

                            }
                            else if (pile.cards[pile_number][edge-1].substr(0,1)=="D"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[6][temp_j]!="___" && upperboard[6][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (pile.cards[pile_number][edge-1]!="" && showing_pile.cards[pile_number][edge-1]!="@@@"){
                                    source_point= stoi(pile.cards[pile_number][edge-1].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[6][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[6][put] =pile.cards[pile_number][edge-1];
                                    pile.cards[pile_number][edge-1]="";
                                    showing_pile.cards[pile_number][edge-1] = "   ";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }

                            }
                            else if (pile.cards[pile_number][edge-1].substr(0,1)=="S"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[7][temp_j]!="___" && upperboard[7][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (pile.cards[pile_number][edge-1]!=""&& showing_pile.cards[pile_number][edge-1]!="@@@"){
                                    source_point= stoi(pile.cards[pile_number][edge-1].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[7][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[7][put] =pile.cards[pile_number][edge-1];
                                    pile.cards[pile_number][edge-1]="";
                                    showing_pile.cards[pile_number][edge-1] = "   ";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                            }
                            else if (pile.cards[pile_number][edge-1].substr(0,1)=="C"){
                                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                                    if (upperboard[8][temp_j]!="___" && upperboard[8][temp_j]!=""){
                                    }
                                    else{
                                            put=temp_j;
                                            break;
                                    }
                                }
                                if (pile.cards[pile_number][edge-1]!=""&& showing_pile.cards[pile_number][edge-1]!="@@@"){
                                    source_point= stoi(pile.cards[pile_number][edge-1].substr(1,2));
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                                if (put==0){
                                    destination_point=0;
                                }
                                else{
                                    destination_point= stoi(upperboard[8][put-1].substr(1,2));
                                }
                                if(source_point-destination_point==1){
                                    upperboard[8][put] =pile.cards[pile_number][edge-1];
                                    pile.cards[pile_number][edge-1]="";
                                    showing_pile.cards[pile_number][edge-1] = "   ";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    source_point=-1;
                                }
                            }
                        }
                        else{
                            myfile << "Invalid Move!" << endl << "****************************************" << endl;
                            source_point=-1;
                            break;

                        }
                    }
                }


            }
        }


//        MOVE ...... KOMUTU



        else if (condition.substr(0,4)=="move"){

            int source_pile_number=-1;
            int source_pile_card_index;
            int destination_pile_number;
            int source_foundation_number;
            string waste;
            string str=condition.substr(5,1);
            if (str=="p"){
                source_pile_number = stoi(condition.substr(10,1));
                source_pile_card_index = stoi( condition.substr(12,2));
                if(source_pile_card_index>9){
                    destination_pile_number = stoi( condition.substr(15,1));
                }
                else{
                    destination_pile_number = stoi( condition.substr(14,1));
                }
            }
            else if(str=="w"){
                waste = "waste";
                destination_pile_number = stoi( condition.substr(11,1));
            }
            else if(str=="f"){
                source_foundation_number=stoi( condition.substr(16,1));
                destination_pile_number = stoi( condition.substr(18,1));
            }



//          WASTEDEN PILE A ATAMA KODU




            if(waste=="waste"){
                int take,top;
                int destination_point=0;
                int source_point=0;

                for (int temp_j = 0; temp_j < 18 ; temp_j++) {
                    if (upperboard[1][temp_j]!="___"&& upperboard[1][temp_j]!=""){
                    }
                    else{
                        if (temp_j==0){
                            take=temp_j;
                            break;
                        }
                        else{
                            take=temp_j-1;
                            break;
                        }
                    }
                }
                for (top=3 ; top>1; top--) {
                    if (upperboard[top][take] != ""&& upperboard[top][take] != "___"){
                        break;
                    }
                }
                if (upperboard[top][take]!="___"&& upperboard[top][take]!=""){
                    int edge;
                    for (edge=0; edge < 52 ; edge++) {
                        if (pile.cards[destination_pile_number][edge]==""){
                            break;
                        }
                    }
                    if (upperboard[top][take]!=""&& upperboard[top][take]!="___"){
                        source_point= stoi(upperboard[top][take].substr(1,2));
                        if (pile.cards[destination_pile_number][edge-1]==""){
                            destination_point=14;
                            if (destination_point==14){
                                if (source_point==13){
                                    pile.cards[destination_pile_number][edge]=upperboard[top][take];
                                    showing_pile.cards[destination_pile_number][edge] =upperboard[top][take];
                                        upperboard[top][take]="";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                }
                            }
                            else if(destination_point-source_point==1){
                                if (upperboard[top][take].substr(0,1)=="H"||upperboard[top][take].substr(0,1)=="D"){
                                    if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="S"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="C"){
                                        pile.cards[destination_pile_number][edge]=upperboard[top][take];
                                        showing_pile.cards[destination_pile_number][edge] =upperboard[top][take];
                                        upperboard[top][take]="";
                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    }
                                }
                                if (upperboard[top][take].substr(0,1)=="S"||upperboard[top][take].substr(0,1)=="C"){
                                    if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="H"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="D"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="")
                                    {
                                        pile.cards[destination_pile_number][edge]=upperboard[top][take];
                                        showing_pile.cards[destination_pile_number][edge] =upperboard[top][take];
                                        upperboard[top][take]="";

                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    }
                                }
                            }
                            else{
                                myfile << "Invalid Move!" << endl << "****************************************" << endl;
                            }
                        }
                        else if(showing_pile.cards[destination_pile_number][edge-1]=="@@@"){
                            myfile << "Invalid Move!" << endl << "****************************************" << endl;
                        }
                        else{
                            destination_point= stoi(pile.cards[destination_pile_number][edge-1].substr(1,2));
                            if (destination_point==14){
                                if (source_point==13){
                                    pile.cards[destination_pile_number][edge]=upperboard[top][take];
                                    showing_pile.cards[destination_pile_number][edge] =upperboard[top][take];
                                    upperboard[top][take]="";
                                }
                                else{
                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                }
                            }
                            else if(destination_point-source_point==1){
                                if (upperboard[top][take].substr(0,1)=="H"||upperboard[top][take].substr(0,1)=="D"){
                                    if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="S"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="C"){
                                        pile.cards[destination_pile_number][edge]=upperboard[top][take];
                                        showing_pile.cards[destination_pile_number][edge] =upperboard[top][take];
                                        upperboard[top][take]="";
                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    }
                                }
                                if (upperboard[top][take].substr(0,1)=="S"||upperboard[top][take].substr(0,1)=="C"){
                                    if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="H"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="D"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="")
                                    {
                                        pile.cards[destination_pile_number][edge]=upperboard[top][take];
                                        showing_pile.cards[destination_pile_number][edge] =upperboard[top][take];
                                        upperboard[top][take]="";

                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                    }
                                }
                            }
                            else{
                                myfile << "Invalid Move!" << endl << "****************************************" << endl;
                            }
                        }
                    }
                    else{
                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                    }
                }
                else{
                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                }
            }



//          PILE DAN PILE A ATAMA KODU



            else if(source_pile_number>=0){
                int edge;
                int source_edge;
                int source_point=0;
                int destination_point=0;
                for (edge=0; edge < 52 ; edge++) {
                    if (pile.cards[destination_pile_number][edge]==""){
                        for (source_edge=0; source_edge <52; source_edge++) {
                            if (pile.cards[source_pile_number][source_edge]==""){
                                if (source_edge!=0){
                                    int index= source_edge-1-source_pile_card_index;
                                    if(index<0){
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }
                                    if (pile.cards[source_pile_number][index]!=""&& showing_pile.cards[source_pile_number][index]!="@@@"){
                                        source_point= stoi(pile.cards[source_pile_number][index].substr(1,2));
                                    }
                                    if (pile.cards[destination_pile_number][edge-1]==""){
                                        destination_point=14;
                                    }
                                    else if(showing_pile.cards[destination_pile_number][edge-1]=="@@@"){
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }
                                    else{
                                        destination_point= stoi(pile.cards[destination_pile_number][edge-1].substr(1,2));
                                    }
                                    if (showing_pile.cards[source_pile_number][source_edge-1]=="@@@"){
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }
                                    else{
                                        for (;source_pile_card_index>=0;source_pile_card_index--) {
                                            if (destination_point==14){
                                                if (source_point!=13){
                                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                                    break;
                                                }
                                            }
                                            else if(destination_point-source_point!=1){
                                                myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                                break;
                                            }

                                            if (pile.cards[source_pile_number][index].substr(0,1)=="H"||pile.cards[source_pile_number][index].substr(0,1)=="D"){
                                                if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="S"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="C"){
                                                }
                                                else{
                                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                                    break;
                                                }
                                            }
                                            if (pile.cards[source_pile_number][index].substr(0,1)=="S"||pile.cards[source_pile_number][index].substr(0,1)=="C"){
                                                if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="H"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="D"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="")
                                                {
                                                }
                                                else{
                                                    myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                                    break;
                                                }
                                            }
                                            pile.cards[destination_pile_number][edge]=pile.cards[source_pile_number][source_edge-1-source_pile_card_index];
                                            showing_pile.cards[destination_pile_number][edge] = pile.cards[source_pile_number][source_edge-1-source_pile_card_index];
                                            showing_pile.cards[source_pile_number][source_edge-1-source_pile_card_index]="   ";
                                            pile.cards[source_pile_number][source_edge-1-source_pile_card_index]="";
                                            edge+=1;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }

//            FOUNDATIONDAN PILE A ATAMA KODU



            else if(source_foundation_number>=0){
                int edge;
                int source_edge;
                int source_point=0;
                int destination_point=0;
                for (source_edge=0; source_edge < 52 ; source_edge++) {
                    if (upperboard[source_foundation_number+5][source_edge]==""){
                        if(source_edge!=0){
                            for (edge=0; edge <52; edge++) {
                                if (pile.cards[destination_pile_number][edge]==""){
                                    break;
                                }
                            }
                            if(upperboard[source_foundation_number+5][source_edge-1]!="___"){
                                if (edge!=0){
                                    if (upperboard[source_foundation_number+5][source_edge-1]!="" && upperboard[source_foundation_number+5][source_edge-1]!="___"){
                                        source_point= stoi(upperboard[source_foundation_number+5][source_edge-1].substr(1,2));
                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }
                                    if (pile.cards[destination_pile_number][edge-1]==""){
                                        destination_point=14;
                                    }
                                    else if(showing_pile.cards[destination_pile_number][edge-1]=="@@@"){
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }
                                    else{
                                        destination_point= stoi(pile.cards[destination_pile_number][edge-1].substr(1,2));
                                    }
                                    if (destination_point==14){
                                        if (source_point==13){
                                            pile.cards[destination_pile_number][edge] = upperboard[source_foundation_number+5][source_edge-1];
                                            showing_pile.cards[destination_pile_number][edge]=upperboard[source_foundation_number+5][source_edge-1];
                                            if (source_edge==1){
                                                upperboard[source_foundation_number+5][source_edge-1]="___";
                                            }
                                            else{
                                                upperboard[source_foundation_number+5][source_edge-1]="";
                                            }
                                        }
                                    }
                                    else if(destination_point-source_point==1){

                                        if (upperboard[source_foundation_number+5][source_edge-1].substr(0,1)=="H"||upperboard[source_foundation_number+5][source_edge-1].substr(0,1)=="D"){
                                            if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="S"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="C"){

                                                pile.cards[destination_pile_number][edge] = upperboard[source_foundation_number+5][source_edge-1];
                                                showing_pile.cards[destination_pile_number][edge]=upperboard[source_foundation_number+5][source_edge-1];
                                                if (source_edge==1){
                                                    upperboard[source_foundation_number+5][source_edge-1]="___";
                                                }
                                                else{
                                                    upperboard[source_foundation_number+5][source_edge-1]="";
                                                }
                                            }
                                            else{
                                                myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                                break;
                                            }
                                        }
                                        if (upperboard[source_foundation_number+5][source_edge-1].substr(0,1)=="S"||upperboard[source_foundation_number+5][source_edge-1].substr(0,1)=="C"){
                                            if (pile.cards[destination_pile_number][edge-1].substr(0,1)=="H"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="D"||pile.cards[destination_pile_number][edge-1].substr(0,1)=="")
                                            {
                                                pile.cards[destination_pile_number][edge] = upperboard[source_foundation_number+5][source_edge-1];
                                                showing_pile.cards[destination_pile_number][edge]=upperboard[source_foundation_number+5][source_edge-1];
                                                if (source_edge==1){
                                                    upperboard[source_foundation_number+5][source_edge-1]="___";
                                                }
                                                else{
                                                    upperboard[source_foundation_number+5][source_edge-1]="";
                                                }
                                            }
                                            else{
                                                myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                                break;
                                            }
                                        }
                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }

                                    edge+=1;
                                }
                                else if (edge == 0){
                                    if (upperboard[source_foundation_number+5][source_edge-1]!="" && upperboard[source_foundation_number+5][source_edge-1]!="___"){
                                        source_point= stoi(upperboard[source_foundation_number+5][source_edge-1].substr(1,2));
                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }
                                    if (pile.cards[destination_pile_number][edge]==""){
                                        destination_point=14;
                                    }
                                    if (destination_point==14){
                                        if (source_point==13){
                                            pile.cards[destination_pile_number][edge] = upperboard[source_foundation_number+5][source_edge-1];
                                            showing_pile.cards[destination_pile_number][edge]=upperboard[source_foundation_number+5][source_edge-1];
                                            if (source_edge==1){
                                                upperboard[source_foundation_number+5][source_edge-1]="___";
                                            }
                                            else{
                                                upperboard[source_foundation_number+5][source_edge-1]="";
                                            }
                                        }
                                        else{
                                            myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                            break;
                                        }
                                    }
                                    else{
                                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                        break;
                                    }
                                    edge+=1;
                                }
                            }
                            else{
                                myfile << "Invalid Move!" << endl << "****************************************" << endl;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }

//        OPEN KOMUTU


        else if (condition.substr(0,4)=="open"){
            int pile_number;
            int edge;
            pile_number = stoi(condition.substr(5,1));
            for (edge=0; edge < 52 ; edge++) {
                if (pile.cards[pile_number][edge]==""){
                    if(edge!=0){
                        if (showing_pile.cards[pile_number][edge-1]!=pile.cards[pile_number][edge-1]) {
                            showing_pile.cards[pile_number][edge - 1] = pile.cards[pile_number][edge - 1];
                        }
                        else{
                            myfile << "Invalid Move!" << endl << "****************************************" << endl;
                        }
                    }
                    else{
                        myfile << "Invalid Move!" << endl << "****************************************" << endl;
                    }
                    break;
                }
            }
        }
        else if (condition.substr(0,4)=="exit"){
            myfile << "Game Over";
            break;
        }




//    Else gelcek buraya
//Table yaz buraya
        int j=0;
        for (j; j < 52; j++) {
            if (deck.cards[0][j]==""){
            }
            else{
                break;
            }
        }
        if (j<52){
            upperboard[0][0]="@@@";
        }
        else {
            upperboard[0][0]="___";
        }
        myfile << upperboard[0][0] << " ";
        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 18 ; j++) {
                if (upperboard[1][j]!="___"&&upperboard[1][j]!=""){
                }
                else{
                    if (j==0){
                        if (upperboard[i][j]==""){
                            myfile << "___ ";
                            break;
                        }
                        else{
                            myfile << upperboard[i][j] << " ";
                            break;
                        }
                    }
                    else if (upperboard[1][j]=="___" && upperboard[2][j]=="___" && upperboard[3][j]=="___"){
                        if (i<3 && upperboard[i+1][j-1]=="___"){
                            if (upperboard[i][j-1]==""){
                                myfile << "___ ";
                                break;
                            }
                            else{
                                myfile << upperboard[i][j - 1] << " ";
                                break;
                            }

                        }
                        else if(i==3 && upperboard[1][j]=="___"){
                            if (upperboard[i][j-1]==""){
                                myfile << "___ ";
                                break;
                            }
                            else{
                                myfile << upperboard[i][j - 1] << " ";
                                break;
                            }
                        }

                    }
                    else{
                        if (upperboard[i][j-1]==""){
                            myfile << "___ ";
                            break;
                        }
                        else{
                            myfile << upperboard[i][j - 1] << " ";
                            break;
                        }

                    }
                }
            }
        }
        for (int i = 4; i < 9; i++) {
            for (int j = 0; j < 18 ; j++) {
                if (upperboard[i][j]!="___"&&upperboard[i][j]!=""){
                }
                else{
                    if (j==0){
                        myfile << upperboard[i][j] << " ";
                        break;
                    }
                    else{
                        myfile << upperboard[i][j - 1] << " ";
                        break;
                    }
                }
            }
        }
        myfile << endl;
        int max_edge=0;
        int edge=0;
        for (int i = 0; i < 7 ; i++) {
            for (int l = 0; l < 20; l++) {
                if (showing_pile.cards[i][l]==""){
                    edge=l;
                    if (max_edge<edge){
                        max_edge=edge;
                    }
                    break;
                }
            }
        }
        for (int i = 0; i < max_edge ; i++) {
            for (int l = 0; l < 7 ; l++) {
                if (showing_pile.cards[l][i]==""){
                    myfile << "      ";
                }
                else{
                    myfile << showing_pile.cards[l][i] << "   ";
                }
            }
            myfile << endl;
        }


        if (upperboard[0][0]=="___"&&upperboard[1][0]==""&&upperboard[2][0]==""&&upperboard[3][0]==""){
            if(pile.cards[0][0]==""&&pile.cards[1][0]==""&&pile.cards[2][0]==""&&pile.cards[3][0]==""&&pile.cards[4][0]==""&&pile.cards[5][0]==""&&pile.cards[6][0]==""){
                myfile << "You Win!" << endl << endl << "Game Over !";
                myfile.close();
                break;
            }
        }
    }
    return 0;
}

