#include <ntddk.h>
void Unload(PDRIVER_OBJECT driverobj)
{
	DbgPrint("ж�سɹ�");
}

VOID Enumeration_Process()
{
	PEPROCESS aprocess = NULL;
	PEPROCESS bprocess = NULL;
	ULONGLONG processname = 0;
	ULONGLONG processid = 0;
	aprocess = PsGetCurrentProcess();//��ȡ��ǰ����eprocess
	if (aprocess == 0)
	{
		DbgPrint("PsGetCurrentProcess��ȡ���� ");
		return STATUS_SUCCESS;
	}
	bprocess = aprocess;
	while (aprocess != NULL)
	{
		//list=0x448 id=0x440 name=0x5a8
		processname = (ULONGLONG)aprocess + 0x5a8;//eprocess��ƫ�ƻ�ȡ����
		processid = *(ULONGLONG*)((ULONGLONG)aprocess + 0x440);//eprocess��ƫ�ƻ�ȡid
		DbgPrint("Processname=%s | Prcoessid=%ld \n", processname, processid);
		aprocess = ((ULONGLONG)(*(ULONGLONG*)((ULONGLONG)aprocess + 0x448)) - 0x448);//��ȡ�����ֵ��ȥƫ�Ƶõ��¸����̵�eprocess��ַ
		if (aprocess == bprocess || processid <= 0) //
		{
			return 0;
		}
	}
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driverobj, PUNICODE_STRING seg_path)
{
	Enumeration_Process();
	driverobj->DriverUnload = Unload;
	return STATUS_SUCCESS;
}