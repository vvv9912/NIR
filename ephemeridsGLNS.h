#ifndef EPHEMERIDSGLNS_H
#define EPHEMERIDSGLNS_H

typedef struct
{
      double X;
      double Y;
      double Z;

} GlonassCoordinates;
GlonassCoordinates ephemeridsGLNS(double N4 ,//����� �������� 4� �����
                              double N,//N � ����������� ����� ����� ������ �������������� �������, ������� � ����������� ����
                              //�� ������� ��������� �������� ������ ������� ti � �������� �� ����� ���
                              double ti, //���������� ������ �� ������ ������� �����. (������� �� ����� �������)
                              double N_A, //����������� ����� ����� �� ����� ��� ������ �������������� ���������, ������������ ��� � ������� ������������� ����������;
                              //����� ������������ � ������ ������ �� ������ 2 4-5-6 �����.
                              double tlymbda_A,//2 ������-7 - ����� ����������� ������� ����, �� ������� ��� ����, �
                              double dT, //�������� � �������������� �������, �
                              double dI,
                              double dTT,
                              double Ee,// ��������������
                              double omegaA,//�������� ������� )
                              double Lam); // ������� ����, ���������, ��� �� ������ A

#endif

