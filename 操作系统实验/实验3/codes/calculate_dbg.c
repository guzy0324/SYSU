#include <conio.h>
#include <stdio.h>
#include <windows.h>
#define NULL ((void *)0)
#define null 0
#define NDSPSZ 256
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN 0x50
#define DEFAULT_X 0
#define DEFUALT_Y 0
#define CMDSZ 8
#define PROGSZ 8
struct ahch
{
	char ch;
	unsigned char ah;
};
void _put(char ch)
{
	_putch(ch);
}
void _move(int x, int y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);
	binfo.dwCursorPosition.X = x;
	binfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
}
unsigned short _get()
{
	return getch();
}
void _cls()
{
	system("cls");
}
int header, cursor, cursor_x, cursor_y;
void int2str(int n, char *s)
{
	int top = 0;
	char stk[10];
	while (n != 0)
	{
		stk[top++] = n % 10 + '0';
		n /= 10;
	}
	while (top != 0)
	{
		s[n++] = stk[--top];
	}
	s[n] = 0;
}
void float2str(float fn, char *s)
{
	int i = 0;
	if (fn < 0)
	{
		fn = -fn;
		s[i++] = '-';
	}
	int top = 0;
	char stk[10];
	int n = (int)fn;
	while (n != 0)
	{
		stk[top++] = n % 10 + '0';
		n /= 10;
	}
	while (top != 0)
	{
		s[i++] = stk[--top];
	}
	float t = fn - (float)(int)fn;
	s[i++] = '.';
	int j = i + 4;
	while (i < j)
	{
		t *= 10;
		s[i++] = (int)t + '0';
		t = t - (int)t;
	}
	s[i] = 0;
}
void new_page()
{
	cursor_x = 0;
	cursor_y = 0;
	_move(cursor_x, cursor_y);
	_cls();
}
void print(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		_put(str[i]);
		cursor_x += 1;
		_move(cursor_x, cursor_y);
	}
}
struct node
{
	char ch;
	int next;
	int last;
};
struct node ndsp[NDSPSZ];
int new_node(char c, int cursor)
{
	int neo = ndsp[null].next;
	if (neo == null)
	{
		return null;
	}
	ndsp[null].next = ndsp[neo].next;
	ndsp[neo].ch = c;
	ndsp[neo].next = cursor;
	if (cursor != null)
	{
		ndsp[neo].last = ndsp[cursor].last;
		if (ndsp[neo].last != null)
		{
			ndsp[ndsp[neo].last].next = neo;
		}
		ndsp[cursor].last = neo;
	}
	else
	{
		ndsp[neo].last = null;
	}
	if (header == cursor)
	{
		header = neo;
	}
	return neo;
}
void delete_node(int nd)
{
	if (header == nd)
	{
		header = ndsp[nd].next;
	}
	if (ndsp[nd].next != null)
	{
		ndsp[ndsp[nd].next].last = ndsp[nd].last;
	}
	if (ndsp[nd].last != null)
	{
		ndsp[ndsp[nd].last].next = ndsp[nd].next;
	}
	ndsp[nd].next = ndsp[null].next;
	ndsp[null].next = nd;
}
void dump_node(char buf[])
{
	int i = 0;
	while (ndsp[header].ch != 0)
	{
		if (ndsp[header].ch >= '0' && ndsp[header].ch <= '9')
		{
			buf[i++] = ndsp[header].ch;
		}
		else
		{
			char *temp = "+-*/().";
			int j = 0;
			while (temp[j] != 0 && ndsp[header].ch != temp[j])
			{
				j++;
			};
			if (temp[j] != 0)
			{
				buf[i++] = ndsp[header].ch;
			}
		}
		delete_node(header);
	}
	buf[i] = 0;
}
void read()
{
	cursor = header;
	cursor_x = DEFAULT_X;
	cursor_y = DEFUALT_Y;
	_move(cursor_x, cursor_y);
	unsigned short temp_ax = _get();
	struct ahch ax = *(struct ahch *)&temp_ax;
	while (ax.ch != '\r')
	{
		if (ax.ch == 0 || ax.ch == -32)
		{
			if (ax.ah == LEFT)
			{
				if (ndsp[cursor].last != null)
				{
					cursor = ndsp[cursor].last;
					cursor_x -= 1;
					_move(cursor_x, cursor_y);
				}
				/*else
                {
                    put('\a');
                }*/
			}
			else if (ax.ah == RIGHT)
			{
				if (ndsp[cursor].next != null)
				{
					cursor = ndsp[cursor].next;
					cursor_x += 1;
					_move(cursor_x, cursor_y);
				}
				/*else
                {
                    put('\a');
                }*/
			}
			else if (ax.ah == UP)
			{
				cursor = header;
				cursor_x = DEFAULT_X;
				_move(cursor_x, cursor_y);
			}
			else if (ax.ah == DOWN)
			{
				for (; ndsp[cursor].ch != 0; cursor = ndsp[cursor].next)
				{
					cursor_x++;
				}
				_move(cursor_x, cursor_y);
			}
		}
		else if (ax.ch == '\b')
		{
			if (ndsp[cursor].last != null)
			{
				delete_node(ndsp[cursor].last);
				cursor_x--;
				int temp_x = cursor_x;
				_move(cursor_x, cursor_y);
				for (int temp = cursor; temp != null; temp = ndsp[temp].next)
				{
					_put(ndsp[temp].ch);
					temp_x++;
					_move(temp_x, cursor_y);
				}
				_move(cursor_x, cursor_y);
			}
			/*else
            {
                put('\a');
            }*/
		}
		else
		{
			int temp = new_node(ax.ch, cursor);
			if (temp != null)
			{
				int temp_x = cursor_x;
				for (; ndsp[temp].ch != 0; temp = ndsp[temp].next)
				{
					_put(ndsp[temp].ch);
					temp_x++;
					_move(temp_x, cursor_y);
				}
				cursor_x++;
				_move(cursor_x, cursor_y);
			}
			/*else
            {
                put('\a');
            }*/
		}
		temp_ax = _get();
		ax = *(struct ahch *)&temp_ax;
	}
}
int init(int *header_ptr)
{
	_cls();
	int i = 0;
	for (; i < NDSPSZ - 1; i++)
	{
		ndsp[i].next = i + 1;
	}
	ndsp[i].next = null;
	*header_ptr = new_node(0, null);
	return *header_ptr;
}
float nums[32];
char ops[32];
int nums_top = 0, ops_top = -1;
float calculate(char *s)
{
	int index = 0;
	nums[0] = 0;
	for (; s[index] != 0; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			float num = s[index] - '0';
			int exponent = 0;
			while (s[index + 1] >= '0' && s[index + 1] <= '9')
			{
				num = num * 10 + s[++index] - '0';
			}
			if (s[index + 1] == '.')
			{
				index++;
				while (s[index + 1] >= '0' && s[index + 1] <= '9')
				{
					num = num * 10 + s[++index] - '0';
					exponent++;
				}
			}
			while (exponent > 0)
			{
				num /= 10;
				exponent--;
			}
			nums[++nums_top] = num;
		}
		else if (ops_top == -1)
		{
			ops[++ops_top] = s[index];
		}
		else if (s[index] == '+' || s[index] == '-')
		{
			if (ops[ops_top] == '+')
			{
				nums_top--;
				nums[nums_top] += nums[nums_top + 1];
				ops[ops_top] = s[index];
			}
			else if (ops[ops_top] == '-')
			{
				nums_top--;
				nums[nums_top] -= nums[nums_top + 1];
				ops[ops_top] = s[index];
			}
			else if (ops[ops_top] == '*')
			{
				nums_top--;
				nums[nums_top] *= nums[nums_top + 1];
				ops[ops_top] = s[index];
			}
			else if (ops[ops_top] == '/')
			{
				nums_top--;
				nums[nums_top] /= nums[nums_top + 1];
				ops[ops_top] = s[index];
			}
			else
			{
				ops[++ops_top] = s[index];
			}
		}
		else if (s[index] == '*' || s[index] == '/')
		{
			if (ops[ops_top] == '*')
			{
				nums_top--;
				nums[nums_top] *= nums[nums_top + 1];
				ops[ops_top] = s[index];
			}
			else if (ops[ops_top] == '/')
			{
				nums_top--;
				nums[nums_top] /= nums[nums_top + 1];
				ops[ops_top] = s[index];
			}
			else
			{
				ops[++ops_top] = s[index];
			}
		}
		else if (s[index] == ')')
		{
			for (; ops[ops_top] != '('; ops_top--)
			{
				if (ops[ops_top] == '+')
				{
					nums_top--;
					nums[nums_top] += nums[nums_top + 1];
				}
				else if (ops[ops_top] == '-')
				{
					nums_top--;
					nums[nums_top] -= nums[nums_top + 1];
				}
				else if (ops[ops_top] == '*')
				{
					nums_top--;
					nums[nums_top] *= nums[nums_top + 1];
				}
				else if (ops[ops_top] == '/')
				{
					nums_top--;
					nums[nums_top] /= nums[nums_top + 1];
				}
			}
			ops_top--;
		}
		else
		{
			ops[++ops_top] = s[index];
			if (s[index + 1] == '-' || s[index + 1] == '+')
			{
				nums[++nums_top] = 0;
			}
		}
	}
	for (; ops_top != -1; ops_top--)
	{
		if (ops[ops_top] == '+')
		{
			nums_top--;
			nums[nums_top] += nums[nums_top + 1];
		}
		else if (ops[ops_top] == '-')
		{
			nums_top--;
			nums[nums_top] -= nums[nums_top + 1];
		}
		else if (ops[ops_top] == '*')
		{
			nums_top--;
			nums[nums_top] *= nums[nums_top + 1];
		}
		else if (ops[ops_top] == '/')
		{
			nums_top--;
			nums[nums_top] /= nums[nums_top + 1];
		}
	}
	return nums[nums_top];
}
int main()
{
	if (init(&header) == null)
	{
		print("Space used up!");
		//put('\a');
		_get();
		return -1;
	}
	char buf[NDSPSZ];
	new_page();
	read();
	dump_node(buf);
	float ans = calculate(buf);
	cursor_x = 0;
	cursor_y++;
	_move(cursor_x, cursor_y);
	if (ops_top != -1)
	{
		print("Invalid expression!");
		//put('\a');
	}
	else
	{
		float2str(ans, buf);
		print(buf);
	}
	_get();
	_cls();
}