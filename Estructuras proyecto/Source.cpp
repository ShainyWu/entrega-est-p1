#include <Windows.h>
#include "Resource.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <Commctrl.h>
#include <CommDlg.h>




using namespace std;

struct usuarios {

    //------------usuarios--------------------

    usuarios* ant;
    char usuario[50];
    char contraseña[50];
    char nombre[50];

    usuarios* sig;


};

int ventana3 = 1;

usuarios* inicio, * aux, * fin, * userAcc = nullptr;

HWND hIS_Ventana;
HWND hREG_Ventana;



HINSTANCE auxH;


void nuevoUsuario(usuarios* nuevo);


LPARAM CALLBACK IS_CALLBACK(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LPARAM CALLBACK REG_CALLBACK(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, PSTR cmdLine, int shocmd)
{
    auxH = hInst;

    hIS_Ventana = CreateDialog(auxH, MAKEINTRESOURCE(IS_Ventana), NULL, IS_CALLBACK);

    ShowWindow(hIS_Ventana, SW_SHOW);

    MSG msg;

    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
    return 0;

}

LPARAM CALLBACK IS_CALLBACK(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    usuarios* registrar = new usuarios;

    switch (msg) {

    case WM_INITDIALOG: {



    }break;

    case WM_COMMAND: {


        switch (LOWORD(wParam)) {


        case IS_BT_InSe: {

            ventana3 = 1;

            if (inicio == nullptr) {

                MessageBox(0, " No se ha registrado ese usuario ", "AVISO", MB_OK);

            }
            else {

                char usuario[50];
                char passw[50];

                aux = inicio;

                GetDlgItemText(hwnd, IS_EC_Usuario, usuario, 50);
                GetDlgItemText(hwnd, IS_EC_Passw, passw, 50);

                while (aux != nullptr && strcmp(usuario, aux->usuario) != 0) {

                    aux = aux->sig;

                }

                if (aux == nullptr) {

                    MessageBox(0, " No se ha registrado ese usuario ", "AVISO", MB_OK);

                }
                else {

                    if (strcmp(passw, aux->contraseña) == 0) {

                        userAcc = aux;

                        ventana3 = 2;

                        MessageBox(0, " Se encontró este usuario ", "AVISO", MB_OK);

                        /*hIDV_Ventana = CreateDialog(auxH, MAKEINTRESOURCE(IDV_Ventana), NULL, IDV_CALLBACK);

                        ShowWindow(hIDV_Ventana, SW_SHOW);
                        DestroyWindow(hwnd);*/


                    }
                    else {

                        MessageBox(0, " contraseña incorrecta ", "AVISO", MB_OK);

                    }


                }



            }



        }break;


        case IS_BT_Salir: {

            int opc = MessageBox(0, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);

            switch (opc) {
            case IDYES:

                DestroyWindow(hwnd);
                PostQuitMessage(0);


            }break;


        }break;

        case IS_BT_Reg: {

            /* ShowWindow(hIS_Ventana, SW_HIDE);

             hREG_Ventana = CreateDialog(auxH, MAKEINTRESOURCE(REG_Ventana), NULL, REG_CALLBACK);

             ShowWindow(hREG_Ventana, SW_SHOW);
             DestroyWindow(hwnd);*/


        }break;



        }break;





    }break;

    case WM_CLOSE: {


    }break;

    case WM_DESTROY: {


    }break;




    }

    return FALSE;

}

//LPARAM CALLBACK REG_CALLBACK(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
//
//    switch (msg) {
//
//        case WM_INITDIALOG: {
//
//
//
//        }break;
//
//        case WM_COMMAND: {
//
//
//        }break;
//
//    }
//
//
//}

void nuevoUsuario(usuarios* nuevo) {

    if (inicio == nullptr) {
        inicio = new usuarios;
        aux = inicio;

        aux->sig = nullptr;
        aux->ant = nullptr;
        fin = aux;

        strcpy_s(aux->usuario, nuevo->usuario);
        strcpy_s(aux->contraseña, nuevo->contraseña);
        strcpy_s(aux->nombre, nuevo->nombre);



    }
    else {
        aux = inicio;

        while (aux->sig != nullptr)
        {
            aux = aux->sig;
        }

        aux->sig = new usuarios;

        aux->sig->sig = nullptr;
        aux->sig->ant = aux;

        aux = aux->sig;
        fin = aux;

        strcpy_s(aux->usuario, nuevo->usuario);
        strcpy_s(aux->contraseña, nuevo->contraseña);
        strcpy_s(aux->nombre, nuevo->nombre);

    }
}