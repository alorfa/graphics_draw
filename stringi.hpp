#ifndef STRINGI

#define SIZE 16

class stringi
{
private:
	int size = 1;				//количество блоков по SIZE
	char* arr = new char[SIZE];	//массив, хранящий текст
	int length = 0;				//длина строки

	void increase(int blocks = 1)//увеличивает количество блоков
	{
		if (!blocks) return;				//если нужно прибавить 0 блоков, просто выхожу

		size += blocks;						//длина массива увеличивается
		char* pointer = new char[size * SIZE];//создаю новый массив

		for (int i = 0; i < length; i++)	//копирую введённые данные
			pointer[i] = arr[i];

		delete[] arr;						//меняю указатели
		arr = pointer;
	}
	void decrease(int blocks = 1)//уменьшает количество блоков
	{
		if (!blocks) return;				//если нужно убрать 0 блоков, просто выхожу

		size -= blocks;						//длина массива уменьшается
		char* pointer = new char[size * SIZE];//создаю новый массив

		for (int i = 0; i < length; i++)	//копирую введённые данные
			pointer[i] = arr[i];

		delete[] arr;						//меняю указатели
		arr = pointer;
	}
	void add(char input)
	{
		length++;	//показываю, что строка увеличена

		if (length >= size * SIZE)//если массив переполнен, то добавляю дополнительные ячейки
			increase();

		arr[length - 1] = input;
	}
	void setSize(int length)	//устанавливает количество блоков под размер строки
	{
		if (length == this->length) return;	//если ничего не изменится, выхожу из функции

		int len = length / SIZE + 1;	//нахожу, сколько станет блоков

		increase(len - size);			//устанавливаю нужное количество блоков
	}
public:
	stringi(const char* input = "")
	{
		length = strlen(input);			//устанавливаю length длины введённого текста

		int will = length / SIZE;		//сколько блоков памяти надо добавить

		increase(will);					//добавляю это количество

		for (int i = 0; i < length; i++)//копирую символы строки
			arr[i] = input[i];
		arr[length] = 0;				//терминирую
	}
	stringi(const stringi& input)
	{
		int will = input.length / SIZE;	//сколько блоков памяти надо добавить

		increase(will);					//добавляю это количество
		length = input.length;			//устанавливаю length длины введённого текста

		for (int i = 0; i < length; i++)//копирую символы строки
			arr[i] = input.arr[i];
		arr[length] = 0;				//терминирую
	}
	~stringi()
	{
		delete[] arr;
		//
	}

	void record()				//запись с консоли
	{
		while (1)
		{
			char ch = getchar();	//сохраняю введённый символ
			if (ch == '\n')
			{
				arr[length] = 0;	//добавляю терминирующий ноль при виде конца строки
				break;
			}

			length++;				//показываю, что строка увеличена

			if (length >= size * SIZE)//если массив переполнен, то добавляю дополнительные ячейки
				increase();

			arr[length - 1] = ch;	//добавляю новый символ
		}
	}
	void append(char input)	//добавляет новый символ в конец строки
	{
		length++;	//показываю, что строка увеличена

		if (length >= size * SIZE)//если массив переполнен, то добавляю дополнительные ячейки
			increase();

		arr[length - 1] = input;

		arr[length] = 0;		//терминирую
	}
	void append(char input, int index)	//добавляет новый символ в указанное место
	{
		length++;						//показываю, что строка увеличена

		if (length >= size * SIZE)		//если массив переполнен, то добавляю дополнительные ячейки
			increase();

		for (int i = length - 1; i > index; i--)
			arr[i] = arr[i - 1];		//перемещаю все следующие элементы на единицу вправо

		arr[index] = input;				//помещаю в указанное место нужный символ

		arr[length] = 0;				//терминирую
	}
	void append(const char* input)	//добавляет строку в конец
	{
		int will = length + strlen(input);	//сколько символов окажется в строке

		setSize(will);						//устанавливаю нужное количество блоков

		int i = length;
		for (int j = 0; i < will; i++, j++)	//копирую вторую строку
			arr[i] = input[j];

		length = will;						//меняю реальную длину строки

		arr[length] = 0;					//терминирую
	}
	void append(const char* input, int index)//добавляет строку куда надо
	{
		int sLen = strlen(input);			//нахожу длину входной строки

		int will = length + sLen;			//сколько символов окажется в строке

		setSize(will);						//устанавливаю нужное количество блоков

		for (int i = length - 1; i >= index; i--)
			arr[i + sLen] = arr[i];			//переношу оставшиеся символы вправо

		int i = index;
		for (int j = 0; j < sLen; j++, i++)	//копирую входную строку
			arr[i] = input[j];

		length = will;						//меняю реальную длину строки

		arr[length] = 0;					//терминирую
	}
	void set_length(int len, char symbol = ' ')
	{
		if (length == len)		//если длина строки не изменится, 
		{
			return;				//просто выхожу из функции
		}
		if (length > len)		//если пользователь хочет укоротить строку
		{
			int will = len / SIZE;	//станет блоков по 16

			length = len;			//уменьшаю длину самой строки

			decrease(size - will);	//убираю лишние ячейки

			arr[len] = 0;			//терминирую
		}
		else
		{
			if (!symbol) return;	//если это терминирующий ноль, просто выхожу

			int will = len / 16 + 1;//станет блоков по 16

			increase(will - size);	//добавляю нужное количество блоков

			for (int i = length; i < len; i++)
				arr[i] = symbol;	//ставлю требуемые символы

			length = len;			//устанавливаю новую длину строки

			arr[length] = 0;		//затем терминирую
		}
	}
	void remove()				//убирает символ с конца строки
	{
		length--;	//показываю, что строка уменьшена

		if (length < size * SIZE - SIZE)//если блок оказался лишним, то убираю его
			decrease();

		arr[length] = 0;		//терминирую
	}
	void remove(int index)		//убирает символ с указанного индекса
	{
		length--;				//показываю, что строка уменьшена

		if (length < size * SIZE - SIZE)//если массив переполнен, то добавляю дополнительные ячейки
			decrease();

		for (int i = index; i < length; i++)
			arr[i] = arr[i + 1];//копирую символы на ячейку влево начианя с указанной

		arr[length] = 0;		//терминирую
	}
	void remove(int index, int count)//убирает указанное количество символов начиная с указанного индекса
	{
		if (count < 1) return;		//при странных данных выхожу из функции

		length -= count;			//станет символов

		setSize(length);			//убираю лишние блоки

		for (int i = index; i < length; i++)
			arr[i] = arr[i + count];//сдвигаю влево символы
		arr[length] = 0;			//терминирую
	}
	void replace(int index, int count, const char* input)
	{
		if (count < 1) return;			//при странных данных выхожу из функции
		if (index < 0) return;

		int sLen = strlen(input);		//сохраняю длину входной строки

		length += sLen - count;			//определяю, какой станет длина строки

		setSize(length);				//устанавливаю нужное количество блоков

		stringi copy(arr);				//сохраняю строку

		int j = 0;
		int i = index;
		for (; j < sLen; i++, j++)
			arr[i] = input[j];			//копирую входную строку

		j = index + count;
		for (; i < length; i++, j++)	//копирую остаток строки
			arr[i] = copy.arr[j];

		arr[length] = 0;				//терминирую
	}
	void reverse()
	{
		char* copy = new char[length];			//создаю массив длины строки

		for (int i = 0; i < length; i++)		//копирую данные
			copy[i] = arr[i];

		int j = length - 1;
		for (int i = 0; i < length; i++, j--)	//меняю данные во входной строке
			arr[i] = copy[j];

		delete[] copy;							//удаляю массив с копией строки
	}
	void clear()				//сбрасывает строку
	{
		size = 1;
		length = 0;

		char* pointer = new char[SIZE];

		delete[] arr;
		arr = pointer;
	}
	void show()
	{
		puts(arr);
		//
	}
	void lower()
	{
		for (int i = 0; i < length; i++)
		{
			if ((arr[i] >= 'A' && arr[i] <= 'Z') || (arr[i] >= 'А' && arr[i] <= 'Я'))
				arr[i] += 32;
			if (arr[i] == 'Ё') arr[i] = 'ё';
		}
	}
	void upper()
	{
		for (int i = 0; i < length; i++)
		{
			if ((arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'а' && arr[i] <= 'я'))
				arr[i] -= 32;
			if (arr[i] == 'ё') arr[i] = 'Ё';
		}
	}
	void capitalize()
	{
		bool point = true;

		for (int i = 0; i < length; i++)	//делаю строку маленькой
		{
			if ((arr[i] >= 'A' && arr[i] <= 'Z') || (arr[i] >= 'А' && arr[i] <= 'Я'))
				arr[i] += 32;
			if (arr[i] == 'Ё') arr[i] = 'ё';
		}

		for (int i = 0; i < length; i++)	//проверяю всю строку
		{
			if (point)						//если точка замечена, то
			{
				if ((arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'а' && arr[i] <= 'я') || arr[i] == 'ё')
				{
					if (arr[i] == 'ё')		//символ заменяю на большой
						arr[i] = 'Ё';
					else
						arr[i] -= 32;
					point = false;			//и делаю так, чтобы другие символы не менялись
				}
				else if (arr[i] != ' ' && arr[i] != ',' && arr[i] != '\t')
				{
					point = false;			//если это не разделительный символ, то просто убираю point
				}
			}
			if (arr[i] == '\n' || arr[i] == '.' || arr[i] == '!' || arr[i] == '?')
			{
				point = true;
			}
		}
	}
	void delete_spaces()	//TODO: не спроектировано
	{
		stringi output;						//входная строка

		for (int i = 0; i < length; i++)
		{
			if (arr[i] != ' ' && arr[i] != '\t')	//если замечен не разделитель
			{
				output.add(arr[i]);					//добавляю текущий символ
				if (arr[i + 1] == ' ' || arr[i + 1] == '\t')
					output.add(' ');				//если после него разделитель, добавляю пробел
			}
		}
		length = output.length;				//устанавливаю реальный размер строки
		setSize(length);					//и устанавливаю такой размер

		for (int i = 0; i < output.length; i++)
			arr[i] = output.arr[i];			//копирую символы
		arr[length] = 0;					//терминирую
	}

	char* c_str()
	{
		return arr;
		//
	}
	int len()
	{
		return length;
		//
	}
	char& operator[](int num)
	{
		return *(arr + num);
		//
	}
	operator char*()
	{
		return arr;
		//
	}
	stringi operator+(char ch)
	{
		stringi output(arr);

		output.append(ch);

		return output;
	}
	stringi& operator+=(const char* input)
	{
		append(input);

		return *this;
	}
	stringi& operator+=(char input)	//+=
	{
		append(input);

		return *this;
	}
	stringi operator*(int input)	//умножение строки
	{
		stringi output;				//создаю выходной объект

		if (!input) return output;	//если умножение на ноль
		if (!length) return output;	//или пустая строка
									//возвращаю пустой объект

		int will = length * abs(input);	//сколько символов будет в строке

		int len = will / SIZE;		//сколько добавится блоков

		output.increase(len);		//добавляю их

		output.length = will;		//устанавливаю длину выходной строки

		if (input > 0)
		{
			int j = 0;					//копирую строку нужное количество раз
			for (int i = 0; i < input; i++)
			{
				for (int i = 0; i < length; i++, j++)
				{
					output.arr[j] = arr[i];
				}
			}
		}
		else
		{
			int j = 0;					//копирую строку нужное количество раз
			for (int i = 0; i < -input; i++)
			{
				for (int i = length - 1; i >= 0; i--, j++)
				{
					output.arr[j] = arr[i];
				}
			}
		}
		output.arr[output.length] = 0;//терминирую

		return output;
	}
	stringi& operator*=(int input)	//умножение строки
	{
		if (!input)					//если умножение на ноль
		{
			clear();				//очищаю строку
			return *this;			//и возвращаю её
		}
		if (!length)				//если пустая строка
		{
			return *this;			//её же и возвращаю
		}

		int will = length * abs(input);	//сколько символов будет в строке

		int len = will / SIZE;		//сколько добавится блоков

		increase(len);				//добавляю их

		if (input > 0)
		{
			int j = length;			//копирую строку нужное количество раз
			for (int i = 0; i < input - 1; i++)
			{
				for (int i = 0; i < length; i++, j++)
				{
					arr[j] = arr[i];
				}
			}
		}
		else
		{
			stringi copy(arr);		//создаю копию текущей строки
			int j = 0;
			for (int i = 0; i < -input; i++)
			{
				for (int i = length - 1; i >= 0; i--, j++)
				{
					arr[j] = copy.arr[i];
				}
			}
		}
		length = will;				//указываю настоящую длину строки
		arr[length] = 0;			//терминирую

		return *this;
	}
	stringi& operator=(const char* input)
	{
		clear();							//очищаю строку

		length = strlen(input);				//устанавливаю length длины введённого текста

		int will = length / SIZE;			//сколько блоков памяти надо добавить

		increase(will);						//добавляю это количество

		for (int i = 0; i < length; i++)	//копирую символы строки
			arr[i] = input[i];
		arr[length] = 0;					//терминирую

		return *this;
	}
	stringi& operator=(const stringi& input)
	{
		clear();								//очищаю строку

		int will = input.length / SIZE;			//сколько блоков памяти надо добавить

		increase(will);							//добавляю это количество

		length = input.length;					//копирую размер строки

		for (int i = 0; i < input.length; i++)	//копирую символы строки
			arr[i] = input.arr[i];
		arr[length] = 0;						//терминирую

		return *this;
	}
	bool operator==(const char* input)
	{
		if (length != strlen(input))
			return false;

		for (int i = 0; i < length; i++)
		{
			if (arr[i] != input[i])
				return false;
		}
		return true;
	}
	bool operator!=(const char* input)
	{
		if (length != strlen(input))
			return true;

		for (int i = 0; i < length; i++)
		{
			if (arr[i] != input[i])
				return true;
		}
		return false;
	}
	bool operator>(const char* input)	//сравнивает длины строк
	{
		int test = strcmp(arr, input);

		if (test == 1)
			return true;
		return false;
	}
	bool operator<(const char* input)	//сравнивает длины строк
	{
		int test = strcmp(arr, input);

		if (test == -1)
			return true;
		return false;
	}
	bool operator>=(const char* input)	//сравнивает длины строк
	{
		int test = strcmp(arr, input);

		if (test == 1 || test == 0)
			return true;
		return false;
	}
	bool operator<=(const char* input)	//сравнивает длины строк
	{
		int test = strcmp(arr, input);

		if (test == -1 || test == 0)
			return true;
		return false;
	}
	friend stringi operator+(const char* str1, stringi str2);
	friend stringi operator+(stringi str1, const char* str2);
};
stringi operator+(const char* str1, stringi str2)
{
	int sLen = strlen(str1);			//запоминаю длину первой строки

	stringi output;						//создаю выходной объект

	int will = sLen + str2.length;		//запоминаю, какая у него будет длина

	int len = will / SIZE;				//определяю, сколько блоков в нём будет

	output.increase(len);				//добавляю их

	output.length = will;				//устанавливаю длину строки

	int i = 0;
	for (; i < sLen; i++)				//копирую первую строку
		output.arr[i] = str1[i];

	for (int j = 0; i < will; i++, j++)
		output.arr[i] = str2.arr[j];	//копирую вторую строку

	output.arr[output.length] = 0;		//терминирую

	return output;
}
stringi operator+(stringi str1, const char* str2)
{
	int sLen = strlen(str2);
	stringi output;						//создаю выходной объект

	int will = str1.length + sLen;		//запоминаю, какая у него будет длина

	int len = will / SIZE;				//определяю, сколько блоков в нём будет

	output.increase(len);				//добавляю их

	output.length = will;				//устанавливаю длину строки

	int i = 0;
	for (; i < str1.length; i++)		//копирую первую строку
		output.arr[i] = str1.arr[i];

	for (int j = 0; i < will; i++, j++)
		output.arr[i] = str2[j];		//копирую вторую строку

	output.arr[output.length] = 0;		//терминирую

	return output;
}

#define STRINGI
#endif //STRINGI