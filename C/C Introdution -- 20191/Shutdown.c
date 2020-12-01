#include <windows.h>
#include <stdio.h>

BOOL Shutdown(unsigned int s)
{
   HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

   // Get a token for this process.
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return FALSE;

   // Get the LUID for the shutdown privilege.
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

   tkp.PrivilegeCount = 1;  // one privilege to set
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

   // Get the shutdown privilege for this process.
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

   if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

   if (!ExitWindowsEx(s, 0))
      return FALSE;

   return TRUE;
}

int main()
{
   int s;
   printf("1. Log off\n2. Restart\n3. Shutdown\n>>> "); scanf("%d", &s);
   switch (s)
   {
   case 1:
       ExitWindowsEx(EWX_LOGOFF, 0);
       break;
   case 2:
      Shutdown(EWX_REBOOT);
      break;
   case 3:
      Shutdown(EWX_SHUTDOWN);
      break;
   default:
       break;
   }
   return 0;
}