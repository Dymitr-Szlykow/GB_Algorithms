#ifndef LESSON2_H
#define LESSON2_H

// ������� � ������� �2.
// 1. ����������� ������� �������� �� ���������� ������� � ��������, ��������� ��������.
// 2. ����������� ������� ���������� ����� a � ������� b :
//    a.��� ��������;
//    b.����������;
//    c.* ����������, ��������� �������� �������� �������.
// 3. * *����������� ����������� ����������� ����� �����, ���������� �� ������.
//    � ����������� ��� �������, ������ ������� �������� �����: ������� 1, ������ �� 2.
//    ������ ������� ����������� ����� �� ������ �� 1, ������ ����������� ��� ����� � 2 ����.
//    ������� ���������� ��������, ������� ����� 3 ����������� � ����� 20 ?

void Task_2_1(void);
int AsBinary_HeadOn_loop(int number, unsigned int maxlength, char* out); // = O(2 * log number) = O(log number), ��. ����
int AsBinary_recursive(int* number, unsigned int* maxlength, char* out); // = O(log number)

void Task_2_2(void);
int Multiply_loop(int first, int second); // = O(n), n = first < second ? first : second  ;  ��������� �� ������� ������� �� �������� �� ����������, ��. ����, ������ 142
double Power_loop(double number, unsigned int power); // = O(power), ��. ����
	// O(Power_loop(_,power))  ��������� ������������  O(log power) + O(power)
	// � ���������������� power ����������� �������������� ���� ������, ����� ���� ����������� �������
	// ������ ������ ��� ������� ����� - ������� ������, ����� ������ ���� �������� 0-1 ���  =>  O(Power_loop(_,power)) ~ O(log power)
	// ������ ������ ��� ������� ����� - power ��������, ����� ���� ������� ����� �� �����������  =>  O(Power_loop(_,power)) ~ O(power)
double Power_recursive(double number, unsigned int power); // = O(power)
	// ��� �� ��������, ��� Power_loop(), ����������� ����������

void Task_2_3(void); // not implemented

#endif