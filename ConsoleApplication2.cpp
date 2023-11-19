#include <iostream>
/*-Класс который отвечает за отдельные элементы списка-*/
class Node {
public:
    double data;
    Node* prev, * next;
/*-Конструктор-*/
public: 
    Node(double data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};
/*-Класс который определяет все операции-*/
class LinkedList {
public:
    Node* head, * tail;
public:
/*-Конструктор-*/
    LinkedList() {
        head = tail = NULL;
    }
/*-(если объект LinkedList по каким то причинам будет удаляться, нужен ->)деструктор - чтобы не было утечки памяти-*/
    ~LinkedList() {
        while (head != NULL)
            pop_front();
    }
/*-Метод - добавление нового обьекта в начало-*/
    Node* push_front(double data) {
        Node* ptr = new Node(data);
        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        head = ptr;

        return ptr;            
    }
 /*-Метод - добавление нового обьекта в конец-*/
    Node* push_back(double data) {
        Node* ptr = new Node(data);
        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;

        return ptr;
    }
/*-Метод - удаление обьекта в начале-*/
    void pop_front() {
        if (head == NULL) return;

        Node* ptr = head->next;
        if (ptr != NULL)
            ptr->prev = NULL;
        else
            tail = NULL;

        delete head;
        head = ptr;
    }
/*-Метод - удаление обьекта в конце-*/
    void pop_back() {
        if (tail == NULL) return;

        Node* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;
        delete tail;
        tail = ptr;
    }
/*-Метод - для произвольного доступа-*/
    Node* getAt(int index) {
        Node* ptr = head;
        int n = 0;

        while (n != index) {
            if (ptr == NULL)
                return ptr;
            ptr = ptr->next;
            n++;
        }
        return ptr;
    }
/*-Оператор который возвращает элемент по определеннму индыксу-*/

Node* operator [] (int index) {
    return getAt(index);
}
/*-Метод- который вставляет новый элем. в произвольное место-*/

Node* insert(int index, double data) {
    Node* right = getAt(index);
    if (right == NULL)
        return push_back(data);
    Node* left = right->prev;
    if (left == NULL)
        return push_front(data);

    Node* ptr = new Node(data);

    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;

    return ptr;
}

/*-Метод удаления промежуточного элемента-*/

void erase(int index) {
    Node* ptr = getAt(index);
    if (ptr == NULL)
        return;

    if (ptr->prev == NULL) {
        pop_front();
        return;
    }
    if (ptr->next == NULL) {
        pop_back();
        return;
    }

    Node* left = ptr->prev;
    Node* right = ptr->next;
    left->next = right;
    right->prev = left;

    delete ptr;
}

};



int main()
{
    LinkedList Lst;

    Lst.push_back(1.0);
    Lst.push_back(3.0);
    Lst.push_back(4.0);
    Lst.push_back(5.0);
    Lst.push_back(7.0);

    std::cout << Lst[3]->data << std::endl;
    std::cout << Lst[2]->data << std::endl;
    std::cout << Lst[4]->data << std::endl;

    Lst.insert(2, -5.0);
    Lst.erase(3);
    Lst.erase(30);

    for (Node* ptr = Lst.head; ptr != NULL; ptr = ptr->next)
        std::cout << ptr->data << " ";
    std::cout << std::endl;

    for (Node* ptr = Lst.tail; ptr != NULL; ptr = ptr->prev)
        std::cout << ptr->data << " ";
    std::cout << std::endl;

    

    return 0;
}

