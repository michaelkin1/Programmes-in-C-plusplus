#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

const int INITIAL_SIZE = 10;

// Class representing a single transaction
class Transaktion {
private:
    string datum;                   // Date of the transaction
    string typ;                     // Type of the transaction
    string namn;                    // Name of the person who made the transaction
    double belopp;                  // Amount of the transaction
    int antal_kompisar;             // Number of friends involved in the transaction
    string* kompisar;               // Dynamic array of friends involved in the transaction

    void copyFrom(const Transaktion &other); // Helper function to copy from another Transaktion
    void free();                             // Helper function to free dynamically allocated memory

public:
    Transaktion();                          // Default constructor
    ~Transaktion();                         // Destructor
    Transaktion(const Transaktion &other);  // Copy constructor
    Transaktion& operator=(const Transaktion &other); // Assignment operator
    string hamtaNamn() const;              // Getter for the name
    double hamtaBelopp() const;            // Getter for the amount
    int hamtaAntalKompisar() const;        // Getter for the number of friends
    bool finnsKompis(const string &namnet) const; // Check if a specific friend is involved
    bool lasIn(istream &is);               // Load transaction details from input stream
    void skrivUt(ostream &os) const;       // Output transaction details to output stream
    void skrivTitel(ostream &os) const;    // Output title/header for transactions
};

// Copy data from another Transaktion object
void Transaktion::copyFrom(const Transaktion &other) {
    datum = other.datum;
    typ = other.typ;
    namn = other.namn;
    belopp = other.belopp;
    antal_kompisar = other.antal_kompisar;
    kompisar = new string[antal_kompisar];
    for (int i = 0; i < antal_kompisar; ++i) {
        kompisar[i] = other.kompisar[i];
    }
}

// Free dynamically allocated memory for friends array
void Transaktion::free() {
    delete[] kompisar;
}

// Default constructor initializes with default values
Transaktion::Transaktion() : belopp(0.0), antal_kompisar(0), kompisar(nullptr) {}

// Destructor calls free to clean up dynamically allocated memory
Transaktion::~Transaktion() {
    free();
}

// Copy constructor creates a copy of another Transaktion object
Transaktion::Transaktion(const Transaktion &other) : kompisar(nullptr) {
    copyFrom(other);
}

// Assignment operator handles self-assignment and copies from another Transaktion object
Transaktion& Transaktion::operator=(const Transaktion &other) {
    if (this == &other) return *this;
    free();
    copyFrom(other);
    return *this;
}

// Getters for private members
string Transaktion::hamtaNamn() const {
    return namn;
}

double Transaktion::hamtaBelopp() const {
    return belopp;
}

int Transaktion::hamtaAntalKompisar() const {
    return antal_kompisar;
}

// Check if a specific friend is involved in the transaction
bool Transaktion::finnsKompis(const string &namnet) const {
    for (int i = 0; i < antal_kompisar; ++i) {
        if (kompisar[i] == namnet) {
            return true;
        }
    }
    return false;
}

// Load transaction details from input stream
bool Transaktion::lasIn(istream &is) {
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;
    free();
    kompisar = new string[antal_kompisar];
    for (int i = 0; i < antal_kompisar; ++i) {
        is >> kompisar[i];
    }
    return !is.eof();
}

// Output transaction details to output stream
void Transaktion::skrivUt(ostream &os) const {
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar;
    for (int i = 0; i < antal_kompisar; ++i) {
        os << "\t" << kompisar[i];
    }
    os << endl;
}

// Output title/header for transactions
void Transaktion::skrivTitel(ostream &os) const {
    os << "Date\tType\tName\tAmount\tNumber and list of friends" << endl;
}

// Class representing a person
class Person {
private:
    string namn;                     // Name of the person
    double betalat_andras;           // Amount the person has paid for others
    double skyldig;                  // Amount the person owes

    void copyFrom(const Person &other); // Helper function to copy from another Person

public:
    Person();                        // Default constructor
    Person(const string &namn, double betalat_andras, double skyldig); // Parameterized constructor
    ~Person();                       // Destructor
    Person(const Person &other);    // Copy constructor
    Person& operator=(const Person &other); // Assignment operator
    string hamtaNamn() const;       // Getter for the name
    double hamtaBetalat() const;   // Getter for the amount paid for others
    double hamtaSkyldig() const;    // Getter for the amount owed
    void skrivUt(ostream &os) const; // Output person details to output stream
};

// Copy data from another Person object
void Person::copyFrom(const Person &other) {
    namn = other.namn;
    betalat_andras = other.betalat_andras;
    skyldig = other.skyldig;
}

// Default constructor initializes with default values
Person::Person() : betalat_andras(0.0), skyldig(0.0) {}

// Parameterized constructor initializes with specified values
Person::Person(const string &namn, double betalat_andras, double skyldig)
    : namn(namn), betalat_andras(betalat_andras), skyldig(skyldig) {}

// Destructor (default, no dynamic allocation to clean up)
Person::~Person() {}

// Copy constructor creates a copy of another Person object
Person::Person(const Person &other) {
    copyFrom(other);
}

// Assignment operator handles self-assignment and copies from another Person object
Person& Person::operator=(const Person &other) {
    if (this == &other) return *this;
    copyFrom(other);
    return *this;
}

// Getters for private members
string Person::hamtaNamn() const {
    return namn;
}

double Person::hamtaBetalat() const {
    return betalat_andras;
}

double Person::hamtaSkyldig() const {
    return skyldig;
}

// Output person details to output stream
void Person::skrivUt(ostream &os) const {
    os << namn << " has paid " << betalat_andras << " and owes " << skyldig << ". ";
    if (betalat_andras > skyldig) {
        os << "Should receive " << betalat_andras - skyldig << " from the pot!" << endl;
    } else {
        os << "Should add " << skyldig - betalat_andras << " to the pot!" << endl;
    }
}

// Class representing a list of persons
class PersonLista {
private:
    Person* personer;     // Dynamic array of persons
    int antal_personer;   // Number of persons in the list
    int capacity;         // Capacity of the array

    void copyFrom(const PersonLista &other); // Helper function to copy from another PersonLista
    void free();                         // Helper function to free dynamically allocated memory
    void resize(int new_capacity);       // Resize the array to a new capacity

public:
    PersonLista();                      // Default constructor
    ~PersonLista();                     // Destructor
    PersonLista(const PersonLista &other); // Copy constructor
    PersonLista& operator=(const PersonLista &other); // Assignment operator
    void laggTill(const Person &ny_person); // Add a new person to the list
    void skrivUtOchFixa(ostream &os) const; // Output person details and fix amounts
    double summaSkyldig() const;           // Calculate total amount owed by all persons
    double summaBetalat() const;           // Calculate total amount paid by all persons
    bool finnsPerson(const string &namn) const; // Check if a person is in the list
};

// Copy data from another PersonLista object
void PersonLista::copyFrom(const PersonLista &other) {
    capacity = other.capacity;
    antal_personer = other.antal_personer;
    personer = new Person[capacity];
    for (int i = 0; i < antal_personer; ++i) {
        personer[i] = other.personer[i];
    }
}

// Free dynamically allocated memory for persons array
void PersonLista::free() {
    delete[] personer;
}

// Resize the persons array to a new capacity
void PersonLista::resize(int new_capacity) {
    Person* new_personer = new Person[new_capacity];
    for (int i = 0; i < antal_personer; ++i) {
        new_personer[i] = personer[i];
    }
    delete[] personer;
    personer = new_personer;
    capacity = new_capacity;
}

// Default constructor initializes with default values
PersonLista::PersonLista() : antal_personer(0), capacity(INITIAL_SIZE) {
    personer = new Person[capacity];
}

// Destructor calls free to clean up dynamically allocated memory
PersonLista::~PersonLista() {
    free();
}

// Copy constructor creates a copy of another PersonLista object
PersonLista::PersonLista(const PersonLista &other) {
    copyFrom(other);
}

// Assignment operator handles self-assignment and copies from another PersonLista object
PersonLista& PersonLista::operator=(const PersonLista &other) {
    if (this == &other) return *this;
    free();
    copyFrom(other);
    return *this;
}

// Add a new person to the list, resizing if necessary
void PersonLista::laggTill(const Person &ny_person) {
    if (antal_personer >= capacity) {
        resize(capacity * 2);
    }
    personer[antal_personer++] = ny_person;
}

// Output person details and fix amounts
void PersonLista::skrivUtOchFixa(ostream &os) const {
    double total_skyldig = summaSkyldig();
    double total_betalat = summaBetalat();

    for (int i = 0; i < antal_personer; ++i) {
        personer[i].skrivUt(os);
    }
}

// Calculate total amount owed by all persons
double PersonLista::summaSkyldig() const {
    double summa = 0.0;
    for (int i = 0; i < antal_personer; ++i) {
        summa += personer[i].hamtaSkyldig();
    }
    return summa;
}

// Calculate total amount paid by all persons
double PersonLista::summaBetalat() const {
    double summa = 0.0;
    for (int i = 0; i < antal_personer; ++i) {
        summa += personer[i].hamtaBetalat();
    }
    return summa;
}

// Check if a person is in the list
bool PersonLista::finnsPerson(const string &namn) const {
    for (int i = 0; i < antal_personer; ++i) {
        if (personer[i].hamtaNamn() == namn) {
            return true;
        }
    }
    return false;
}

// Class representing a list of transactions
class TransaktionsLista {
private:
    Transaktion* transaktioner;   // Dynamic array of transactions
    int antal_transaktioner;      // Number of transactions in the list
    int capacity;                // Capacity of the array

    void copyFrom(const TransaktionsLista &other); // Helper function to copy from another TransaktionsLista
    void free();                          // Helper function to free dynamically allocated memory
    void resize(int new_capacity);        // Resize the array to a new capacity

public:
    TransaktionsLista();                // Default constructor
    ~TransaktionsLista();               // Destructor
    TransaktionsLista(const TransaktionsLista &other); // Copy constructor
    TransaktionsLista& operator=(const TransaktionsLista &other); // Assignment operator
    void lasIn(istream &is);            // Load transactions from input stream
    void skrivUt(ostream &os) const;    // Output transaction details to output stream
    void laggTill(const Transaktion &t); // Add a new transaction to the list
    double totalKostnad() const;        // Calculate total cost of all transactions
    double liggerUteMed(const string &namnet) const; // Calculate how much a person has advanced
    double arSkyldig(const string &namnet) const;   // Calculate how much a person owes
    PersonLista FixaPersoner() const;   // Create a list of persons with fixed amounts
};

// Copy data from another TransaktionsLista object
void TransaktionsLista::copyFrom(const TransaktionsLista &other) {
    capacity = other.capacity;
    antal_transaktioner = other.antal_transaktioner;
    transaktioner = new Transaktion[capacity];
    for (int i = 0; i < antal_transaktioner; ++i) {
        transaktioner[i] = other.transaktioner[i];
    }
}

// Free dynamically allocated memory for transactions array
void TransaktionsLista::free() {
    delete[] transaktioner;
}

// Resize the transactions array to a new capacity
void TransaktionsLista::resize(int new_capacity) {
    Transaktion* new_transaktioner = new Transaktion[new_capacity];
    for (int i = 0; i < antal_transaktioner; ++i) {
        new_transaktioner[i] = transaktioner[i];
    }
    delete[] transaktioner;
    transaktioner = new_transaktioner;
    capacity = new_capacity;
}

// Default constructor initializes with default values
TransaktionsLista::TransaktionsLista() : antal_transaktioner(0), capacity(INITIAL_SIZE) {
    transaktioner = new Transaktion[capacity];
}

// Destructor calls free to clean up dynamically allocated memory
TransaktionsLista::~TransaktionsLista() {
    free();
}

// Copy constructor creates a copy of another TransaktionsLista object
TransaktionsLista::TransaktionsLista(const TransaktionsLista &other) {
    copyFrom(other);
}

// Assignment operator handles self-assignment and copies from another TransaktionsLista object
TransaktionsLista& TransaktionsLista::operator=(const TransaktionsLista &other) {
    if (this == &other) return *this;
    free();
    copyFrom(other);
    return *this;
}

// Load transactions from input stream
void TransaktionsLista::lasIn(istream &is) {
    Transaktion t;
    while (t.lasIn(is)) {
        laggTill(t);
    }
}

// Output transaction details to output stream
void TransaktionsLista::skrivUt(ostream &os) const {
    os << "Number of transactions = " << antal_transaktioner << endl;
    for (int i = 0; i < antal_transaktioner; ++i) {
        transaktioner[i].skrivUt(os);
    }
}

// Add a new transaction to the list, resizing if necessary
void TransaktionsLista::laggTill(const Transaktion &t) {
    if (antal_transaktioner >= capacity) {
        resize(capacity * 2);
    }
    transaktioner[antal_transaktioner++] = t;
}

// Calculate total cost of all transactions
double TransaktionsLista::totalKostnad() const {
    double total = 0.0;
    for (int i = 0; i < antal_transaktioner; ++i) {
        total += transaktioner[i].hamtaBelopp();
    }
    return total;
}

// Calculate how much a person has advanced
double TransaktionsLista::liggerUteMed(const string &namnet) const {
    double summa = 0.0;
    for (int i = 0; i < antal_transaktioner; ++i) {
        if (transaktioner[i].hamtaNamn() == namnet) {
            summa += transaktioner[i].hamtaBelopp() * (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
        }
    }
    return summa;
}

// Calculate how much a person owes
double TransaktionsLista::arSkyldig(const string &namnet) const {
    double skuld = 0.0;
    for (int i = 0; i < antal_transaktioner; ++i) {
        if (transaktioner[i].finnsKompis(namnet)) {
            skuld += transaktioner[i].hamtaBelopp() / (transaktioner[i].hamtaAntalKompisar() + 1);
        }
    }
    return skuld;
}

// Create a list of persons with fixed amounts
PersonLista TransaktionsLista::FixaPersoner() const {
    PersonLista personlista;
    for (int i = 0; i < antal_transaktioner; ++i) {
        const string &namn = transaktioner[i].hamtaNamn();
        double betalat = liggerUteMed(namn);
        double skyldig = arSkyldig(namn);

        if (!personlista.finnsPerson(namn)) {
            Person ny_person(namn, betalat, skyldig);
            personlista.laggTill(ny_person);
        }
    }
    return personlista;
}

int main() {
    cout << "Starting by reading from a file." << endl;

    TransaktionsLista transaktioner;
    ifstream is("resa.txt");
    transaktioner.lasIn(is);

    int operation = 1;
    while (operation != 0) {
        cout << endl;
        cout << "Choose from the menu below:" << endl;
        cout << "0. Exit. All transactions will be saved to a file." << endl;
        cout << "1. Print information about all transactions." << endl;
        cout << "2. Enter a transaction from the keyboard." << endl;
        cout << "3. Calculate the total cost." << endl;
        cout << "4. How much does a certain person owe?" << endl;
        cout << "5. How much has a certain person advanced?" << endl;
        cout << "6. List all persons and fix the amounts." << endl;

        cout << "Choose an option: ";
        cin >> operation;
        cout << endl;

        switch (operation) {
            case 1: {
                transaktioner.skrivUt(cout);
                break;
            }
            case 2: {
                Transaktion transaktion;
                cout << "Enter the transaction in the following format:" << endl;
                transaktion.skrivTitel(cout);
                transaktion.lasIn(cin);
                transaktioner.laggTill(transaktion);
                break;
            }
            case 3:
            {
                cout << "The total cost for the trip was " << transaktioner.totalKostnad() << endl;
                break;
            }
            case 4:
            {
                cout << "Enter the person's name: ";
                string namn;
                cin >> namn;
                double ar_skyldig = transaktioner.arSkyldig(namn);
                if (ar_skyldig == 0.)
                    cout << "Cannot find the person " << namn << endl;
                else
                    cout << namn << " owes " << ar_skyldig << endl;
                break;
            }
            case 5:
            {
                cout << "Enter the person's name: ";
                string namn;
                cin >> namn;
                double ligger_ute_med = transaktioner.liggerUteMed(namn);
                if (ligger_ute_med == 0.)
                    cout << "Cannot find the person " << namn << endl;
                else
                    cout << namn << " has advanced " << ligger_ute_med << endl;
                break;
            }
            case 6:
            {
                cout << "Now creating a person array and sorting it out!" << endl;
                PersonLista lista = transaktioner.FixaPersoner();
                lista.skrivUtOchFixa(cout);
                break;
            }
        }
    }

    std::ofstream os("resa.txt");
    transaktioner.skrivUt(os);

    return 0;
}


