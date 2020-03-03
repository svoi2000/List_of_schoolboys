// List_of_schoolboys.cpp : Определяет точку входа для приложения.
// Программа работы со списком школьников

#include "stdafx.h"
#include "List_of_schoolboys.h"
#include "Schoolboy.h"
#include "Editboxes.h"
#include <vector>

#define ID_LISTBOX 1001
#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна



// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    schoolboyAdd(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LISTOFSCHOOLBOYS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
	

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LISTOFSCHOOLBOYS));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LISTOFSCHOOLBOYS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LISTOFSCHOOLBOYS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, (LPCWSTR)"Школьники", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hListBox;
	RECT rectPlace;
	TCHAR workTime[10];
	PAINTSTRUCT ps;
	HDC hdc;
	static std::vector<Schoolboy> listOfSchoolboys;
	static int listItem = NULL;
	static PTCHAR textBuf = (PTCHAR)GlobalAlloc(GPTR, 50000 * sizeof(TCHAR));     //Буфер
	Editboxes editBoxesInDialog = { "", "", 0, 0 };      //Структура, в которой хранятся поля ввода диалогового окна
	HANDLE hFile;
	static DWORD dwByte = 0;

	switch (message)
	{
	case WM_CREATE:
	    {
		    //Заполним наш список школьниками
		    listOfSchoolboys.push_back(Schoolboy("Вася", "Пупкин", 8, 2));
		    listOfSchoolboys.push_back(Schoolboy("Иван", "Петров", 9, 3));
		    listOfSchoolboys.push_back(Schoolboy("Арнольд", "Шварценеггер", 13, 4));
			std::sort(listOfSchoolboys.begin(), listOfSchoolboys.end());
		    MessageBox(NULL, "На экран выводится список школьников", "Начало работы", MB_ICONASTERISK | MB_OK);
			GetClientRect(hWnd, &rectPlace);
			hListBox = CreateWindow("Listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD,
				rectPlace.left + 50, rectPlace.top + 50, 200, 150, hWnd, (HMENU)ID_LISTBOX, hInst, NULL);
			for (size_t i = 0; i < listOfSchoolboys.size(); i++)
			{
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)(listOfSchoolboys[i].surname + " " +
					listOfSchoolboys[i].name).c_str());
			}
		}
	
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case IDM_SCHOOLBOY_ADD:                 //Добавление нового школьника в список
				DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_SCHOOLBOY_ADD), hWnd, schoolboyAdd, (LPARAM)&editBoxesInDialog);
				if (strcmp(editBoxesInDialog.edit_box1, "") != 0)     //Проверка - не была ли нажата в диалоговом окне
					                                                  //кнопка "Cancel"
				{
					listOfSchoolboys.push_back(Schoolboy((std::string)editBoxesInDialog.edit_box1,
						                                 (std::string)editBoxesInDialog.edit_box2,
						                                 atoi(editBoxesInDialog.edit_box3),
						                                 atoi(editBoxesInDialog.edit_box4)));
					std::sort(listOfSchoolboys.begin(), listOfSchoolboys.end());
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)strcat(strcat(editBoxesInDialog.edit_box2, " "), 
						editBoxesInDialog.edit_box1));
				}
				break;
			case IDM_SCHOOLBOY_DEL:                 //Удаление школьника из списка
				listItem = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				if (listItem != LB_ERR && listItem != -1)
				{
					listOfSchoolboys.erase(listOfSchoolboys.begin() + listItem);
					SendMessage(hListBox, LB_DELETESTRING, (WPARAM)listItem, 0);
				}
				break;
			case IDM_SAVE:
				hFile = CreateFile("proba.zzz", GENERIC_WRITE,
					FILE_SHARE_READ,
					NULL, CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					MessageBox(hWnd, "Ошибка при записи файла", "Возникла ошибка", MB_OK);
					return 0;
				}
				WriteFile(hFile,
						&listOfSchoolboys, sizeof
						(listOfSchoolboys),
						&dwByte, NULL);
				SetEndOfFile(hFile);
				CloseHandle(hFile);
				break;
			case IDM_OPEN:
				hFile = CreateFile
				("proba.zzz", GENERIC_READ, FILE_SHARE_READ,
					NULL, OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					MessageBox(hWnd, "Ошибка при открытии файла", "Возникла ошибка", MB_OK);
					return 0;
				}
				SetFilePointer
					(hFile, 0, 0, FILE_BEGIN);
				ReadFile(hFile, &listOfSchoolboys, sizeof(listOfSchoolboys), &dwByte, NULL);
				CloseHandle(hFile);
				SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
				for (size_t i = 0; i < listOfSchoolboys.size(); i++)
				{
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)(listOfSchoolboys[i].surname + " " +
						listOfSchoolboys[i].name).c_str());
				}
				break;
			case IDM_EXIT:
                DestroyWindow(hWnd);
				GlobalFree((HGLOBAL)textBuf);
                break;
			case ID_LISTBOX:
				if (HIWORD(wParam) == LBN_DBLCLK)   //На школьника даблкликнули левой кнопкой мыши, покажем его средний балл
				{
					listItem = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
					if (listItem != LB_ERR && listItem != -1)
					{
						SendMessage(hListBox, LB_GETTEXT, listItem, (LPARAM)textBuf);
						_itoa(listOfSchoolboys[listItem].ball, workTime, 10);
						std::string head = "Средний балл " + listOfSchoolboys[listItem].surname +
							" " + listOfSchoolboys[listItem].name;
						MessageBox(NULL, (LPCSTR)workTime, head.c_str(), MB_ICONASTERISK | MB_OK);
					}
				}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
			
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_DESTROY:
        PostQuitMessage(0);
		GlobalFree((HGLOBAL)textBuf);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Обработчик сообщений для окна "Добавление нового школьника".
INT_PTR CALLBACK schoolboyAdd(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Editboxes* pEditboxes;
	
	switch (message)
	{
	case WM_INITDIALOG:
		pEditboxes = (Editboxes*)lParam;
		strcpy(pEditboxes->edit_box1, "");
		strcpy(pEditboxes->edit_box2, "");
		strcpy(pEditboxes->edit_box3, "");
		strcpy(pEditboxes->edit_box4, "");
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
		    if (LOWORD(wParam) == IDOK)
		    {
				GetDlgItemText(hDlg, IDC_EDIT1, pEditboxes->edit_box1, 16);
				GetDlgItemText(hDlg, IDC_EDIT2, pEditboxes->edit_box2, 16);
				GetDlgItemText(hDlg, IDC_EDIT3, pEditboxes->edit_box3, 16);
				GetDlgItemText(hDlg, IDC_EDIT4, pEditboxes->edit_box4, 16);
				if (strcmp(pEditboxes->edit_box1, "") == 0 ||
					strcmp(pEditboxes->edit_box2, "") == 0 ||
					strcmp(pEditboxes->edit_box3, "") == 0 ||
					strcmp(pEditboxes->edit_box4, "") == 0)
				{
					MessageBox(NULL, "Пожалуйста, заполните все поля!", "Ошибка", MB_ICONASTERISK | MB_OK);
					strcpy(pEditboxes->edit_box1, "");       //По этому элементу основная программа поймет, что
					                                          //в диалоговом окне нажато "Cancel"
					break;
				}
				if (atoi(pEditboxes->edit_box4) < 1 ||
					atoi(pEditboxes->edit_box4) > 5 ||
					_tcslen (pEditboxes->edit_box4) > 1)
				{
					MessageBox(NULL, "Средний балл должен быть целым числом в диапазоне от 1 до 5", "Ошибка", MB_ICONASTERISK | MB_OK);
					strcpy(pEditboxes->edit_box1, "");       //По этому элементу основная программа поймет, что
															  //в диалоговом окне нажато "Cancel"
					break;
				}
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		} 
		break;
	}
	return (INT_PTR)FALSE;
}


