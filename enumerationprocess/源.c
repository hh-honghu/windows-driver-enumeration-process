#include <ntddk.h>
void Unload(PDRIVER_OBJECT driverobj)
{
	DbgPrint("卸载成功");
}

VOID Enumeration_Process()
{
	PEPROCESS aprocess = NULL;
	PEPROCESS bprocess = NULL;
	ULONGLONG processname = 0;
	ULONGLONG processid = 0;
	aprocess = PsGetCurrentProcess();//获取当前进程eprocess
	if (aprocess == 0)
	{
		DbgPrint("PsGetCurrentProcess获取错误 ");
		return STATUS_SUCCESS;
	}
	bprocess = aprocess;
	while (aprocess != NULL)
	{
		//list=0x448 id=0x440 name=0x5a8
		processname = (ULONGLONG)aprocess + 0x5a8;//eprocess加偏移获取名称
		processid = *(ULONGLONG*)((ULONGLONG)aprocess + 0x440);//eprocess加偏移获取id
		DbgPrint("Processname=%s | Prcoessid=%ld \n", processname, processid);
		aprocess = ((ULONGLONG)(*(ULONGLONG*)((ULONGLONG)aprocess + 0x448)) - 0x448);//获取链表的值减去偏移得到下个进程的eprocess地址
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