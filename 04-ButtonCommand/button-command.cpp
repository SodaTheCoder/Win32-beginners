/*Win32-beginners
File: button.cpp
Date: 14th March 2025
Author: SodaTheCoder

Note: In this file-based tutorial you will learn how to create button in window
Note2: Code for creating parent window and button is same as in previous file.*/

#include <windows.h>
#define ID_BUTTTON 101

//create variables for parent class name and handle for button
const char ClassName[] = "SimpleWindow";
HWND button;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
    {
        button = CreateWindowA("BUTTON",
                               "Click me!",
                               WS_CHILD | WS_VISIBLE,
                               10,
                               10, 
                               125,
                               50,
                               hwnd,
                               (HMENU)ID_BUTTON,
                               NULL);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    /*WM_COMMAND message is sent whenever we click on button, checkbox, radiobutton,...
    When handling it, we check from which control message was sent and then do all the
    necesarry processing. We'll make it so our button displays message box when clicked.*/
    case WM_COMMAND:
        /*ID of control that user has interacted with is sent as wParam. If you don't remember what that is,
        it is basically an additional argument system passes to us while calling window procedure. It can be 
        very useful at the times, as we get really important information from it.*/
        switch(wParam)
        {
            /*If ID if our button is passed as wParam, that means that our button was clicked by the user.
            Here, we will create message box that will pop-up after user has clicked the button.*/
            case ID_BUTTON:
                /*Now, when creating message box, we can fill first argument with handle of our parent window.
                This is not necesarry when creating message box, but if we leave this empty, message box will be
                created as a standalone window and it won't flash when we click on our main window. MB_ICONINFORMATION
                shows a standard information icon, so blue circle with 'i' in it.*/
                MessageBoxA(hwnd, "You clicked a button!", "Information", MB_OK | MB_ICONINFORMATION);
                break;
        }
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreviousInst, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASSEXA wcex;

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

    if(!RegisterClassExA(&wcex))
    {
        MessageBoxA(NULL, "Window registration failed!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

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

    if(hwnd == NULL)
    {
        MessageBoxA(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(hwnd, &msg, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}