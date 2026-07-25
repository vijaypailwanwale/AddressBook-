#include "contact.h"
#include<stdio.h>
#include<ctype.h>



static int chance ;

void clear_buffer()
{
    char ch;
    while ((ch=getchar()) !='\n' && ch != EOF );
    
}

void read_name(char name[], int size,AddressBook *create, int *temp_name)
{
    // Read input from user
    fgets(name,size,stdin);

    //clear input buffer 
    clear_buffer();

    //Check Entered name is all alphabets - check 

    int i = 0;
    int space = 0;
    while ( name[i] != '\0')
    {
        if(!isalpha(name[i]))
        {
            i++;
        }
        else
        {
            if(name[i]==' ')
            {
                if(space < 3){
                space++;
                i++;
                }
                else
                {
                    printf("Too many spaces try agian");
                    chance++;
                    return;
                }
            }
        }
    }
    
    //validate input name to check is it present in the contact list
     i = 0;
    while (i <= create->contactCount)
    {
        if(strcmp(name, create->contacts[i].name) == 0)
        {
            printf("Name already exists. Please enter a different name.\n");
            chance++;
            return;
        }
        else
        {
            i++;
        }
    }
    
    *temp_name = 1;
    chance = 0;
    return;

}

void read_email(char mail[], AddressBook *create, int *emailExists )
{
    //Read Email ID from user

    // Validate Email id format
    
    // Check if Email id already exists

}


void listContacts(AddressBook *addresslist)
{
    printf("-----------------------------------------------");
    printf("\n|%5s|%20s |%12s| |%30s|\n", "Sr.no","Name", "Phone", "Email");
    printf("-----------------------------------------------");

    for(int i = 0; i < addresslist->contactCount; i++)
    {
        printf("|%5.4d| |%20.20s| |%12.12s| |%30.30s|\n", i + 1, addresslist->contacts[i].name, addresslist->contacts[i].phone, addresslist->contacts[i].email);
    }

    printf("-----------------------------------------------");
}

void read_phone(char phone[], int size, AddressBook *create, int *temp_phone)
{
    fgets(phone, size, stdin);
    clear_buffer();

    // Validate phone number format
    if (strlen(phone) != 10 || strspn(phone, "0123456789") != 10) {
        printf("Invalid phone number. Please enter a 10-digit number.\n");
        chance++;
        return;
    }

    // Check if phone number already exists
    for (int i = 0; i < create->contactCount; i++) {
        if (strcmp(phone, create->contacts[i].phone) == 0) {
            printf("Phone number already exists. Please enter a different number.\n");
            chance++;
            return;
        }
    }

    *temp_phone = 1;
    chance = 0;
}

void createContact(AddressBook *create)
{
    char temp_name[50], temp_phone[20], temp_email[50];

    int nameExists = 0;
    int phoneExists = 0;
    int emailExists = 0;

    while(chance <= 3)
    {
        //Read name
        if(!nameExists)
        {
            printf("Enter name: ");
            read_name(temp_name, sizeof(temp_name), create, &nameExists);

            if(!nameExists)
            {
                continue;
            }
        }

        if(!phoneExists)
        {
            printf("Enter phone number: ");
            read_phone(temp_phone, sizeof(temp_phone), create, &phoneExists);

            if(!phoneExists)
            {
                continue;
            }
        }

         if(!emailExists)
        {
            printf("Enter email: ");
            read_email(temp_email, sizeof(temp_email), create, &emailExists );

            if(!emailExists)
            {
                continue;
            }
        }

    }


}