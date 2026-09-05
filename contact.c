#include "contact.h"
#include<stdio.h>
#include<ctype.h>


//using this veriable for the crate contact function to keep track of chnace given to user to enter valid inputs
static int chance ;

void clear_buffer()
{
    char ch;
    while ((ch=getchar()) !='\n' && ch != EOF );
    
}

int read_name(char temp_name[],int size,AddressBook *create,int editIndex)
{
    int space = 0;

    temp_name[strcspn(temp_name, "\n")] = '\0';

    if (strlen(temp_name) == 0)
    {
        printf("Name cannot be empty.\n");
        return 0;
    }

    for (int i = 0; temp_name[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)temp_name[i]))
        {
            continue;
        }
        else if (temp_name[i] == ' ')
        {
            space++;

            if (space > 3)
            {
                printf("Too many spaces. Try again.\n");
                return 0;
            }
        }
        else
        {
            printf("Name should contain only "
                   "alphabets and spaces.\n");
            return 0;
        }
    }

    for (int i = 0; i < create->contactCount; i++)
    {
        if (i != editIndex)
        {
            if (strcmp(temp_name,
                       create->contacts[i].name) == 0)
            {
                printf("Name already exists. "
                       "Please enter a different name.\n");

                return 0;
            }
        }
    }

    return 1;
}

int read_phone(char temp_phone[],int size,AddressBook *create,int editIndex)
{
    temp_phone[strcspn(temp_phone, "\n")] = '\0';

    if (strlen(temp_phone) != 10)
    {
        printf("Invalid phone number. "
               "Please enter a 10-digit number.\n");

        return 0;
    }

    for (int i = 0; temp_phone[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)temp_phone[i]))
        {
            printf("Phone number should contain "
                   "only digits.\n");

            return 0;
        }
    }

    for (int i = 0; i < create->contactCount; i++)
    {
        if (i != editIndex)
        {
            if (strcmp(temp_phone,
                       create->contacts[i].phone) == 0)
            {
                printf("Phone number already exists. "
                       "Please enter a different number.\n");

                return 0;
            }
        }
    }

    return 1;
}

int read_email(char temp_email[],int size,AddressBook *create,int editIndex)
{
    char *at;
    char *dot;

    temp_email[strcspn(temp_email, "\n")] = '\0';

    if (strlen(temp_email) == 0)
    {
        printf("Email cannot be empty.\n");
        return 0;
    }

    at = strchr(temp_email, '@');

    if (at == NULL || at == temp_email)
    {
        printf("Invalid Email ID.\n");
        return 0;
    }

    if (strchr(at + 1, '@') != NULL)
    {
        printf("Invalid Email ID.\n");
        return 0;
    }

    dot = strchr(at + 1, '.');

    if (dot == NULL || *(dot + 1) == '\0')
    {
        printf("Invalid Email ID.\n");
        return 0;
    }

    for (int i = 0; i < create->contactCount; i++)
    {
        if (i != editIndex)
        {
            if (strcmp(temp_email,
                       create->contacts[i].email) == 0)
            {
                printf("Email ID already exists. "
                       "Please enter a different Email ID.\n");

                return 0;
            }
        }
    }

    return 1;
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

void createContact(AddressBook *create)
{
    char temp_name[50];
    char temp_phone[20];
    char temp_email[50];

    int nameValid = 0;
    int phoneValid = 0;
    int emailValid = 0;

    if (create->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full.\n");
        return;
    }

    while (!nameValid)
    {
        printf("Enter name: ");

        fgets(temp_name,sizeof(temp_name),stdin);

        nameValid = read_name(temp_name,sizeof(temp_name),create,-1);
    }

    while (!phoneValid)
    {
        printf("Enter phone number: ");

        fgets(temp_phone,
              sizeof(temp_phone),
              stdin);

        phoneValid = read_phone(temp_phone,sizeof(temp_phone),create,-1);
    }

    while (!emailValid)
    {
        printf("Enter email: ");

        fgets(temp_email,sizeof(temp_email),stdin);

        emailValid = read_email(temp_email,sizeof(temp_email),create,-1);
    }

    int index = create->contactCount;

    strcpy(create->contacts[index].name,temp_name);

    strcpy(create->contacts[index].phone,temp_phone);

    strcpy(create->contacts[index].email,temp_email);

    create->contactCount++;

    printf("Contact created successfully.\n");
}

int search_disp(AddressBook *book,char string[],int size,int op,int matchIndex[])
{
    int found = 0;

    printf("-----------------------------------------------\n");
    printf("|%5s|%20s|%12s|%30s|\n",
           "Sr.no", "Name", "Phone", "Email");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < book->contactCount; i++)
    {
        int match = 0;

        if (op == 1)
        {
            if (strstr(book->contacts[i].name, string) != NULL)
                match = 1;
        }
        else if (op == 2)
        {
            if (strstr(book->contacts[i].phone, string) != NULL)
                match = 1;
        }
        else if (op == 3)
        {
            if (strstr(book->contacts[i].email, string) != NULL)
                match = 1;
        }

        if (match)
        {
            printf("|%5d|%20.20s|%12.12s|%30.30s|\n",
                   i + 1,
                   book->contacts[i].name,
                   book->contacts[i].phone,
                   book->contacts[i].email);

            matchIndex[found] = i;

            found++;
        }
    }

    printf("-----------------------------------------------\n");

    if (found == 0)
    {
        printf("Contact not found.\n");
    }

    return found;
}

void searchContact(AddressBook *search)
{
    int op;
    char temp[50];
    //just bcz serch display function needs this input parameter 
    int matchIndex[MAX_CONTACTS];

    printf("\nSelect the option to search by\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone no\n");
    printf("3. Search by Email id\n");

    printf("Enter option: ");
    scanf("%d", &op);

    clear_buffer();

    if (op < 1 || op > 3)
    {
        printf("Invalid option.\n");
        return;
    }

    printf("Enter the search string: ");

    fgets(temp, sizeof(temp), stdin);

    temp[strcspn(temp, "\n")] = '\0';

    search_disp(search,temp,sizeof(temp),op,matchIndex);
}

void editContact(AddressBook *edit)
{
    char name[50];

    int matchIndex[MAX_CONTACTS];

    printf("Enter the name to search: ");

    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = '\0';

    int found = search_disp(edit,name,sizeof(name),1,matchIndex);

    if (found == 0)
    {
        return;
    }

    int selectedIndex;

    // Only one result 

    if (found == 1)
    {
        selectedIndex = matchIndex[0];
    }

    // Multiple results 
    else
    {
        int choice;

        printf("\nMultiple contacts found.\n");
        printf("Enter Sr.no of contact to edit: ");

        scanf("%d", &choice);

        clear_buffer();

        selectedIndex = -1;


        for (int i = 0; i < found; i++)
        {
            if (matchIndex[i] == choice - 1)
            {
                selectedIndex = matchIndex[i];
                break;
            }
        }


        if (selectedIndex == -1)
        {
            printf("Invalid selection.\n");
            return;
        }
    }

    //Show selected contact

    printf("\nSelected Contact:\n");

    printf("Name  : %s\n",edit->contacts[selectedIndex].name);

    printf("Phone : %s\n",edit->contacts[selectedIndex].phone);

    printf("Email : %s\n",edit->contacts[selectedIndex].email);

    char temp_name[50];
    char temp_phone[20];
    char temp_email[50];


    // New name 

    printf("\nEnter new name: ");

    fgets(temp_name,sizeof(temp_name),stdin);

    if (!read_name(temp_name,sizeof(temp_name),edit,selectedIndex))
    {
        printf("Invalid name. Edit cancelled.\n");
        return;
    }


    // New phone

    printf("Enter new phone: ");

    fgets(temp_phone,sizeof(temp_phone),stdin);

    if (!read_phone(temp_phone,sizeof(temp_phone),edit,selectedIndex))
    {
        printf("Invalid phone. Edit cancelled.\n");
        return;
    }


    // New email

    printf("Enter new email: ");

    fgets(temp_email,sizeof(temp_email),stdin);

    if (!read_email(temp_email,sizeof(temp_email),edit,selectedIndex))
    {
        printf("Invalid email. Edit cancelled.\n");
        return;
    }

    // All valid -> update

    strcpy(edit->contacts[selectedIndex].name,temp_name);

    strcpy(edit->contacts[selectedIndex].phone,temp_phone);

    strcpy(edit->contacts[selectedIndex].email,temp_email);

    printf("\nContact updated successfully.\n");
}
