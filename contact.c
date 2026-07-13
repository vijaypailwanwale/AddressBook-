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


Void createContact(AddressBook *create)
{
    char name[50], phone[20], email[50];

    static int chance ;
    int nameExists = 0;
    int phoneExists = 0;
    int emailExists = 0;

    while(chance < 3)
    {
        //Read name
        if(nameExists <= 0)
        {
            printf("Enter name: ");
            read(char name, sizeof(name);
        }

        if(phoneExists <= 0)
        {
            printf("Enter phone: ");
            read(char phone, sizeof(phone));
        }

         if(emailExists <= 0)
        {
            printf("Enter email: ");
            read(char email, sizeof(email));
        }
;
    }


}