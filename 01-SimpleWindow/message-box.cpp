/*Win32-beginners
File: message-box.cpp
Date: 9th March 2025
Author: SodaTheCoder

Note: In this file-based tutorial you wil learn how to create message box*/

//Include windows header
#include <windows.h>

/*Win32 doesn't use standard c++ main(), but instead it uses WinMain.
As you can see, it has 4 instead of 2 arguments:
HINSTANCE hInst: handle to current instance of application
HINSTANCE hPreviousInst: handle to previous instance of application, always NULL
LPSTR lpCmdLine: command line for application, excluding application name(similar to argv)
int nCmdShow: Controls how the window is to be shown.
WINAPI means __stdcall*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreviousInst, LPSTR lpCmdLine, int nCmdShow)
{
    /*Create a simple message box. MessageBoxA() uses ANSI charset, while MessageBoxW() uses UNICODE.
    First argument is handle to parent window. Because we don't have window here, we set this argument to NULL.
    In modern c++ coding, you can set this argument to nullptr, which is even better that setting it to NULL.
    Second argument is text in message box. To create a new line, we don't use standard \n, but instead use \r\n.
    Last argument are styles. If set to NULL, message box will appear as MB_OK.
    We can change buttons and icon in message box. operator | is binary AND.*/
    MessageBoxA(NULL, "Hello World!", "Message box", MB_OK | MB_ICONINFORMATION);
    return 0;
}