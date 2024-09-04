
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <exception>
using namespace std;

ifstream Inp;
ofstream Out; // Gobal
string getCurrentTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char currentDate[11];
    char currentTime[9];

    // Formatação de data: "DD/MM/YYYY"
    strftime(currentDate, sizeof(currentDate), "%d/%m/%Y", localTime);
    // Formatação de hora: "HH:MM:SS"
    strftime(currentTime, sizeof(currentTime), "%H:%M:%S", localTime);

    return string(currentDate) + " " + string(currentTime);
}
class User
{
protected:
	string username;
	string password;

public:
	User()
	{
	}
	User(string username, string password)
	{
		this->username = username;
		this->password = password;
	}

	virtual bool login() = 0;
	void setusername(string name)
	{
		username = name;
	}
	void setpassword(string pass)
	{
		password = pass;
	}
	void changePassword()
	{
		string newPassword;
		cout << "\t\t\tEntre com a nova senha: ";
		cin >> newPassword;
		password = newPassword;
		cout << "\t\t\tSenha modificada com sucesso!" << endl;
	}
	string getname()
	{
		return username;
	}
	string getpassword()
	{
		return password;
	}
	virtual ~User() {}
};

class Customer : public User
{
private:
public:
	Customer()
	{
	}
	Customer(string username, string password)
		: User(username, password)
	{
	}

	bool login()
	{
		string enteredPin, enteredpass;
		cout << "\t\t\tDigite o nome do usuário: ";
		cin >> enteredpass;
		cout << "\t\t\tDigite seu código PIN: ";
		cin >> enteredPin;

		if (enteredPin == "user" && enteredpass == "user")
		{
			cout << "\t\t\tLogin bem-sucedido" << endl;
			return true;
		}
		else
		{
			cout << "\t\t\tCódigo PIN inválido. Falha no login." << endl;
			cout << "\t\t\tSe quiser alterar a senha pressione Y" << endl;
			char y;
			cin >> y;
			if (y == 'Y' || y == 'y')
			{
				Customer::changePassword();

			}
			return false;
		}
	}
	~Customer() {

	}
};

class Admin : public User
{

public:
	Admin()
	{
		username = "admin";
		password = "admin";
	}
	Admin(string username, string password)
		: User(username, password)
	{
	}

	void display()
	{
		cout << "Administrador" << endl;
	}

	bool login()
	{
		string enter_Username, enter_Password;
		cout << "\t\t\tInsira o nome de usuário do administrador: ";
		cin >> enter_Username;
		cout << "\t\t\tDigite a senha do administrador: ";
		cin >> enter_Password;

		if (enter_Username == "admin" && enter_Password == "admin")
		{
			cout << "\t\t\tLogin de adminstrador realizado com sucesso !" << endl;
			return true;
		}
		else
		{
			cout << "\t\t\tCredencial de login Invalida. Login falhado." << endl;
			cout << "\t\t\tSe você deseja mudar a senha pressione Y" << endl;
			char y;
			cin >> y;
			if (y == 'Y' || y == 'y')
			{
				Admin::changePassword();

			}
			return false;
		}
	}
	~Admin() {

	}
};

class Account
{
protected:
	int accountNumber;
	string firstname;
	string lastname;
	double balance;
	string cardtype;
	string email;
	int phonenumber;

public:
	Account()
	{
		accountNumber = 0;
		firstname = "";
		lastname = "";
		balance = 0;
		cardtype = "";
		email = "";
		phonenumber = 0;
	}
	Account(string firstname, string lastname, int accountNumber, double balance, string cardtype, string email, int phonenumber)
	{
		this->accountNumber = accountNumber;
		this->balance = balance;
		this->cardtype = cardtype;
		this->email = email;
		this->phonenumber = phonenumber;
		this->firstname = firstname;
		this->lastname = lastname;
	}

	string getFirstName()
	{
		return firstname;
	}

	void setFirstName(string firstName)
	{
		firstname = firstName;
	}

	string getLastName()
	{
		return lastname;
	}

	void setLastName(string lastName)
	{
		lastname = lastName;
	}
	string getemail()
	{
		return email;
	}
	int getphone()
	{
		return phonenumber;
	}
	void setphone(int Num)
	{
		phonenumber = Num;
	}
	void setemail(string mail)
	{
		email = mail;
	}
	int getAccountNumber()
	{
		return accountNumber;
	}
	void setbalance(double bal)
	{
		balance = bal;
	}
	double getBalance()
	{
		return balance;
	}
	void setaccountnumber(int accno)
	{
		accountNumber = accno;
	}
	string getcardtype()
	{
		return cardtype;
	}
	void setcardtype(string type)
	{
		cardtype = type;
	}
	virtual void deposit(double amount) = 0;
	virtual void withdraw(double amount) = 0;
	virtual void display() const = 0;
	virtual void saveAccountData() = 0;
	virtual void serachaccount() = 0;
	virtual void Addaccount(int sz) = 0;
	virtual void updateaccount() = 0;
	virtual void deleteaccount(string filename, int size) = 0;

	virtual ~Account() {}
};

class SavingsAccount : public Account
{
private:
	string savedatafile;
	int size;
	Customer** customer;
	SavingsAccount** saveaccount;
	Admin admin;


public:
	SavingsAccount()
	{
		customer = nullptr;
		saveaccount = nullptr;
		size = 0;
	}
	SavingsAccount(string filename, int S)
	{
		this->savedatafile = filename;
		this->size = S;

		saveaccount = new SavingsAccount * [size];
		customer = new Customer * [size];
		for (int i = 0; i < size; i++)
		{
			saveaccount[i] = nullptr;
			customer[i] = nullptr;
		}

		Inp.open(filename);
		if (!Inp)
		{
			cout << "Falha ao abrir o salvamento do arquivo de dados da conta." << endl;
			return;
		}
		int index = 0;
		string line;
		while (getline(Inp, line))
		{

			istringstream SS(line);
			// Read data
			string fname, lname, user_nnam, pass_word, C_type, Email;
			int accountNO, phone_num;
			double bal;

			SS >> fname >> lname >> user_nnam >> pass_word >> accountNO >> bal >> C_type >> Email >> phone_num;

			customer[index] = new Customer(user_nnam, pass_word);
			saveaccount[index] = new SavingsAccount(fname, lname, accountNO, bal, C_type, Email, phone_num);

			index++;
			if (index >= size)
			{
				break; // to avoid buffer
			}
		}

		Inp.close();
	}

	SavingsAccount(string firstname, string lastname, int accountNumber, double balance, string cardtype, string email, int phonenumber)
		: Account(firstname, lastname, accountNumber, balance, cardtype, email, phonenumber)
	{
	}

	void deposit(double amount)
	{
		int accountno;
		cout << setw(30) << "\t\tDigite o número da conta: ";
		cin >> accountno;

		bool found = false;
		int Index = -1;

		for (int i = 0; i < size; i++)
		{
			if (saveaccount[i]->accountNumber == accountno)
			{
				found = true;
				Index = i;
				break;
			}

		}
		if (found)
		{
			if (customer[Index]->login())
			{
				saveaccount[Index]->balance += amount;
				cout << setw(30) << "\t\tDeposito de R$" << amount << " em conta " << saveaccount[Index]->accountNumber << " bem-sucedido" << endl;
				SavingsAccount::saveAccountData();
			}

		}
		else
		{
			cout << left << setw(30) << "\t\tConta não encontrada!" << endl;
		}
	}
	void withdraw(double amount)
	{
		int accountno;
		cout << setw(30) << "\t\tDigite o número da conta: ";
		cin >> accountno;

		bool found = false;
		int Index = -1;

		for (int i = 0; i < size; i++)
		{
			if (saveaccount[i]->getAccountNumber() == accountno)
			{
				found = true;
				Index = i;
				break;
			}

		}
		if (found)
		{
			if (customer[Index]->login())
			{
				try
				{
					if (saveaccount[Index]->balance < amount) {
						throw runtime_error("Insufficient balance in account: ");
					}
					else
					{
						saveaccount[Index]->balance -= amount;
						cout << setw(30) << "\t\t\tRetirada de R$" << amount << " da conta" << saveaccount[Index]->accountNumber << " bem-sucedida." << endl;
						SavingsAccount::saveAccountData();

					}

				}
				catch (runtime_error e)
				{
					cout << e.what() << endl;
					cout << "\t\t\tPor Favor, insira o saldo suficiente menor ou igual que o saldo da sua conta" << endl;
					double Amount_W;
					cout << "\t\t\tInsira o valor que deseja sacar" << endl;
					cin >> Amount_W;
					SavingsAccount::withdraw(Amount_W);

				}

			}

		}
		else
		{
			cout << "\t\t\t\tConta não encontrada" << endl;
		}
	}
	void updateaccount()
	{
		int updateaccount;
		SavingsAccount::display();

		cout << left << setw(30) << "\t\t\tInsira o numero de atualização da conta: ";
		cin >> updateaccount;
		string User, PASS, type, mail;
		double  Balance;
		int accNo;
		int phone_num;
		bool found = false;
		int updateIndex = -1;
		string fname, lname;
		for (int i = 0; i < size; i++)
		{
			if (saveaccount[i]->accountNumber == updateaccount)
			{
				cout << setw(30) << "\t\tNome: " << saveaccount[i]->getFirstName() << " " << saveaccount[i]->getLastName() << endl;
				cout << setw(30) << "\t\tNome de Usuário: " << customer[i]->getname() << endl;
				cout << setw(30) << "\t\tNúmero da Conta: " << saveaccount[i]->getAccountNumber() << endl;
				cout << setw(30) << "\t\tSaldo: R$" << saveaccount[i]->balance << endl;
				cout << setw(30) << "\t\tTipo de Cartão: " << saveaccount[i]->getcardtype() << endl;
				cout << setw(30) << "\t\tEmail: " << saveaccount[i]->getemail() << endl;
				cout << setw(30) << "\t\tNúmero de Celular: " << saveaccount[i]->getphone() << endl;
				found = true;
				updateIndex = i;
				break;
			}
		}
		if (found)
		{
			cout << setw(30) << "\t\tInsira o novo nome: ";
			cin >> fname;
			cout << setw(30) << "\t\tInsira o nove Sobrenome: ";
			cin >> lname;
			cout << setw(30) << "\t\tInsira o novo nome de usuário: ";
			cin >> User;

			cout << setw(30) << "\t\tDigite uma nova Senha: ";
			cin >> PASS;

			cout << setw(30) << "\t\tInsira um novo tipo de cartão: ";
			cin >> type;

			cout << setw(30) << "\t\tInsira o novo número da conta: ";
			cin >> accNo;

			cout << setw(30) << "\t\tInsira o novo Saldo inicial: ";
			cin >> Balance;

			cout << setw(30) << "\t\tDigite o novo Email: ";
			cin >> mail;

			cout << setw(30) << "\t\tDigite o novo número de celular: ";
			cin >> phone_num;

			customer[updateIndex]->setusername(User);
			customer[updateIndex]->setpassword(PASS);
			saveaccount[updateIndex]->setcardtype(type);
			saveaccount[updateIndex]->setaccountnumber(accNo);
			saveaccount[updateIndex]->setbalance(Balance);
			saveaccount[updateIndex]->setphone(phone_num);
			saveaccount[updateIndex]->setemail(mail);
			saveaccount[updateIndex]->setFirstName(fname);
			saveaccount[updateIndex]->setLastName(lname);

			cout << setw(30) << "\t\t\tConta editada com sucesso" << endl;
			SavingsAccount::saveAccountData();
		}
		else
		{
			cout << setw(30) << "\t\t\tConta não encontrada" << endl;
		}
	}
	
	void Addaccount(int S)
	{
		size = S;


		Out.open(savedatafile, ios::app); // Open the file
		if (!Out)
		{
			cout << left << setw(30) << "Não foi possível abrir o arquivo!" << endl;
			return;
		}

		cout << left << setw(30) << "\t\t\t\tREGISTRO DE CONTA DE CLIENTE" << endl;
		string us, pass, type;
		char c;
		bool added = false;
		do
		{
			cout << left << setw(30) << "\t\tInsira o nome: ";
			string firstname;
			cin >> firstname;

			cout << setw(30) << "\t\tInsira o Sobrenome: ";
			string lastname;
			cin >> lastname;

			cout << setw(30) << "\t\tCrie um usuário: ";
			cin >> us;

			cout << setw(30) << "\t\tDigite uma Senha: ";
			cin >> pass;

			cout << setw(30) << "\t\tInsira um tipo de cartão cartão: ";
			cin >> type;

			int accountNumber;
			cout << setw(30) << "\t\tInsira um número da conta: ";
			cin >> accountNumber;

			double balance;
			cout << setw(30) << "\t\tInsira o Saldo inicial: ";
			cin >> balance;

			string email;
			cout << setw(30) << "\t\tDigite o Email: ";
			cin >> email;

			int phoneNumber;
			cout << setw(30) << "\t\tDigite o número de celular: ";
			cin >> phoneNumber;


			added = true;
			if (added)
			{


				customer[size] = new Customer(us, pass);

				saveaccount[size] = new SavingsAccount(firstname, lastname, accountNumber, balance, type, email, phoneNumber);;

				size++;

				cout << left << setw(30) << "\t\tConta criado com sucesso  " << getCurrentTime() << endl;
				// Write the data to the file
				for (int i = size - 1; i < size; i++)
				{
					Customer* cust = customer[i];
					SavingsAccount* saveaccou = saveaccount[i];
					Out << left << setw(20) << saveaccou->getFirstName() << " "
						<< left << setw(20) << saveaccou->getLastName()
						<< left << setw(20) << cust->getname()
						<< left << setw(20) << cust->getpassword()
						<< left << setw(20) << saveaccou->getAccountNumber()
						<< left << setw(20) << saveaccou->getBalance()
						<< left << setw(20) << saveaccou->getcardtype()
						<< left << setw(20) << saveaccou->getemail()
						<< left << setw(20) << saveaccou->getphone()
						<< endl;
				}
				Out.close();
			}
			cout << left << setw(30) << "\t\tDeseja adicionar outro registro? Se sim digite S, ou não digite N: ";

			cin >> c;
		} while (c == 'S' || c == 'S');



	}

	void serachaccount()
	{
		int serachaccount;
		cout << setw(30) << "\t\t\tDigite o número da conta para pesquisar: ";
		cin >> serachaccount;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{
			if (saveaccount[i]->accountNumber == serachaccount)
			{

				found1 = true;
				Index = i;
				break;
			}

		}
		if (found1)
		{
			cout << "\t\t\tNome: " << saveaccount[Index]->getFirstName() << " " << saveaccount[Index]->getLastName() << endl;
			cout << "\t\t\tNome de Usuário: " << customer[Index]->getname() << endl;
			cout << "\t\t\tNúmero da Conta: " << saveaccount[Index]->getAccountNumber() << endl;
			cout << "\t\t\tSaldo: R$" << saveaccount[Index]->getBalance() << endl;
			cout << "\t\t\tTipo de Cartão: " << saveaccount[Index]->getcardtype() << endl;
			cout << "\t\t\tEmail: " << saveaccount[Index]->getemail() << endl;
			cout << "\t\t\tNumero de Celular: " << saveaccount[Index]->getphone() << endl;
		}

		else
		{
			cout << left << setw(30) << "Número da Conta não encontrado" << endl;
		}
	}
	void deleteaccount(string filename, int s)
	{
		int deleteacc;
		if (admin.login())
		{
			SavingsAccount::display();

			cout << left << setw(30) << "\t\tInsira o número da Conta que deseja excluir: ";
			cin >> deleteacc;
			bool found = false;
			int deleteIndex = -1;
			for (int i = 0; i < size; i++)
			{
				if (saveaccount[i]->getAccountNumber() == deleteacc)
				{
					cout << setw(30) << "\t\tNome: " << saveaccount[i]->getFirstName() << " " << saveaccount[i]->getLastName() << endl;
					cout << setw(30) << "\t\tNome do Usuário: " << customer[i]->getname() << endl;
					cout << setw(30) << "\t\tNúmero da Conta: " << saveaccount[i]->accountNumber << endl;
					cout << setw(30) << "\t\tSaldo: R$" << saveaccount[i]->balance << endl;
					cout << setw(30) << "\t\tTipo do Cartão: " << saveaccount[i]->getcardtype() << endl;
					cout << setw(30) << "\t\tEmail: " << saveaccount[i]->getemail() << endl;
					cout << setw(30) << "\t\tNúmero de Celular: " << saveaccount[i]->getphone() << endl;

					found = true;
					deleteIndex = i;
					break;
				}
			}
			if (found)
			{
				char a;
				cout << "\n\t\t\tSe você deseja excluir esta conta, digite Y...";
				cin >> a;
				if (a == 'Y' || a == 'y')
				{


					if (deleteIndex >= 0 && deleteIndex < size) {
						delete customer[deleteIndex];
						delete saveaccount[deleteIndex];
						for (int i = deleteIndex; i < size - 1; i++)
						{
							customer[i] = customer[i + 1];
							saveaccount[i] = saveaccount[i + 1];
						}
						size--;
						SavingsAccount::saveAccountData();
						cout << setw(30) << "\t\t\tConta deletada com sucesso ás " << getCurrentTime() << endl;
					}
				}
				else {
					cout << "\t\t\tConta não deletada" << endl;
				}
			}
			else
			{
				cout << left << setw(30) << "Conta não encontrada." << endl;
			}
		}

	}

	void saveAccountData()
	{
		Out.open(savedatafile, ios::out);

		if (!Out)
		{
			cout << setw(30) << "\t\t\tFalha ao abrir o arquivo de dados da conta salvada." << endl;
			return;
		}
		Customer* cust;
		SavingsAccount* saveaccou;
		// Write student
		for (int i = 0; i < size; i++)
		{
			cust = customer[i];
			saveaccou = saveaccount[i];
			Out << left << setw(20) << saveaccou->getFirstName() << " "
				<< left << setw(20) << saveaccou->getLastName()
				<< left << setw(20) << cust->getname()
				<< left << setw(20) << cust->getpassword()
				<< left << setw(20) << saveaccou->getAccountNumber()
				<< left << setw(20) << saveaccou->getBalance()
				<< left << setw(20) << saveaccou->getcardtype()
				<< left << setw(30) << saveaccou->getemail()
				<< left << setw(30) << saveaccou->getphone()
				<< endl;
		}
		Out.close();
	}

	void display() const
	{
		cout << left << setw(30) << "Tipo de conta: Poupança" << endl;
		cout << setw(50) << "================================PARA SALVAR LISTA DE CONTAS DOS CLIENTES=====================================" << endl;
		cout << left << setw(10) << "A/C"
			<< left << setw(20) << "Nome"
			<< left << setw(20) << "Número da Conta"
			<< left << setw(20) << "Nome de Usuário"
			<< left << setw(15) << "Tipo de Cartão"
			<< left << setw(30) << "Email"
			<< left << setw(15) << "Número de Celular"
			<< left << setw(15) << "Saldo"
			<< endl;

		for (int i = 0; i < size; i++)
		{
			cout << left << setw(10) << "Salvando" << left << setw(20) << saveaccount[i]->getFirstName() + " " + saveaccount[i]->getLastName()
				<< left << setw(20) << saveaccount[i]->getAccountNumber() << left << setw(20) << customer[i]->getname() << left << setw(15) << saveaccount[i]->getcardtype() << left << setw(30) << saveaccount[i]->getemail()
				<< left << setw(15) << saveaccount[i]->getphone() << left << setw(15) << saveaccount[i]->getBalance() << endl;
		}
	}

	~SavingsAccount()
	{
		SavingsAccount::saveAccountData();
		if (saveaccount != nullptr)

		{
			delete[] saveaccount;
		}
		if (customer != nullptr) {
			delete[] customer;
		}

	}
};

class CheckingAccount : public Account
{
private:
	string checkdatafile;
	int size;
	Customer** customer;
	CheckingAccount** checkaccount;
	Admin admin;
	double feecharge;
public:
	CheckingAccount() {
		customer = nullptr;
		checkaccount = nullptr;
		size = 0;

	}
	CheckingAccount(string filename, int size)
	{
		checkdatafile = filename;
		this->size = size;
		this->feecharge = 0.5;
		customer = new Customer * [size];
		checkaccount = new CheckingAccount * [size];

		for (int i = 0; i < size; i++)
		{
			checkaccount[i] = nullptr;
			customer[i] = nullptr;
		}

		checkdatafile = filename;

		Inp.open(filename);
		if (!Inp)
		{
			cout << setw(30) << "Falha ao abrir Verificando arquivo de dados da classe." << endl;
			return;
		}
		int index = 0;
		string line;
		while (getline(Inp, line))
		{
			stringstream SS(line);

			// Read data
			string fname, lname, user_nnam, pass_word, C_type, Email;
			int accountNO, phone_num;
			double bal;

			SS >> fname >> lname >> user_nnam >> pass_word >> accountNO >> bal >> C_type >> Email >> phone_num;



			customer[index] = new Customer(user_nnam, pass_word);
			checkaccount[index] = new CheckingAccount(fname, lname, accountNO, bal, C_type, Email, phone_num);

			index++;
			if (index >= size)
			{

				break;
			}
		}

		Inp.close();
	}

	CheckingAccount(string firstname, string lastname, int accountNumber, double balance, string cardtype, string email, int phonenumber)
		: Account(firstname, lastname, accountNumber, balance, cardtype, email, phonenumber) {
		this->feecharge = 0.5;

	}

	void deposit(double amount)
	{
		cout << "\n======================================================================================\n";
		int accountno;
		cout << left << setw(30) << "\t\t\t\tInsira o número da conta: ";
		cin >> accountno;

		bool found = false;
		int Index = -1;

		for (int i = 0; i < size; i++)
		{
			if (checkaccount[i]->accountNumber == accountno)
			{
				found = true;
				Index = i;
				break;
			}
		}
		if (found)
		{
			if (customer[Index]->login())
			{
				amount -= feecharge;
				checkaccount[Index]->balance += amount;
				cout << "\t\t\t\t\t\tCobranças de taxas R$" << feecharge << " dedicadas do seu saldo\n";
				cout << left << setw(30) << "\t\t\tDeposito de R$" << amount << " para a sua conta " << checkaccount[Index]->accountNumber << " bem-sucedido " << getCurrentTime() << endl;
				CheckingAccount::saveAccountData();
			}

		}
	}

	void withdraw(double amount)
	{

		int accountno;
		cout << left << setw(30) << "\t\t\tInsira o número da Conta: ";
		cin >> accountno;

		bool found = false;
		int Index = -1;

		for (int i = 0; i < size; i++)
		{
			if (checkaccount[i]->getAccountNumber() == accountno)
			{
				found = true;
				Index = i;
				break;
			}
		}
		if (found)
		{
			if (customer[Index]->login())
			{
				try
				{
					if (checkaccount[Index]->balance >= amount)
					{

						checkaccount[Index]->balance -= amount;
						checkaccount[Index]->balance -= feecharge;
						cout << "\t\t\t\t\tTaxas R$" << feecharge << " dedicado do seu Saldo\n";
						cout << "\t\t\tRetirada de R$" << amount << " da conta " << checkaccount[Index]->accountNumber << " bem-sucedida. " << getCurrentTime() << endl;
						CheckingAccount::saveAccountData();
					}
					else
					{
						throw runtime_error("\t\t\tSaldo insuficiente! ");

					}
				}
				catch (runtime_error e)
				{
					cout << e.what() << endl;
					cout << "\t\t\tPor favor, insira o saldo suficiente menor ou igual que o saldo da sua conta" << endl;
					double Amount_W;
					cout << "\t\t\tInsira o valor que deseja sacar" << endl;
					cin >> Amount_W;
					CheckingAccount::withdraw(Amount_W);

				}

			}

		}
		else {
			cout << "Conta não encontrada" << endl;
		}
	}

	void updateaccount()
	{
		int updateaccount;
		CheckingAccount::display();

		cout << "\t\t\t\t\t\tDigite o número da conta para atualizar: ";
		cin >> updateaccount;
		string fname, lname;
		string User, PASS, type, mail;
		double Balance;
		int accNo;
		int phone_num;
		bool found = false;
		bool added = false;
		int updateIndex = -1;
		for (int i = 0; i < size; i++)
		{
			if (checkaccount[i]->accountNumber == updateaccount)
			{
				cout << setw(30) << "\t\t\tConta encontrada! " << endl;
				cout << setw(30) << "\t\t\tNome: " << checkaccount[i]->getFirstName() << " " << checkaccount[i]->getLastName() << endl;
				cout << setw(30) << "\t\t\tNome de Usuário: " << customer[i]->getname() << endl;
				cout << setw(30) << "\t\t\tNúmero da Conta: " << checkaccount[i]->accountNumber << endl;
				cout << setw(30) << "\t\t\tSaldo: R$" << checkaccount[i]->balance << endl;
				cout << setw(30) << "\t\t\tTipo de Cartão: " << checkaccount[i]->getcardtype() << endl;
				cout << setw(30) << "\t\t\tEmail: " << checkaccount[i]->getemail() << endl;
				cout << setw(30) << "\t\t\tNúmero de Telefone: " << checkaccount[i]->getphone() << endl;
				found = true;
				updateIndex = i;
				break;
			}
		}
		if (found)
		{
			cout << setw(30) << "\t\t\t\tInsira o novo Nome: ";
			cin >> fname;

			cout << setw(30) << "\t\t\t\tInsira o novo Sobrenome: ";
			cin >> lname;

			cout << setw(30) << "\t\t\t\tDigite um novo Usuário: ";
			cin >> User;

			cout << setw(30) << "\t\t\t\tDigite uma nova Senha: ";
			cin >> PASS;

			cout << setw(30) << "\t\t\t\tInsira um novo tipo de Cartão: ";
			cin >> type;

			cout << setw(30) << "\t\t\t\tInsira um novo número da Conta: ";
			cin >> accNo;

			cout << setw(30) << "\t\t\t\tInsira um novo Saldo inicial: ";
			cin >> Balance;

			cout << setw(30) << "\t\t\t\tInsira um novo email: ";
			cin >> mail;

			cout << setw(30) << "\t\t\t\tInsira um novo número de Celular: ";
			cin >> phone_num;
			added = true;
			if (added)
			{


				customer[updateIndex]->setusername(User);
				customer[updateIndex]->setpassword(PASS);
				checkaccount[updateIndex]->setcardtype(type);
				checkaccount[updateIndex]->setaccountnumber(accNo);
				checkaccount[updateIndex]->setbalance(Balance);
				checkaccount[updateIndex]->setphone(phone_num);
				checkaccount[updateIndex]->setemail(mail);
				checkaccount[updateIndex]->setFirstName(fname);
				checkaccount[updateIndex]->setLastName(lname);

				cout << setw(30) << "\t\t\t\tConta editada com sucesso ás " << getCurrentTime() << endl;
				CheckingAccount::saveAccountData();
			}
		}
		else
		{
			cout << setw(30) << "Conta não encontrada" << endl;
		}
	}

	void Addaccount(int s)
	{
		Out.open(checkdatafile, ios::app);
		if (!Out)
		{
			cout << left << setw(30) << "O arquivo não pode ser encontrado!" << endl;
			return;
		}

		cout << left << setw(30) << "\t\t\t\t\tREGISTRO DE CONTA DE CLIENTE" << endl;
		string us, pass, type;
		char c;
		bool added;
		do
		{
			cout << setw(30) << "\t\tInsira seu Nome: ";
			string firstname;
			cin >> firstname;

			cout << left << setw(30) << "\t\tInsira o seu Sobrenome: ";
			string lastname;
			cin >> lastname;

			cout << left << setw(30) << "\t\tInsira um nome de Usuário: ";
			cin >> us;

			cout << left << setw(30) << "\t\tDigite uma Senha: ";
			cin >> pass;

			cout << left << setw(30) << "\t\tAdicione um tipo de cartão: ";
			cin >> type;

			int accountNumber;
			cout << left << setw(30) << "\t\tInsira um número da conta: ";
			cin >> accountNumber;

			double balance;
			cout << left << setw(30) << "\t\tInsira o Saldo Inicial: ";
			cin >> balance;

			string email;
			cout << left << setw(30) << "\t\tDigite o email: ";
			cin >> email;

			int phoneNumber;
			cout << left << setw(30) << "\t\tDigite o número de celular: ";
			cin >> phoneNumber;
			added = true;
			if (added)
			{


				Customer* cust = new Customer(us, pass);
				CheckingAccount* checkacc = new CheckingAccount(firstname, lastname, accountNumber, balance, type, email, phoneNumber);

				customer[size] = cust;
				checkaccount[size] = checkacc;

				size++;
				// Write the data
				for (int i = size - 1; i < size; i++)
				{
					Customer* cust = customer[i];
					CheckingAccount* checkacc = checkaccount[i];
					Out << left << setw(20) << checkacc->getFirstName()
						<< left << setw(20) << checkacc->getLastName()
						<< left << setw(20) << cust->getname()
						<< left << setw(20) << cust->getpassword()
						<< left << setw(20) << checkacc->getAccountNumber()
						<< left << setw(20) << checkacc->getBalance()
						<< left << setw(20) << checkacc->getcardtype()
						<< left << setw(30) << checkacc->getemail()
						<< left << setw(30) << checkacc->getphone()
						<< endl;
				}

				Out.close();

				cout << left << setw(30) << "\t\t\t\t\tConta criada com sucesso ás  " << getCurrentTime() << endl;
			}
			cout << left << setw(30) << "\t\t\t\tDeseja adicionar outro registro? Se sim digite S, senão digite N: ";
			cin >> c;
		} while (c == 'S' || c == 's');


	}
	void serachaccount()
	{
		int serachaccount;
		cout << left << setw(30) << "\t\t\tInsira o número de uma conta para pesquisar: ";
		cin >> serachaccount;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{
			if (checkaccount[i]->getAccountNumber() == serachaccount)
			{
				if (customer[i]->login())
				{
					found1 = true;
					Index = i;
					break;
				}
			}
		}
		if (found1)
		{
			cout << setw(30) << "\t\t\tNome: " << checkaccount[Index]->getFirstName() << " " << checkaccount[Index]->getLastName() << endl;
			cout << setw(30) << "\t\t\tNome do titular da conta: " << customer[Index]->getname() << endl;
			cout << setw(30) << "\t\t\tNúmero da Conta: " << checkaccount[Index]->getAccountNumber() << endl;
			cout << setw(30) << "\t\t\tSaldo: R$" << checkaccount[Index]->getBalance() << endl;
			cout << setw(30) << "\t\t\tTipo de Cartão: " << checkaccount[Index]->getcardtype() << endl;
			cout << setw(30) << "\t\t\tEmail: " << checkaccount[Index]->getemail() << endl;
			cout << setw(30) << "\t\t\tNúmero de Telefone: " << checkaccount[Index]->getphone() << endl;
		}

		else
		{
			cout << "\t\t\tNúmero da conta não encontrada" << endl;
		}
	}
	void deleteaccount(string filename, int s)
	{
		int deleteacc;
		if (admin.login())
		{
			CheckingAccount::display();
			cout << "\t\t\tDigite a conta que você deseja deletar: ";
			cin >> deleteacc;
			bool found = false;
			int deleteIndex = -1;
			for (int i = 0; i < size; i++)
			{
				if (checkaccount[i]->getAccountNumber() == deleteacc)
				{
					cout << "Conta Encontrada! " << endl;
					cout << setw(30) << "\t\t\tNome: " << checkaccount[i]->getFirstName() << " " << checkaccount[i]->getLastName() << endl;
					cout << setw(30) << "\t\t\tNome do Titular da Conta: " << customer[i]->getname() << endl;
					cout << setw(30) << "\t\t\tNúmero da Conta: " << checkaccount[i]->getAccountNumber() << endl;
					cout << setw(30) << "\t\t\tSaldo: R$" << checkaccount[i]->getBalance() << endl;
					cout << setw(30) << "\t\t\tTipo de Cartão: " << checkaccount[i]->getcardtype() << endl;
					cout << setw(30) << "\t\t\tEmail: " << checkaccount[i]->getemail() << endl;
					cout << setw(30) << "\t\t\tNúmero de Telefone: " << checkaccount[i]->getphone() << endl;
					found = true;
					deleteIndex = i;
					break;
				}
			}
			if (found)
			{
				char y;
				cout << "\t\t\t\tDigite Y para deletar esta conta... ";
				cin >> y;
				if (y == 'Y' || y == 'y') 
				{
					delete customer[deleteIndex];
					delete checkaccount[deleteIndex];
					for (int i = deleteIndex; i < size - 1; i++)
					{
						customer[i] = customer[i + 1];
						checkaccount[i] = checkaccount[i + 1];
					}
					size--;
					CheckingAccount::saveAccountData();
					cout << "\t\t\t\tConta deletada com sucesso... em " << getCurrentTime() << endl;
				}
			}
			else
			{
				cout << "\t\t\tConta não encontrada." << endl;
			}
		}
	}

	void saveAccountData()
	{
		Out.open(checkdatafile, ios::out);

		if (!Out)
		{
			return;
		}
		Customer* cust;
		CheckingAccount* checkacc;
		for (int i = 0; i < size; i++)
		{
			cust = customer[i];
			checkacc = checkaccount[i];
			Out << left << setw(20) << checkacc->getFirstName()
				<< left << setw(20) << checkacc->getLastName()
				<< left << setw(20) << cust->getname()
				<< left << setw(20) << cust->getpassword()
				<< left << setw(20) << checkacc->getAccountNumber()
				<< left << setw(20) << checkacc->getBalance()
				<< left << setw(20) << checkacc->getcardtype()
				<< left << setw(30) << checkacc->getemail()
				<< left << setw(30) << checkacc->getphone()
				<< endl;
		}

		Out.close();
	}

	void display() const
	{
		cout << "Tipo de Conta: Conta Corrente" << endl;
		cout << setw(50) << "=====================================LISTA DE CLIENTES DA CONTA CORRENTE================================" << endl;
		cout << left << setw(15) << "A/C"
			<< left << setw(18) << "Nome"
			<< left << setw(15) << "Nº Conta"
			<< left << setw(20) << "Usuário"
			<< left << setw(15) << "Tipo de Cartão"
			<< left << setw(30) << "Endereço de Email"
			<< left << setw(30) << "Nº de Telefone"
			<< left << setw(5) << "Saldo"
			<< endl;

		for (int i = 0; i < size; i++)
		{
			cout << left << setw(15) << "Corrente"
				<< left << setw(18) << checkaccount[i]->getFirstName() + " " + checkaccount[i]->getLastName()
				<< left << setw(15) << checkaccount[i]->getAccountNumber()
				<< left << setw(20) << customer[i]->getname()
				<< left << setw(15) << checkaccount[i]->getcardtype()
				<< left << setw(30) << checkaccount[i]->getemail()
				<< left << setw(30) << checkaccount[i]->getphone()
				<< left << setw(5) << checkaccount[i]->getBalance()
				<< endl;
		}
	}

	~CheckingAccount()
	{
		CheckingAccount::saveAccountData();
		if (checkaccount != nullptr)
		{
			delete[] checkaccount;
		}
		if (customer != nullptr)
		{
			delete[] customer;
		}
	}
};

class Loan
{
protected:
	int loanNumber;
	double loanAmount;
	double interestRate;
	string email;
	string phonenumber;
	string firstname;
	string lastname;

public:
	Loan(string firstname, string lastname, int loanNumber, double loanAmount, double interestRate, string email, string phonenumber)
	{
		this->firstname = firstname;
		this->lastname = lastname;
		this->loanNumber = loanNumber;
		this->loanAmount = loanAmount;
		this->interestRate = interestRate;
		this->email = email;
		this->phonenumber = phonenumber;
	}
	Loan() {
		loanNumber = 0;
		loanAmount = 0;
		interestRate = 0;
		email = "";
		phonenumber = "";
		firstname = "";
		lastname = "";

	}
	string getFirstName()
	{
		return firstname;
	}

	void setFirstName(string firstName)
	{
		firstname = firstName;
	}

	string getLastName()
	{
		return lastname;
	}

	void setLastName(string lastName)
	{
		lastname = lastName;
	}
	string getemail()
	{
		return email;
	}
	string getphone()
	{
		return phonenumber;
	}
	void setphone(string Num)
	{
		phonenumber = Num;
	}
	void setemail(string mail)
	{
		email = mail;
	}
	int getloannumber()
	{
		return loanNumber;
	}
	void setloannumber(int Number)
	{
		loanNumber = Number;
	}
	void setloanamount(double Amount)
	{
		loanAmount = Amount;
	}
	void setinterestrate(double rate)
	{
		interestRate = rate;
	}
	double getloanamount()
	{
		return loanAmount;
	}
	double getinterestrate()
	{
		return interestRate;
	}
	virtual void calculateInterest() = 0;
	virtual void display() = 0;
	virtual void saveLoanData() = 0;
	virtual void sreachaccount() = 0;

	virtual void addloan() = 0;
	virtual void updateaccount() = 0;
	virtual void deleteAccount(string filename, int size) = 0;
	virtual ~Loan() {}
};

class StudentFeeLoan : public Loan
{
private:
	string enrollmentYear;
	string studentLoanDataFile;
	int size;

	Customer** customer;
	Admin admin;
	StudentFeeLoan** studentLoans;

public:
	StudentFeeLoan()
	{
		customer = nullptr;
		studentLoans = nullptr;
		size = 0;
	}
	StudentFeeLoan(string filename, int size)
	{
		this->studentLoanDataFile = filename;
		this->size = size;
		customer = new Customer * [size];
		studentLoans = new StudentFeeLoan * [size];

		for (int i = 0; i < size; i++)
		{
			studentLoans[i] = nullptr;
			customer[i] = nullptr;
		}

		Inp.open(filename);
		if (!Inp)
		{
			cout << "\t\t\tFalha ao abrir o arquivo de dados do Empréstimo Estudantil." << endl;
			return;
		}
		int index = 0;
		string line;
		while (getline(Inp, line))
		{
			stringstream ss(line);

			// Read data
			int loan_Number;
			double amountNO;
			double rate;
			string fname, lname;
			string enrollyear;
			string phone_numb;
			string user_name, Email;
			string pass_word;

			ss >> fname >> lname >> user_name >> pass_word >> loan_Number >> amountNO >> rate >> enrollyear >> Email >> phone_numb;


			customer[index] = new Customer(user_name, pass_word);
			studentLoans[index] = new StudentFeeLoan(fname, lname, loan_Number, amountNO, rate, enrollyear, Email, phone_numb);

			index++;
			if (index >= size)
			{

				break;
			}
		}

		Inp.close();
	}
	StudentFeeLoan(string firstname, string lastname, int lnNumber, double amount, double rate, string year, string email, string phonenumber)
		: Loan(firstname, lastname, lnNumber, amount, rate, email, phonenumber)
	{
		this->enrollmentYear = year;
	}
	string getenrollmentYear()
	{
		return enrollmentYear;
	}
	void setenrollmeantyear(string year)
	{
		enrollmentYear = year;
	}
	void saveLoanData()
	{
		Out.open(studentLoanDataFile);

		if (Out.is_open())
		{

			for (int i = 0; i < size; i++)
			{
				Customer* cust = customer[i];
				StudentFeeLoan* loan = studentLoans[i];
				Out << left << setw(20) << loan->getFirstName()
					<< left << setw(20) << loan->getLastName()
					<< left << setw(20) << cust->getname()
					<< left << setw(20) << cust->getpassword()
					<< left << setw(20) << loan->getloannumber()
					<< left << setw(20) << loan->getloanamount()
					<< left << setw(20) << loan->getinterestrate()
					<< left << setw(20) << loan->getenrollmentYear()
					<< left << setw(30) << loan->getemail()
					<< left << setw(30) << loan->getphone()
					<< endl;
			}



		}
		else
		{

			return;
		}
		Out.close();


	}
	void addloan()
	{
		Out.open(studentLoanDataFile, ios::app); // Abre o arquivo
		if (!Out)
		{
			cout << "\t\t\tO arquivo não está aberto!" << endl;
			return;
		}

		cout << "\t\t\t\t\t\tREGISTRO DE CONTA DE EMPRÉSTIMO ESTUDANTIL" << endl;
		string us, pass;
		string enrollyear;
		char c;
		bool added;
		do
		{
			cout << "\t\t\tDigite o novo Primeiro Nome do Usuário: ";
			string fname;
			cin >> fname;

			cout << "\t\t\tDigite o novo Sobrenome do Usuário: ";
			string lname;
			cin >> lname;

			cout << "\t\t\tDigite o Nome de Usuário: ";
			cin >> us;

			cout << "\t\t\tDigite a Senha: ";
			cin >> pass;

			cout << "\t\t\tDigite o ano de matrícula: ";
			cin >> enrollyear;

			int loanNo;
			cout << "\t\t\tDigite o Número do Empréstimo: ";
			cin >> loanNo;

			double amount_L;
			cout << "\t\t\tDigite o Valor: ";
			cin >> amount_L;

			string email;
			cout << "\t\t\tDigite o Endereço de Email: ";
			cin >> email;
			double ratE;
			cout << "\t\t\tDigite a Taxa de Juros: ";
			cin >> ratE;
			string phoneNumber;
			cout << "\t\t\tDigite o Número de Telefone: ";
			cin >> phoneNumber;
			added = true;
			if (added)
			{

				Customer* cust = new Customer(us, pass);
				StudentFeeLoan* studloan = new StudentFeeLoan(fname, lname, loanNo, amount_L, ratE, enrollyear, email, phoneNumber);

				customer[size] = cust;
				studentLoans[size] = studloan;

				size++;
				// Escreve os dados
				for (int i = size - 1; i < size; i++)
				{
					Customer* cust = customer[i];
					StudentFeeLoan* loan = studentLoans[i];
					Out << left << setw(20) << loan->getFirstName()
						<< left << setw(20) << loan->getLastName()
						<< left << setw(15) << cust->getname()
						<< left << setw(15) << cust->getpassword()
						<< left << setw(20) << loan->getloannumber()
						<< left << setw(15) << loan->getloanamount()
						<< left << setw(15) << loan->getinterestrate()
						<< left << setw(15) << loan->getenrollmentYear()
						<< left << setw(30) << loan->getemail()
						<< left << setw(30) << loan->getphone()
						<< endl;
				}

				Out.close();
				cout << "\t\t\tA Conta foi Registrada com Sucesso em " << getCurrentTime() << endl;
			}
			cout << "\t\t\tDeseja Adicionar Outro Registro? (S/N): ";
			cin >> c;
		} while (c == 'S' || c == 's');
	}

	void updateaccount()
	{
		int updateloan;
		StudentFeeLoan::display();

		cout << "\t\t\tDigite o número da conta para atualizar: ";
		cin >> updateloan;
		bool updated = false;
		string User, PASS, mail;
		double amount, rate;
		int loan_NO;
		string phone_num;
		string Yearr;
		bool found = false;
		int updateIndex = -1;
		string fname, lname;
		for (int i = 0; i < size; i++)
		{
			if (studentLoans[i]->getloannumber() == updateloan)
			{
				cout << setw(30) << "\t\tConta Encontrada" << endl;
				cout << setw(30) << "\t\tNome: " << studentLoans[i]->getFirstName() << " " << studentLoans[i]->getLastName() << endl;
				cout << setw(30) << "\t\tNome de Usuário: " << customer[i]->getname() << endl;
				cout << setw(30) << "\t\tNúmero do Empréstimo: " << studentLoans[i]->getloannumber() << endl;
				cout << setw(30) << "\t\tValor do Empréstimo: R$" << studentLoans[i]->getloanamount() << endl;
				cout << setw(30) << "\t\tTaxa de Juros: " << studentLoans[i]->getinterestrate() << "%" << endl;
				cout << setw(30) << "\t\tAno de Matrícula: " << studentLoans[i]->getenrollmentYear() << endl;
				cout << setw(30) << "\t\tEndereço de Email: " << studentLoans[i]->getemail() << endl;
				cout << setw(30) << "\t\tNúmero de Telefone: " << studentLoans[i]->getphone() << endl;
				found = true;
				updateIndex = i;
				break;
			}
		}
		if (found)
		{
			cout << "\t\t\tDigite o Primeiro Nome: ";
			cin >> fname;
			cin.ignore();
			cout << "\t\t\tDigite o Sobrenome: ";
			cin >> lname;

			cout << "\t\t\tDigite o novo Nome de Usuário: ";
			cin >> User;

			cout << "\t\t\tDigite a nova Senha: ";
			cin >> PASS;

			cout << "\t\t\tDigite o novo Número do Empréstimo: ";
			cin >> loan_NO;

			cout << "\t\t\tDigite o novo Valor do Empréstimo: ";
			cin >> amount;

			cout << "\t\t\tDigite a nova Taxa de Juros: ";
			cin >> rate;

			cout << "\t\t\tDigite o novo Email: ";
			cin >> mail;

			cout << "\t\t\tDigite o novo Número de Telefone: ";
			cin >> phone_num;
			cout << "\t\t\tDigite o ano de matrícula: ";
			cin >> Yearr;
			updated = true;
			if (updated)
			{
				customer[updateIndex] = new Customer(User, PASS);
				studentLoans[updateIndex] = new StudentFeeLoan(fname, lname, loan_NO, amount, rate, Yearr, mail, phone_num);

				cout << "\t\t\tConta Editada com Sucesso em " << getCurrentTime() << endl;
				StudentFeeLoan::saveLoanData();
			}
			else
			{
				cout << "\t\t\tErro ao adicionar conta" << endl;
			}
		}
		else
		{
			cout << "\t\t\tConta Não Encontrada" << endl;
		}
	}

	void sreachaccount()
	{
		int serachaccount;
		cout << "\t\t\tDigite o Número do Empréstimo para buscar: ";
		cin >> serachaccount;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{
			if (studentLoans[i]->getloannumber() == serachaccount)
			{
				if (customer[i]->login())
				{
					found1 = true;
					Index = i;
					break;
				}
			}
		}
		if (found1)
		{
			cout << left << setw(50) << "\t\tNome: " << studentLoans[Index]->getFirstName() << " " << studentLoans[Index]->getLastName() << endl;
			cout << left << setw(50) << "\t\tNome de Usuário: " << customer[Index]->getname() << endl;
			cout << left << setw(50) << "\t\tNúmero do Empréstimo: " << studentLoans[Index]->getloannumber() << endl;
			cout << left << setw(50) << "\t\tValor do Empréstimo: R$" << studentLoans[Index]->getloanamount() << endl;
			cout << left << setw(50) << "\t\tTaxa de Juros: " << studentLoans[Index]->getinterestrate() << "%" << endl;
			cout << left << setw(50) << "\t\tAno de Matrícula: " << studentLoans[Index]->getenrollmentYear() << endl;
			cout << left << setw(50) << "\t\tEndereço de Email: " << studentLoans[Index]->getemail() << endl;
			cout << left << setw(50) << "\t\tNúmero de Telefone: " << studentLoans[Index]->getphone() << endl;
		}
		else
		{
			cout << "\t\tNúmero do Empréstimo não encontrado" << endl;
		}
	}

	void deleteAccount(string filename, int s)
	{
		int deleteLoanNumber;
		if (admin.login())
		{
			StudentFeeLoan::display();
			cout << "\t\tDigite o número do empréstimo que deseja excluir: "; // Tradução
			cin >> deleteLoanNumber;
			bool found = false;
			int deleteIndex = -1;
			for (int i = 0; i < size; i++)
			{
				if (studentLoans[i]->getloannumber() == deleteLoanNumber)
				{
					cout << setw(30) << "\t\tConta Encontrada" << endl; // Tradução
					cout << setw(30) << "\t\tNome: " << studentLoans[i]->getFirstName() << " " << studentLoans[i]->getLastName() << endl; // Tradução
					cout << setw(30) << "\t\tNome de Usuário: " << customer[i]->getname() << endl; // Tradução
					cout << setw(30) << "\t\tNúmero do Empréstimo: " << studentLoans[i]->getloannumber() << endl; // Tradução
					cout << setw(30) << "\t\tMontante do Empréstimo: $" << studentLoans[i]->getloanamount() << endl; // Tradução
					cout << setw(30) << "\t\tTaxa de Juros: " << studentLoans[i]->getinterestrate() << "%" << endl; // Tradução
					cout << setw(30) << "\t\tAno de Matrícula: " << studentLoans[i]->getenrollmentYear() << endl; // Tradução
					cout << setw(30) << "\t\tEndereço de Email: " << studentLoans[i]->getemail() << endl; // Tradução
					cout << setw(30) << "\t\tNúmero de Telefone: " << studentLoans[i]->getphone() << endl; // Tradução
					found = true;
					deleteIndex = i;
					break;
				}
			}
			if (found)
			{
				char y;
				cout << "\t\tDigite Y para excluir esta conta " << endl; // Tradução
				cin >> y;
				if (y == 'Y' || y == 'y') {
					delete customer[deleteIndex];
					delete studentLoans[deleteIndex];
					for (int i = deleteIndex; i < size - 1; i++)
					{
						customer[i] = customer[i + 1];
						studentLoans[i] = studentLoans[i + 1];
					}
					size--;


					StudentFeeLoan::saveLoanData();

					cout << "\t\t\tEmpréstimo excluído com sucesso em " << getCurrentTime() << endl; // Tradução
				}


			}
			else
			{
				cout << "\t\tNúmero do Empréstimo não encontrado." << endl; // Tradução
			}
		}
		else
		{
			cout << "Senha Inválida" << endl; // Tradução
		}
	}

	void calculateInterest()
	{
		int serach_account;
		cout << "\t\t\tDigite o Número do Empréstimo Estudantil para buscar: "; // Tradução
		cin >> serach_account;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{

			if (studentLoans[i]->getloannumber() == serach_account)
			{
				if (customer[i]->login())
				{
					found1 = true;
					Index = i;
					break;
				}
			}
		}
		if (found1)
		{
			double interest = studentLoans[Index]->getloanamount() * studentLoans[Index]->getinterestrate() / 100;

			cout << "\t\t\tO total de Juros sobre o Empréstimo Estudantil número " << studentLoans[Index]->getloannumber() << " é de $ " << interest << endl; // Tradução

		}
		else
		{
			cout << "\t\tNúmero do Empréstimo Estudantil não encontrado" << endl; // Tradução

		}
	}

	void display()
	{
		cout << "Tipo de Empréstimo: Empréstimo de Taxas Estudantis" << endl; // Tradução
		cout << left << setw(20) << "A/C"
			<< left << setw(20) << "Nome: " // Tradução

			<< left << setw(15) << "Nome de Usuário" // Tradução
			<< left << setw(15) << "Número do Empréstimo" // Tradução
			<< left << setw(20) << "Montante" // Tradução
			<< left << setw(30) << "Endereço de Email" // Tradução
			<< left << setw(20) << "Número de Telefone" // Tradução
			<< left << setw(10) << "Ano do Empréstimo" // Tradução
			<< endl;

		for (int i = 0; i < size; i++)
		{
			cout << left << setw(20) << "Empréstimo Estudantil" // Tradução
				<< left << setw(20) << studentLoans[i]->getFirstName() + " " + studentLoans[i]->getLastName()
				<< left << setw(15) << customer[i]->getname()
				<< left << setw(15) << studentLoans[i]->getloannumber()

				<< left << setw(20) << studentLoans[i]->getloanamount()
				<< left << setw(30) << studentLoans[i]->getemail()
				<< left << setw(20) << studentLoans[i]->getphone()
				<< left << setw(10) << studentLoans[i]->getenrollmentYear()
				<< endl;
		}
	}

	~StudentFeeLoan()
	{
		StudentFeeLoan::saveLoanData();
		if (studentLoans != nullptr)
		{
			delete[] studentLoans;
		}
		if (customer != nullptr)
		{
			delete[] customer;
		}

	}
};

class Personalloan : public Loan
{
private:
	int loantime;
	string personLoanDataFile;
	int size;

	Customer** customer;
	Admin admin;
	Personalloan** personLoans;

public:
	Personalloan()
	{

	}
	Personalloan(string filename, int size)
	{
		this->personLoanDataFile = filename;
		this->size = size;
		customer = new Customer * [size];
		personLoans = new Personalloan * [size];

		for (int i = 0; i < size; i++)
		{
			personLoans[i] = nullptr;
			customer[i] = nullptr;
		}

		Inp.open(filename);
		if (!Inp)
		{
			cout << "Falha ao abrir o arquivo de dados do Empréstimo Pessoal." << endl;
			return;
		}
		int index = 0;
		string line;
		while (getline(Inp, line))
		{
			stringstream SS(line);

			// Read data
			int loan_Number;
			double amountNO;
			double rate;
			string fname, lname;
			int time;
			string phone_numb;
			string user_name, Email;
			string pass_word;

			SS >> fname >> lname >> user_name >> pass_word >> loan_Number >> amountNO >> rate >> time >> Email >> phone_numb;

			customer[index] = new Customer(user_name, pass_word);
			personLoans[index] = new Personalloan(fname, lname, loan_Number, amountNO, rate, time, Email, phone_numb);

			index++;
			if (index >= size)
			{
				break;
			}
		}

		Inp.close();
	}
	Personalloan(string firstname, string lastname, int lnNumber, double amount, double rate, int loantime, string email, string phonenumber)
		: Loan(firstname, lastname, lnNumber, amount, rate, email, phonenumber)
	{
		this->loantime = loantime;
	}
	void settime(int tm)
	{
		loantime = tm;
	}
	int getloanyear() {
		return loantime;
	}
	void calculateInterest()
	{
		int serachaccount;
		cout << "\t\tDigite o número do empréstimo pessoal para pesquisar: ";
		cin >> serachaccount;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{
			if (personLoans[i]->getloannumber() == serachaccount)
			{
				if (customer[i]->login())
				{
					found1 = true;
					Index = i;
					break;
				}
			}
		}
		if (found1)
		{
			double interest = personLoans[Index]->getloanamount() * personLoans[Index]->getinterestrate() / 100;

			cout << "\t\t\tO número total de juros sobre o empréstimo pessoal " << personLoans[Index]->getloannumber() << " é R$ " << interest << endl;

		}
		else
		{
			cout << "Id de empréstimo pessoal não encontrado" << endl;

		}

	}

	int gettimeloan()
	{
		return loantime;
	}

	void addloan()
	{
		Out.open(personLoanDataFile, ios::app); // Abre o arquivo
		if (!Out)
		{
			cout << "Arquivo não está aberto!" << endl;
			return;
		}

		cout << "\t\t\tREGISTRO DE CONTA DE EMPRÉSTIMO ESTUDANTIL" << endl;
		string us, pass;
		int time;
		char c;
		bool added = false;
		do
		{
			cout << "\t\t\tDigite o novo nome do usuário: ";
			string fname;
			cin >> fname;

			cout << "\t\t\tDigite o novo sobrenome do usuário: ";
			string lname;
			cin >> lname;

			cout << "\t\t\tDigite o nome de usuário: ";
			cin >> us;

			cout << "\t\t\tDigite a senha: ";
			cin >> pass;

			cout << "\t\t\tDigite o prazo do empréstimo em anos: ";
			cin >> time;

			int loanNo;
			cout << "\t\t\tDigite o número do empréstimo: ";
			cin >> loanNo;

			double amount_L;
			cout << "\t\t\tDigite o valor do empréstimo: ";
			cin >> amount_L;

			string email;
			cout << "\t\t\tDigite o endereço de email: ";
			cin >> email;
			double ratE;
			cout << "\t\t\tDigite a taxa de juros: ";
			cin >> ratE;
			string phoneNumber;
			cout << "\t\t\tDigite o número de telefone: ";
			cin >> phoneNumber;
			added = true;
			if (added)
			{

				Customer* cust = new Customer(us, pass);
				Personalloan* perloan = new Personalloan(fname, lname, loanNo, amount_L, ratE, time, email, phoneNumber);

				customer[size] = cust;
				personLoans[size] = perloan;

				size++;

				cout << "\t\t\tConta registrada com sucesso em " << getCurrentTime() << endl;
			}
			else
			{
				cout << "\t\t\tErro no registro " << endl;
			}
			cout << "\t\t\tDeseja adicionar outro registro? (S/N): ";
			cin >> c;
		} while (c == 'S' || c == 's');

		// Escreve os dados
		for (int i = size - 1; i < size; i++)
		{
			Customer* cust = customer[i];
			Personalloan* loan = personLoans[i];
			Out << left << setw(20) << loan->getFirstName()
				<< left << setw(20) << loan->getLastName()
				<< left << setw(20) << cust->getname()
				<< left << setw(20) << cust->getpassword()
				<< left << setw(20) << loan->getloannumber()
				<< left << setw(20) << loan->getloanamount()
				<< left << setw(20) << loan->getinterestrate()
				<< left << setw(20) << loan->getloanyear()
				<< left << setw(30) << loan->getemail()
				<< left << setw(30) << loan->getphone()
				<< endl;
		}

		Out.close();
	}

	void updateaccount()
	{
		bool updated = false;
		int updateloan;
		Personalloan::display();
		cout << "\t\t\tDigite o número do empréstimo a ser atualizado: ";
		cin >> updateloan;
		string User, PASS, mail;
		double amount, Rate_P;
		int loan_NO, time;
		string phone_num;
		bool found = false;
		int updateIndex = -1;
		for (int i = 0; i < size; i++)
		{
			if (personLoans[i]->getloannumber() == updateloan)
			{
				cout << left << setw(30) << "\t\tConta encontrada" << endl;
				cout << left << setw(30) << "\t\tNome: " << customer[i]->getname() << endl;
				cout << left << setw(30) << "\t\tNúmero do empréstimo: " << personLoans[i]->getloannumber() << endl;
				cout << left << setw(30) << "\t\tValor do empréstimo: R$ " << personLoans[i]->getloanamount() << endl;
				cout << left << setw(30) << "\t\tTaxa de juros: " << personLoans[i]->getinterestrate() << "%" << endl;
				cout << left << setw(30) << "\t\tPrazo do empréstimo: " << personLoans[i]->getloanyear() << " anos!" << endl;
				cout << left << setw(30) << "\t\tEndereço de email: " << personLoans[i]->getemail() << endl;
				cout << left << setw(30) << "\t\tNúmero de telefone: " << personLoans[i]->getphone() << endl;
				found = true;
				updateIndex = i;
				break;
			}
		}
		if (found)
		{
			cout << "\t\tDigite o novo nome de usuário: ";
			cin >> User;

			cout << "\t\tDigite a nova senha: ";
			cin >> PASS;

			cout << "\t\tDigite o novo número do empréstimo: ";
			cin >> loan_NO;

			cout << "\t\tDigite o novo valor do empréstimo: ";
			cin >> amount;

			cout << "\t\tDigite o novo prazo do empréstimo: ";
			cin >> time;

			cout << "\t\tDigite o novo email: ";
			cin >> mail;

			cout << "\t\tDigite o novo número de telefone: ";
			cin >> phone_num;
			cout << "\t\tDigite a nova taxa de juros: ";
			cin >> Rate_P;
			updated = true;
			if (updated)
			{
				customer[updateIndex]->setusername(User);
				customer[updateIndex]->setpassword(PASS);
				personLoans[updateIndex]->setloannumber(loan_NO);
				personLoans[updateIndex]->setloanamount(amount);
				personLoans[updateIndex]->setinterestrate(Rate_P);
				personLoans[updateIndex]->settime(time);
				personLoans[updateIndex]->setemail(mail);
				personLoans[updateIndex]->setphone(phone_num);

				cout << "\t\tConta editada com sucesso em " << getCurrentTime() << endl;
				Personalloan::saveLoanData();
			}
			else
			{
				cout << "\t\tNão atualizado" << endl;
			}
		}
		else
		{
			cout << "\t\tConta não encontrada" << endl;
		}
	}

	void display()
	{
		cout << "\t\t============Tipo de Empréstimo: Empréstimo Pessoal============" << endl;

		cout << left << setw(15) << "Tipo"
			<< left << setw(15) << "Nome"
			<< left << setw(15) << "Nome de Usuário"
			<< left << setw(15) << "Número do Empréstimo"
			<< left << setw(15) << "Valor"
			<< left << setw(15) << "Prazo"
			<< left << setw(15) << "Taxa de Juros"
			<< left << setw(25) << "Endereço de Email"
			<< left << setw(20) << "Número de Telefone"
			<< endl;

		for (int i = 0; i < size; i++)
		{
			cout << left << setw(15) << "Empréstimo Pessoal"
				<< left << setw(15) << personLoans[i]->getFirstName() + " " + personLoans[i]->getLastName()
				<< left << setw(15) << customer[i]->getname()
				<< left << setw(15) << personLoans[i]->getloannumber()
				<< left << setw(15) << personLoans[i]->getloanamount()
				<< left << setw(15) << personLoans[i]->getloanyear()
				<< left << setw(15) << personLoans[i]->getinterestrate()
				<< left << setw(25) << personLoans[i]->getemail()
				<< left << setw(20) << personLoans[i]->getphone()
				<< endl;
		}
	}

	void sreachaccount()
	{
		int serachaccount;
		cout << "\t\t\tDigite o número do empréstimo para buscar: ";
		cin >> serachaccount;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{
			if (personLoans[i]->getloannumber() == serachaccount)
			{
				if (customer[i]->login())
				{
					found1 = true;
					Index = i;
					break;
				}
			}
		}
		if (found1)
		{
			cout << left << setw(30) << "\t\tNome: " << personLoans[Index]->getFirstName() << " " << personLoans[Index]->getLastName() << endl;
			cout << left << setw(30) << "\t\tNome de Usuário: " << customer[Index]->getname() << endl;
			cout << left << setw(30) << "\t\tNúmero do Empréstimo: " << personLoans[Index]->getloannumber() << endl;
			cout << left << setw(30) << "\t\tValor do Empréstimo: R$ " << personLoans[Index]->getloanamount() << endl;
			cout << left << setw(30) << "\t\tTaxa de Juros: " << personLoans[Index]->getinterestrate() << "%" << endl;
			cout << left << setw(30) << "\t\tPrazo do Empréstimo: " << personLoans[Index]->getloanyear() << endl;
			cout << left << setw(30) << "\t\tEndereço de Email: " << personLoans[Index]->getemail() << endl;
			cout << left << setw(30) << "\t\tNúmero de Telefone: " << personLoans[Index]->getphone() << endl;
		}
		else
		{
			cout << "\t\tNúmero do empréstimo não encontrado" << endl;
		}
	}

	void saveLoanData()
	{
		Out.open(personLoanDataFile);

		if (Out.is_open())
		{
			// Escreve os dados pessoais

			for (int i = 0; i < size; i++)
			{
				Customer* cust = customer[i];
				Personalloan* loan = personLoans[i];

				Out << left << setw(20) << loan->getFirstName()
					<< left << setw(20) << loan->getLastName()
					<< left << setw(20) << cust->getname()
					<< left << setw(20) << cust->getpassword()
					<< left << setw(20) << loan->getloannumber()
					<< left << setw(20) << loan->getloanamount()
					<< left << setw(20) << loan->getinterestrate()
					<< left << setw(20) << loan->getloanyear()
					<< left << setw(30) << loan->getemail()
					<< left << setw(30) << loan->getphone()
					<< endl;
			}
		}
		else
		{
			return;
		}

		Out.close();
	}

	void deleteAccount(string filename, int s)
	{
		int deleteacc;
		if (admin.login())
		{
			Personalloan::display();
			cout << "\t\t\tDigite o número do empréstimo que você deseja excluir: ";
			cin >> deleteacc;
			bool found = false;
			int deleteIndex = -1;
			for (int i = 0; i < size; i++)
			{
				if (personLoans[i]->getloannumber() == deleteacc)
				{
					cout << left << setw(30) << "\t\tConta encontrada" << endl;
					cout << left << setw(30) << "\t\tNome: " << customer[i]->getname() << endl;
					cout << left << setw(30) << "\t\tNúmero do Empréstimo: " << personLoans[i]->getloannumber() << endl;
					cout << left << setw(30) << "\t\tValor do Empréstimo: R$ " << personLoans[i]->getloanamount() << endl;
					cout << left << setw(30) << "\t\tTaxa de Juros: " << personLoans[i]->getinterestrate() << "%" << endl;
					cout << left << setw(30) << "\t\tPrazo do Empréstimo: " << personLoans[i]->getloanyear() << endl;
					cout << left << setw(30) << "\t\tEndereço de Email: " << personLoans[i]->getemail() << endl;
					cout << left << setw(30) << "\t\tNúmero de Telefone: " << personLoans[i]->getphone() << endl;
					found = true;
					deleteIndex = i;
					break;
				}
			}
			if (found)
			{
				char y;
				cout << "\t\tDigite S para excluir esta conta...! ";
				cin >> y;
				if (y == 'S' || y == 's')
				{
					delete customer[deleteIndex];
					delete personLoans[deleteIndex];
					for (int i = deleteIndex; i < size - 1; i++)
					{
						customer[i] = customer[i + 1];
						personLoans[i] = personLoans[i + 1];
					}
					size--;
					Personalloan::saveLoanData();
					cout << "\t\tConta de empréstimo excluída com sucesso em " << getCurrentTime() << endl;
				}
			}
			else
			{
				cout << "\t\tConta de empréstimo não encontrada." << endl;
			}
		}
		else
		{
			cout << "\t\tSenha inválida" << endl;
		}
	}

	~Personalloan()
	{
		Personalloan::saveLoanData();
		if (personLoans != nullptr)
		{
			delete[] personLoans;
		}
		if (customer != nullptr)
		{
			delete[] customer;
		}


	}
};

class Investment
{
protected:
	int investmentID;
	string firstname;
	string lastname;
	double investmentAmount;
	string investmentDataFile;
	string email;
	string phonenumber;

public:
	string getFirstName()
	{
		return firstname;
	}

	void setFirstName(string firstName)
	{
		firstname = firstName;
	}

	string getLastName()
	{
		return lastname;
	}

	void setLastName(string lastName)
	{
		lastname = lastName;
	}
	string getemail()
	{
		return email;
	}
	string getphone()
	{
		return phonenumber;
	}
	void setphone(int Num)
	{
		phonenumber = Num;
	}
	void setemail(string mail)
	{
		email = mail;
	}
	Investment()
	{
	}
	Investment(string firstname, string lastname, int investmentID, double investmentAmount, string email, string phonenumber)
	{
		this->firstname = firstname;
		this->lastname = lastname;
		this->investmentID = investmentID;
		this->investmentAmount = investmentAmount;
		this->email = email;
		this->phonenumber = phonenumber;
	}
	int getinvestmentID()
	{
		return investmentID;
	}
	void setinvestmentid(int id)
	{
		investmentID = id;
	}
	void setinvestmentamount(double amount)
	{
		investmentAmount = amount;
	}
	double getinvestamount()
	{
		return investmentAmount;
	}

	virtual void calculateReturns() = 0;
	virtual void display() = 0;
	virtual void sreachaccount() = 0;
	virtual void saveData() = 0;
	virtual void addinvest() = 0;
	virtual void deleteAccount(string filename, int s) = 0;
	virtual void updateaccount() = 0;
	virtual ~Investment() {}
};

class RelativeInvestment : public Investment
{
private:
	string risklevel;
	string relativeName;
	string relativeinvestFile;
	int size;
	Admin admin;

	Customer** customer;
	RelativeInvestment** investments;

public:
	RelativeInvestment()
	{
		risklevel = "";
		relativeName = "";
		relativeinvestFile = "";
		size = 0;
		customer = nullptr;

	}
	void setrisklevel(string level)
	{
		risklevel = level;
	}
	void setrelativeName(string name)
	{
		relativeName = name;
	}
	RelativeInvestment(string filename, int size)
	{
		this->relativeinvestFile = filename;
		this->size = size;
		customer = new Customer * [size];
		investments = new RelativeInvestment * [size];

		for (int i = 0; i < size; i++)
		{
			investments[i] = nullptr;
			customer[i] = nullptr;
		}

		Inp.open(filename);
		if (!Inp)
		{
			cout << "\t\tFalha ao abrir o arquivo de dados do Empréstimo Estudantil." << endl;
			return;
		}
		int index = 0;
		string line;
		while (getline(Inp, line))
		{
			stringstream SS(line);

			// Read data
			int investID;
			double amountNO;
			string rel_name;
			string fname, lname;
			string risk_level;
			string phone_numb;
			string user_name, Email;
			string pass_word;

			SS >> fname >> lname >> user_name >> pass_word >> investID >> amountNO >> rel_name >> risk_level >> Email >> phone_numb;


			customer[index] = new Customer(user_name, pass_word);
			investments[index] = new RelativeInvestment(fname, lname, investID, amountNO, rel_name, risk_level, Email, phone_numb);
			index++;
			if (index >= size)
			{

				break;
			}
		}

		Inp.close();
	}
	RelativeInvestment(string firstname, string lastname, int investmentID, double investmentAmount, string relativeName, string risklevel, string email, string phonenumber)
		: Investment(firstname, lastname, investmentID, investmentAmount, email, phonenumber)
	{
		this->relativeName = relativeName;
		this->risklevel = risklevel;
	}
	string getrelativename()
	{
		return relativeName;
	}
	void deleteAccount(string filename, int s)
	{
		int deleteacc;
		if (admin.login())
		{
			RelativeInvestment::display();
			cout << "Insira o ID do investimento que deseja excluir: ";
			cin >> deleteacc;
			bool found = false;
			int deleteIndex = -1;
			for (int i = 0; i < size; i++)
			{
				if (investments[i]->getinvestmentID() == deleteacc)
				{
					cout << setw(30) << "\t\tConta Encontrada" << endl;
					cout << setw(30) << "\t\tNome: " << investments[i]->getFirstName() + " " + investments[i]->getLastName() << endl;
					cout << setw(30) << "\t\tSobrenome: " << customer[i]->getname() << endl;
					cout << setw(30) << "\t\tId de investimento: " << investments[i]->getinvestmentID() << endl;
					cout << setw(30) << "\t\tValor de Investimento: R$" << investments[i]->getinvestamount() << endl;
					cout << setw(30) << "\t\tNível de Risco: " << investments[i]->getrisklevel() << endl;
					cout << setw(30) << "\t\tNome Relativo: " << investments[i]->getrelativename() << endl;
					cout << setw(30) << "\t\tEmail: " << investments[i]->getemail() << endl;
					cout << setw(30) << "\t\tNúmero de Celular: " << investments[i]->getphone() << endl;
					found = true;
					deleteIndex = i;
					break;
				}
			}
			if (found)
			{
				char y;
				cout << "\t\tDigite Y para excluir esta conta...! ";
				cin >> y;
				if (y == 'Y' || y == 'y') {
					delete customer[deleteIndex];
					delete investments[deleteIndex];
					for (int i = deleteIndex; i < size - 1; i++)
					{
						customer[i] = customer[i + 1];
						investments[i] = investments[i + 1];
					}
					size--;
					RelativeInvestment::saveData();
					cout << "\t\tConta de investimento excluída com sucesso em " << getCurrentTime() << endl;
				}
				else
				{
					cout << "\t\tA conta não foi excluída" << endl;
				}
			}
			else
			{
				cout << "\t\tConta de investimento não encontrada." << endl;
			}
		}
		else
		{
			cout << "\t\tSenha inválida" << endl;
		}
	}
	void saveData()
	{
		Out.open(relativeinvestFile);


		if (Out.is_open())
		{
			
			// Write data to the file
			for (int i = 0; i < size; i++)
			{
				Customer* cust = customer[i];
				RelativeInvestment* invest = investments[i];

				Out << left << setw(20) << invest->getFirstName()
					<< left << setw(20) << invest->getLastName()
					<< left << setw(20) << cust->getname()
					<< left << setw(20) << cust->getpassword()
					<< left << setw(20) << invest->getinvestmentID()
					<< left << setw(20) << invest->getinvestamount()
					<< left << setw(30) << invest->getrelativename()
					<< left << setw(25) << invest->getrisklevel()
					<< left << setw(30) << invest->getemail()
					<< left << setw(30) << invest->getphone()
					<< endl;
			}
			
		}
		else
		{
			

			return;
		}


		Out.close();
	}
	string getrisklevel()
	{
		return risklevel;
	}
	void sreachaccount()
	{
		int serachaccount;
		cout << "\t\tDigite o Número do Investimento para pesquisar: ";
		cin >> serachaccount;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{
			if (investments[i]->getinvestmentID() == serachaccount)
			{
				if (customer[i]->login())
				{
					found1 = true;
					Index = i;
				}
			}
		}
		if (found1)
		{
			cout << left << setw(20) << "\t\tNome: " << investments[Index]->getFirstName() << " " << investments[Index]->getLastName() << endl;
			cout << left << setw(20) << "\t\tNome de usuário: " << customer[Index]->getname() << endl;
			cout << left << setw(20) << "\t\tID do Investimento: " << investments[Index]->investmentID << endl;
			cout << left << setw(20) << "\t\tValor do Investimento: R$ " << investments[Index]->getinvestamount() << endl;
			cout << left << setw(25) << "\t\tNome do Parente: " << investments[Index]->getrelativename() << endl;
			cout << left << setw(30) << "\t\tEmail: " << investments[Index]->getemail() << endl;
			cout << left << setw(30) << "\t\tTelefone: " << investments[Index]->getphone() << endl;
		}

		else
		{
			cout << "\t\tNúmero de Investimento não encontrado" << endl;
		}
	}

	void addinvest()
	{
		bool added = false;
		Out.open(relativeinvestFile, ios::app); // Abre o arquivo
		if (!Out)
		{
			cout << "\t\tArquivo não está aberto!" << endl;
			return;
		}

		cout << "\t\t\tREGISTRO DE CONTA DE INVESTIMENTO" << endl;
		string us, pass;
		string risk_level;
		char c;

		do
		{
			cout << "\t\t\tDigite o novo Primeiro Nome do Usuário: ";
			string fname;
			cin >> fname;

			cout << "\t\t\tDigite o novo Sobrenome do Usuário: ";
			string lname;
			cin >> lname;

			cout << "\t\t\tDigite o Nome de Usuário: ";
			cin >> us;

			cout << "\t\t\tDigite a Senha: ";
			cin >> pass;

			cout << "\t\t\tDigite o Nível de Risco: ";
			cin >> risk_level;

			int investId;
			cout << "\t\t\tDigite o Número do Investimento: ";
			cin >> investId;

			double Amountinvest;
			cout << "\t\t\tDigite o Valor do Investimento: ";
			cin >> Amountinvest;

			string email;
			cout << "\t\t\tDigite o Endereço de Email: ";
			cin >> email;

			string Rel_name;
			cout << "\t\t\tDigite o Nome do Parente: ";
			cin >> Rel_name;
			string phoneNumber;
			cout << "\t\t\tDigite o Número de Telefone: ";
			cin >> phoneNumber;
			added = true;
			if (added)
			{
				Customer* cust = new Customer(us, pass);
				RelativeInvestment* relinvest = new RelativeInvestment(fname, lname, investId, Amountinvest, Rel_name, risk_level, email, phoneNumber);

				customer[size] = cust;
				investments[size] = relinvest;

				size++;
			}

			cout << "\t\tA Conta foi Registrada com Sucesso em " << getCurrentTime() << endl;
			cout << "\t\tDeseja Adicionar Outro Registro? (S/N): ";
			cin >> c;
		} while (c == 'S' || c == 's');

		// Escreve os dados
		for (int i = size - 1; i < size; i++)
		{
			Customer* cust = customer[i];
			RelativeInvestment* invest = investments[i];
			Out << left << setw(20) << invest->getFirstName()
				<< left << setw(20) << invest->getLastName()
				<< left << setw(20) << cust->getname()
				<< left << setw(20) << cust->getpassword()
				<< left << setw(20) << invest->getinvestmentID()
				<< left << setw(20) << invest->getinvestamount()
				<< left << setw(20) << invest->getrelativename()
				<< left << setw(30) << invest->getrisklevel()
				<< left << setw(30) << invest->getemail()
				<< left << setw(30) << invest->getphone()
				<< endl;
		}

		Out.close();
	}

	void updateaccount()
	{
		bool updated = false;
		int updateinvest;
		RelativeInvestment::display();
		cout << "\t\t\tDigite o número do investimento para atualizar: ";
		cin >> updateinvest;
		string User, PASS, relativename, levelrish, mail;
		double amount;
		int id, phone_num;
		bool found = false;
		string fname, lname;
		int updateIndex = -1;
		for (int i = 0; i < size; i++)
		{
			if (investments[i]->getinvestmentID() == updateinvest)
			{
				cout << left << setw(20) << "\t\tNome: " << investments[i]->getFirstName() << " " << investments[i]->getLastName() << endl;
				cout << left << setw(20) << "\t\tNome de usuário: " << customer[i]->getname() << endl;
				cout << left << setw(20) << "\t\tID do Investimento: " << investments[i]->investmentID << endl;
				cout << left << setw(20) << "\t\tValor do Investimento: R$ " << investments[i]->investmentAmount << endl;
				cout << left << setw(20) << "\t\tNome do Parente: " << investments[i]->relativeName << endl;
				cout << left << setw(20) << "\t\tEmail: " << investments[i]->getemail() << endl;
				cout << left << setw(20) << "\t\tTelefone: " << investments[i]->getphone() << endl;
				found = true;
				updateIndex = i;
				break;
			}
		}
		if (found)
		{
			cout << "\t\t\tDigite o primeiro nome: ";
			cin >> fname;
			cout << "\t\t\tDigite o sobrenome: ";
			cin >> lname;

			cout << "\t\t\tDigite o novo Nome de Usuário: ";
			cin >> User;

			cout << "\t\t\tDigite a nova Senha: ";
			cin >> PASS;

			cout << "\t\t\tDigite o novo Nome do Parente: ";
			cin >> relativename;
			cout << "\t\t\tDigite o novo Número do Investimento: ";
			cin >> id;

			cout << "\t\t\tDigite o novo Valor do Investimento: ";
			cin >> amount;

			cout << "\t\t\tDigite o Nível de Risco: ";
			cin >> levelrish;
			cout << "\t\t\tDigite o Endereço de Email: ";
			cin >> mail;
			cout << "\t\t\tDigite o Número de Telefone: ";
			cin >> phone_num;
			updated = true;
			if (updated)
			{
				investments[updateIndex]->setFirstName(fname);
				investments[updateIndex]->setLastName(lname);

				customer[updateIndex]->setusername(User);
				customer[updateIndex]->setpassword(PASS);
				investments[updateIndex]->setrisklevel(levelrish);
				investments[updateIndex]->setrelativeName(relativename);
				investments[updateIndex]->setinvestmentid(id);
				investments[updateIndex]->setinvestmentamount(amount);

				investments[updateIndex]->setemail(mail);
				investments[updateIndex]->setphone(phone_num);
				cout << "\t\t\tConta Editada com Sucesso em " << getCurrentTime() << endl;
				RelativeInvestment::saveData();
			}
			else
			{
				cout << "\t\t\tAinda não foi Atualizado" << endl;
			}
		}
		else
		{
			cout << "\t\tConta Não Encontrada" << endl;
		}
	}

	void calculateReturns()
	{
		int serachaccount;
		cout << "\t\t\tDigite o Número do Investimento para pesquisar: ";
		cin >> serachaccount;
		bool found1 = false;

		int Index = -1;
		for (int i = 0; i < size; i++)
		{
			if (investments[i]->getinvestmentID() == serachaccount)
			{
				if (customer[i]->login())
				{
					found1 = true;
					Index = i;
					break;
				}
			}
		}
		if (found1)
		{
			double returns = investments[Index]->getinvestamount() * 0.05;
			cout << "\t\t\tO retorno total do seu Investimento é R$ " << returns << endl;
		}
		else
		{
			cout << "\t\tID do Investimento não Encontrado" << endl;
		}
	}

	void display()
	{
		cout << "\t\t\t==============Tipo de Investimento: Investimento Relativo=================" << endl;

		cout << left << setw(15) << "Número do Investimento"
			<< left << setw(18) << "Nome"
			<< left << setw(20) << "Valor do Investimento"
			<< left << setw(20) << "Informações do Parente"
			<< left << setw(30) << "Endereço de Email"
			<< left << setw(30) << "Telefone"
			<< left << setw(20) << "Nível de Risco"
			<< endl;

		for (int i = 0; i < size; i++)
		{
			cout << left << setw(15) << investments[i]->getinvestmentID()
				<< left << setw(18) << investments[i]->getFirstName() + " " + investments[i]->getLastName()
				<< left << setw(20) << investments[i]->getinvestamount()
				<< left << setw(20) << investments[i]->getrelativename()
				<< left << setw(30) << investments[i]->getemail()
				<< left << setw(30) << investments[i]->getphone()
				<< left << setw(20) << investments[i]->getrisklevel()
				<< endl;
		}
	}
	~RelativeInvestment() {
		RelativeInvestment::saveData();
		if (customer != nullptr) {
			delete[]customer;
		}
		if (investments != nullptr)
		{
			delete[]investments;

		}

	}
};

void aboutus()
{
	cout << setw(100) << "==================================================" << endl;
	cout << "\t\t\t\t\t\t\tSobre Nós" << endl;
	cout << setw(100) << "==================================================" << endl << endl;
	cout << "\t\t\t\t\tEste é um Projeto Simples de Sistema de Gerenciamento Bancário para o ";
	cout << "2º Semestre baseado na linguagem de programação C++ orientada a objetos.";

	cout << "\n\n\t\t\t\t\t\t\tMembros da Equipe Guerreiros: \n\n" << endl;

	cout << "\t\t\t\t\t\t\t[1] .Umair Inayat\n" << endl;
}

int CountLinesInFile(const string& filename)
{
	ifstream file(filename);
	int count = 0;
	string line;
	while (getline(file, line))
	{
		if (!line.empty())
		{
			count++;
		}
	}
	file.close();
	return count;
}

int main()
{
	system("cls");
	system("color f3");

	cout << setw(100) << "==================================================" << endl;
	cout << setw(100) << "            Bem-vindo ao Sistema de Gestão Bancária!         " << endl;
	cout << setw(100) << "==================================================" << endl;

	int S_Size = 0, C_Size = 0, St_Size = 0, P_Size = 0, R_Size = 0;
	S_Size = CountLinesInFile("save.txt");
	C_Size = CountLinesInFile("check.txt");
	St_Size = CountLinesInFile("student.txt");
	P_Size = CountLinesInFile("personal.txt");
	R_Size = CountLinesInFile("invest.txt");

	Account* SA = new SavingsAccount("save.txt", S_Size);
	Account* CA = new CheckingAccount("check.txt", C_Size);
	Loan* S_L = new StudentFeeLoan("student.txt", St_Size);
	Loan* PL = new Personalloan("personal.txt", P_Size);
	Investment* RI = new RelativeInvestment("invest.txt", R_Size);
	bool AloggedIn = false;
	bool UloggedIn = false;

	int choice;
	cout << "\t\t\t\t\t\t\t\tTipo de Conta \n";
	cout << endl;
	cout << setw(60) << " \t\t                  [1] . Administrador\n";
	cout << setw(50) << "\t\t  [2] . Usuário" << endl;
	cout << endl;
	cout << "\t\t\t\t\t\t\t\tDigite sua escolha...!";
	cin >> choice;
	char x;
	switch (choice)
	{
	case 1:
		system("cls");
		AloggedIn = true;
		while (AloggedIn)
		{
			system("cls");
			cout << "\n\n";
			cout << "\t\t\t\t\t\t==================================================" << endl;
			cout << "\t\t\t\t\t\t\t\tBem-vindo ao Portal do Administrador" << endl;
			cout << "\t\t\t\t\t\t==================================================" << endl;

			cout << "\n\t\t\t\t\t\t[1] . Conta Poupança: \n";
			cout << "\t\t\t\t\t\t[2] . Conta Corrente: \n";
			cout << "\t\t\t\t\t\t[3] . Empréstimo Estudantil: \n";
			cout << "\t\t\t\t\t\t[4] . Empréstimo Pessoal: \n";
			cout << "\t\t\t\t\t\t[5] . Investimento Relativo: \n";
			cout << "\t\t\t\t\t\t[6] . Sobre Nós \n";
			cout << "\t\t\t\t\t\t[7] . Sair \n";
			cout << "\n\t\t\t\t\t\tSelecione uma opção...!";
			int adchoice;
			cin >> adchoice;
			switch (adchoice)
			{
			case 1:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal de Administração da Conta Poupança\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\n\t\t\t\t\t\tSelecione uma Opção\n";
				cout << "\n\t\t\t\t\t\t[1] . Visualizar Contas de Clientes\n";
				cout << "\t\t\t\t\t\t[2] . Registro de Conta de Cliente\n";
				cout << "\t\t\t\t\t\t[3] . Editar Conta de Cliente\n";
				cout << "\t\t\t\t\t\t[4] . Excluir Conta de Cliente\n";
				cout << "\t\t\t\t\t\t[5] . Buscar Conta de Cliente\n";
				cout << "\n\t\t\t\t\t\tSelecione uma Opção...!";
				int svechoice;
				cin >> svechoice;
				switch (svechoice)
				{
				case 1:
					system("cls");
					SA->display();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 2:
					system("cls");
					SA->Addaccount(S_Size);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				case 3:
					system("cls");
					SA->updateaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				case 4:
					system("cls");
					SA->deleteaccount("save.txt", S_Size);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				case 5:
					system("cls");
					SA->serachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				}
				break;
			case 2:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\tPortal de Administração da Conta Corrente" << endl;
				cout << "\t\t\t\t\t\t==================================================" << endl;

				cout << "\n\n\t\t\t\t\t\t[1] . Visualizar Contas de Clientes\n";
				cout << "\t\t\t\t\t\t[2] . Registro de Conta de Cliente\n";
				cout << "\t\t\t\t\t\t[3] . Editar Conta de Cliente\n";
				cout << "\t\t\t\t\t\t[4] . Excluir Conta de Cliente\n";
				cout << "\t\t\t\t\t\t[5] . Buscar Conta de Cliente\n";
				cout << "\n\t\t\t\t\t\t\tSelecione uma Opção...!";
				int checkchoice;
				cin >> checkchoice;
				switch (checkchoice)
				{
				case 1:
					system("cls");
					CA->display();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				case 2:
					system("cls");
					CA->Addaccount(C_Size);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				case 3:
					system("cls");
					CA->updateaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				case 4:
					system("cls");
					CA->deleteaccount("check.txt", C_Size);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				case 5:
					system("cls");
					CA->serachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
					cin >> x;
					break;
				}
				break;
			case 3:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal de Administração do Empréstimo Estudantil" << endl;
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\n\t\t\t\t\t\tSelecione uma Opção\n\n";
				cout << "\t\t\t\t\t\t[1] . Visualizar Contas de Estudantes\n";
				cout << "\t\t\t\t\t\t[2] . Registro de Conta de Estudante\n";
				cout << "\t\t\t\t\t\t[3] . Editar Conta de Estudante\n";
				cout << "\t\t\t\t\t\t[4] . Excluir Conta de Estudante\n";
				cout << "\t\t\t\t\t\t[5] . Buscar Conta de Estudante\n";
				cout << "\n\t\t\t\t\t\tSelecione uma Opção...!";
				int studchoice;
				cin >> studchoice;
				switch (studchoice)
				{
				case 1:
					system("cls");
					S_L->display();
					cout << "\n\n";
					cout << "\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 2:
					system("cls");
					S_L->addloan();
					cout << "\n\n";
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 3:
					S_L->updateaccount();
					cout << "\n\n";
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 4:
					system("cls");
					S_L->deleteAccount("student.txt", St_Size);
					cout << "\n\n";
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 5:
					system("cls");
					S_L->sreachaccount();
					cout << "\n\n";
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\n\n";
					cout << "\t\t\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				}
				break;
			case 4:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal de Administração do Empréstimo Pessoal" << endl;
				cout << "\t\t\t\t\t\t==================================================" << endl;

				cout << "\n\n\t\t\t\t\t\tSelecione uma Opção \n\n";
				cout << "\t\t\t\t\t\t[1] . Visualizar Contas de Empréstimos Pessoais\n";
				cout << "\t\t\t\t\t\t[2] . Registro de Conta de Empréstimo Pessoal\n";
				cout << "\t\t\t\t\t\t[3] . Editar Conta de Empréstimo Pessoal\n";
				cout << "\t\t\t\t\t\t[4] . Excluir Conta de Empréstimo Pessoal\n";
				cout << "\t\t\t\t\t\t[5] . Buscar Conta de Empréstimo Pessoal\n";
				cout << "\n\t\t\t\t\t\tSelecione uma Opção...!";
				int Pchoice;
				cin >> Pchoice;
				switch (Pchoice)
				{
				case 1:
					system("cls");
					PL->display();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 2:
					system("cls");
					PL->addloan();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 3:
					system("cls");
					PL->updateaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 4:
					system("cls");
					PL->deleteAccount("personal.txt", P_Size);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 5:
					system("cls");
					PL->sreachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				}
				break;
			case 5:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal de Administração de Investimentos Relativos" << endl;
				cout << "\t\t\t\t\t\t==================================================" << endl;

				cout << "\n\n\t\t\t\t\t\tSelecione uma Opção \n\n";
				cout << "\t\t\t\t\t\t[1] . Visualizar Contas de Investimentos Relativos\n";
				cout << "\t\t\t\t\t\t[2] . Registro de Conta de Investimento Relativo\n";
				cout << "\t\t\t\t\t\t[3] . Editar Conta de Investimento Relativo\n";
				cout << "\t\t\t\t\t\t[4] . Excluir Conta de Investimento Relativo\n";
				cout << "\t\t\t\t\t\t[5] . Buscar Conta de Investimento Relativo\n";
				cout << "\n\t\t\t\t\t\tSelecione uma Opção...!";
				int Rchoice;
				cin >> Rchoice;
				switch (Rchoice)
				{
				case 1:
					system("cls");
					RI->display();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 2:
					system("cls");
					RI->addinvest();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 3:
					system("cls");
					RI->updateaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 4:
					system("cls");
					RI->deleteAccount("invest.txt", R_Size);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				case 5:
					system("cls");
					RI->sreachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal... ";
					cin >> x;
					break;
				}
				break;
			case 6:
				system("cls");
				aboutus();
				cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
				cin >> x;
				break;
			case 7:
				system("cls");
				AloggedIn = false;
				cout << "\n\n\t\t\t\t\t\tSaindo\n\n";
				cout << "\t\t\t\t\t\tSair do administrador em " << getCurrentTime() << endl;
				break;
			default:
				cout << "\t\t\t\t\tEntrada inválida" << endl;
				cout << "\t\t\t\t\t\tDigite qualquer caractere para ir ao menu principal...";
				cin >> x;
				break;
			}
		}
		break;
		case 2:
		system("cls");
		UloggedIn = true;
		while (UloggedIn)
		{

			system("cls");
			cout << "\n\n";
			cout << "\t\t\t\t\t\t==================================================" << endl;
			cout << "\t\t\t\t\t\t\t\tPortal do Usuário" << endl;
			cout << "\t\t\t\t\t\t==================================================" << endl;

			cout << "\t\t\t\t\t\t[1] . Conta Poupança: \n";
			cout << "\t\t\t\t\t\t[2] . Conta Corrente: \n";
			cout << "\t\t\t\t\t\t[3] . Empréstimo Estudantil: \n";
			cout << "\t\t\t\t\t\t[4] . Empréstimo Pessoal: \n";
			cout << "\t\t\t\t\t\t[5] . Investimento Relativo: \n";
			cout << "\t\t\t\t\t\t[6] . Sobre Nós \n";
			cout << "\t\t\t\t\t\t[7] . Sair!!! \n";

			cout << "\n\t\t\t\t\t\t\tSelecione uma opção...!";
			int userchoice;
			cin >> userchoice;
			switch (userchoice)
			{
			case 1:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal da Conta Poupança\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;

				cout << "\t\t\t\t\t\t[1] . Consulta de Saldo\n";
				cout << "\t\t\t\t\t\t[2] . Saque:\n";
				cout << "\t\t\t\t\t\t[3] . Depósito:\n";
				cout << "\t\t\t\t\t\t\tSelecione uma opção...!";
				int sachoice;

				cin >> sachoice;
				switch (sachoice)
				{
				case 1:
					system("cls");
					SA->serachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				case 2:
					system("cls");
					cout << "\t\t\t\t\t\tDigite o valor que deseja sacar";
					double amount;
					cin >> amount;
					SA->withdraw(amount);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				case 3:
					system("cls");
					cout << "\t\t\t\t\t\tDigite o valor que deseja depositar";
					double de_amount;
					cin >> de_amount;

					SA->deposit(de_amount);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				}

				break;
			case 2:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal da Conta Corrente\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\n\t\t\t\t\t\t[1] . Consulta de Saldo\n";
				cout << "\t\t\t\t\t\t[2] . Saque:\n";
				cout << "\t\t\t\t\t\t[3] . Depósito:\n";
				int ckchoice;
				cout << "\n\t\t\t\t\t\t\tDigite sua opção...";
				cin >> ckchoice;
				switch (ckchoice)
				{
				case 1:
					system("cls");
					cout << "\n\t\t\t\t======================================================================================\n";
					CA->serachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal... ";
					cin >> x;
					break;
				case 2:
					system("cls");
					cout << "\n\t\t\t\t======================================================================================\n";
					cout << "\t\t\t\t\t\tDigite o valor que deseja sacar... ";
					double amount;
					cin >> amount;
					CA->withdraw(amount);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal... ";
					cin >> x;
					break;
				case 3:
					system("cls");
					cout << "\n\t\t\t\t======================================================================================\n";
					cout << "\t\t\t\t\t\tDigite o valor que deseja depositar.. ";
					double de_amount;
					cin >> de_amount;

					CA->deposit(de_amount);
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\n======================================================================================\n";
					cout << "\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				}
				break;
			case 3:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal de Empréstimo Estudantil\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\n\t\t\t\t\t\t[1] . Consulta de Empréstimo\n";
				cout << "\t\t\t\t\t\t[2] . Calcular Juros:\n";

				int loanchoice;
				cout << "\n\t\t\t\t\t\t\tDigite sua opção...";
				cin >> loanchoice;
				switch (loanchoice)
				{
				case 1:
					system("cls");
					S_L->sreachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				case 2:
					system("cls");
					S_L->calculateInterest();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				}
				break;
			case 4:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal de Empréstimo Pessoal\n";
				cout << "\t\t\t\t\t\t================================================\n" << endl;
				cout << "\t\t\t\t\t\t[1] . Consulta de Empréstimo\n";
				cout << "\t\t\t\t\t\t[2] . Calcular Juros:\n";

				int ploanchoice;
				cout << "\n\t\t\t\t\t\t\tDigite sua opção...";
				cin >> ploanchoice;
				switch (ploanchoice)
				{
				case 1:
					system("cls");
					PL->sreachaccount();
					cout << "\t\t\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				case 2:
					system("cls");
					PL->calculateInterest();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				}
				break;
			case 5:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\t\t\t\tPortal de Investimento Relativo" << endl;
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\n\t\t\t\t\t\t[1] . Consulta de Investimento\n";
				cout << "\t\t\t\t\t\t[2] . Calcular Juros:\n";
				int invectchoice;
				cout << "\n\t\t\t\t\t\t\tDigite sua opção..." << endl;
				cin >> invectchoice;
				switch (invectchoice)
				{
				case 1:
					system("cls");
					RI->sreachaccount();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				case 2:
					system("cls");
					RI->calculateReturns();
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				default:
					system("cls");
					cout << "\t\t\tEntrada Inválida" << endl;
					cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
					cin >> x;
					break;
				}
				break;
			case 6:
				system("cls");
				cout << "\n\n";
				cout << "\t\t\t\t\t\t==================================================" << endl;
				cout << "\t\t\t\t\tSobre Nós " << endl;
				cout << "\t\t\t\t\t\t==================================================" << endl << endl;
				aboutus();
				cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
				cin >> x;
				break;
			case 7:
				system("cls");
				cout << "\n\n\n";
				cout << "\t\t\t\t\t\tObrigado por usar nossos serviços" << endl;
				cout << "\t\t\t\t\t\tUsuário desconectado em " << getCurrentTime() << endl;
				UloggedIn = false;

				break;

			default:
				system("cls");
				cout << "\t\t\t\t\tEntrada Inválida" << endl;
				cout << "\t\t\t\t\t\tDigite qualquer caractere para voltar ao menu principal...";
				cin >> x;
				break;
			}
		}
		break;
	default:
		system("cls");
		cout << "\t\t\t\t\t\tEntrada Inválida" << endl;
		break;
	}
	return 0;
}
