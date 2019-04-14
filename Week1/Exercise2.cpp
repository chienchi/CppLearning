// Create by Chienchi Lo on 2018-11-30
#include <iostream>

using namespace std;

void leaky(){
    // on heap
    // pointer to an array of 10 integers
    int *p = new int[10];
    for (int i =0; i < 20; ++i){
        p[i] = 1;
    }
    delete [] p;
}

void stack(){
    // on stack
    // array of 10 integers
    int array[8];
    for (int i =0; i < 10; ++i){
        array[i] = 1;
    }
}

int main(){
    // pointer to a character
    char tt ='a';
    char* c;
    c = &tt;

    // pointer to an array of character strings
    char str[] = "Hello";
    char str2[10];
    char* pstrings;
    //pstrings = str;
    cout << pstrings[1] << endl;
    cout << str[1] << endl;
    cout << *pstrings << endl;
    cout << *(pstrings+1) << endl;
    cout << *(str+1) << endl;

    // pointer to pointer to a character
    char** pptr;
    char* ptr;
    ptr = &tt;
    pptr = &ptr;
    cout << **pptr << endl;

    // integer constant
    const int ci = 1;

    // pointer to an integer constant
    const int *pci;
    pci = &ci;

    // constant pointer to an integer
    int i=2;
    int * const cp = &i;

    //leaky();
    //stack();
}