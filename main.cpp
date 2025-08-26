#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Item;
class Weapon;
class Potion;

bool compareItemsByPrice(const Item& a, const Item& b);

class Item
{
protected:
	string name_;
	int price_;

public:
	Item() : name_("Unknown"), price_(0) {}
	Item(const string& name, const int& price) : name_(name), price_(price) {}

	string GetName() const { return name_; }
	int GetPrice() const { return price_; }
	void SetName(const string& name) { name_ = name; }
	void SetPrice(const int& price) { price_ = price; }

	virtual void PrintInfo() const 
	{
		cout << "[�̸�: " << name_ << ", ����: " << price_ << "G]" << endl;
	}
};

class Weapon : public Item
{
public:
	Weapon() : Item("Unknown", 0) {}
	Weapon(const string& name, const int& price) : Item(name, price) {}

	void PrintInfo() const override
	{
		cout << "[���� �̸�: " << name_ << ", ����: " << price_ << "G]" << endl;
	}
};

class Potion : public Item
{
public:
	Potion() : Item("Unknown", 0) {}
	Potion(const string& name, const int& price) : Item(name, price) {}

	void PrintInfo() const override
	{
		cout << "[���� �̸�: " << name_ << ", ����: " << price_ << "G]" << endl;
	}
};

template<typename T>
class Inventory 
{
private:
	T* pItems_;
	int capacity_;
	int size_;

public:
	Inventory(int capacity = 10) 
	{
		size_ = 0;
		capacity_ = (capacity <= 0) ? 1: capacity;
		pItems_ = new T[capacity_];
	}

	~Inventory()
	{
		delete[] pItems_;
		pItems_ = nullptr;
	}

	// ���� ������
	Inventory(const Inventory<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "�κ��丮 ���� �Ϸ�" << endl;
	}
	
	void AddItem(const T& item) 
	{
		if (size_ < capacity_) {
			pItems_[size_] = item;
			size_++;
		}

		else {
			Resize(capacity_ * 2);
			pItems_[size_] = item;
			size_++;
		}
	}

	void RemoveLastItem() 
	{
		if (!size_)
			cout << "�κ��丮�� ����ֽ��ϴ�." << '\n';
		else {
			size_--;
		}
	}

	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }

	void PrintAllItems() const
	{
		if (!size_)
			cout << "(�������)" << '\n';
		else {
			for (int i = 0; i < size_; i++) {
				pItems_[i].PrintInfo();
			}
		}
	}

	void Assign(const Inventory<T>& other)
	{
		if (this == &other)
			return;

		size_ = other.size_;
		capacity_ = other.capacity_;
		delete[] pItems_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; i++) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "�κ��丮 �Ҵ� �Ϸ�" << endl;
	}

	void Resize(int newCapacity)
	{
		capacity_ = newCapacity;
		T* pNewItems = new T[newCapacity];
		for (int i = 0; i < size_; i++) {
			pNewItems[i] = pItems_[i];
		}
		delete[] pItems_; 
		pItems_ = pNewItems;
	}

	void SortItems()
	{
		sort(&(pItems_[0]), &(pItems_[size_]), compareItemsByPrice);
	}
};

bool compareItemsByPrice(const Item& a, const Item& b) {
	return a.GetPrice() < b.GetPrice();
}

int main() {
	Inventory<Weapon> itemInventory(5);
	cout << "Capacity: " << itemInventory.GetCapacity() << endl;
	cout << "Size: " << itemInventory.GetSize() << endl;
	cout << "������ ���" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	cout << "������ �߰� : ���� ����, 50G" << endl;
	cout << "������ �߰� : �Ķ� ����, 30G" << endl;
	cout << "������ �߰� : �ʷ� ����, 20G" << endl;
	cout << "������ �߰� : ��� ����, 40G" << endl;
	itemInventory.AddItem(Weapon("���� ����", 50));
	itemInventory.AddItem(Weapon("�Ķ� ����", 30));
	itemInventory.AddItem(Weapon("�ʷ� ����", 20));
	itemInventory.AddItem(Weapon("��� ����", 40));
	cout << "Capacity: " << itemInventory.GetCapacity() << endl;
	cout << "Size: " << itemInventory.GetSize() << endl;
	cout << "������ ���" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	cout << "������ �߰� : ���� ����, 10G" << endl;
	cout << "������ �߰� : ���� ����, 60G" << endl;
	itemInventory.AddItem(Weapon("���� ����", 10));
	itemInventory.AddItem(Weapon("���� ����", 60));
	cout << "Capacity: " << itemInventory.GetCapacity() << endl;
	cout << "Size: " << itemInventory.GetSize() << endl;
	cout << "������ ���" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	cout << "������ ����" << endl;
	itemInventory.RemoveLastItem();
	cout << "Capacity: " << itemInventory.GetCapacity() << endl;
	cout << "Size: " << itemInventory.GetSize() << endl;
	cout << "������ ���" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	itemInventory.SortItems();
	cout << "���� ��" << endl;
	cout << "������ ���" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	Inventory<Weapon> itemInventory2(itemInventory);
	itemInventory2.PrintAllItems();
	cout << endl;

	Inventory<Weapon> itemInventory3;
	itemInventory3.Assign(itemInventory);
	itemInventory3.PrintAllItems();
}