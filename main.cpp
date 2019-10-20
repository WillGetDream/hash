/*
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on October 15, 2019, 12:06 PM
 * Purpose:  To show how hash functions are created.
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <time.h>
#include <iomanip>
#include <list>
#include "hash.h"
using namespace std;


//User Libraries

//Global Constants

//Function prototypes
unsigned int mrkHash(char [],int);
void filArry(char [],int);
string LargeArry(string a,int length);
int LinearSearch(string arr[], string x);
int binarySearch(string arr[], string x,int n);
unsigned int RSHash  (const std::string& str);
unsigned int APHash(const std::string& str);

//Execution begins here
int main(int argc, char** argv) {


    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));


    //Declare Variables
    const int LSTSIZE=100;
    const int SIZE=2000;
    char array[SIZE];
    int largesize=10000000;

    //header
    int count[LSTSIZE]={};
    cout<<setw(25)<<"N"<<setw(25)
                  <<"Linear"<<setw(25)<<" Linear without"<<setw(25)
                                          <<"binarySearch"<<setw(25)<<" binarySearch without"<<setw(25)
            <<"hashSearch"<<setw(25)<<" hashSearch without"<<setw(25)
            <<endl;

//update N
    for(int i=1000;i<largesize;i=i+10000){
        float time1, time2,time3,time4,time5,time6;
        int result;
        string arraystring[i];
        Hash h(i);

        //fill arry fill hash
        for(int j=0;j<i;j++){
            filArry(array,SIZE);
            arraystring[j]+=array;
            h.insertItem(arraystring[j]);
        }
       //h.displayHash();

        //with linear
        clock_t start1 = clock();
       result=LinearSearch(arraystring, arraystring[i / 2]);
         time1=((float) clock() - start1) / CLOCKS_PER_SEC;

        //without linear
        start1 = clock();
        result= LinearSearch(arraystring, "ssssssssssssssssssss");
        time2=((float) clock() - start1) / CLOCKS_PER_SEC;

       //binarySearch
        sort(arraystring, arraystring + i);
        start1 = clock();
       result = binarySearch(arraystring,  arraystring[i / 2],i);
        time3=((float) clock() - start1) / CLOCKS_PER_SEC;

        //binarySearch
        start1 = clock();
        result = binarySearch(arraystring,  "ssssssssssssssssssss",i);
        time4=((float) clock() - start1) / CLOCKS_PER_SEC;

        //hashSearch
        start1 = clock();
        result = h.search(arraystring[i/2]);
        time5=((float) clock() - start1) / CLOCKS_PER_SEC;


        //hashSearch
        start1 = clock();
        result = h.search("ssssssssssssssssssss");
        time6=((float) clock() - start1) / CLOCKS_PER_SEC;



        cout<<fixed<<setw(25)<<i<<setw(25)<<time1<<setw(25)
                             <<time2<<setw(25)<<time3<<setw(25)
                             <<time4<<setw(25)<<time5<<setw(25)
                                    <<time6<<setw(25)<<endl;
    }
    //Exit stage right
    return 0;
}

void filArry(char a[],int n){
    for(int i=0;i<n;i++){
        int any=rand()%26;//0-25
        int upLow=rand()%2;//0,1
        if(upLow)a[i]=any+65; //up case
        else a[i]=any+97; //low case
    }
    a[n-1]='\0';
}

unsigned int mrkHash(char a[],int n){
    unsigned int sum=0,prod=1;
    char c;
    for(int i=0;i<n;i++){
        if(a[i]<=91)c=a[i]-65;
        else c=a[i]-71;
        sum+=(sum+c*prod);
        prod*=52;
        prod%=9999991;
        sum%=999999991;
    }
    return sum;
}


int LinearSearch(string arr[], string x)
{

    int i;
    for (i = 0; i < sizeof(arr); i++) {
        if (arr[i]==x) {
            return i;
        }
    }

    return -1;
}

int binarySearch(string arr[], string x,int n)
    {
        int l = 0 ;
        int r = n - 1;
        while (l <= r)
        {
            int m = l + (r - l) / 2;

            int res;
            if (x == (arr[m]))
                res = 0;


            // Check if x is present at mid
            if (res == 0)
                return m;

            // If x greater, ignore left half
            if (x > (arr[m]))
                l = m + 1;

                // If x is smaller, ignore right half
            else
                r = m - 1;
        }

        return -1;
    }




unsigned int APHash(const std::string& str)
{
    unsigned int hash = 0xAAAAAAAA;

    for(std::size_t i = 0; i < str.length(); i++)
    {
        hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                (~((hash << 11) + (str[i] ^ (hash >> 5))));
    }

    return hash;
}
