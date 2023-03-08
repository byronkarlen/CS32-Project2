//
//  WeddingGuest.cpp
//  CS32Project2
//
//  Created by Byron Karlen on 6/30/22.
//

#include "WeddingGuest.h"
using namespace std;

WeddingGuest::WeddingGuest(){
    head = nullptr;
}

WeddingGuest::WeddingGuest(const WeddingGuest& old){
    
    //If old list is empty
    if(old.head == nullptr){
        head = nullptr;
    }
    //If there is at least one node
    else{
        head = new Node;
        Node* n = head;
        
        n->prev = nullptr;
        
        Node* p = old.head;
    
        //Traverse through old list
        while(p != nullptr){
            //Copy values
            n->value = p->value;
            n->firstName = p-> firstName;
            n->lastName = p-> lastName;
            
            //If this is old's last node
            if(p->next == nullptr){
                n->next = nullptr;
            }
            //If there are more nodes
            else{
                n->next = new Node; //Add a new node
                n->next->prev = n; //Point this new node's 'prev' to the current node
                n = n->next; //Increment n
            }
            p = p->next; //Increment p
        }
    }
}

WeddingGuest::~WeddingGuest(){
    Node* p = head;
    
    //Iterate through the list and delete every node
    while (p != nullptr){
        Node* temp;
        temp = p->next;
        delete p;
        p = temp; //set p to the next node to delete
    }
}

WeddingGuest& WeddingGuest::operator=(const WeddingGuest &old){
    //Aliasing Check:
    if(this == &old){
        return *this;
    }
    
    //Delete the current list
    Node* q = head;
    while(q != nullptr){
        Node* temp = q->next;
        delete q;
        q = temp;
    }
    
    //If 'old' is empty
    if(old.head == nullptr){
        head = nullptr;
    }
    //If 'old' has at least one node
    else{
        head = new Node;
        Node* n = head;
        n->prev = nullptr;
        
        Node* p = old.head;
        
        //Traverse through 'old' list and copy over values
        while(p != nullptr){
            n->value = p->value;
            n->firstName = p->firstName;
            n->lastName = p->lastName;

            if(p->next == nullptr){
                n->next = nullptr;
            }
            else{
                n->next = new Node;
                n->next->prev = n;
                n = n->next;
            }
            p = p->next;
        }
    }
    return *this;
}

bool WeddingGuest::noGuests() const{
    return head == nullptr;
}

int WeddingGuest::guestCount() const{
    int count = 0;
    
    Node* p = head;
    while (p != nullptr){
        p = p->next;
        count++;
    }
    return count;
}

bool WeddingGuest::inviteGuest(const std::string &firstName, const std::string &lastName,const GuestType &value){
    if(invitedToTheWedding(firstName, lastName)){
        return false;
    }

    int index = 0;
    Node* p = head;
    while(p != nullptr){
        //If the guest's name belongs before the current guest in the list
        if(lastName < p->lastName || (lastName == p->lastName && firstName < p->firstName)){
            //Add the guest to the list at the current index
            addToList(firstName, lastName, value, index);
            return true;
        }
        index++;
        p = p->next;
    }
    //If the guests name belongs after all guests in the list, add the guest to the end of the list
    addToList(firstName, lastName, value, index);
    return true;
    
}

bool WeddingGuest::alterGuest(const std::string &firstName, const std::string &lastName, const GuestType &value){
    
    Node* p = head;
    //Traverse through list
    while(p != nullptr){
        //If the full name exists in the list
        if(p->firstName == firstName && p->lastName == lastName){
            p->value = value; //If the full name is found in the list map the guest's value to 'value'
            return true;
        }
        p = p->next; //Increment p
    }
    //The full name was not found in the list, so return false
    return false;
}

bool WeddingGuest::inviteOrAlter(const std::string &firstName, const std::string &lastName, const GuestType &value){
    //If guest is invited to wedding, alter the guest to map to the third parameter
    if(invitedToTheWedding(firstName, lastName)){
        alterGuest(firstName, lastName, value);
    }
    //If guest is not yet invited to wedding, invite the guest
    else{
        inviteGuest(firstName, lastName, value);
    }
    //This function always returns true
    return true;
}

bool WeddingGuest::crossGuestOff(const std::string &firstName, const std::string &lastName){
    
    Node* p = head;
    //Traverse through list
    while (p != nullptr){
        //If the sought-out guest was found in the list
        if(p->firstName == firstName && p->lastName == lastName){
            
            //If it's the only guest in the list
            if(p->prev == nullptr && p->next == nullptr){
                head = nullptr;
            }
            //If it's the first guest in the list
            else if(p->prev == nullptr){
                head = p->next;
                p->next->prev = nullptr;
            }
            //If it's the last guest in the list
            else if(p->next == nullptr){
                p->prev->next = nullptr;
            }
            //If it's somewhere in the middle of the list
            else{
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            //After all linking pointers are adjusted, delete the guest from the list
            delete p;
            return true;
        }
        p = p->next;
    }
    
    //Return false since the guest was not found in the list
    return false;
}

bool WeddingGuest::invitedToTheWedding(const std::string &firstName, const std::string &lastName) const{
    Node* p = head;
    while(p != nullptr){
        if(p->firstName == firstName && p->lastName == lastName){
            return true;
        }
        p = p->next;
    }
    return false;
}


bool WeddingGuest::matchInvitedGuest(const std::string &firstName, const std::string &lastName, GuestType &value) const{
    
    Node* p = head;
    //Traverse through list
    while(p != nullptr){
        if(p->firstName == firstName && p->lastName == lastName){
            value = p->value; //If the full name is found in the list map 'value' to guest's value
            return true;
        }
        p = p->next;
    }
    //Return false since the guest was not found in list
    return false;
}

bool WeddingGuest::verifyGuestOnTheList(int i, string &firstName, string &lastName, GuestType &value) const {
    
    //If the index given is invalid
    if(i < 0 || i >= guestCount()){
        return false;
    }
    
    //Iterate through the list to set p to point to the element at index i
    Node* p = head;
    for(int j = 0; j < i; j++){
        p = p->next;
    }
   
    //Map the guest's data to the parameters
    firstName = p->firstName;
    lastName = p->lastName;
    value = p->value;
    
    return true;
}

void WeddingGuest::swapWeddingGuests(WeddingGuest &other){
    //To swap the guest lists, swap the head node-pointers using a 'temp' variable
    Node* temp = head;
    head = other.head;
    other.head = temp;
}

//void WeddingGuest::dump() const{
//    Node* p = head;
//    while(p != nullptr){
//        cerr << p->firstName << " " << p->lastName << " " << p->value << endl;
//        p = p->next;
//    }
//}

//Helper

void WeddingGuest::addToList(const std::string &firstName, const std::string lastName, const GuestType& value, int index){
    
    //This method will only be called with a valid index
    Node* p = head;
    for(int i = 0; i < index; i++){
        p = p->next;
    }
    //p now points the the index at which a new guest will be inserted
    Node* n = new Node;
    
    //If element should be inserted at the beginning
    if(p == head){
        n->next = head;
        n->prev = nullptr;
        head = n;
        //If the next element exists, update it's 'prev' pointer
        if(n->next != nullptr){
            n->next->prev = n;
        }
    }
    //If element should be inserted at the end
    else if(p == nullptr){
        n->next = nullptr;
        
        //Set q to point to the last element in the list
        Node* q = head;
        for(int i = 0; i < index - 1; i++){
            q = q->next;
        }
        
        q->next = n;
        n->prev = q;
    }
    //If element should be inserted somewhere in the middle
    else{
        n->next = p;
        n->prev = p->prev;
        
        n->prev->next = n;
        n->next->prev = n;
    }
    //After all pointers have been updated to link to the correct nodes, add the guest's data to the list
    n->firstName = firstName;
    n->lastName = lastName;
    n->value = value;
}


//Non-member functions

bool joinGuests(const WeddingGuest & odOne, const WeddingGuest & odTwo, WeddingGuest & odJoined){
    
    //To account for aliasing:
    WeddingGuest cpy1 = odOne;
    WeddingGuest cpy2 = odTwo;
    
    bool output = true;
    
    //Copy into odJoined the guests in odOne
    odJoined = cpy1;
    
    //Iterate through the guests in odTwo (through cpy2)
    for(int i = 0; i < cpy2.guestCount(); i++){
        string first, last;
        GuestType val;
        cpy2.verifyGuestOnTheList(i, first, last, val); //set 'first', 'last', and 'val' equal to the current guest's corresponding data
        
        //If the current guest is not already invited to the wedding
        if(!odJoined.invitedToTheWedding(first, last)){
            odJoined.inviteGuest(first, last, val);
        }
        //If the current guest is already invited to the wedding
        else{
            GuestType val2;
            odJoined.matchInvitedGuest(first, last, val2); //set val2 equal to the the value of the guest already in odJoined with the same name
            
            //If their values do not match, remove the guest from odJoined and set 'output' equal to false
            if(val2 != val){
                odJoined.crossGuestOff(first, last);
                output = false;
            }
        }
    }
    return output;
}

void attestGuests (const std::string& fsearch,const std::string& lsearch, const WeddingGuest& odOne,WeddingGuest& odResult){
    
    WeddingGuest result;
    
    //if no '*' are used in the search
    if(fsearch != "*" && lsearch != "*"){
        if(odOne.invitedToTheWedding(fsearch, lsearch)){
            GuestType val;
            odOne.matchInvitedGuest(fsearch, lsearch, val);
            result.inviteGuest(fsearch, lsearch, val);
        }
    }
    //if '*' are used for both first and last name in the search
    else if(fsearch == "*" && lsearch == "*"){
        result = odOne; //Use the assignment operator to copy over all guests into odResult
    }
    //If '*' are used for one of either first or last name in the search
    else{
        //iterate through the guest list
        for(int j = 0; j < odOne.guestCount(); j++){
            string first, last;
            GuestType val;
            odOne.verifyGuestOnTheList(j, first, last, val);

            //If one of the search fields equal '*', and the current guest has a first/last name that matches the other input, add the guest to '   odResult'
            if( (fsearch == "*" && last == lsearch) || (lsearch == "*" && first == fsearch) ) {
                result.inviteGuest(first, last, val);
            }
        }
    }
    odResult = result;
}



