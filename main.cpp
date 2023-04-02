#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <cstdio>

using namespace std;

struct User
{
    int userID;
    string userName, password;
};
struct Contact
{
    int contactIDNumber = 0;
    int userIDNumber = 0;
    string contactFirstName = "", contactSurname = "", contactPhoneNumber = "", contactEmailAdress = "", contactAddress = "";
};

string readLine()
{
    string line = "";
    cin.sync();
    getline(cin, line);
    return line;
}

void loadUsersDataToVector(vector <User> & users)
{
    User dataFromFile;
    fstream contactsStorageFile;
    string lineFromFile;
    string fileLineFragment = "";
    string fileSingleCharacter = "";
    int dataSeparatorNumber = 0;
    int fileLineNumber = 0;
    int fileCharacterNumber = 0;
    contactsStorageFile.open("dane-uzytkownikow.txt",ios::in | ios::app);
    if(contactsStorageFile.good() == false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
        exit(0);
    }
    while(getline(contactsStorageFile,lineFromFile))
    {
        int numberOfCharactersToSeparate = lineFromFile.length();
        while(numberOfCharactersToSeparate > 0)
        {
            fileSingleCharacter = lineFromFile[fileCharacterNumber];
            if(fileSingleCharacter != "|")
            {
                fileLineFragment += fileSingleCharacter;
                numberOfCharactersToSeparate--;
                fileCharacterNumber++;
                continue;
            }
            else if(fileSingleCharacter == "|")
            {
                dataSeparatorNumber += 1;
                numberOfCharactersToSeparate--;
                fileCharacterNumber++;
            }
            switch(dataSeparatorNumber)
            {
            case 1:
                dataFromFile.userID = atoi(fileLineFragment.c_str());
                fileLineFragment = "";
                break;
            case 2:
                dataFromFile.userName = fileLineFragment;
                fileLineFragment = "";
                break;
            case 3:
                dataFromFile.password = fileLineFragment;
                fileLineFragment = "";
                fileLineNumber++;
                dataSeparatorNumber = 0;
                fileCharacterNumber = 0;
                users.push_back(dataFromFile);
                break;
            }
        }
    }
    contactsStorageFile.close();
}

void loadContactDataToVector(vector <Contact> & contacts, int loggedUserID)
{
    Contact dataFromFile;
    fstream textFile;
    string lineFromFile;
    string lineFragment = "";
    string fileSingleCharacter = "";
    int dataSeparatorNumber = 0;
    int fileLineNumber = 0;
    int fileCharacterNumber = 0;

    textFile.open("adresaci.txt",ios::in | ios::app);
    if(textFile.good() == false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
        exit(0);
    }
    while(getline(textFile,lineFromFile))
    {
        int numberOfCharactersToSeparate = lineFromFile.length();
        while(numberOfCharactersToSeparate > 0)
        {
            fileSingleCharacter = lineFromFile[fileCharacterNumber];
            if(fileSingleCharacter != "|")
            {
                lineFragment += fileSingleCharacter;
                numberOfCharactersToSeparate--;
                fileCharacterNumber++;
                continue;
            }
            else if(fileSingleCharacter == "|")
            {
                dataSeparatorNumber += 1;
                numberOfCharactersToSeparate--;
                fileCharacterNumber++;
            }
            switch(dataSeparatorNumber)
            {
            case 1:
                dataFromFile.contactIDNumber = atoi(lineFragment.c_str());
                lineFragment = "";
                break;
             case 2:
                dataFromFile.userIDNumber = atoi(lineFragment.c_str());
                lineFragment = "";
                break;
            case 3:
                dataFromFile.contactFirstName = lineFragment;
                lineFragment = "";
                break;
            case 4:
                dataFromFile.contactSurname = lineFragment;
                lineFragment = "";
                break;
            case 5:
                dataFromFile.contactPhoneNumber = lineFragment;
                lineFragment = "";
                break;
            case 6:
                dataFromFile.contactEmailAdress = lineFragment;
                lineFragment = "";
                break;
            case 7:
                dataFromFile.contactAddress = lineFragment;
                lineFragment = "";
                fileLineNumber++;
                dataSeparatorNumber = 0;
                fileCharacterNumber = 0;

                if(loggedUserID == 0)
                {
                    contacts.push_back(dataFromFile);
                }
                else if(dataFromFile.userIDNumber == loggedUserID)
                {
                    contacts.push_back(dataFromFile);
                }
                break;
            }
        }
    }
    textFile.close();
}

void saveUserDataInFile(vector <User> & users,User & newData)
{
    fstream dataFile;
    dataFile.open("dane-uzytkownikow.txt",ios::out | ios::app);
    dataFile << newData.userID << "|" << newData.userName << "|";
    dataFile << newData.password << "|" << endl;
    dataFile.close();
}

void saveContactDataInFile(vector <Contact> & specificUserContacts,Contact & newData)
{
    fstream allContactsFile;
    fstream temporaryFile;
    string lineFromContactFile = "";

    allContactsFile.open("adresaci.txt",ios::in);
    temporaryFile.open("temp.txt",ios::out | ios::app);
    while(getline(allContactsFile, lineFromContactFile))
    {
        temporaryFile << lineFromContactFile << endl;
    }
    temporaryFile << newData.contactIDNumber << "|" << newData.userIDNumber << "|" << newData.contactFirstName << "|";
    temporaryFile << newData.contactSurname << "|" << newData.contactPhoneNumber << "|";
    temporaryFile << newData.contactEmailAdress << "|" << newData.contactAddress << "|" << endl;
    allContactsFile.close();
    temporaryFile.close();
    remove("adresaci.txt");
    rename("temp.txt", "adresaci.txt");
}

void changeUserPasswordInFile(vector <User> & users)
{
    fstream contactsStorageFile;

    remove("dane-uzytkownikow.txt");
    contactsStorageFile.open("dane-uzytkownikow.txt",ios::out | ios::app);

    for(int i = 0; i < (int) users.size(); i++)
    {
        contactsStorageFile << users[i].userID << "|" << users[i].userName << "|";
        contactsStorageFile << users[i].password << "|"  << endl;
    }
    contactsStorageFile.close();
}

void userRegistration(vector <User> & users)
{
    string userName, password;
    User newUserData;
    int numberOfRegisteredUsers = users.size();
    int lastIndexOnList = 0;
    int lastUserIDOnList = 0;
    int i = 0;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> userName;
    while (i < numberOfRegisteredUsers)
    {
        if (users[i].userName == userName)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> userName;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;
    newUserData.userName = userName;
    newUserData.password = password;
    if(numberOfRegisteredUsers == 0)
    {
        newUserData.userID = 1;
    }
    else
    {
        lastIndexOnList = numberOfRegisteredUsers - 1;
        lastUserIDOnList = users[lastIndexOnList].userID;
        newUserData.userID = lastUserIDOnList + 1;
    }

    users.push_back(newUserData);
    cout << "Konto Utworzone!" << endl;
    saveUserDataInFile(users, newUserData);
    Sleep(1000);
}

int logIn(vector <User> & users)
{
    string userName, password;
    int numberOfRegisteredUsers = users.size();
    cout << "Podaj loging: ";
    cin >> userName;
    int i = 0;

    while (i < numberOfRegisteredUsers)
    {
        if (users[i].userName == userName)
        {
            for(int checks = 0; checks < 3; checks++)
            {
                cout << "Podaj haslo. Pozostalo " << 3-checks << " prob: ";
                cin >> password;
                if (users[i].password == password)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return users[i].userID;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sek. przed kolejna proba.";
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika.";
    Sleep(2000);
    return 0;
}

void changePassword(vector <User> & users, int loggedUserID)
{
    string newPassword;
    int numberOfRegisteredUsers = users.size();
    cout << "Podaj haslo: ";
    cin >> newPassword;
    for (int i = 0; i < numberOfRegisteredUsers; i++)
    {
        if (users[i].userID == loggedUserID)
        {
            users[i].password = newPassword;
            cout << "Haslo zostalo zmienione" << endl;
            changeUserPasswordInFile(users);
            Sleep(1500);
        }
    }
}

void provideContactData(vector <Contact> & contacts, int userIDNumber)
{
    Contact newData;
    vector <Contact> allContactsOnList;
    loadContactDataToVector(allContactsOnList,0);
    int numberOfPeopleOnList = allContactsOnList.size();

    cout << "Wprowadz nowe dane: " << endl;
    cout << "Imie: ";
    newData.contactFirstName = readLine();

    cout << "Nazwisko: ";
    newData.contactSurname = readLine();

    cout << "Numer telefonu: ";
    newData.contactPhoneNumber = readLine();

    cout << "Email: ";
    newData.contactEmailAdress = readLine();

    cout << "Adres: ";
    newData.contactAddress = readLine();

    if(numberOfPeopleOnList == 0)
    {
        newData.contactIDNumber = 1;
    }
    else
    {
        newData.contactIDNumber = allContactsOnList[numberOfPeopleOnList-1].contactIDNumber + 1;
    }
    newData.userIDNumber = userIDNumber;
    contacts.push_back(newData);
    saveContactDataInFile(contacts,newData);
}

void searchByFirstName(vector <Contact> & contacts)
{
    string searchedFirstName;
    cout << "Wprowadz imie adresata, ktorego danych poszukujesz: ";
    searchedFirstName = readLine();

    if(contacts.size() == 0)
    {
        cout << "Na liscie nie ma danych do wyswietlenia" << endl;
        system("pause");
        return;
    }

    for(int i=0; i <= (int) contacts.size(); i++)
    {
        if(searchedFirstName == contacts[i].contactFirstName)
        {
            cout << "Znaleziono dane osoby o imieniu " << searchedFirstName << ":" << endl;
            cout << "Numer ID: " << contacts[i].contactIDNumber << endl;
            cout << "Imie: " << contacts[i].contactFirstName << endl;
            cout << "Nazwisko: " << contacts[i].contactSurname << endl;
            cout << "Numer telefonu: " << contacts[i].contactPhoneNumber << endl;
            cout << "Email: " << contacts[i].contactEmailAdress << endl;
            cout << "Adres: " << contacts[i].contactAddress << endl;
            cout << endl;
        }
        if((i == (int) contacts.size()) && (searchedFirstName != contacts[i-1].contactFirstName)) cout << "Nie znaleziono osoby o takim imieniu" << endl;
    }
    system("pause");
}

void searchBySurname(vector <Contact> & contacts)
{
    string searchedSurname;
    cout << "Wprowadz nazwisko adresata, ktorego danych poszukujesz: ";
    cin.sync();
    getline(cin, searchedSurname);

    if(contacts.size() == 0)
    {
        cout << "Na liscie nie ma danych do wyswietlenia" << endl;
        system("pause");
        return;
    }

    for(int i=0; i <= (int) contacts.size(); i++)
    {
        if(searchedSurname == contacts[i].contactSurname)
        {
            cout << "Znaleziono dane osoby o nazwisku " << searchedSurname << ":" << endl;
            cout << "Numer ID: " << contacts[i].contactIDNumber << endl;
            cout << "Imie: " << contacts[i].contactFirstName << endl;
            cout << "Nazwisko: " << contacts[i].contactSurname << endl;
            cout << "Numer telefonu: " << contacts[i].contactPhoneNumber << endl;
            cout << "Email: " << contacts[i].contactEmailAdress << endl;
            cout << "Adres: " << contacts[i].contactAddress << endl;
            cout << endl;
        }
        if((i == (int) contacts.size()) && (searchedSurname != contacts[i-1].contactSurname)) cout << "Nie znaleziono osoby o takim nazwisku" << endl;

    }
    system("pause");
}

void displayAllUsersContacts(vector <Contact> & contacts)
{
    cout << "Lista kontaktow: " << endl;
    cout << "___________________________" << endl;

    if(contacts.size() == 0) cout << "Na liscie nie ma danych, aby wyswietlac informacje, dodaj adresatow do listy" << endl;

    for(int i = 0; i < (int) contacts.size(); i++)
    {
        cout << contacts[i].contactIDNumber <<"|"<< contacts[i].userIDNumber << "|" << contacts[i].contactFirstName << "|";
        cout << contacts[i].contactSurname << "|" << contacts[i].contactPhoneNumber << "|";
        cout << contacts[i].contactEmailAdress << "|" << contacts[i].contactAddress << "|" << endl;
    }
    system("pause");
}

void saveChangesInContactsFile(vector <Contact> & specificUsersContacts, int editedContactID, int indexNumber)
{
    fstream allContactsFile;
    fstream temporaryFile;
    string lineFromContactFile = "";
    string idFromLine = "";
    string singleCharacterFromFileLine = "";
    int i = 0;
    int contactIDFromFile = 0;
    int lineFromFileNumber = 0;

    allContactsFile.open("adresaci.txt",ios::in);
    temporaryFile.open("temp.txt",ios::out | ios::app);
    while(getline(allContactsFile, lineFromContactFile))
    {
        singleCharacterFromFileLine = lineFromContactFile[i];
        while(singleCharacterFromFileLine != "|")
        {
            idFromLine += singleCharacterFromFileLine;
            i++;
            singleCharacterFromFileLine = lineFromContactFile[i];
        }
        contactIDFromFile = atoi(idFromLine.c_str());
        if(contactIDFromFile == editedContactID)
        {
          temporaryFile << specificUsersContacts[indexNumber].contactIDNumber << "|" << specificUsersContacts[indexNumber].userIDNumber << "|";
          temporaryFile << specificUsersContacts[indexNumber].contactFirstName << "|" << specificUsersContacts[indexNumber].contactSurname << "|";
          temporaryFile << specificUsersContacts[indexNumber].contactPhoneNumber << "|" << specificUsersContacts[indexNumber].contactEmailAdress << "|";
          temporaryFile << specificUsersContacts[indexNumber].contactAddress << "|" << endl;
        }
        else if(contactIDFromFile != editedContactID)
        {
            temporaryFile << lineFromContactFile << endl;
        }
        i = 0;
        idFromLine = "";
        lineFromFileNumber ++;
    }
    allContactsFile.close();
    temporaryFile.close();
    remove("adresaci.txt");
    rename("temp.txt", "adresaci.txt");

}

void editSpecifiedContactData(vector <Contact> & contacts)
{
    Contact contactDataToEdition;
    char optionNumber;
    int contactsIDToChange;
    int idIndexOfContact = 0;
    int numberFoundOnListIndicator = 0;

    string dataToEdition;
    system("cls");
    cout << "Edycja danych" << endl;
    cout << "________________________" << endl;
    cout << "Wybierz, ktore dane chcesz edytowac" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu glownego" << endl;
    cin.sync();
    optionNumber = getch();

    system("cls");
    if(optionNumber != '6')
    {
        displayAllUsersContacts(contacts);
        cout << "Wprowadz numer ID adresata, ktorego dane chcesz zmienic: ";
        cin.sync();
        cin >> contactsIDToChange;

        for(int i = 0; i < (int) contacts.size(); i++)
        {
            if(contacts[i].contactIDNumber == contactsIDToChange)
            {
                idIndexOfContact = i;
                numberFoundOnListIndicator =+ 1;
            }
        }
        if(numberFoundOnListIndicator == 0)
        {
            cout << "Na liscie nie ma danych pod wskazanym numerem indeksu" << endl;
            system("pause");
            return;
        }
    }
    contactDataToEdition = contacts[idIndexOfContact];
    switch(optionNumber)
    {
    case '1':
    {
        cout << "Wprowadz aktualne imie: ";
        dataToEdition = readLine();
        contacts[idIndexOfContact].contactFirstName = dataToEdition;
        saveChangesInContactsFile(contacts,  contactsIDToChange, idIndexOfContact);
        cout << "Dane zostaly zmienione: " << endl;
        system("pause");
        break;
    }
    case '2':
    {
        cout << "Wprowadz aktualne nazwisko: ";
        dataToEdition = readLine();
        contacts[idIndexOfContact].contactSurname = dataToEdition;
        saveChangesInContactsFile(contacts,  contactsIDToChange, idIndexOfContact);
        cout << "Dane zostaly zmienione" << endl;
        system("pause");
        break;
    }
    case '3':
    {
        cout << "Wprowadz aktualny numer telefonu: ";
        dataToEdition = readLine();
        contacts[idIndexOfContact].contactPhoneNumber = dataToEdition;
        saveChangesInContactsFile(contacts,  contactsIDToChange, idIndexOfContact);
        cout << "Dane zostaly zmienione" << endl;
        system("pause");
        break;
    }
    case '4':
    {
        cout << "Wprowadz aktualny email: ";
        dataToEdition = readLine();
        contacts[idIndexOfContact].contactEmailAdress = dataToEdition;
        saveChangesInContactsFile(contacts,  contactsIDToChange, idIndexOfContact);
        cout << "Dane zostaly zmienione" << endl;
        system("pause");
        break;
    }
    case '5':
    {
        cout << "Wprowadz aktualny adres: ";
        dataToEdition = readLine();
        contacts[idIndexOfContact].contactAddress = dataToEdition;
        saveChangesInContactsFile(contacts,  contactsIDToChange, idIndexOfContact);
        cout << "Dane zostaly zmienione" << endl;
        system("pause");
        break;
    }
    case '6':
    {
        break;
    }
    }
}

void displaySpecifiedIDData(vector <Contact> & contacts, int numerID)
{
        for(int i = 0; i <(int) contacts.size(); i++)
        {
            if(contacts[i].contactIDNumber == numerID)
            {
                cout << contacts[i].contactIDNumber << "|" << contacts[i].contactFirstName << "|";
                cout << contacts[i].contactSurname << "|" << contacts[i].contactPhoneNumber << "|";
                cout << contacts[i].contactEmailAdress << "|" << contacts[i].contactAddress << "|" << endl;
                break;
            }
        }
}

void deleteSpecifiedContactFromFile(vector <Contact> & contacts, int specifiedContactIDInVector)
{
    fstream allContactsFile;
    fstream temporaryFile;
    string lineFromContactFile = "";
    string idFromLine = "";
    string singleCharacterFromFileLine = "";
    int i = 0;
    int contactIDFromFile = 0;

    allContactsFile.open("adresaci.txt",ios::in);
    temporaryFile.open("temp.txt",ios::out | ios::app);
    while(getline(allContactsFile, lineFromContactFile))
    {
        singleCharacterFromFileLine = lineFromContactFile[i];
        while(singleCharacterFromFileLine != "|")
        {
            idFromLine += singleCharacterFromFileLine;
            i++;
            singleCharacterFromFileLine = lineFromContactFile[i];
        }
        contactIDFromFile = atoi(idFromLine.c_str());
        if(contactIDFromFile == specifiedContactIDInVector)
        {
          ;
        }
        else if(contactIDFromFile != specifiedContactIDInVector)
        {
            temporaryFile << lineFromContactFile << endl;
        }
        i = 0;
        idFromLine = "";
    }
    allContactsFile.close();
    temporaryFile.close();
    remove("adresaci.txt");
    rename("temp.txt", "adresaci.txt");

}

void deleteSpecifiedContactData(vector <Contact> & contacts)
{
    int contactIDToDelete, numberFoundOnListIndicator = 0, specifiedContactIDInVector = 0;
    char choiceIndicator;
    vector <Contact> newDataSet;
    cout << "USUWANE DANYCH" << endl;
    cout << "________________________" << endl;
    displayAllUsersContacts(contacts);
    cout << "Wprowadz numer ID adresata, ktorego dane chcesz usunac: ";
    cin >> contactIDToDelete;

    for(int i = 0; i < (int) contacts.size(); i++)
    {
        if(contacts[i].contactIDNumber == contactIDToDelete)
        {
            system("cls");
                cout << "USUWANE DANYCH" << endl;
    cout << "________________________" << endl;
            specifiedContactIDInVector = i;
            cout << endl << "Dane wskazanego adresata: ";
            displaySpecifiedIDData(contacts, contactIDToDelete);
            numberFoundOnListIndicator =+ 1;
            break;
        }
    }
    if(numberFoundOnListIndicator == 0)
    {
        cout << "Na liscie pod wskazanym numerem nie ma danych" << endl;
        system("pause");
        return;
    }

    cout << "Czy usunac dane adresata o numerze " << contactIDToDelete << "? (T/N)" << endl;

    choiceIndicator = getch();
    if((choiceIndicator == 'T') || (choiceIndicator == 't'))
    {
        deleteSpecifiedContactFromFile(contacts, contactIDToDelete);
        cout << "Dane zostaly usuniete" << endl;
        contacts.erase(contacts.begin() + specifiedContactIDInVector);
        system("pause");
    }
    else if ((choiceIndicator == 'N') || (choiceIndicator == 'n'));
}

int main()
{
    vector <User> users;
    vector <Contact> contacts;
    int loggedUserID = 0;
    char menuOptionNumber;

    loadUsersDataToVector(users);

    while (1)
    {
        if (loggedUserID == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            menuOptionNumber = getch();

            if (menuOptionNumber == '1')
            {
                userRegistration(users);
            }
            else if (menuOptionNumber == '2')
            {
                loggedUserID = logIn(users);
                contacts.clear();
                loadContactDataToVector(contacts,loggedUserID);
            }
            else if (menuOptionNumber == '9')
            {
                    exit(0);
            }
        }
        else
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Edytuj adresata" << endl;
            cout << "6. Usun adresata" << endl;
            cout << "------------------" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wylogowanie" << endl;

            menuOptionNumber = getch();
            system("cls");

            switch(menuOptionNumber)
            {
             case '1':
                provideContactData(contacts, loggedUserID);
                break;
            case '2':
                searchByFirstName(contacts);
                break;
            case '3':
                searchBySurname(contacts);
                break;
            case '4':
                displayAllUsersContacts(contacts);
                break;
            case '5':
                editSpecifiedContactData(contacts);
                break;
            case '6':
                deleteSpecifiedContactData(contacts);
                break;
            case '7':
                changePassword(users, loggedUserID);
                break;
            case '8':
                loggedUserID = 0;
                break;
            }
        }
    }

    return 0;
}
