#include "contact.h"

void listContacts(AddressBook *addresslist)
{
    printf("-----------------------------------------------");
    printf("\n|%5s|%20s |%12s| |%30s|\n", "Sr.no","Name", "Phone", "Email");
    printf("-----------------------------------------------");

    for(int i = 0; i < contactCount; i++)
    {
        printf("|%5.4d| |%20.20s| |%12.12s| |%30.30s|\n", i + 1, addresslist->contacts[i].name, addresslist->contacts[i].phone, addresslist->contacts[i].email);
    }
    
    printf("-----------------------------------------------");
}

