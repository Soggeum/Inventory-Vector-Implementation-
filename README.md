# Inventory-Vector-Implementation-
Studying Vector mechanism

C++ 템플릿(Template)을 사용하여 다양한 타입의 아이템을 저장할 수 있는 인벤토리 클래스를 구현합니다. 동적 메모리 할당과 해제를 직접 관리하며, C++ STL 컨테이너 중 `std::vector`의 핵심 동작 원리를 이해합니다. 이를 통해 제네릭 프로그래밍의 필요성과 메모리 관리의 중요성을 학습합니다.

# 인벤토리 기능 구현

<img width="255" height="230" alt="image" src="https://github.com/user-attachments/assets/43dbd858-79de-4305-9441-df1e385fb972" />


**`Inventory<T>` 클래스 구현**

`Item` 뿐만 아니라, `Weapon`, `Potion` 등 어떤 타입의 객체든 저장할 수 있도록 **템플릿 클래스**로 작성합니다.
새로운 클래스를 만들었을 경우에도 Inventory 클래스 내에 수정을 할 필요 없이 템플릿을 통해 쉽게 사용 가능합니다.


**멤버 변수 (private)**

- `T* pItems_`: 아이템 객체들을 저장할 **동적 배열을 가리키는 포인터**입니다. `new T[]`를 통해 메모리를 할당받습니다.
- `int capacity_`: 인벤토리가 최대로 저장할 수 있는 공간의 크기입니다.
- `int size_`: 현재 인벤토리에 저장된 아이템의 실제 개수입니다.

**생성자, 소멸자**

- **생성자: `Inventory(int capacity = 10)`**
    - 매개변수로 인벤토리의 용량(`capacity`)을 받으며, 값을 전달하지 않으면 **기본값으로 10**이 설정됩니다.
    - 안정성을 위해, 만약 0 이하의 `capacity` 값이 들어오면 **최소 용량을 1로 보정**합니다.
    
- **소멸자: `~Inventory()`**
    - `delete[] pItems_`를 실행하여 생성자에서 할당했던 메모리를 **반드시 해제**합니다. 메모리 누수(Memory Leak)를 방지하는 중요한 역할을 합니다.
    - 안전한 코드를 위해, 메모리 해제 후 포인터를 `nullptr`로 초기화합니다.

**멤버 함수 (public)**

- **`void AddItem(const T& item)`**
    - 새로운 아이템을 인벤토리에 추가합니다.
    - 인벤토리가 꽉 찼다면 "인벤토리가 꽉 찼습니다!" 메시지를 출력하고 아무 동작도 하지 않습니다.

- **`void RemoveLastItem()`**
    - 인벤토리의 가장 마지막에 추가된 아이템을 제거합니다.
    - 인벤토리가 비어있다면 "인벤토리가 비어있습니다." 메시지를 출력합니다.

- **`void PrintAllItems() const`**
    - 인벤토리에 있는 모든 아이템의 정보를 화면에 출력합니다.
    - 만약 인벤토리가 비어있다면 "(비어있음)" 메시지를 출력합니다.
 
## 도전 기능
<img width="337" height="361" alt="image" src="https://github.com/user-attachments/assets/2c07b29f-feff-4f1a-a2ad-3ebe210e693e" />


- **복사 생성자 및 대입(Assign) 함수 구현:**
    - 인벤토리가 복사/대입될 때, 아이템 데이터가 그대로 복사되는 깊은 복사(Deep Copy)를 구현합니다.
    - `void Assign(const Inventory<T>& other);` (대입 역할을 하는 함수)
        - 이미 존재하는 객체에 값을 덮어쓸 때 호출
     
- **`AddItem` 기능 확장:**
    - 인벤토리가 꽉 찬 상태에서 `AddItem`이 호출되면, 기존 `capacity`의 **2배** 크기로 인벤토리를 확장하고 새로운 아이템을 추가합니다. (기존 아이템들은 모두 유지되어야 합니다.)
      
- **`Resize` 멤버 함수 추가:**
    - `void Resize(int newCapacity)`: 인벤토리의 `capacity`를 `newCapacity`로 변경합니다.
      
- **`SortItems` 멤버 함수 추가:**
    - `void SortItems()`: 인벤토리의 아이템들을 **가격 오름차순**으로 정렬합니다. 
