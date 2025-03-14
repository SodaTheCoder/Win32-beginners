/*Win32-beginners
File: button.cpp
Date: 14th March 2025
Author: SodaTheCoder

Note: In this file-based tutorial you will learn how to create button in window
Note2: Code for creating parent window is same as in previous file.*/

#include <windows.h>
#define ID_BUTTTON 101

//create variables for parent class name and handle for button
const char ClassName[] = "SimpleWindow";
HWND button;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        /*WM_CREATE message is sent when window is created. In this message handling we usually
        initialize variables, add controls such as buttons, and like that so on...
        In this example, button will be created here.*/
    case WM_CREATE:
    {
        /*Here, button is created. As you can see, it is created similarly to window, but some things differ.
        We used function CreateWindowA() instead of CreateWindowExA(). The reason is we don't need to set
        extended window style here. Neither do we need to that in creation process on parent window, but it's a good practice.
        For controls, we generally use CreateWindowA() function. This function, for difference of CreateWindowExA(), has 1
        argument less, so first is different. So, first here is class name. When creating window, we set class name to whatever
        we wanted, we created our own class for our window. But it doesn't go like that for controls. Controls have pre-defined
        classes. If you want to create a button, you can use "BUTTON" as class name, as I did, or specify WC_BUTTONA or WC_BUTTONW
        as value of this argument. It comes down to your preference. Second argument is text in button. You can set this to
        whatever you want, I set it to "Click me!". Third argument are the styles. When we were creating the parent window, we set
        this argument to WS_OVERLAPPEDWINDOW, which is a normal window. But here, we aren't creating parent, but child window, that is control.
        Always remember: Controls are windows! When creating child window, we must always specify WS_CHILD as value of this argument, but WS_VISIBLE
        one is actually optional, but strongly preferred as if we don't use it, we have to call ShowWindow() manually. But we can't use
        this argument when creating parent window. Next 4 arguments are X and Y position and width and height. You can set them to whatever
        you desire, I made a standard-sized button. The next argument, however, is a handle to the parent window. As it is passed as argument
        when system calls window procedure, we can specify it. The next argument is new. This is ID of control. Why has it type HMENU, and what
        is HMENU? HMENU is handle to menu, as name says, and we'll talk about menus later. They are created differently. Basically, this argument can be
        used as passing handle to the menu or passing ID of control, which we are doing here. ID of control in a number that we will use when checking
        for commands, i.e. when we'll get notified when button is clicked. But we'll learn that in one of the next files. We can freely set last argument to NULL.*/
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