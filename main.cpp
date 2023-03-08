//
//  main.cpp
//  CS32Project2
//
//  Created by Byron Karlen on 6/30/22.
//
#include <cassert>
#include <iostream>

#include "WeddingGuest.h"
#include<string>
using namespace std;

int main(){
    WeddingGuest w;
    w.inviteGuest("Byron", "Karlen", "abc");
    w.inviteGuest("byron", "Karlen", "abc");
    w.inviteGuest("Byron", "Larlen", "abc");
    WeddingGuest w2;
    w2.inviteGuest("Byron", "Larlen", "Abc");
    WeddingGuest output;
    cout << joinGuests(w, w2, output);
    cout << output.guestCount();
}
