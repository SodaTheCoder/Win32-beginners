/*Win32-beginners
File: simple-window.cpp
Date: 9th March 2025
Author: SodaTheCoder

Note: In this file-based tutorial you will learn how to create simple window*/

#include <windows.h>

//This is name of window class
const char ClassName[] = "SimpleWindow";

/*Here we create window procedure and process messages.
Explanation of arguments:
HWND hwnd: handle to the window
UINT msg: this contains ID number of message received
WPARAM wParam: additional message argument 1, set by system
LPARAM lParam: additional message argument 2, set by system*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    /*Check which message was received.
    We don't need to check for every message, system has default
    handlings for those we don't process.*/
    switch(msg)
    {
    case WM_CLOSE:
        /*If close button was pressed, destroy window and break.
        Actions for maximize and minimize button are controlled by system.*/
        DestroyWindow(hwnd);
        break;
    default:
        //if no message is received, call default window procedure and return.
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreviousInst, LPSTR lpCmdLine, int nCmdShow)
{
    /*Here we create some variables that will be used for window creation. 
    HWND hwnd: handle to the window we're going to create.
    MSG msg: a variable that will be used for sending messages to window's procedure(it processes messages)
    WNDCLASSEXA wcex: it contains information about window class, such as icon, small icon, cursor, background brush, ...*/
    HWND hwnd;
    MSG msg;
    WNDCLASSEXA wcex;

    /*Here we configure window class.
    cbSize: size of structure, always just use sizeof operator
    style: styles for window, for example CS_VREDRAW or CS_HREDRAW for vertical/horizontal redrawing
    lpfnWndProc: name of window procedure function. Program will send messages to it
    cbClsExtra: number of extra bytes to allocate for window class. usually 0.
    cbWndExtra: number of extra bytes to allocate for window instance. usually 0.
    hInst: handle to application instance
    hIcon: icon in taskbar, can be predefined or custom
    hCursor: cursor inside window, can be predefined or custom
    hbrBackground: color of window's background, we select color using RGB system
    lpszMenuName: export menu from resource. You will learn about resources later
    lpszClassName: actual name of class that we'll use when creating window
    hIconSm: icon in top-left corner of the window, can be predefined or custom*/
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInst = hInst;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(240, 240, 240)));
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = ClassName;
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    /*Here we register class for subsequent use in CreateWindowEx() function, which will create the window.
    We also check for errors and display a message box if an error occurred.
    MB_ICONERROR is an icon with red circle and white cross in it.*/
    if(!RegisterClassExA(&wcex))
    {
        MessageBoxA(NULL, "Window registration failed!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    /*Here it comes, the process of actual creation of window. CreateWindowExA() and CreateWindowExW() functions,
    again, only have one major difference, first uses ANSI charset and second one uses UNICODE.
    There are a lot of arguments we need to configure when calling this function. 
    DWORD dxExStyle: extended window style.
    LPCSTR lpClassName: name of class(that we registered earlier).
    LPCSTR lpWindowName: text in titlebar.
    DWORD dwStyle: style of window. WS_OVERLAPPEDWINDOW is standard standalone window with close, maximize and minimize buttons all enabled.
    int X: X position of the window on screen. CW_USEDEFAULT is predefined macro and is default position.
    int Y: Y position of the window on screen. CW_USEDEFAULT is predefined macro and is default position.
    int nWidth: Width of window, in pixels.
    int nHeight: height of window, in pixels.
    HWND hwndParent: parent of window. Because we are creating parent window, we will set this argument to NULL.
    HMENU hMenu: Usually used to set ID of contols, here we'll set it to NULL.
    HINSTANCE hInstance: handle to current instance of application.
    LPVOID lpParam: Pointer to a value to be passed to the window through the CREATESTRUCT structure. Very rarely used.*/
    hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, 
                           ClassName,
                           "Simple window",
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           500,
                           500,
                           NULL,
                           NULL,
                           hInst, NULL);

    /*Here we check if window registration failed. If it fails, hwnd is set to NULL.
    This process, as well as window registration, should never fail under normal cicumstances.
    If window registration or creation fails, that almost certainly means arguments are incorrectly set.*/
    if(hwnd == NULL)
    {
        MessageBoxA(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    /*Here we show and update window so it is visible on screen.
    Instead of nCmdShow, we can also use predefined macros, such as SW_SHOW, SW_HIDE,...
    If we show/hide window, we must update it so the changes are visible on screen.*/
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /*Here we create main message loop of program.
    Task of message loop is to look for messages such as button clicks and 
    forward them to window procedure which processes it.*/
    while(GetMessage(hwnd, &msg, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}