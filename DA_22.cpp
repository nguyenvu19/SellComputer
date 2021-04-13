#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#define runSQL if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR *)SQLQuery, SQL_NTS))	{ cout << "Error querying SQL Server" << endl; close();	}
#define get cout << "\nPress Any Key to exit\n";  getchar(); getchar();	Menu(choice); cin >> choice1; continue
#define get1 cout << "\nPress Any Key to exit\n";  getchar(); getchar(); MenuThem(); /*cin >> choice1;*/ continue
#define coutcus	cout << "\t\t\t\t\t\t -----------------------" << endl<< "\t\t\t\t\t\t|       CUSTOMER        |" << endl << "\t\t\t\t\t\t -----------------------" << endl;
#define coutpro cout << "\t\t\t\t\t\t -----------------------" << endl<< "\t\t\t\t\t\t|         PRODUCT       |" << endl << "\t\t\t\t\t\t -----------------------" << endl;

using namespace std;

class NodeBillinfo
{
private:
	char  ID[12], Date[22];
	int Giatien;
	NodeBillinfo* next;
public:
	NodeBillinfo()
	{
		strcpy_s(ID, "");
		strcpy_s(Date, "");
		Giatien = 0;
		this->next = NULL;
	}
	~NodeBillinfo() {}
	NodeBillinfo* GetNode(char* _IDBill, char* _Date, int _Giatien);
	void print();
	void printID();
	template <typename T>	friend class List;
	friend class NodeBill;
	friend class DBHelper;

};

class NodeBill
{
private:
	char ID[12], IDPro[12], IDCus[12];
	NodeBillinfo* billinfo;
	NodeBill* next;

public:
	NodeBill();
	~NodeBill() {}
	NodeBill* GetNode(char* _ID, char* _IDPro, char* _IDCus, NodeBillinfo* p);
	void Getdata(char* _ID, char* _IDPro, char* _IDCus);
	void print();
	void print1();
	template <typename T> friend class List;
	friend class DBHelper;
};

template <class T>
class List
{
	T* head;
public:
	List()	{	head = NULL; }
	~List()	{}
	template<class T>
	void AddTail(T* temp)
	{
		T* p = new T;
		if (!this->head)	this->head = temp;
		else
		{
			p = this->head;
			while (p->next != NULL)	p = p->next;
			p->next = temp;
		}
	}

	template<class T>
	void AddHead(T* temp)
	{
		if (this->head == NULL)	this->head = temp;
		else
		{
			temp->next = this->head;
			this->head = temp;
		}
	}

	template<class T>
	void AddAt(T* temp, int position) {
		if (position == 0 || head == NULL) AddHead(temp);
		else
		{
			int k = 1;
			T* p = this->head;
			while (p != NULL && k != position)
			{
				p = p->next;
				++k;
			}
			if (k != position)	AddTail(temp);
			else
			{
				temp->next = p->next;
				p->next = temp;
			}
		}
	}

	template<class T>
	void Output(List<T> l)
	{
		for (T* p = l.head; p != NULL; p = p->next)	p->print();
	}

	template<class T>
	void Output1(List<T> l)
	{
		for (T* p = l.head; p != NULL; p = p->next)	p->printID();
	}
	friend class DBHelper;
	friend class Customer;
	friend class Product;
};

class Customer
{
private:
	char ID[12], Name[32], Email[32], Phone[11];
	int nBill;
	List<NodeBill> bill;
public:
	Customer();
	~Customer();
	void Getdata(char* _ID, char* _Name, char* _Email, char* _Phone);
	void print();
	void printBill();
	friend class DBHelper;
};

class Product
{
private:
	char ID[12], Name[32];
	int Price, nBill;
	List<NodeBill> bill1;
public:
	Product();
	~Product();
	void Getdata(char* _ID, char* _Name, int _Price);
	void print();
	void printbill();
	friend class DBHelper;

};

class DBHelper
{
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlStmtHandle1;
	SQLHANDLE sqlStmtHandle2;
	SQLHANDLE sqlStmtHandle3;
	SQLHANDLE sqlStmtHandle4;
	SQLHANDLE sqlStmtHandle5;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
public:
	DBHelper() {	
		sqlConnHandle = NULL;
		sqlStmtHandle = sqlStmtHandle1 = sqlStmtHandle2 = sqlStmtHandle3 = sqlStmtHandle4 = sqlStmtHandle5 = NULL;
	};
	void init();
	void close();
	void getsBillinfo(List<NodeBillinfo>& lBilinfo, int& n);
	void getsBill(List<NodeBillinfo>&, Customer Cus[100], Product Pro[100], int nCustomer, int nProduct);
	void getsProduct(Product products[100], int& nProduct);
	void getsCustomer(Customer Customers[100], int& nCustomers);
	///////////////////////////////////////
	template <class T>	int of1(char* s, List<T>&);
	template <class T>	int of2(char* s, T a[100], int n);
	template <class T>	void find(List<T> a, int i);
	template <class T>	int Nbill(T t);
	template <class T>	void delNode(List<T>& a, int i, int& n);
	////////////////////////////////////////
	void insertCustomer(char* ID, char* Name, char* Email, char* Phone);
	void insertProduct(char* ID, char* Name, int Price);
	void insertBill(char* ID, char* IDPro, char* IDCus);
	void insertBillinfo(char* IDBill, char* Date, int Giatien);
	////////////////////////////////////////
	void delSQL(char* ID, int choice);
	void delBill(Customer Cus[100], char* s, int n, char* s1);
	//////////////////////////////////
	void updateCustomer(char* ID, char* Name, char* Email, char* Phone);
	void updateProduct(char* ID, char* Name, int Price);
	void updateBill(char* ID, char* IDPro, char* IDCus);
	void updateBILLinfo(char* IDBill, char* Date, int Giatien);
	//////////////////////////////////
	void insertBillinCus(char* s, char* ID, char* IDPro, char* Date, int Giatien, Customer Cus[100], int nCus, Product Pro[100], int nPro);
	void updateBillinCus(char* s, char* s1, Customer Cus[100], int nCus);
	//////////////////////////////////
	~DBHelper() {  getchar(); exit(0); }
};

template <class T>
int DBHelper::of1(char* s, List<T>& l)
{
	int i = 0;
	for (T* p = l.head; p != NULL; p = p->next, i++)
		if (strncmp(s, p->ID, strlen(s)) == 0)	return i;

	cout << "Khong tim thay doi tuong yeu cau " << endl;
	return -1;
}

template <class T>
void DBHelper::find(List<T> a, int i)
{
	T* temp = a.head;
	for (int j = 0; j < i; j++, temp = temp->next);
	temp->print();
}

template <class T>
void DBHelper::delNode(List<T>& a, int i, int& n)
{
	T* temp = a.head;
	if (i == 0)
	{
		a.head = temp->next;
		n--;
	}
	else
	{
		for (int j = 0; j < i - 1; j++, temp = temp->next);
		if (i == n - 1)
		{
			temp->next = NULL;
			n--;
		}
		else
		{
			temp->next = temp->next->next;
			n--;
		}
	}
}

template <class T>
int DBHelper::of2(char* s, T a[100], int n) // tim
{
	for (int i = 0; i < n; i++)
		if (strncmp(s, a[i].ID, strlen(s)) == 0)	return i;

	cout << "Khong tim thay doi tuong yeu cau " << endl;
	return -1;
}

template <class T>
int DBHelper::Nbill(T t)
{
	return t.nBill;
}

NodeBillinfo* NodeBillinfo::GetNode(char* _IDBill, char* _Date, int _Giatien)
{
	NodeBillinfo* p = new NodeBillinfo;
	if (p == NULL)	return NULL;
	strcpy_s(p->ID, 11, _IDBill);
	strcpy_s(p->Date, 21, _Date);
	p->Giatien = _Giatien;
	p->next = NULL;
	return p;
}

void NodeBillinfo::print()
{
	cout << "\t|\t\t\t\t|Date Buy:";
	for (int i = 0; i < sizeof(Date); i++)
	{
		if (Date[i] == 'þ') Date[i] = ' '; cout << Date[i];
	}
	cout << "|Gia Tien:" << Giatien;
	cout << endl;
}

void NodeBillinfo::printID()
{
	for (int i = 0; i < sizeof(ID); i++)
	{
		if (ID[i] == 'þ') ID[i] = ' '; cout << ID[i];
	}
	cout << endl;
}

NodeBill::NodeBill()
{
	strcpy_s(ID, "");
	strcpy_s(IDPro, "");
	strcpy_s(IDCus, "");
	billinfo = nullptr;
	this->next = NULL;
}

NodeBill* NodeBill::GetNode(char* _ID, char* _IDPro, char* _IDCus, NodeBillinfo* a)
{
	NodeBill* p = new NodeBill;

	if (p == NULL)
	{
		return NULL;
	}
	strcpy_s(p->ID, 11, _ID);
	strcpy_s(p->IDPro, 11, _IDPro);
	strcpy_s(p->IDCus, 11, _IDCus);
	p->billinfo = a;
	p->next = NULL;
	return p;
}

void NodeBill::Getdata(char* _ID, char* _IDPro, char* _IDCus)
{
	strcpy_s(ID, 11, _ID);
	strcpy_s(IDPro, 11, _IDPro);
	strcpy_s(IDCus, 11, _IDCus);
}

void NodeBill::print()
{
	this->print1();
	billinfo->print();
}

void NodeBill::print1()
{
	cout << "\t "; char gach = '_';
	for (int i = 0; i < 91; i++) cout << gach;
	cout << "\n\t|ID:";
	for (int i = 0; i < sizeof(ID); i++)
	{
		if (ID[i] == 'þ') ID[i] = ' '; cout << ID[i];
	}
	cout << "\t\t|ID San Pham:";
	for (int i = 0; i < sizeof(IDPro); i++)
	{
		if (IDPro[i] == 'þ') IDPro[i] = ' '; cout << IDPro[i];
	}
	cout << "\t|ID Khach Hang:";
	for (int i = 0; i < sizeof(IDCus); i++)
	{
		if (IDCus[i] == 'þ') IDCus[i] = ' '; cout << IDCus[i];
	}
	cout << " |";

	cout << endl;
}

Customer::Customer()
{
	strcpy_s(ID, "");
	strcpy_s(Name, "");
	strcpy_s(Email, "");
	strcpy_s(Phone, "000000000");
	nBill = 0;
}

Customer::~Customer(){}

void Customer::Getdata(char* _ID, char* _Name, char* _Email, char* _Phone)
{
	strcpy_s(ID, 11, _ID);
	strcpy_s(Name, 31, _Name);
	strcpy_s(Email, 31, _Email);
	strcpy_s(Phone, 12, _Phone);
}

void Customer::print()
{
	cout << "\t|";
	for (int i = 0; i < sizeof(ID) - 2; i++) { if (ID[i] == 'þ') ID[i] = ' ';  cout << ID[i]; }
	cout << "|";
	for (int i = 0; i < sizeof(Name) - 2; i++) { if (Name[i] == 'þ') Name[i] = ' '; cout << Name[i]; }
	cout << "|";
	for (int i = 0; i < sizeof(Email) - 2; i++) { if (Email[i] == 'þ') Email[i] = ' ';  cout << Email[i]; }
	cout << "|";
	for (int i = 0; i < sizeof(Phone) - 1; i++) { if (Phone[i] == 'þ') Phone[i] = ' ';  cout << Phone[i]; }
	cout << "|" << endl;
}

void Customer::printBill()
{
	if (nBill == 0)
	{
		cout << "\nKhach Hang Chua Co Hoa Don " << endl;
		return;
	}
	else
	{
		cout << "\nSo hoa don khach hang co la : " << nBill << endl;
		bill.Output(bill);
	}
}

Product::Product()
{
	strcpy_s(ID, "");
	strcpy_s(Name, "");
	Price = 0;
	nBill = 0;
}

Product::~Product()	{}

void Product::Getdata(char* _ID, char* _Name, int _Price)
{
	strcpy_s(ID, 11, _ID);
	strcpy_s(Name, 31, _Name);
	Price = _Price;
}

void Product::print()
{
	cout << "\t|";
	for (int i = 0; i < sizeof(ID) - 2; i++) { if (ID[i] == 'þ') ID[i] = ' ';  cout << ID[i]; }
	cout << "|";
	for (int i = 0; i < sizeof(Name) - 2; i++) { if (Name[i] == 'þ') Name[i] = ' '; cout << Name[i]; }
	cout << "|";
	cout << setw(12) << Price << "|" << endl;

}

void Product::printbill()
{
	if (nBill == 0)
	{
		cout << "\nSan Pham Chua Co Hoa Don " << endl;
		return;
	}
	else
	{
		cout << "\nSo hoa don San Pham co la : " << nBill << endl;
		bill1.Output(bill1);
	}
}

void DBHelper::init()
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))	close();
	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))		close();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))	close();
	cout << "SQL Server..." << endl;
	switch (SQLDriverConnect(sqlConnHandle, NULL, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=TUEPHANTHE;DATABASE=BanHang;Trusted=true;", SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT))
	{
	case SQL_SUCCESS:
		cout << "Successfully connected to SQL Server" << endl;
		break;
	case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server" << endl;
		break;
	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server" << endl;
		close();
		break;
	case SQL_ERROR:
		cout << "Could not connect to SQL Server" << endl;
		close();
		break;
	default:
		break;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))	close();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle1))	close();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle2))	close();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle3))	close();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle4))	close();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle5))	close();
}

void DBHelper::close()
{
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	cout << "Press Any Key" << endl;
	getchar();
}

void DBHelper::getsBillinfo(List<NodeBillinfo>& lBillinfo, int& n)
{
	NodeBillinfo node;
	wchar_t SQLQuery[256] = L"SELECT * FROM BILLinfo ";
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle4, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		return;
	}
	else
	{
		SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLINTEGER ptrSqlVersion;
		char ID[11], Date[21];
		int Giatien;
		while (SQLFetch(sqlStmtHandle4) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle4, 1, SQL_CHAR, ID, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle4, 2, SQL_CHAR, Date, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle4, 3, SQL_C_ULONG, &Giatien, 0, &ptrSqlVersion);
			NodeBillinfo* a = node.GetNode(ID, Date, Giatien);
			lBillinfo.AddTail(a);
			n++;
		}

	}

}

void DBHelper::getsCustomer(Customer Customers[100], int& n)
{
	wchar_t SQLQuery[256] = L"SELECT * FROM Customer ";
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle1, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		return;
	}
	else
	{
		SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLINTEGER ptrSqlVersion;
		char ID[11], Name[31], Email[31], Phone[12];
		while (SQLFetch(sqlStmtHandle1) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle1, 1, SQL_CHAR, ID, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle1, 2, SQL_CHAR, Name, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle1, 3, SQL_CHAR, Email, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle1, 4, SQL_CHAR, Phone, SQL_RESULT_LEN, &ptrSqlVersion);
			Customers[n++].Getdata(ID, Name, Email, Phone);
		}
	}
}

void DBHelper::getsProduct(Product products[100], int& n)
{
	wchar_t SQLQuery[256] = L"SELECT * FROM Product ";
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle2, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		return;
	}
	else
	{
		SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLINTEGER ptrSqlVersion;
		char ID[11], Name[51];
		int Price;
		while (SQLFetch(sqlStmtHandle2) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle2, 1, SQL_CHAR, ID, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle2, 2, SQL_CHAR, Name, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle2, 3, SQL_C_ULONG, &Price, 0, &ptrSqlVersion);
			products[n++].Getdata(ID, Name, Price);
		}
	}
}

void DBHelper::getsBill(List<NodeBillinfo>& lBillinfo, Customer Cus[100], Product Pro[100], int nCus, int nPro)
{
	NodeBill node, node1;
	wchar_t SQLQuery[256] = L"SELECT * FROM Bill ";
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle3, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		return;
	}
	else
	{
		SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLINTEGER ptrSqlVersion;
		char ID[11], IDPro[11], IDCus[11];
		NodeBillinfo* p = lBillinfo.head;
		while (SQLFetch(sqlStmtHandle3) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle3, 1, SQL_CHAR, ID, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle3, 2, SQL_CHAR, IDPro, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle3, 3, SQL_CHAR, IDCus, SQL_RESULT_LEN, &ptrSqlVersion);
			NodeBill* a = node.GetNode(ID, IDPro, IDCus, p);
			NodeBill* b = node1.GetNode(ID, IDPro, IDCus, p);
			p = p->next;
			int i = of2(IDCus, Cus, nCus);
			Cus[i].bill.AddTail(a);
			Cus[i].nBill++;
			i = of2(IDPro, Pro, nPro);
			Pro[i].bill1.AddTail(b);
			Pro[i].nBill++;
		}
	}
}

void DBHelper::insertCustomer(char* ID, char* Name, char* Email, char* Phone)
{
	string a1, a2, a3, a4;
	a1 = ID;	a2 = Name;	a3 = Email;	a4 = Phone;
	string s = "insert into Customer values ('" + a1 + "','" + a2 + "','" + a3 + "','" + a4 + "')";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		close();
	}
}

void DBHelper::insertProduct(char* ID, char* Name, int Price)
{
	string a1, a2, a3;
	a1 = ID;
	a2 = Name;
	stringstream ss;
	ss << Price;
	ss >> a3;
	string s = "insert into Product values ('" + a1 + "','" + a2 + "','" + a3 + "')";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		close();
	}
}

void DBHelper::insertBill(char* ID, char* IDPro, char* IDCus)
{
	string a1 = ID, a2 = IDPro, a3 = IDCus;
	string s = "insert into Bill values ('" + a1 + "','" + a2 + "','" + a3 + "')";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		close();
	}
}

void DBHelper::insertBillinfo(char* IDBill, char* Date, int Giatien)
{
	string a1 = IDBill, a2 = Date, a3;
	stringstream ss;
	ss << Giatien;
	ss >> a3;
	string s = "insert into BILLinfo values ('" + a1 + "','" + a2 + "','" + a3 + "')";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)SQLQuery, SQL_NTS))
	{
		cout << "Error querying SQL Server" << endl;
		close();
	}
}

void DBHelper::delSQL(char* ID, int choice)
{
	string s;
	string a1 = ID;
	if (choice == 1)	  s = "DELETE Customer WHERE ID = '" + a1 + "'";
	else if (choice == 2) s = "DELETE Product WHERE ID = '" + a1 + "'";
	else if (choice == 3) s = "DELETE Bill WHERE ID = '" + a1 + "'";
	else if (choice == 4) s = "DELETE BILLinfo WHERE IDBill = '" + a1 + "'";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	runSQL;
}

void DBHelper::delBill(Customer Cus[100], char* s, int n, char* s1)
{
	int j = of2(s, Cus, n);
	int i = of1(s1, Cus[j].bill);
	if (i == -1)
	{
		cout << "\n NHAP ID CAN XOA SAI\n ";
		return;
	}
	delNode(Cus[j].bill, i, Cus[j].nBill);
}

void DBHelper::updateCustomer(char* ID, char* Name, char* Email, char* Phone)
{
	string a1 = ID, a2 = Name, a3 = Email, a4 = Phone;
	string s = "UPDATE Customer SET Name = '" + a2 + "', Email = '" + a3 + "', Phone = '" + a4 + "' WHERE ID = '" + a1 + "'";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	runSQL
}

void DBHelper::updateProduct(char* ID, char* Name, int Price)
{
	string a1 = ID, a2 = Name, a3;
	stringstream ss;
	ss << Price;
	ss >> a3;
	string s = "UPDATE Product SET Name = '" + a2 + "', Price = '" + a3 + "' WHERE ID = '" + a1 + "'";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	runSQL
}

void DBHelper::updateBill(char* ID, char* IDPro, char* IDCus)
{
	string a1 = ID, a2 = IDPro, a3 = IDCus;
	string s = "UPDATE Bill SET IDPro = '" + a2 + "', IDCus = '" + a3 + "' WHERE ID = '" + a1 + "'";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	runSQL
}

void DBHelper::updateBILLinfo(char* IDBill, char* Date, int Giatien)
{
	string a1, a2, a3;
	a1 = IDBill;
	a2 = Date;
	stringstream ss;
	ss << Giatien;
	ss >> a3;
	string s = "UPDATE BILLinfo SET DateBuy = '" + a2 + "', GiaTien = '" + a3 + "' WHERE IDBill = '" + a1 + "'";
	wchar_t SQLQuery[256] = L" ";
	for (int i = 0; i < s.length(); i++)
		SQLQuery[i] = s[i];
	runSQL
}

void DBHelper::insertBillinCus(char* s, char* ID, char* IDPro, char* Date, int Giatien, Customer Cus[100], int nCus, Product Pro[100], int nPro)
{
	NodeBillinfo node;
	NodeBillinfo* a = node.GetNode(ID, Date, Giatien);
	NodeBill node1;
	NodeBill* b = node1.GetNode(ID, IDPro, s, a);
	int i = of2(s, Cus, nCus);
	Cus[i].bill.AddTail(b);
	Cus[i].nBill++;
	i = of2(IDPro, Pro, nPro);
	Pro[i].bill1.AddTail(b);
	Pro[i].nBill++;
}

void DBHelper::updateBillinCus(char* s, char* s1, Customer Cus[100], int nCus)
{
	int i = of2(s, Cus, nCus);
	int j = of1(s1, Cus[i].bill);

	NodeBill* temp = Cus[i].bill.head;
	for (int k = 0; k < j; k++, temp = temp->next);

	char IDPro[12], IDCus[12];
	strcpy_s(IDPro, 11, temp->IDPro);
	strcpy_s(IDCus, 11, temp->IDCus);

	delBill(Cus, s, nCus, s1);

	cout << "Nhap thong tin Update:" << endl;
	char IDBill[11], Date[21];
	int Giatien;
	cout << "Date Buy : "; cin >> Date;
	cout << "Gia tien : "; cin >> Giatien;
	NodeBillinfo node;
	NodeBillinfo* a = node.GetNode(s1, Date, Giatien);
	NodeBill node1;
	NodeBill* b = node1.GetNode(s1, IDPro, IDCus, a);
	Cus[i].bill.AddAt(b, j);
	Cus[i].nBill++;
	updateBILLinfo(s1, Date, Giatien);

}

void printCus()
{
	char gach = '_';
	cout << "\t|ID" << setw(13) << "|Name" << setw(32) << "|Email" << setw(31) << "|Phone" << setw(6) << "|" << endl;
	cout << "\t|";
	for (int i = 0; i < 83; i++)
	{
		if (i == 10 || i == 41 || i == 72) cout << "|";
		else cout << gach;
	}
	cout << "|" << endl;
}

void printPro()
{
	char gach = '_';
	cout << "\t|ID" << setw(13) << "|Name" << setw(32) << "|Price" << setw(8) << "|" << endl;
	cout << "\t|";
	for (int i = 0; i < 54; i++)
	{
		if (i == 10 || i == 41) cout << "|";
		else cout << gach;
	}
	cout << "|" << endl;
}

void Menu0()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\t\t\t\t  ********************* MENU *********************\n";
	cout << "\t\t\t\t  *  Chon thao tac tren :                        *\n";
	cout << "\t\t\t\t  *  1. TABLE CUSTOMER                           *\n";
	cout << "\t\t\t\t  *  2. TABLE PRODUCT                            *\n";
	cout << "\t\t\t\t  *  3. Nhap lua chon khac tu 1->2 de thoat      *\n";
	cout << "\t\t\t\t  ************************************************\n";
	cout << "\n\t\t\t\t  Nhap lua chon cua ban: ";
}

void Menu(int choice) // trong menu da co system clear
{
	system("cls");
	if (choice == 1) coutcus
	if (choice == 2) coutpro
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\t\t\t\t  ********************* MENU TABLE ********************\n";
	cout << "\t\t\t\t  *  Chon thao tac:                                   *\n";
	cout << "\t\t\t\t  *  1. Xuat thong tin toan bo doi tuong              *\n";
	cout << "\t\t\t\t  *  2. Xuat thong tin doi tuong theo yeu cau ma ID   *\n";
	cout << "\t\t\t\t  *  3. Them thong tin doi tuong                      *\n";
	cout << "\t\t\t\t  *  4. Xoa thong tin doi tuong theo yeu cau ma ID    *\n";
	cout << "\t\t\t\t  *  5. Update thong tin doi tuong theo yeu cau ma ID *\n";
	cout << "\t\t\t\t  *  6. Nhap khac so tu 1 -> 6 de thoat               *\n";
	cout << "\t\t\t\t  *****************************************************\n";
	cout << "\n\t\t\t\t  Nhap lua chon cua ban: ";
}

void MenuThem()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\t\t\t\t  ********************* MENU *********************\n";
	cout << "\t\t\t\t  *  Chon thao tac:                              *\n";
	cout << "\t\t\t\t  *  1.  Khach Hang                              *\n";
	cout << "\t\t\t\t  *  2.  Hoa don Khach Hang                      *\n";
	cout << "\t\t\t\t  *  3.  Nhap khac so tu 1 - 3 de thoat          *\n";
	cout << "\t\t\t\t  ************************************************\n";
	cout << "\n\t\t\t\t  Nhap lua chon cua ban: ";
}

int main()
{
	DBHelper database;
	database.init();
	List <NodeBillinfo> Lbillinfo;
	Customer Cus[100];
	Product Pro[100];
	int nBillinfo = 0, nBill = 0, nCus = 0, nPro = 0;
	database.getsCustomer(Cus, nCus);
	database.getsProduct(Pro, nPro);
	database.getsBillinfo(Lbillinfo, nBillinfo);
	database.getsBill(Lbillinfo, Cus, Pro, nCus, nPro);
	int choice, choice1;

	do
	{
		Menu0();
		cin >> choice;
		if (choice == 1)
		{
			Menu(choice);	cin >> choice1;
			do
			{
				if (choice1 == 1)
				{
					system("cls");
					coutcus	printCus();
					for (int i = 0; i < nCus; i++)	Cus[i].print();
					get;
				}
				if (choice1 == 2)
				{
					system("cls");	coutcus
					cout << "Nhap ID khach hang can tim:";	char s[11];	cin >> s;
					int i = database.of2(s, Cus, nCus);
					if (i != -1)
					{
						printCus();	Cus[i].print();
						cout << "\n\nBAN CO MUON XUAT THONG TIN HOA DON CUA KHACH HANG NAY KO (Y / N)?";
						char luachon;	cin >> luachon;
						if (luachon == 'y' || luachon == 'Y') Cus[i].printBill();
					}
					get;
				}
				if (choice1 == 3)
				{
					do
					{
						MenuThem(); cin >> choice1;
						if (choice1 == 1)
						{
							system("cls");	coutcus
							char ID[12], Name[32], Email[32], Phone[12];
							cout << "Nhap thong tin doi tuong " << endl;
							cout << "ID Khach hang :"; cin >> ID;
							int i = database.of2(ID, Cus, nCus);
							if (i != -1)
							{
								cout << "Khach hang nay da ton tai khong can them" << endl;
								get1;
							}
							cout << "Ho ten Khach hang:"; cin.ignore(1); cin.getline(Name, 32);
							cout << "Email Khach hang: "; cin >> Email;
							cout << "SDT Khach hang: "; cin >> Phone;
							Cus[nCus++].Getdata(ID, Name, Email, Phone);
							database.insertCustomer(ID, Name, Email, Phone);
							printCus();
							Cus[nCus - 1].print();
							get1;
						}
						if (choice1 == 2)
						{
							system("cls");	coutcus
							char s[12];
							cout << "Nhap ID Khach Hang can them Hoa Don:"; cin >> s;
							int i = database.of2(s, Cus, nCus);
							if (i == -1) { get1; }
							printCus();	Cus[i].print(); Cus[i].printBill();
							char ID[12], IDPro[12], Date[21];
							int Giatien;
							cout << "Nhan enter de tiep tuc ";	getchar(); getchar(); system("cls");
							coutcus
							cout << "\nID Cac hoa don da su dung: \n";
							Lbillinfo.Output1(Lbillinfo);
							cout << "Nhap ID Bill khong thuoc tap tren : "; cin >> ID;
							i = database.of1(ID, Lbillinfo);
							if (i != -1)
							{
								cout << "Hoa don da ton tai KHONG CAN THEM" << endl;
								get1;
							}
							cout << "Nhan enter de tiep tuc ";	getchar(); getchar();	system("cls");
							coutcus printPro();
							for (int i = 0; i < nPro; i++) Pro[i].print();

							cout << "Nhap ID San Pham thuoc tap tren: "; cin >> IDPro;
							i = database.of2(IDPro, Pro, nPro); if (i == -1) { get1; }
							cout << "Nhan enter de tiep tuc ";	getchar(); getchar();	system("cls");
							coutcus
							cout << "Them du lieu vao HOA DON CHI TIET : \n" ;
							cout << "Date Buy: "; cin >> Date;
							cout << "Gia tien: "; cin >> Giatien;
							database.insertBillinCus(s, ID, IDPro, Date, Giatien, Cus, nCus, Pro, nPro);
							database.insertBill(ID, IDPro, s);
							database.insertBillinfo(ID, Date, Giatien);
							get1;
						}
						get;
					} while (choice1 >= 1 && choice1 <= 2);
				}
				if (choice1 == 4)
				{
					do
					{
						MenuThem();
						cin >> choice1;
						if (choice1 == 1)
						{
							system("cls");	coutcus
							cout << "Nhap thong tin doi tuong muon xoa: "; char s[10];	cin >> s;
							int i = database.of2(s, Cus, nCus);
							if (i == -1) { get1; }
							printCus(); Cus[i].print();	Cus[i].printBill();
							if (database.Nbill(Cus[i]) == 0)
							{
								cout << "\nKhach hang nay khong co hoa don CO THE XOA " << endl;
								database.delSQL(s, 1);
								for (int j = i; j < nCus - 1; j++)	Cus[j] = Cus[j + 1];
								nCus--;
							}
							else	cout << "\nKHONG THE XOA Khach hang nay vi chua Xoa du lieu o BILL va Billinfo" << endl;
							get1;
						}
						if (choice1 == 2)
						{
							system("cls");	coutcus
							cout << "Nhap thong tin Khach Hang: "; char s[12];	cin >> s;
							int i = database.of2(s, Cus, nCus);
							if (i == -1) { get1; }
							printCus(); Cus[i].print();	Cus[i].printBill();
							if (database.Nbill(Cus[i]) == 0)
							{
								cout << "Khach Hang KO CO HOA DON de xoa "; get1;
							}
							cout << "\nNhap ID Bill ban muon xoa :"; char s1[12]; cin >> s1;
							cout << "\n\nSau khi xoa: \n";
							database.delBill(Cus, s, nCus, s1);
							printCus();	Cus[i].print(); Cus[i].printBill();
							database.delSQL(s1, 4);
							database.delSQL(s1, 3);
							get1;
						}
						get;
					} while (choice1 >= 1 && choice1 <= 2);
				}
				if (choice1 == 5)
				{
					do
					{
						MenuThem();
						cin >> choice1;
						if (choice1 == 1)
						{
							system("cls");
							coutcus
								cout << "Nhap ID thong tin doi tuong muon update" << endl;
							char ID[11], Name[31], Email[31], Phone[11];	cin >> ID;
							int i = database.of2(ID, Cus, nCus);
							if (i == -1) { get1; }
							printCus();	Cus[i].print();
							cout << "Nhap thong tin Update:" << endl;;
							cout << "Ho ten Khach hang:"; cin.ignore(1); cin.getline(Name, 30);
							cout << "Email Khach hang: "; cin >> Email;
							cout << "SDT Khach hang: "; cin >> Phone;
							Cus[i].Getdata(ID, Name, Email, Phone);
							printCus();	Cus[i].print();
							database.updateCustomer(ID, Name, Email, Phone);
							get1;
						}
						if (choice1 == 2)
						{
							system("cls");
							coutcus
								cout << "Nhap thong tin Khach Hang: "; char s[12];	cin >> s;
							int i = database.of2(s, Cus, nCus);
							if (i == -1) { get1; }
							printCus(); Cus[i].print(); Cus[i].printBill();
							cout << "\n\nNhap ID Hoa Don ban muon UPDATE :"; char s1[12]; cin >> s1;
							database.updateBillinCus(s, s1, Cus, nCus);
							printCus(); Cus[i].print(); Cus[i].printBill();
							get1;
						}
						get;
					} while (choice1 >= 1 && choice1 <= 2);
				}
			} while (choice1 >= 1 && choice1 <= 5);
		}
		if (choice == 2)
		{
			Menu(choice);
			cin >> choice1;
			do
			{
				if (choice1 == 1)
				{
					system("cls");	coutpro	printPro();
					for (int i = 0; i < nPro; i++) Pro[i].print();
					get;
				}
				if (choice1 == 2)
				{
					system("cls");	coutpro
					cout << "Nhap ID can tim: ";	char s[10];	cin >> s;
					int i = database.of2(s, Pro, nPro);
					if (i != -1)
					{
						printPro();	Pro[i].print();
						cout << "\n\nBAN CO MUON XUAT THONG TIN HOA DON CUA SAN PHAM NAY KO (Y / N)?";
						char luachon;
						cin >> luachon;
						if (luachon == 'y' || luachon == 'Y') Pro[i].printbill();
					}
					get;
				}
				if (choice1 == 3)
				{
					system("cls"); coutpro
					char ID[12], Name[32];
					int Price;
					cout << "Nhap thong tin doi tuong " << endl;
					cout << "ID San pham :"; cin >> ID;
					int i = database.of2(ID, Pro, nPro);
					if (i != -1)
					{
						cout << "San pham nay da ton tai khong can them" << endl;
						get;
					}
					cout << "Ten san Pham: "; cin.ignore(1); cin.getline(Name, 31);
					cout << "Gia tien: "; cin >> Price;
					Pro[nPro++].Getdata(ID, Name, Price);
					database.insertProduct(ID, Name, Price);
					printPro();	Pro[nPro - 1].print();
					get;
				}
				if (choice1 == 4)
				{
					system("cls");	coutpro
					cout << "Nhap thong tin doi tuong muon xoa" << endl;
					char s[10];	cin >> s;
					int i = database.of2(s, Pro, nPro);	if (i == -1) { get; }
					printPro(); Pro[i].print(); Pro[i].printbill();
					if (database.Nbill(Pro[i]) == 0)
					{
						cout << "\nSan Pham nay khong co hoa don CO THE XOA" << endl;
						database.delSQL(s, 2);
						for (int j = i; j < nPro - 1; j++)	Pro[j] = Pro[j + 1]; // gan lui 1 gia tri
						nPro--;
					}
					else cout << "\nKHONG THE XOA San pham nay vi chua Xoa du lieu o BILL" << endl;
					get;
				}
				if (choice1 == 5)
				{
					system("cls"); coutpro
					cout << "Nhap ID thong tin doi tuong muon update: ";
					char ID[11], Name[31];
					int Price;
					cin >> ID;
					int i = database.of2(ID, Pro, nPro);	if (i == -1) { get; }
					printPro(); Pro[i].print();
					cout << "Nhap thong tin Update:" << endl;
					cout << "Ten san pham: "; cin.ignore(1); cin.getline(Name, 30);
					cout << "Gia tien: "; cin >> Price;
					Pro[i].Getdata(ID, Name, Price);
					printPro(); Pro[i].print();
					database.updateProduct(ID, Name, Price);
					get;
				}
			} while (choice1 >= 1 && choice1 <= 5);
		}
	} while (choice >= 1 && choice <= 2);
	database.close();
	return 0;
}
