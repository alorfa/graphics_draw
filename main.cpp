#define _CRT_SECURE_NO_WARNINGS
#include <SFML\Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "stringi.hpp"

using std::cout;
using std::cin;
using std::endl;

#define LINIES 17

#define VARIABLE (mat.type[mat.last] == 'X')
#define NUMBER (mat.type[mat.last] == 'x')

#define VIEW for (int i = 0; i < LINIES; i++)			\
{														\
	window.draw(xlines[i]);								\
	window.draw(ylines[i]);								\
}														\
window.draw(linex);										\
window.draw(liney);										\
for (int i = 0; i < 9000; i++)							\
	window.draw(points[i])

#define LINIES_EBATb for (int i = 0; i < LINIES; i++)	\
{														\
	xlines[i].setPosition(0.f, (i + 1) * 50.f);			\
	ylines[i].setPosition((i + 1) * 50.f, 0.f);			\
}														\
linex.setPosition(0.f, 450.f);							\
liney.setPosition(450.f, 0.f)

class Dibil
{
private:
	int size = 16;

	void increase()
	{
		size += 16;								//увеличиваю size

		char* type2 = new char[size];			//создаю новые массивы
		double* value2 = new double[size];

		for (int i = 0; i < length; i++)		//копирую старые данные в новые массивы
		{
			type2[i] = type[i];
			value2[i] = value[i];
		}
		delete[] type;							//удаляю старые массивы
		delete[] value;

		type = type2;							//меняю указатели
		value = value2;
	}
	void setSize(int input)
	{
		size = input;

		char* type2 = new char[size];
		double* value2 = new double[size];

		delete[] type;
		delete[] value;

		type = type2;
		value = value2;
	}
	void delet(int i, int i2)
	{
		for (; i < length - i2; i++)
		{
			type[i] = type[i + i2];
			value[i] = value[i + i2];
		}
		length -= i2;
	}
public:
	char* type = new char[16];
	double* value = new double[16];

	int length = 0;
	int last = -1;

	Dibil()
	{}

	Dibil(Dibil& copy)
	{
		setSize(copy.size);

		length = copy.length;
		last = copy.last;

		for (int i = 0; i < length; i++)
		{
			type[i] = copy.type[i];
			value[i] = copy.value[i];
		}
	}
	~Dibil()
	{
		delete[] type;
		delete[] value;
	}

	void add(char typ, double valu = 0.0)
	{
		last = length;
		length++;

		if (length >= size)
			increase();

		type[last] = typ;
		value[last] = valu;
	}
	void show()
	{
		if (length == 1)
		{
			puts("Ошибка");
			//return;
		}
		for (int i = 1; i < length; i++)
			cout << value[i] << '\t';
		cout << endl;
		for (int i = 1; i < length; i++)
			cout << type[i] << '\t';
		cout << endl;
	}

	void replace(int& i, float x)
	{
		switch (type[i])
		{
		case '+':
			value[i - 1] += value[i + 1];
			delet(i, 2);
			break;
		case '*':
			value[i - 1] *= value[i + 1];
			delet(i, 2);
			break;
		case '^':
			value[i - 1] = pow(value[i - 1], value[i + 1]);
			delet(i, 2);
			break;
		case '/':
			if (value[i + 1] == 0)
			{
				i = -1;
				break;
			}
			value[i - 1] /= value[i + 1];
			delet(i, 2);
			break;
		case '~':
			value[i + 1] *= -1;
			delet(i, 1);
			break;
		case 's':
			value[i + 1] = sin(value[i + 1]);
			delet(i, 1);
			break;
		case 'c':
			value[i + 1] = cos(value[i + 1]);
			delet(i, 1);
			break;
		case 'q':
			value[i + 1] = sqrt(value[i + 1]);
			delet(i, 1);
			break;
		case 'a':
			value[i + 1] = abs(value[i + 1]);
			delet(i, 1);
			break;
		}
		i--;
	}
};

double to_number_10(const char* input, int& i)
{
	int sLen = strlen(input);

	double output = 0;		//хранит конечное значение
	bool point = false;		//проверяет наличие точки
	int count = 10;			//на сколько нужно делить новое значение во fract

	for (; i < sLen; i++)
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			if (!point)
			{
				output *= 10;
				output += input[i] - 48.0;
			}
			else
			{
				double t = input[i] - 48.0;
				t /= count;
				count *= 10;
				output += t;
			}
		}
		else if (input[i] == '.')
		{
			if (!point)
			{
				point = true;
			}
			else
			{
				i = -1;
				return 0;
			}

		}
		else
		{
			i--;
			break;
		}
	}
	return output;
}

bool lexer(stringi& input, Dibil& mat)
{
	bool error = false;		//допущена ли ошибка
	bool minus = false;		//найден ли минус

	int sk = 0;

	mat.add(0);

	const double ADD = 5.0;

	for (int i = 0; i < input.len(); i++)
	{
		if (error) break;

		if (input[i] == ' ' || input[i] == '\t')
			continue;

		switch (input[i])
		{
		case '+':
			if (NUMBER || VARIABLE)					//если до плюса стояло число,
				mat.add('+', 1.0 + sk * ADD);		//добавляю число в токены
			break;
		case '-':
			minus = !minus;							//меняю знак на противоположный
			if (NUMBER || VARIABLE)					//если до минуса число, то ставлю плюс(сложение отрицательного == вычитание)
				mat.add('+', 1.0 + sk * ADD);
			break;
		case '*':
			if (NUMBER || VARIABLE)
			{
				mat.add('*', 2.0 + sk * ADD);		//если до '*' число, добавляю умноежение в токены
				break;
			}
			error = true;							//если что-то другое, то ошибка
			break;
		case '/':
			if (NUMBER || VARIABLE)
			{
				mat.add('/', 2.0 + sk * ADD);		//если до '/' число, добавляю деление в токены
				break;
			}
			error = true;							//если что-то другое, то ошибка
			break;
		case '^':
			if (NUMBER || VARIABLE)
			{
				mat.add('^', 3.0 + sk * ADD);		//если до '^' число, добавляю умноежение в токены
				break;
			}
			error = true;							//если что-то другое, то ошибка
			break;
		case ')':
			if (NUMBER || VARIABLE)					//если до закрытой скобочки число, то всё прекрасно
			{
				sk--;

				if (sk < 0)							//если закрытых скобок больше открытых, то ошибка
					error = true;

				break;
			}
			error = true;
			break;
		case '(':
			if (NUMBER || VARIABLE)					//если до открытой скобочки число, то происходит умножение
			{
				mat.add('*', 2.0 + sk * ADD);
			}
			if (minus)								//если до скобки был минус, то ставится унарный минус, работающий на всё выражение
			{
				mat.add('~', 4.0 + sk * ADD);
				minus = false;
			}
			sk++;
			break;
		case 'x':
			if (NUMBER || VARIABLE)					//если до переменной число или другая переменная, то происходит умножение
			{
				mat.add('*', 2.0 + sk * ADD);
			}
			mat.add('X');
			break;
		case 's':
			if (NUMBER || VARIABLE) error = true;	//до синуса не должна быть переменная
			if (input[i + 1] == 'i' && input[i + 2] == 'n')
			{
				i += 2;								//если замечено слово sin, то добавляю его
				mat.add('s', 5.0 + sk * ADD);
			}
			else if (input[i + 1] == 'q' && input[i + 2] == 'r' && input[i + 3] == 't')
			{
				//если замечено sqrt
				i += 3;
				mat.add('q', 5.0 + sk * ADD);
			}
			else
			{
				error = true;
			}
			break;
		case 'c':
			if (NUMBER || VARIABLE) error = true;	//до косинуса не должна быть переменная
			if (input[i + 1] == 'o' && input[i + 2] == 's')
			{
				i += 2;
				mat.add('c', 5.0 + sk * ADD);
			}
			else
			{
				error = true;
			}
			break;
		case 'a':
			if (NUMBER || VARIABLE) error = true;	//до модуля не должна быть переменная
			if (input[i + 1] == 'b' && input[i + 2] == 's')
			{
				i += 2;
				mat.add('a', 5.0 + sk * ADD);
			}
			break;
		default:
			if (input[i] >= '0' && input[i] <= '9')
			{
				double result;

				result = to_number_10(input, i);

				if (i == -1 || NUMBER || VARIABLE)
				{
					error = true;
					break;
				}

				if (minus)
				{
					result *= -1;
					minus = false;
				}

				mat.add('x', result);
			}
			else
			{
				error = true;
				break;
			}
		}
	}
	if (mat.type[mat.last] != 'x' && mat.type[mat.last] != 'X')
	{
		error = true;
	}
	if (error)
	{
		return true;
	}
	return false;
}

float lexerResult(Dibil& copy, float x)
{
	Dibil mat(copy);
	int priority = 0;	//приоритет

	for (int i = 1; i < mat.length; i++)
	{
		if (mat.type[i] != 'x' && mat.type[i] != 'X')
		{
			if (mat.value[i] > priority)	//нахожу максимальный приоритет
				priority = mat.value[i];
		}
		if (mat.type[i] == 'X')				//заменяю все иксы на текущее значение
		{
			mat.value[i] = x;
		}
	}

	while (priority > 0)
	{
		for (int i = 1; i < mat.length; i++)	//ищу результат
		{
			if (mat.type[i] != 'x' && mat.type[i] != 'X')
			{
				if (mat.value[i] == priority)
					mat.replace(i, x);

				if (i == -1)
					return 0.f;
			}
		}
		priority--;
	}
	return (float)mat.value[1];
}

void Hide()
{
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Hide, 0);
}

int main(int argc, char** argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FILE* fptr;
	stringi input;
	if (argc == 2)
	{
		if (fptr = fopen(argv[1], "r"))
		{
			Hide();

			int ch;
			while ((ch = fgetc(fptr)) != EOF)
			{
				input += ch;
			}
		}
		else
		{
			cout << "Не удалось открыть файл" << endl;
			system("pause");
			return 0;
		}
	}

#ifdef LINIES
	sf::RectangleShape linex(sf::Vector2f(900.f, 2.f));		//две основные x и y линии
	sf::RectangleShape liney(sf::Vector2f(900.f, 2.f));

	sf::Color pointColor(190, 190, 190);
	sf::Color mainColor(180, 180, 180);
	sf::Color sideColor(66, 66, 66);

	linex.setPosition(0.f, 450.f);							//настройка главных линий
	linex.setFillColor(mainColor);
	liney.setPosition(450.f, 0.f);
	liney.setFillColor(mainColor);
	liney.setRotation(90.f);

	sf::RectangleShape xlines[LINIES];						//побочные линии
	sf::RectangleShape ylines[LINIES];

	for (int i = 0; i < LINIES; i++)						//цвета побочных линий
	{
		xlines[i].setFillColor(sideColor);
		ylines[i].setFillColor(sideColor);
		ylines[i].setRotation(90.f);						//поворот вертикальных линий

		xlines[i].setSize(sf::Vector2f(900.f, 2.f));		//устанавливаю длину
		ylines[i].setSize(sf::Vector2f(900.f, 2.f));
	}

	for (int i = 0; i < LINIES; i++)						//расположение линий
	{
		xlines[i].setPosition(0.f, (i + 1) * 50.f);
		ylines[i].setPosition((i + 1) * 50.f, 0.f);
	}
#endif //LINIES

	sf::RectangleShape* points = new sf::RectangleShape[9000];//точки

	for (int i = 0; i < 9000; i++)
	{
		points[i].setSize(sf::Vector2f(2.f, 2.f));
		points[i].setFillColor(pointColor);
	}

	if (argc == 1)
		cout << "Введите уравнение:" << endl;

	sf::View view;

	while (1)
	{
		view.setCenter(450.f, 450.f);
		view.setSize(900.f, 900.f);

		LINIES_EBATb;

		if (argc == 1)
		{
			cout << "y = ";

			input.clear();
			input.record();			//получаю строку
		}

		if (input.len() == 0)		//если она пустая - выхожу
			break;

		input.lower();				//делаю её полностью маленькой, делая лексер не регистрочувствительным

		const char* str = input;

		Dibil mat;
		if (lexer(input, mat))		//создаю объект лекса и проверяю на наличие ошибки
		{
			puts("Ошибка");
			continue;
		}
		//mat.show();

		///////////////расставляю точки///////////////
		float y;
		float x = -9.f;
		for (int i = 0; i < 9000; i++)
		{
			y = lexerResult(mat, x);

			y *= -100;

			points[i].setPosition((x * 100 + 900.f) / 2, y / 2 + 450.f);

			//printf("point %d: %f %f\n", i + 1, points[i].getPosition().x, points[i].getPosition().y);

			x += 0.002f;
		}
		///////////////уже не расставляю точки///////////////

		sf::RenderWindow window(sf::VideoMode(900, 900), "TEST", sf::Style::Close);

		DISPLAY_DEVICE device;
		ZeroMemory(&device, sizeof(device));
		device.cb = sizeof(device);
		EnumDisplayDevices(NULL, (DWORD)0, &device, 0);
		DEVMODE devmode;
		ZeroMemory(&devmode, sizeof(DEVMODE));
		devmode.dmSize = sizeof(DEVMODE);
		EnumDisplaySettings((LPSTR)device.DeviceName, ENUM_REGISTRY_SETTINGS, &devmode);
		window.setFramerateLimit(devmode.dmDisplayFrequency);

		window.setView(view);

		for (int i = 0; i < LINIES; i++)	//фон
		{
			window.draw(xlines[i]);
			window.draw(ylines[i]);
		}
		window.draw(linex);
		window.draw(liney);

		for (int i = 0; i < 9000; i++)		//точки
			window.draw(points[i]);

		window.display();

		bool movex = true, movey = true;

		while (window.isOpen())
		{
			sf::Event event;
			if (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
					case sf::Keyboard::Enter:
						window.close();
						break;
					case sf::Keyboard::S:
						if (event.key.control)
						{
							FILE* fptr;
							if (fptr = fopen("graphic.dibil", "w"))
							{
								fputs(input, fptr);
							}
							fclose(fptr);
						}
						break;
					case sf::Keyboard::Up:

						liney.move(0.f, -50.f);

						for (int i = 0; i < LINIES; i++)
						{
							ylines[i].move(0.f, -50.f);
							xlines[i].move(0.f, -50.f);
						}

						view.move(0.f, -50.f);

						window.setView(view);
						window.clear();
						VIEW;
						window.display();
						break;
					case sf::Keyboard::Down:

						liney.move(0.f, 50.f);

						for (int i = 0; i < LINIES; i++)
						{
							ylines[i].move(0.f, 50.f);
							xlines[i].move(0.f, 50.f);
						}

						view.move(0.f, 50.f);

						window.setView(view);
						window.clear();
						VIEW;
						window.display();
						break;
					case sf::Keyboard::Left:

						linex.move(-50.f, 0.f);

						for (int i = 0; i < LINIES; i++)
						{
							xlines[i].move(-50.f, 0.f);
							ylines[i].move(-50.f, 0.f);
						}

						view.move(-50.f, 0.f);

						window.setView(view);
						window.clear();
						VIEW;
						window.display();
						break;
					case sf::Keyboard::Right:

						linex.move(50.f, 0.f);

						for (int i = 0; i < LINIES; i++)
						{
							xlines[i].move(50.f, 0.f);
							ylines[i].move(50.f, 0.f);
						}

						view.move(50.f, 0.f);

						window.setView(view);
						window.clear();
						VIEW;
						window.display();
						break;
					}
				}
			}
		}
		if (argc == 2)
			break;

		//input.clear();
	}
	delete[] points;

	return 0;
}