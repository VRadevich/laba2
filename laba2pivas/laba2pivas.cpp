
#include <iostream>

class Stack
{
private: 
	int peek = -1;
	
	int* arr = nullptr;
public:
	int size = 0;
	Stack(int s) { size = s; arr = new int[size]; }
	~Stack() { delete[] arr; }
	void push(int val) // добавляет элемент в стек на вершину
	{
		if (peek == size-1) return;
		arr[++peek] = val;		
	}
	int pop() // выталкивает верхний элемент из стека
	{
		if (peek == -1) return NULL;
		return arr[peek--];
	}
	int top() { return *(arr + peek); }
	int series()
	{
		int series = 0;
		for (int i = 0; i < size - 1; i++)
			if (arr[i] < arr[i + 1])
				series++;
		return series;
	}
	void print_stack() // распечатывает стек в консоль
	{
		if (arr == nullptr) return;
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
			if ((i != 0) && (i % 15 == 0))
				std::cout << "\n";
		}
		std::cout << "\n\n";
	}
	bool is_empty() // проверка на пустоту стека
	{
		if (peek == -1) return true;
		else return false;
	}
};

class Queue
{
private:
	int peek = -1;
	int tail = -1;
	int* arr = nullptr;
public:
	int size;
	Queue(int s) { size = s; arr = new int[size];  }
	~Queue() { delete[] arr; }
	void push(int val)	 // стандартный метод вталкивания элемента
	{
		if (peek == size-1) return;
		arr[++peek] = val;
	}
	void set_arr() { arr = new int[size]; }
	void init() {  peek = tail = -1; }  // убрал тут удаление массива и переадресацию на нуллптр

	int pop()	 // стандартный метод выталкивания элемента
	{
		if (tail == peek) return NULL;
		return arr[++tail];
	}
	void print_stack() // распечатывает стек в консоль
	{
		if (arr == nullptr) return;
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
			if ((i != 0) && (i % 15 == 0))
				std::cout << "\n";
		}
		std::cout << "\n\n";
	}
	int top() { return *(arr+peek); } // взятие верхнего значения без его удаления из очереди
	int bot() { return *(arr+tail); } // взятие нижнего значения без его удаления из очереди
	bool is_empty() // пустая ли очередь
	{
		if (peek == tail) return true;
		else return false;
	}
};


void fill_stack(Stack& s, int ch)
{
	switch (ch)
	{
	case 1: // возрастающими числами
	{
		for (int i = 0; i < s.size; i ++)		
			s.push(i);	
		break;
	}
	case 2: // убывающими
	{
		for (int i = s.size; i >= 0; i--)
			s.push(i);
		break;
	}
	case 3: // случайными
	{
		for (int i = 0; i < s.size; i++)
			s.push(rand() % s.size);
	}
	}
}

void merge(Stack& a, Stack& b, Queue& c) 
{
	while ((!a.is_empty()) && (!b.is_empty()))
	{
		if (a.top() > b.top())
			c.push(a.pop());
		else
			c.push(b.pop());
	}
	while (!a.is_empty())
		c.push(a.pop());

	while (!b.is_empty())
		c.push(b.pop());
}

void split(Stack& s,static Stack& a,static Stack& b)
{
	int sz = s.size;
	for (int i = 0; i < sz / 2; i++)
	{
		a.push(s.pop());
		b.push(s.pop());
	}

}

void qts(Queue& q, Stack& s)
{
	while(!q.is_empty())	
		s.push(q.pop());	
}

void merge_sort(Stack& s) 
{
	Stack a(s.size);
	Stack b(s.size);
	int n = s.size;
	Queue c[] = { (n), (n) };
	split(s,a,b);
	int p = 1, q = 0, r = 0;
	while (p < n)
	{			
		c[0].init(); c[1].init(); 
		int i = 0, m = n; 
		while (m > 0)
		{
			if (m >= p) q = p; else q = m;
			m = m - q;
			if (m >= p) r = p; else r = m;
			m = m - r;
			merge(a, b, c[i]);
			i = 1 - i;					
		}
		qts(c[0], a);
		qts(c[1], b);
		p = 2 * p;
	}
	qts(c[0], s);
}

void console_dial()
{
	int ch = 0;
	int size = 0;
	std::cout << "Задайте размер стека: ";
	std::cin >> size;
	Stack main_stack(size);
	std::cout << "Выберите способ заполнения стека\n1)Возрастающими числами\n2)Убывающими\n3)Случайными\n";
	
	std::cin >> ch;
	fill_stack(main_stack, ch);
	main_stack.print_stack();
	merge_sort(main_stack);
	main_stack.print_stack();

}


/*void test1()
{
	Stack test_s(100);
	Queue test_q(100);
	fill_stack(test_s, 3);
	while (!test_s.is_empty())
		test_q.push(test_s.pop());
	test_q.print_stack();
	while (!test_q.is_empty())
		test_s.push(test_q.pop());
	test_s.print_stack();
}*/

int main()
{
	setlocale(LC_ALL, "Russian");
	while (1)
	{
	console_dial();
	}
	//test1();
}

