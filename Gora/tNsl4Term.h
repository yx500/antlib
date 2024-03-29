#ifndef tNsl4TermH
#define tNsl4TermH

//#include "old_sys_types.h"
//#include "tGConst.h"

#pragma pack(push, 1)

// ����� ������ ������
// Vagon � �������� ���

struct tSlVagon
{
  uint32 _tick; //  ���� ���������

  uint32 Id; // ������������� ��������
  int16 NO;  // ����� ������ �� ���
  int16 IV;  // ����� ������ �� ���
  int16 SP;  // ���� ���� �� ���

  uint32 NumV; // ����� ������
  int16 MassG; // ����� �����
  int16 MassV; // �����
  int16 Ln;    // ����� � ��
  uint8 Osy;   // ���
               //  uint16  ULn;          //  �������� ����� ������

  uint8 Rod; // ��� ������
  uint8 aDb; // ��������
  uint8 aNg; // ���������
  int16 ktp; // ��� ����� ���� ������
  int16 OSO; // ���

  uint8 Ur; // ������� ��������
  uint16 Vnadv;
  uint8 STATE_LOCATION;
  uint8 STATE_N_IN_OTCEP;
  uint8 STATE_ZKR_PROGRESS;
  //  char    strUR[32];  // 2*4 + 21 + 1 = �������� ������� 4 ����� +x ����� ���������� +0 ������ ������
};

// Vagon �� ��������� ���
struct tVagonFromTerm
{
  uint32 _tick; //  ���� ���������

  uint32 Id; // ������������� ��������
  int16 NO;  // ����� ������ �� ���
  int16 IV;  // ����� ������ �� ���
  int16 SP;  // ���� ���� �� ���

  uint32 NumV; // ����� ������
  int16 MassG; // ����� �����
  int16 MassV; // �����
  int16 Ln;    // ����� � ��
  uint8 Osy;   // ���

  uint8 Rod; // ��� ������
  uint8 aDb; // ��������
  uint8 aNg; // ���������
  int16 ktp; // ��� ����� ���� ������
  int16 Vr;  // �������� ��������

  uint8 Ur; // ������� ��������
};

#pragma pack(pop)

#endif // tNsl4TermH
