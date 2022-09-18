#include <iostream>

struct Element
{
	int data;
	Element* next = NULL;
	Element* prev = NULL;
};

struct Ring
{
	Element* current = NULL;
};

void pushNext(Ring& r, int d)
{
	Element* e = (Element*)malloc(sizeof(Element));
	e->data = d;

	if (r.current == NULL)
	{
		r.current = e;
		e->next = e;
		e->prev = e;
		return;
	}

	e->next = r.current->next;
	e->prev = r.current;
	r.current->next->prev = e;
	r.current->next = e;
}

void pushPrev(Ring& r, int d)
{
	Element* e = (Element*)malloc(sizeof(Element));
	e->data = d;

	if (r.current == NULL)
	{
		r.current = e;
		e->next = e;
		e->prev = e;
		return;
	}

	e->next = r.current;
	e->prev = r.current->prev;
	r.current->prev->next = e;
	r.current->prev = e;
}

int pull(Ring& r)
{
	if (r.current == NULL)	
		return 0;

	int d = r.current->data;
	Element* e = r.current;

	if (r.current->next == r.current)
		r.current = NULL;
	else
	{
		r.current->prev->next = r.current->next;
		r.current->next->prev = r.current->prev;
		r.current = r.current->next;
	}
	free(e);

	return d;
}

void goNext(Ring& r)
{
	if (r.current == NULL)	return;
	r.current = r.current->next;
}

void goPrev(Ring& r)
{
	if (r.current == NULL)	return;
	r.current = r.current->prev;
}

void print(Ring& r)
{
	if (r.current == NULL)
	{
		printf("��������� ������ ������\n");
		return;
	}

	printf("%d ", r.current->data);
	for (Element* cur = r.current->next; cur != r.current; cur = cur->next)
		printf("<-> %d ", cur->data);
	printf("\n");
}

void findEl(Ring& r, int d)
{
	if (r.current == NULL)
		return;

	if (r.current->data == d)
	{
		printf("���� ������� %d � ��������� ������\n", d);
		return;
	}
	for (Element* cur = r.current->next; cur != r.current; cur = cur->next)
	{
		if (cur->data == d)
		{
			printf("���� ������� %d � ��������� ������\n", d);
			return;
		}
	}
	printf("��� �������� %d � ��������� ������\n", d);
}

void loopRing()
{
	Ring r;
	int choose;
	
	while (true)
	{
		printf("1 - �������� ������� �����; 2 - �������� ������� �����; 3 - ������� ������� �������; 4 - ����� �������; 5 - ������� �����; 6 - ������� �����; 7 - �����\n�����: ");
		do {
			scanf_s("%d", &choose);
		} while (choose < 1 || choose > 7);
		printf("\n");

		int tmp;
		switch (choose)
		{
		case 1:
			printf("������� ����������� ������ ��������: ");
			scanf_s("%d", &tmp);
			pushNext(r, tmp);
			break;
		case 2:
			printf("������� ����������� ������ ��������: ");
			scanf_s("%d", &tmp);
			pushPrev(r, tmp);
			break;
		case 3:
			tmp = pull(r);
			printf("�������� �������: %d\n", tmp);
			break;
		case 4:
			printf("������� ����������� ��������: ");
			scanf_s("%d", &tmp);
			findEl(r, tmp);
			break;
		case 5:
			goNext(r);
			printf("���������� �����\n");
			break;
		case 6:
			goPrev(r);
			printf("���������� �����\n");
			break;
		case 7:
			return;
		}

		print(r);
		printf("\n");
	}
}

int main()
{
	system("chcp 1251"); system("cls");

	loopRing();

	return 0;
}