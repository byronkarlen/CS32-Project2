//
//  WeddingGuest.h
//  CS32Project2
//
//  Created by Byron Karlen on 6/30/22.
//

#ifndef WeddingGuest_hpp
#define WeddingGuest_hpp

#include <string>
typedef std::string GuestType; // This can change to other types such as double and int, not just string
//typedef int GuestType;
//typedef double GuestType;

class WeddingGuest
{
  public:
    // Create an empty WeddingGuest list
    WeddingGuest();
    
    //Create a copy constructor
    WeddingGuest(const WeddingGuest & old);
    
    //Create a destructor
    ~WeddingGuest();
    
    //Create an assignment operator
    WeddingGuest& operator=(const WeddingGuest & old);
    
    // Return true if the WeddingGuest list is empty, otherwise false.
    bool noGuests() const;
 
    // Return the number of matches on the WeddingGuest list.
    int guestCount() const;
 
    /* If the full name (both the first and last name) is not equal to any full name currently in the list then add it and return true. Elements should be added according to their last name. Elements with the same last name should be added according to their first names. Otherwise, make no change to the list and return false (indicating that the name is already in the list).*/
    bool inviteGuest(const std::string& firstName, const std::string& lastName, const GuestType& value);
       
    /* If the full name is equal to a full name currently in the list, then make that full name no longer map to the value it currently maps to, but instead map to the value of the third parameter; return true in this case. Otherwise, make no change to the list and return false.*/
    bool alterGuest(const std::string& firstName, const std::string& lastName, const GuestType & value);

    /* If the full name is equal to a full name currently in the list, then make that full name no longer map to the value it currently maps to, but instead map to the value of the third parameter; return true in this case. If the full name is not equal to any full name currently in the list then add it and return true. In fact, this function always returns true.*/
    bool inviteOrAlter(const std::string& firstName, const std::string& lastName, const GuestType& value);

    /* If the full name is equal to a full name currently in the list, remove the full name and value from the list and return true. Otherwise, make no change to the list and return false.*/
    bool crossGuestOff(const std::string& firstName, const std::string& lastName);
    
    /* Return true if the full name is equal to a full name currently in the list, otherwise false.*/
    bool invitedToTheWedding(const std::string& firstName, const std::string& lastName) const;

    /* If the full name is equal to a full name currently in the list, set value to the value in the list that that full name maps to, and return true.  Otherwise, make no change to the value parameter of this function and return false.*/
    bool matchInvitedGuest(const std::string& firstName, const std::string& lastName, GuestType& value) const;

    /* If 0 <= i < size(), copy into firstName, lastName and value parameters the corresponding information of the element at position i in the list and return true.  Otherwise, leave the parameters unchanged and return false. (See below for details about this function.)*/
    bool verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, GuestType & value) const;

    // Exchange the contents of this list with the other one.
    void swapWeddingGuests(WeddingGuest& other);
    
    
    //Print the content of the WeddingGuest list (for testing purposes only)
//    void dump() const;
    
  private:
    struct Node {
        GuestType value;
        std::string firstName;
        std::string lastName;
        Node *next;
        Node *prev;
    };
    Node* head;
    
    //Add a guest to the list at the given index
    void addToList(const std::string& firstName, const std::string lastName, const GuestType& value, int index);
};


//NON-MEMBER FUNCTIONS: 
bool joinGuests(const WeddingGuest & odOne, const WeddingGuest & odTwo, WeddingGuest & odJoined);

void attestGuests (const std::string& fsearch,const std::string& lsearch, const WeddingGuest& odOne,WeddingGuest& odResult);


#endif /* WeddingGuest_hpp */


