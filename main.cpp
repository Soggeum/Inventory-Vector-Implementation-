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
		cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
	}
};

class Weapon : public Item
{
public:
	Weapon() : Item("Unknown", 0) {}
	Weapon(const string& name, const int& price) : Item(name, price) {}

	void PrintInfo() const override
	{
		cout << "[무기 이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
	}
};

class Potion : public Item
{
public:
	Potion() : Item("Unknown", 0) {}
	Potion(const string& name, const int& price) : Item(name, price) {}

	void PrintInfo() const override
	{
		cout << "[포션 이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
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

	// 복사 생성자
	Inventory(const Inventory<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "인벤토리 복사 완료" << endl;
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
			cout << "인벤토리가 비어있습니다." << '\n';
		else {
			size_--;
		}
	}

	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }

	void PrintAllItems() const
	{
		if (!size_)
			cout << "(비어있음)" << '\n';
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
		cout << "인벤토리 할당 완료" << endl;
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
	cout << "아이템 목록" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	cout << "아이템 추가 : 빨간 모자, 50G" << endl;
	cout << "아이템 추가 : 파란 모자, 30G" << endl;
	cout << "아이템 추가 : 초록 모자, 20G" << endl;
	cout << "아이템 추가 : 노란 모자, 40G" << endl;
	itemInventory.AddItem(Weapon("빨간 모자", 50));
	itemInventory.AddItem(Weapon("파란 모자", 30));
	itemInventory.AddItem(Weapon("초록 모자", 20));
	itemInventory.AddItem(Weapon("노란 모자", 40));
	cout << "Capacity: " << itemInventory.GetCapacity() << endl;
	cout << "Size: " << itemInventory.GetSize() << endl;
	cout << "아이템 목록" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	cout << "아이템 추가 : 보라 모자, 10G" << endl;
	cout << "아이템 추가 : 검정 모자, 60G" << endl;
	itemInventory.AddItem(Weapon("보라 모자", 10));
	itemInventory.AddItem(Weapon("검정 모자", 60));
	cout << "Capacity: " << itemInventory.GetCapacity() << endl;
	cout << "Size: " << itemInventory.GetSize() << endl;
	cout << "아이템 목록" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	cout << "아이템 제거" << endl;
	itemInventory.RemoveLastItem();
	cout << "Capacity: " << itemInventory.GetCapacity() << endl;
	cout << "Size: " << itemInventory.GetSize() << endl;
	cout << "아이템 목록" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	itemInventory.SortItems();
	cout << "정렬 후" << endl;
	cout << "아이템 목록" << endl;
	itemInventory.PrintAllItems();
	cout << endl;

	Inventory<Weapon> itemInventory2(itemInventory);
	itemInventory2.PrintAllItems();
	cout << endl;

	Inventory<Weapon> itemInventory3;
	itemInventory3.Assign(itemInventory);
	itemInventory3.PrintAllItems();
}