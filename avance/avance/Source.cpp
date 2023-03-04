#include <windows.h>
#include "resource.h"
#include <fstream>
#include <CommDlg.h>
using namespace std;

struct Usuario
{
	char usuario_clave[15];
	char usuario_contrasenia[50];
	char apellidopa[10];
	char apellidoma[20];
	char Nombres[50];
	char usuarios_direccion[100];
	Usuario* Usuario_sig;
	Usuario* Usuario_ant;
};
Usuario* Usuario_aux, * Usuario_inicio, * NUsuario, * miInfo = nullptr;

struct Paciente
{
	char Paciente_nombre[50];
	char Paciente_AP[50];
	char Paciente_AM[50];
	char CURP[50];
	char RFC[50];
	char FechaNac[50];
	char calle[25];
	char ciudad[15];
	char estado[50];
	char estadocivil[50];
	char telefono[50];
	char docindet[300];
	char Sexo[50];
	char PerfilRies[50];
	char Paciente_direccion[100];
	Paciente* Paciente_sig;
	Paciente* Paciente_ant;

};
Paciente* Paciente_inicio, * NUPaciente,* Paciente_aux = nullptr;


struct Vacunas
{
	char tipovacuna[50];
	char marca[30];
	char clavevacuna[30];
	char Descripcion[30];
	char Precio[99];
	char Numdosis[99];
	char Vacunas_direccion[100];
	Vacunas* Vacunas_sig;
	Vacunas* Vacunas_ant;
};
Vacunas* Vacunas_inicio, * Vacunas_aux = nullptr;

char zFile[MAX_PATH];
char direccion[MAX_PATH] = { 0 };

HMENU hmenu;
HINSTANCE hintance;
HWND ghDlg = 0;

void Agregar_usuario(Usuario* nuevo_u);
void Modificar_Usuario(Usuario* newInfo, char nomUsuario[50]);
void Eliminar_Usuario(char nomUsuario[50]);
void Escribir_Binario_Usuario();
void Leer_Binario_Usuario();

void Agregar_Paciente(Paciente* nuevo);
void Escribir_Binario_Paciente();
void Leer_Binario_Paciente();
void Eliminar_Paciente(char nomPaciente[50]);



void Agregar_Vacunas(Vacunas* nuevo);
void Escribir_Binario_Vacunas();
void Leer_Binario_Vacunas();
void Eliminar_Vacunas(char nomVacunas[50]);



HINSTANCE hInstGlobal;
HWND hPrinGlob;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Registrar(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK VentanaInicio(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK repesonas(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK reVacunas(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK recarnet(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	Leer_Binario_Usuario();
	Leer_Binario_Paciente();
	
	hInstGlobal = hInst;
	HWND hVInicio = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProc);

	ShowWindow(hVInicio, cmdshow);

	MSG Mensaje;
	ZeroMemory(&Mensaje, sizeof(Mensaje));

	while (GetMessage(&Mensaje, 0, 0, 0)) {
		TranslateMessage(&Mensaje);
		DispatchMessage(&Mensaje);
	}
	Escribir_Binario_Usuario(); //escribe el binario al terminar el programa
	Escribir_Binario_Paciente();
	/*Escribir_Binario_Vacunas();
	Escribir_Binario_Consumo();*/
	return Mensaje.wParam;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

		/*case WM_INITDIALOG:
			break;*/

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1000: { //VALIDACION PARA EL INICIO DE SESION
			char usuarios_nombre[15];
			char usuarios_contrasenia[10];
			GetDlgItemText(hwnd, 1, usuarios_nombre, sizeof(usuarios_nombre));
			GetDlgItemText(hwnd, 2, usuarios_contrasenia, sizeof(usuarios_contrasenia));
			
			Usuario_aux = Usuario_inicio;
			if (Usuario_inicio == nullptr) {
				MessageBox(hwnd, "No hay usuario registrados.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else {
				while (Usuario_aux != nullptr && strcmp(Usuario_aux->usuario_clave, usuarios_nombre) != 0) {
					Usuario_aux = Usuario_aux->Usuario_sig;
				}
				if (Usuario_aux == nullptr) {
					MessageBox(hwnd, "Usuario no encontrado", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {
					if (strcmp(Usuario_aux->usuario_contrasenia, usuarios_contrasenia) == 0)
					{
								EndDialog(hwnd, 0);
								DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG3), hwnd, VentanaInicio);

						
					}
					else {
						MessageBox(hwnd, "Contraseña incorrecta", "AVISO", MB_OK | MB_ICONERROR);
					}
				}
			}
		}break;

		case 1002: { //DE INICIAR SESION A REGISTRARSE
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, Registrar);

		}
				 break;


		case 1001: { //DE INICIAR SESION A SALIR
			/*int Opcion = MessageBox(0, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (Opcion) {
			case IDYES: {
				DestroyWindow(hwnd);
			}
					  break;
			}*/
			Escribir_Binario_Usuario();
			/*Escribir_Binario_Paciente();
			Escribir_Binario_Vacunas();
			Escribir_Binario_Consumo();*/
			PostQuitMessage(0);
		}
				 break;
		}

		break;


	}

	return FALSE;
}


LRESULT CALLBACK Registrar(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg) {
		{

	case WM_INITDIALOG:
	{
	}

		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case  1004: {//De Registro REGRESAR a Inicio Sesion
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProc);
		}
				  break;

		case 1003: { //Boton de Aceptar registro
			int CLetras = 0;
			int CNumeros = 0;
			int CCaracteres = 0;
			int CEspacios = 0;
			int lengthClave = 0;
			int lengthContra = 0;
			int lengthPaciente_AP = 0;
			int lengthPaciente_AM = 0;
			int lengthNombres = 0;
			Usuario* Nuevo_usuario = new Usuario;
			GetDlgItemText(hwnd, 3, Nuevo_usuario->usuario_clave, sizeof(Nuevo_usuario->usuario_clave));
			GetDlgItemText(hwnd, 4, Nuevo_usuario->usuario_contrasenia, sizeof(Nuevo_usuario->usuario_contrasenia));
			GetDlgItemText(hwnd, 5, Nuevo_usuario->apellidopa, sizeof(Nuevo_usuario->apellidopa));
			GetDlgItemText(hwnd, 5, Nuevo_usuario->apellidoma, sizeof(Nuevo_usuario->apellidoma));
			GetDlgItemText(hwnd, 5, Nuevo_usuario->Nombres, sizeof(Nuevo_usuario->Nombres));

			lengthClave = strlen(Nuevo_usuario->usuario_clave);
			lengthContra = strlen(Nuevo_usuario->usuario_contrasenia);
			lengthPaciente_AP = strlen(Nuevo_usuario->apellidopa);
			lengthPaciente_AM = strlen(Nuevo_usuario->apellidoma);
			lengthNombres = strlen(Nuevo_usuario->Nombres);

			char usuarios_nombre_registro[15];
			GetDlgItemText(hwnd, 3, usuarios_nombre_registro, sizeof(usuarios_nombre_registro));
			Usuario_aux = Usuario_inicio;




			if (lengthClave <= 0 || lengthClave > 15)//valida nombre
			{
				MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfabeticos (Sin espacios).", "Clave", MB_OK | MB_ICONEXCLAMATION);
			}
			else {
				for (int i = 0; i < lengthClave; i++)
				{
					if (ispunct(Nuevo_usuario->usuario_clave[i]))
					{
						CCaracteres++;
					}
				
					if (isspace(Nuevo_usuario->usuario_clave[i]))
					{
						CEspacios++;
					}
				}
				if (CCaracteres != 0 || CEspacios != 0)
				{
					MessageBox(hwnd, "Favor de solo ingresar caracteres alfabeticos (Sin espacios).", "Clave", MB_OK | MB_ICONEXCLAMATION);
				}
				else
				{
					CLetras = 0;
					CNumeros = 0;
					CCaracteres = 0;
					CEspacios = 0;
					while (Usuario_aux != nullptr && strcmp(Usuario_aux->usuario_clave, usuarios_nombre_registro) != 0) {//validacion mismmo nombre
						Usuario_aux = Usuario_aux->Usuario_sig;
					}
					if (Usuario_aux != nullptr) {
						MessageBox(hwnd, "Clave existente, intente con otro nombre", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						if (lengthContra < 3 || lengthContra>10)//valida contraseña
						{
							MessageBox(hwnd, "Favor de ingresar de 3 a 10 caracteres. Minimo 1 letra, 1 numero y 1 caracter especial (Sin espacios).", "CONTRASEÑA", MB_OK | MB_ICONEXCLAMATION);
						}
						else {
							for (int i = 0; i < lengthContra; i++)
							{
								if (isalpha(Nuevo_usuario->usuario_contrasenia[i]))
								{
									CLetras++;
								}
								if (ispunct(Nuevo_usuario->usuario_contrasenia[i]))
								{
									CCaracteres++;
								}
								if (isdigit(Nuevo_usuario->usuario_contrasenia[i]))
								{
									CNumeros++;
								}
								if (isspace(Nuevo_usuario->usuario_contrasenia[i]))
								{
									CEspacios++;
								}
							}
							if (CCaracteres == 0 || CNumeros == 0 || CLetras == 0 || CEspacios != 0)
							{
								MessageBox(hwnd, "Favor de ingresar minimo 1 letra, 1 numero (Sin espacios).", "CONTRASEÑA", MB_OK | MB_ICONEXCLAMATION);
							}
							else
							{
								CLetras = 0;
								CNumeros = 0;
								CCaracteres = 0;
								CEspacios = 0;
							}
							while (Usuario_aux != nullptr && strcmp(Usuario_aux->usuario_clave, usuarios_nombre_registro) != 0) {//validacion mismmo nombre
								Usuario_aux = Usuario_aux->Usuario_sig;
							}
							if (Usuario_aux != nullptr) {
								
							}
							else {
								if (lengthPaciente_AP < 3 || lengthPaciente_AP>10)//valida contraseña
								{
									MessageBox(hwnd, "Favor de ingresar de 3 a 10 caracteres. Minimo 1 letra, 1 numero y 1 caracter especial (Sin espacios).", "Apellido Paterno", MB_OK | MB_ICONEXCLAMATION);
								}
								else {
									for (int i = 0; i < lengthPaciente_AP; i++)
									{
										if (isalpha(Nuevo_usuario->apellidopa[i]))
										{
											CLetras++;
										}
										if (ispunct(Nuevo_usuario->apellidopa[i]))
										{
											CCaracteres++;
										}
										if (isdigit(Nuevo_usuario->apellidopa[i]))
										{
											CNumeros++;
										}
										if (isspace(Nuevo_usuario->apellidopa[i]))
										{
											CEspacios++;
										}
									}
									if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0 || CEspacios != 0)
									{
										MessageBox(hwnd, "Favor de ingresar minimo 1 letra, 1 numero y 1 caracter especial(Sin espacios).", "Apellido Paterno", MB_OK | MB_ICONEXCLAMATION);
									}
									else
									{
										CLetras = 0;
										CNumeros = 0;
										CCaracteres = 0;
										CEspacios = 0;
									}
									if (lengthPaciente_AM < 3 || lengthPaciente_AM>10)//valida contraseña
									{
										MessageBox(hwnd, "Favor de ingresar de 3 a 10 caracteres. Minimo 1 letra, 1 numero y 1 caracter especial (Sin espacios).", "Apellido Materno", MB_OK | MB_ICONEXCLAMATION);
									}
									else {
										for (int i = 0; i < lengthPaciente_AP; i++)
										{
											if (isalpha(Nuevo_usuario->apellidoma[i]))
											{
												CLetras++;
											}
											if (ispunct(Nuevo_usuario->apellidoma[i]))
											{
												CCaracteres++;
											}
											if (isdigit(Nuevo_usuario->apellidoma[i]))
											{
												CNumeros++;
											}
											if (isspace(Nuevo_usuario->apellidoma[i]))
											{
												CEspacios++;
											}
										}
										if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0 || CEspacios != 0)
										{
											MessageBox(hwnd, "Favor de ingresar minimo 1 letra, 1 numero y 1 caracter especial(Sin espacios).", "Apellido Materno", MB_OK | MB_ICONEXCLAMATION);
										}
										else
										{
											CLetras = 0;
											CNumeros = 0;
											CCaracteres = 0;
											CEspacios = 0;
										}
										if (lengthNombres < 3 || lengthNombres>10)//valida contraseña
										{
											MessageBox(hwnd, "Favor de ingresar de 3 a 10 caracteres. Minimo 1 letra (Sin espacios).", "Nombre", MB_OK | MB_ICONEXCLAMATION);
										}
										else {
											for (int i = 0; i < lengthNombres; i++)
											{
												if (isalpha(Nuevo_usuario->apellidoma[i]))
												{
													CLetras++;
												}
												if (ispunct(Nuevo_usuario->apellidoma[i]))
												{
													CCaracteres++;
												}
												if (isdigit(Nuevo_usuario->apellidoma[i]))
												{
													CNumeros++;
												}
												
											}
											if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0 )
											{
												MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Apellido Materno", MB_OK | MB_ICONEXCLAMATION);
											}
											else {
												strcpy_s(Nuevo_usuario->usuarios_direccion, "");
												Agregar_usuario(Nuevo_usuario);
												delete Nuevo_usuario;
												Escribir_Binario_Usuario();

												SetDlgItemText(hwnd, 3, "");
												SetDlgItemText(hwnd, 4, "");
												SetDlgItemText(hwnd, 5, "");
												SetDlgItemText(hwnd, 6, "");
												SetDlgItemText(hwnd, 7, "");
											}
											
										}
									}
								}
							}
						}
					}

				}

			}

		}

		}
	}
return false;
}

LRESULT CALLBACK VentanaInicio(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

		case WM_INITDIALOG: 
		{
		}
	    break;
		case WM_COMMAND: 
			switch (LOWORD(wParam))
			{
				{
			case 9999:
			{
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, repesonas);
			}
			break;
			case 9998:
			{
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG5), hwnd, reVacunas);
			}
			break;
			case 9997:
			{
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG6), hwnd, recarnet);
			}
			break;
				}
		}break;
	}
	return FALSE;
}

LRESULT CALLBACK repesonas(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		{

	case WM_INITDIALOG:
	{

		char TipodeUsuario[7][25] = { "Casado(a)", "Conviviente","Anulado(a)","Separado de unión legal","Viudo(a)","Soltero(a)" };
		for (int i = 0; i < 7; i++) {
			SendDlgItemMessage(hwnd, 15, CB_INSERTSTRING, (WPARAM)i, (LPARAM)TipodeUsuario[i]);

		}
		SendMessage(GetDlgItem(hwnd, 15), CB_SETCURSEL, (WPARAM)0, 0);

		char sexousuario[2][25] = { "Masculino", "Femenino" };
		for (int i = 0; i < 2; i++) {
			SendDlgItemMessage(hwnd, 17, CB_INSERTSTRING, (WPARAM)i, (LPARAM)sexousuario[i]);

		}
		SendMessage(GetDlgItem(hwnd, 17), CB_SETCURSEL, (WPARAM)0, 0);;
		SYSTEMTIME fechaHoy;
		ZeroMemory(&fechaHoy, sizeof(fechaHoy));
		GetLocalTime(&fechaHoy);

		char fechaCompleta[11] = { 0 };
		char charFecha[5] = { 0 };
		sprintf_s(charFecha, "%d", fechaHoy.wDay);
		strcat_s(fechaCompleta, charFecha);
		strcat_s(fechaCompleta, "/");
		sprintf_s(charFecha, "%d", fechaHoy.wMonth);
		strcat_s(fechaCompleta, charFecha);
		strcat_s(fechaCompleta, "/");
		sprintf_s(charFecha, "%d", fechaHoy.wYear);
		strcat_s(fechaCompleta, charFecha);
		SetDlgItemText(hwnd, 11, fechaCompleta);
	}

		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case  1005: {//De Registro REGRESAR a Inicio Sesion
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG3), NULL, VentanaInicio);
		}
				  break;

		case 20:
		{
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "ALL\0 * .*\0Bitmaps\0 * .bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;

			if (GetOpenFileName(&ofn) == TRUE) {
				HBITMAP bmp; //1

				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
				SetDlgItemText(hwnd, 21, zFile);
				SendDlgItemMessage(hwnd, 22, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 
			}
			else {
				MessageBox(hwnd, "No seleccionó foto", "AVISO", MB_OK | MB_ICONERROR);
				strcpy_s(zFile, NUPaciente->docindet);

			}
		}
		break;
		case 1006: { //Boton de Aceptar registro
			int CLetras = 0;
			int CNumeros = 0;
			int CCaracteres = 0;
			int CEspacios = 0;
			int lengthPaciente_nombre = 0;
			int lengthPaciente_AP = 0;
			int lengthPaciente_AM = 0;
			int lengthCURP = 0;
			int lengthRFC = 0;
			int lengthcalle = 0;
			int lengthciudad = 0;
			int lengthestado = 0;
			int lengthtelefono = 0; 
			int lengthPerfilRies = 0;
	
			char perfil[50];
			Paciente* Nuevo_usuario = new Paciente;
			GetDlgItemText(hwnd, 1022, Nuevo_usuario->Paciente_nombre, sizeof(Nuevo_usuario->Paciente_nombre));
			GetDlgItemText(hwnd, 8 , Nuevo_usuario->Paciente_AP, sizeof(Nuevo_usuario->Paciente_AP));
			GetDlgItemText(hwnd, 9 , Nuevo_usuario->Paciente_AM, sizeof(Nuevo_usuario->Paciente_AM));
			GetDlgItemText(hwnd, 10, Nuevo_usuario->CURP, sizeof(Nuevo_usuario->CURP));
			GetDlgItemText(hwnd, 19, Nuevo_usuario->RFC, sizeof(Nuevo_usuario->RFC));
			GetDlgItemText(hwnd, 11, Nuevo_usuario->FechaNac, sizeof(Nuevo_usuario->FechaNac));
			GetDlgItemText(hwnd, 12, Nuevo_usuario->calle, sizeof(Nuevo_usuario->calle));
			GetDlgItemText(hwnd, 13, Nuevo_usuario->ciudad, sizeof(Nuevo_usuario->ciudad));
			GetDlgItemText(hwnd, 14, Nuevo_usuario->estado, sizeof(Nuevo_usuario->estado));
			GetDlgItemText(hwnd, 15, Nuevo_usuario->estadocivil, sizeof(Nuevo_usuario->estadocivil));
			GetDlgItemText(hwnd, 16, Nuevo_usuario->telefono, sizeof(Nuevo_usuario->telefono));
			GetDlgItemText(hwnd, 17, Nuevo_usuario->Sexo, sizeof(Nuevo_usuario->Sexo));
			GetDlgItemText(hwnd, 18, Nuevo_usuario->PerfilRies, sizeof(Nuevo_usuario->PerfilRies));
			GetDlgItemText(hwnd, 21, Nuevo_usuario->docindet, sizeof(Nuevo_usuario->docindet));
			lengthPaciente_AP = strlen(Nuevo_usuario->Paciente_AP);
			lengthPaciente_AM = strlen(Nuevo_usuario->Paciente_AM);
			lengthCURP = strlen(Nuevo_usuario->CURP);
			lengthRFC = strlen(Nuevo_usuario->RFC);
			lengthcalle = strlen(Nuevo_usuario->calle);
			lengthciudad = strlen(Nuevo_usuario->ciudad);
			lengthestado = strlen(Nuevo_usuario->estado);
			lengthtelefono= strlen(Nuevo_usuario->telefono);
			lengthPerfilRies= strlen(Nuevo_usuario->PerfilRies);
			char usuarios_nombre_registro[15];
		/*	GetDlgItemText(hwnd, 3, usuarios_nombre_registro, sizeof(usuarios_nombre_registro));
			Usuario_aux = Usuario_inicio;*/
			char comparar[15];
			GetDlgItemText(hwnd, 8, comparar, sizeof(comparar));
			Paciente_aux = Paciente_inicio;
			/*Paciente_inicio, * NUPaciente, * Paciente_aux*/


			if (lengthPaciente_AP <= 0 || lengthPaciente_AP > 15)//valida nombre
			{
				MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfabeticos (Sin espacios).", "Apellido Páterno", MB_OK | MB_ICONEXCLAMATION);
			}
			else {
				for (int i = 0; i < lengthPaciente_AP; i++)
				{
					if (isalpha(Nuevo_usuario->Paciente_AP[i]))
					{
						CLetras++;
					}
					if (ispunct(Nuevo_usuario->Paciente_AP[i]))
					{
						CCaracteres++;
					}
					if (isdigit(Nuevo_usuario->Paciente_AP[i]))
					{
						CNumeros++;
					}

				}
				if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0)
				{
					MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Apellido Paterno", MB_OK | MB_ICONEXCLAMATION);
				}
				else
				{
					CLetras = 0;
					CNumeros = 0;
					CCaracteres = 0;
					CEspacios = 0;
				}
				while (Paciente_aux != nullptr && strcmp(Paciente_aux->Paciente_AP, comparar) != 0) {//validacion mismmo nombre
					Paciente_aux = Paciente_aux->Paciente_sig;
				}
				if (Paciente_aux != nullptr) {
					MessageBox(hwnd, "Persona ya existente, intente otro nombre", "AVISO", MB_OK | MB_ICONERROR);
				}
				if (lengthPaciente_AM <= 0 || lengthPaciente_AM > 15)//valida nombre
				{
					MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfabeticos (Sin espacios).", "Apellido Máterno", MB_OK | MB_ICONEXCLAMATION);
				}
				else {
					for (int i = 0; i < lengthPaciente_AM; i++)
					{
						if (isalpha(Nuevo_usuario->Paciente_AM[i]))
						{
							CLetras++;
						}
						if (ispunct(Nuevo_usuario->Paciente_AM[i]))
						{
							CCaracteres++;
						}
						if (isdigit(Nuevo_usuario->Paciente_AM[i]))
						{
							CNumeros++;
						}

					}
					if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0)
					{
						MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Apellido Materno", MB_OK | MB_ICONEXCLAMATION);
					}
					else
					{
						CLetras = 0;
						CNumeros = 0;
						CCaracteres = 0;
						CEspacios = 0;
					}
					if (lengthCURP <= 0 || lengthCURP > 22)//valida nombre
					{
						MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfabeticos (Sin espacios).", "CURP", MB_OK | MB_ICONEXCLAMATION);
					}
					else {
						for (int i = 0; i < lengthCURP; i++)
						{
							if (isalpha(Nuevo_usuario->CURP[i]))
							{
								CLetras++;
							}
							if (ispunct(Nuevo_usuario->CURP[i]))
							{
								CCaracteres++;
							}
							if (isdigit(Nuevo_usuario->CURP[i]))
							{
								CNumeros++;
							}
					
						}
						if (CCaracteres != 0 || CNumeros == 0 || CLetras == 0 || CNumeros>8 || CLetras >12)
						{
							MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "CURP", MB_OK | MB_ICONEXCLAMATION);
						}
						else
						{
							CLetras = 0;
							CNumeros = 0;
							CCaracteres = 0;
							CEspacios = 0;
						}
								if (lengthcalle <= 0 || lengthcalle > 15)//valida nombre de la calle
								{
									MessageBox(hwnd, "Favor de ingresar la calle.", "Calle", MB_OK | MB_ICONEXCLAMATION);
								}
								else {
									for (int i = 0; i < lengthcalle; i++)
									{
										if (isalpha(Nuevo_usuario->calle[i]))
										{
											CLetras++;
										}
										if (ispunct(Nuevo_usuario->calle[i]))
										{
											CCaracteres++;
										}
										if (isdigit(Nuevo_usuario->calle[i]))
										{
											CNumeros++;
										}

									}
									if (CCaracteres != 0 || CNumeros == 0 || CLetras == 0 )
									{
										MessageBox(hwnd, "Favor de ingresar la calle correctamente.", "calle", MB_OK | MB_ICONEXCLAMATION);
									}
									else
									{
										CLetras = 0;
										CNumeros = 0;
										CCaracteres = 0;
										CEspacios = 0;
									}
									if (lengthciudad <= 0 || lengthciudad > 30)//valida nombre
									{
										MessageBox(hwnd, "Favor de ingresar la ciudad.", "ciudad", MB_OK | MB_ICONEXCLAMATION);
									}
									else {
										for (int i = 0; i < lengthciudad; i++)
										{
											
											if (ispunct(Nuevo_usuario->ciudad[i]))
											{
												CCaracteres++;
											}
			

										}
										if (CCaracteres != 0 )
										{
											MessageBox(hwnd, "Favor de ingresar la ciudad correcta.", "ciudad", MB_OK | MB_ICONEXCLAMATION);
										}
										else
										{
											CLetras = 0;
											CNumeros = 0;
											CCaracteres = 0;
											CEspacios = 0;
										}
										if (lengthestado <= 0 || lengthestado > 22)//valida nombre
										{
											MessageBox(hwnd, "Favor de ingresar el estado.", "estado", MB_OK | MB_ICONEXCLAMATION);
										}
										else {
											for (int i = 0; i < lengthestado; i++)
											{
												if (isalpha(Nuevo_usuario->estado[i]))
												{
													CLetras++;
												}
												if (ispunct(Nuevo_usuario->estado[i]))
												{
													CCaracteres++;
												}
										

											}
											if (CCaracteres != 0 ||  CLetras == 0)
											{
												MessageBox(hwnd, "Favor de ingresar el estad correcto.", "estado", MB_OK | MB_ICONEXCLAMATION);
											}
											else
											{
												CLetras = 0;
												CNumeros = 0;
												CCaracteres = 0;
												CEspacios = 0;
											}

											if (lengthPerfilRies <= 0 || lengthPerfilRies > 15)//valida nombre
											{
												MessageBox(hwnd, "Favor de ingresar perfil de riesgo.", "perfil de riesgo", MB_OK | MB_ICONEXCLAMATION);
											}
											else {
												for (int i = 0; i < lengthPerfilRies; i++)
												{
													if (isalpha(Nuevo_usuario->PerfilRies[i]))
													{
														CLetras++;
													}
													if (ispunct(Nuevo_usuario->PerfilRies[i]))
													{
														CCaracteres++;
													}
													if (isdigit(Nuevo_usuario->PerfilRies[i]))
													{
														CNumeros++;
													}

												}
												if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0)
												{
													MessageBox(hwnd, "Favor de ingresar perfil de riesgo correcto.", "perfil de riesgo", MB_OK | MB_ICONEXCLAMATION);
												}
												else
												{
													CLetras = 0;
													CNumeros = 0;
													CCaracteres = 0;
													CEspacios = 0;
												}
												if (lengthtelefono <= 0 || lengthtelefono > 22)//valida nombre
												{
													MessageBox(hwnd, "Favor de ingresar un telefono.", "telefono", MB_OK | MB_ICONEXCLAMATION);
												}
												else {
													for (int i = 0; i < lengthtelefono; i++)
													{
														if (isalpha(Nuevo_usuario->telefono[i]))
														{
															CLetras++;
														}
														
														if (isdigit(Nuevo_usuario->telefono[i]))
														{
															CNumeros++;
														}

													}
													if (CNumeros == 0 || CLetras != 0)
													{
														MessageBox(hwnd, "Favor de ingresar un telefono correcto.", "telefono", MB_OK | MB_ICONEXCLAMATION);
													}
													else
													{
														strcpy_s(Nuevo_usuario->Paciente_direccion, "");
														Agregar_Paciente(Nuevo_usuario);
														delete NUPaciente;
														Escribir_Binario_Paciente();

														SetDlgItemText(hwnd, 8, "");
														SetDlgItemText(hwnd, 9, "");
														SetDlgItemText(hwnd, 10, "");
														SetDlgItemText(hwnd, 12, "");
														SetDlgItemText(hwnd, 13, "");
														SetDlgItemText(hwnd, 14, "");
														SetDlgItemText(hwnd, 16, "");
														SetDlgItemText(hwnd, 18, "");
														SetDlgItemText(hwnd, 21, "");
														SetDlgItemText(hwnd, 19, "");
													}
												}
												
										
									}
								}
							}
						}
					}
				}
			}

		}
		}
	}
	return false;
}

LRESULT CALLBACK reVacunas(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
		switch (msg)
		{

			

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{

			case 1006:
			{//De Registro REGRESAR a Inicio Sesion
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG3), NULL, VentanaInicio);
			}
			break;
			case 1007:
			{
				int CLetras = 0;
				int CNumeros = 0;
				int CCaracteres = 0;
				int CEspacios = 0;
				int lengthtipo = 0;
				int lengthmarca = 0;
				int lengthclave = 0;
				int lengthdesc = 0;
				int lengthnum = 0;

				/*char tipovacuna[50];
				char marca[30];
				char clavevacuna[30];
				char Descripcion[30];
				char Precio[99];
				char Numdosis[99];*/

				char perfil[50];
				Vacunas* Nuevo_usuario = new Vacunas;
				GetDlgItemText(hwnd, 25, Nuevo_usuario->tipovacuna, sizeof(Nuevo_usuario->tipovacuna));
				GetDlgItemText(hwnd, 26, Nuevo_usuario->marca, sizeof(Nuevo_usuario->marca));
				GetDlgItemText(hwnd, 27, Nuevo_usuario->clavevacuna, sizeof(Nuevo_usuario->clavevacuna));
				GetDlgItemText(hwnd, 28, Nuevo_usuario->Descripcion, sizeof(Nuevo_usuario->Descripcion));
				GetDlgItemText(hwnd, 29, Nuevo_usuario->Precio, sizeof(Nuevo_usuario->Precio));
				GetDlgItemText(hwnd, 30, Nuevo_usuario->Numdosis, sizeof(Nuevo_usuario->Numdosis));
				lengthtipo = strlen(Nuevo_usuario->tipovacuna);
				lengthmarca = strlen(Nuevo_usuario->marca);
				lengthclave = strlen(Nuevo_usuario->clavevacuna);
				lengthdesc = strlen(Nuevo_usuario->Descripcion);
				lengthnum = strlen(Nuevo_usuario->Numdosis);


				char comparar[15];
				GetDlgItemText(hwnd, 25, comparar, sizeof(comparar));
				Vacunas_aux = Vacunas_inicio;
				/*Vacunas_inicio, * Vacunas_aux*/

				if (lengthtipo <= 0 || lengthtipo > 15)//valida nombre
				{
					MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfabeticos (Sin espacios).", "Tipo de vacuna", MB_OK | MB_ICONEXCLAMATION);
				}
				else {
					for (int i = 0; i < lengthtipo; i++)
					{
						if (isalpha(Nuevo_usuario->tipovacuna[i]))
						{
							CLetras++;
						}
						if (ispunct(Nuevo_usuario->tipovacuna[i]))
						{
							CCaracteres++;
						}
						if (isdigit(Nuevo_usuario->tipovacuna[i]))
						{
							CNumeros++;
						}

					}
					if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0)
					{
						MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Tipo de vacuna", MB_OK | MB_ICONEXCLAMATION);
					}
					else
					{
						CLetras = 0;
						CNumeros = 0;
						CCaracteres = 0;
						CEspacios = 0;
					}
					if (lengthmarca <= 0 || lengthmarca > 15)//valida nombre
					{
						MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfabeticos (Sin espacios).", "Marca", MB_OK | MB_ICONEXCLAMATION);
					}
					else {
						for (int i = 0; i < lengthmarca; i++)
						{
							if (isalpha(Nuevo_usuario->marca[i]))
							{
								CLetras++;
							}
							if (ispunct(Nuevo_usuario->marca[i]))
							{
								CCaracteres++;
							}
							if (isdigit(Nuevo_usuario->marca[i]))
							{
								CNumeros++;
							}

						}
						if (CCaracteres != 0 || CNumeros != 0 || CLetras == 0)
						{
							MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Marca", MB_OK | MB_ICONEXCLAMATION);
						}
						else
						{
							CLetras = 0;
							CNumeros = 0;
							CCaracteres = 0;
							CEspacios = 0;
						}
						if (lengthclave <= 0 || lengthclave > 15)//valida nombre
						{
							MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfanumericos (Sin espacios).", "Clave", MB_OK | MB_ICONEXCLAMATION);
						}
						else {
							for (int i = 0; i < lengthclave; i++)
							{
							
								if (ispunct(Nuevo_usuario->clavevacuna[i]))
								{
									CCaracteres++;
								}
							

							}
							if (CCaracteres != 0)
							{
								MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Clave", MB_OK | MB_ICONEXCLAMATION);
							}
							else
							{
								CLetras = 0;
								CNumeros = 0;
								CCaracteres = 0;
								CEspacios = 0;
							}
							if (lengthdesc <= 0 || lengthdesc > 15)//valida nombre
							{
								MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres alfanumericos (Sin espacios).", "Descripcion", MB_OK | MB_ICONEXCLAMATION);
							}
							else {
								for (int i = 0; i < lengthdesc; i++)
								{
								
									if (ispunct(Nuevo_usuario->Descripcion[i]))
									{
										CCaracteres++;
									}
								

								}
								if (CCaracteres != 0 )
								{
									MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Descripcion", MB_OK | MB_ICONEXCLAMATION);
								}
								else
								{
									CLetras = 0;
									CNumeros = 0;
									CCaracteres = 0;
									CEspacios = 0;
								}
							}
							if (lengthnum <= 0 || lengthnum > 15)//valida nombre
							{
								MessageBox(hwnd, "Favor de ingresar de un maximo de 15 caracteres numericos (Sin espacios).", "Numero de dosis", MB_OK | MB_ICONEXCLAMATION);
							}
							else {
								for (int i = 0; i < lengthnum; i++)
								{
									if (isalpha(Nuevo_usuario->Numdosis[i]))
									{
										CLetras++;
									}
									if (ispunct(Nuevo_usuario->Numdosis[i]))
									{
										CCaracteres++;
									}
									if (isdigit(Nuevo_usuario->Numdosis[i]))
									{
										CNumeros++;
									}

								}
								if (CCaracteres != 0 || CNumeros == 0 || CLetras != 0)
								{
									MessageBox(hwnd, "Favor de ingresar minimo 1 letra (Sin espacios).", "Numero de dosis", MB_OK | MB_ICONEXCLAMATION);
								}
								else
								{
									strcpy_s(Nuevo_usuario->Vacunas_direccion, "");
									Agregar_Vacunas(Nuevo_usuario);
									delete NUPaciente;
									Escribir_Binario_Paciente();

									SetDlgItemText(hwnd,25, "");
									SetDlgItemText(hwnd,26, "");
									SetDlgItemText(hwnd,27, "");
									SetDlgItemText(hwnd,28, "");
									SetDlgItemText(hwnd,29, "");
									SetDlgItemText(hwnd,30, "");
						
								}
							}
						}
					}
				}
			
			}
			break;
			}

			break;


		}

		return FALSE;
}

LRESULT CALLBACK recarnet(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return false;
}















void Agregar_usuario(Usuario* nuevo_u) {
	if (Usuario_inicio == nullptr) {
		Usuario_inicio = new Usuario;
		Usuario_aux = Usuario_inicio;

		Usuario_aux->Usuario_sig = nullptr;
		Usuario_aux->Usuario_ant = nullptr;

		strcpy_s(Usuario_aux->usuario_clave, nuevo_u->usuario_clave);
		strcpy_s(Usuario_aux->usuario_contrasenia, nuevo_u->usuario_contrasenia);
		strcpy_s(Usuario_aux->apellidopa, nuevo_u->apellidopa);
		strcpy_s(Usuario_aux->apellidoma, nuevo_u->apellidoma);
		strcpy_s(Usuario_aux->usuarios_direccion, nuevo_u->usuarios_direccion);
	
	}
	else {
		Usuario_aux = Usuario_inicio;

		while (Usuario_aux->Usuario_sig != nullptr)
		{
			Usuario_aux = Usuario_aux->Usuario_sig;
		}

		Usuario_aux->Usuario_sig = new Usuario;

		Usuario_aux->Usuario_sig->Usuario_sig = nullptr;
		Usuario_aux->Usuario_sig->Usuario_ant = Usuario_aux;

		Usuario_aux = Usuario_aux->Usuario_sig;

		strcpy_s(Usuario_aux->usuario_clave, nuevo_u->usuario_clave);
		strcpy_s(Usuario_aux->usuario_contrasenia, nuevo_u->usuario_contrasenia);
		strcpy_s(Usuario_aux->apellidopa, nuevo_u->apellidopa);
		strcpy_s(Usuario_aux->apellidoma, nuevo_u->apellidoma);
		strcpy_s(Usuario_aux->usuarios_direccion, nuevo_u->usuarios_direccion);

	}
	MessageBox(0, "Usuario registrado", "AVISO", MB_OK);
}

void Modificar_Usuario(Usuario* newInfo, char nomUsuario[50]) {

	Usuario_aux = Usuario_inicio;

	if (Usuario_aux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (Usuario_aux != nullptr && strcmp(Usuario_aux->usuario_clave, nomUsuario) != 0) {

			Usuario_aux = Usuario_aux->Usuario_sig;
		}
		if (Usuario_aux == nullptr) {
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {
			strcpy_s(Usuario_aux->usuario_clave, newInfo->usuario_clave);


			MessageBox(0, "Usuario modificado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
	}

}

void Eliminar_Usuario(char nomUsuario[50]) {
	Usuario_aux = Usuario_inicio;

	if (Usuario_aux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (Usuario_aux != nullptr && strcmp(Usuario_aux->usuario_clave, nomUsuario) != 0) {

			Usuario_aux = Usuario_aux->Usuario_sig;
		}
		if (Usuario_aux == nullptr) {
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK);
		}
		else if (Usuario_aux == Usuario_inicio) {	//El nodo es el primero 

			if (Usuario_aux->Usuario_sig == nullptr) {

				Usuario_inicio = nullptr;
				delete Usuario_aux;
				Usuario_aux = Usuario_inicio;
			}
			else {
				Usuario_inicio = Usuario_inicio->Usuario_sig;
				Usuario_aux->Usuario_sig->Usuario_ant = nullptr;
				delete Usuario_aux;
				Usuario_aux = Usuario_inicio;

			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {

			if (Usuario_aux->Usuario_sig == nullptr) { //Si el nodo es el último
				Usuario_aux->Usuario_ant->Usuario_sig = nullptr;
				delete Usuario_aux;
				Usuario_aux = Usuario_inicio;
			}
			else {
				Usuario_aux->Usuario_sig->Usuario_ant = Usuario_aux->Usuario_ant;
				Usuario_aux->Usuario_ant->Usuario_sig = Usuario_aux->Usuario_sig;
				delete Usuario_aux;
				Usuario_aux = Usuario_inicio;
			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);

		}
	}

}

void Escribir_Binario_Usuario()
{
	Usuario_aux = Usuario_inicio;

	ofstream escribirUsuario;
	escribirUsuario.open("C:\\Users\\karla\\source\\repos\\avance\\Usuario.bin", ios::out | ios::binary | ios::trunc);

	if (escribirUsuario.is_open()) {
		while (Usuario_aux != nullptr)
		{
			escribirUsuario.write((char*)Usuario_aux, sizeof(Usuario));
			Usuario_aux = Usuario_aux->Usuario_sig;
		}

		escribirUsuario.close();
	}
	else
	{
		system("PAUSE");
	}
}

void Leer_Binario_Usuario()
{
	ifstream archivoUsuario;
	archivoUsuario.open("C:\\Users\\karla\\source\\repos\\avance\\Usuario.bin", ios::in | ios::binary);


	if (archivoUsuario.is_open()) {

		Usuario* Usuario_leido = new Usuario;

		while (!archivoUsuario.read((char*)Usuario_leido, sizeof(Usuario)).eof()) {

			if (Usuario_inicio == nullptr) {
				Usuario_inicio = Usuario_leido;
				Usuario_inicio->Usuario_sig = nullptr;
				Usuario_inicio->Usuario_ant = nullptr;
				Usuario_aux = Usuario_inicio;
			}
			else {
				Usuario_aux->Usuario_sig = Usuario_leido;
				Usuario_aux->Usuario_sig->Usuario_ant = Usuario_aux;
				Usuario_aux = Usuario_aux->Usuario_sig;
				Usuario_aux->Usuario_sig = nullptr;
				//fin = aux;
			}

			Usuario_leido = new Usuario;
		}
		archivoUsuario.close();
		delete Usuario_leido;
	}
	else {
		system("PAUSE");
	}
}




void Agregar_Paciente(Paciente* nuevo) {


	if (Paciente_inicio == nullptr) {
		Paciente_inicio = new Paciente;
		Paciente_aux = Paciente_inicio;

		Paciente_aux->Paciente_sig = nullptr;
		Paciente_aux->Paciente_ant = nullptr;

		strcpy_s(Paciente_aux->Paciente_AP, nuevo->Paciente_AP);
		strcpy_s(Paciente_aux->Paciente_AM, nuevo->Paciente_AM);
		strcpy_s(Paciente_aux->CURP, nuevo->CURP);
		strcpy_s(Paciente_aux->RFC, nuevo->RFC);
		strcpy_s(Paciente_aux->FechaNac, nuevo->FechaNac);
		strcpy_s(Paciente_aux->calle, nuevo->calle);
		strcpy_s(Paciente_aux->estado, nuevo->estado);
		strcpy_s(Paciente_aux->estadocivil, nuevo->estadocivil);
		strcpy_s(Paciente_aux->telefono, nuevo->telefono);
		strcpy_s(Paciente_aux->Sexo, nuevo->Sexo);
		strcpy_s(Paciente_aux->PerfilRies, nuevo->PerfilRies);
		strcpy_s(Paciente_aux->Paciente_direccion, nuevo->Paciente_direccion);

	}
	else {
		Paciente_aux = Paciente_inicio;
		while (Paciente_aux->Paciente_sig != nullptr)
		{
			Paciente_aux = Paciente_aux->Paciente_sig;
		}

		Paciente_aux->Paciente_sig = new Paciente;

		Paciente_aux->Paciente_sig->Paciente_sig = nullptr;
		Paciente_aux->Paciente_sig->Paciente_ant = Paciente_aux;

		Paciente_aux = Paciente_aux->Paciente_sig;

	
		strcpy_s(Paciente_aux->Paciente_AP, nuevo->Paciente_AP);
		strcpy_s(Paciente_aux->Paciente_AM, nuevo->Paciente_AM);
		strcpy_s(Paciente_aux->CURP, nuevo->CURP);
		strcpy_s(Paciente_aux->RFC, nuevo->RFC);
		strcpy_s(Paciente_aux->FechaNac, nuevo->FechaNac);
		strcpy_s(Paciente_aux->calle, nuevo->calle);
		strcpy_s(Paciente_aux->estado, nuevo->estado);
		strcpy_s(Paciente_aux->estadocivil, nuevo->estadocivil); 
		strcpy_s(Paciente_aux->telefono, nuevo->telefono);
		strcpy_s(Paciente_aux->Sexo, nuevo->Sexo);
		strcpy_s(Paciente_aux->PerfilRies, nuevo->PerfilRies);
		strcpy_s(Paciente_aux->Paciente_direccion, nuevo->Paciente_direccion);

		Paciente_aux->Paciente_sig = nullptr;
	}
	MessageBox(0, "Paciente registrado", "AVISO", MB_OK);
}
void Escribir_Binario_Paciente()
{
	Paciente_aux = Paciente_inicio;

	ofstream escribirPaciente;
	escribirPaciente.open("C:\\Users\\karla\\source\\repos\\avance\\Paciente.bin", ios::out | ios::binary | ios::trunc);
	if (escribirPaciente.is_open()) {
		while (Paciente_aux != nullptr)
		{
			escribirPaciente.write((char*)Paciente_aux, sizeof(Paciente));
			Paciente_aux = Paciente_aux->Paciente_sig;
		}

		escribirPaciente.close();
	}
	else
	{
		system("PAUSE");
	}
}
void Leer_Binario_Paciente()
{
	ifstream archivoPaciente;
	archivoPaciente.open("C:\\Users\\karla\\source\\repos\\avance\\Paciente.bin", ios::in | ios::binary);

	if (archivoPaciente.is_open()) {

		Paciente* Paciente_leido = new Paciente;

		while (!archivoPaciente.read((char*)Paciente_leido, sizeof(Paciente)).eof()) {

			if (Paciente_inicio == nullptr) {
				Paciente_inicio = Paciente_leido;
				Paciente_inicio->Paciente_sig = nullptr;
				Paciente_inicio->Paciente_ant = nullptr;
				Paciente_aux = Paciente_inicio;
			}
			else {
				Paciente_aux->Paciente_sig = Paciente_leido;
				Paciente_aux->Paciente_sig->Paciente_ant = Paciente_aux;
				Paciente_aux = Paciente_aux->Paciente_sig;
				Paciente_aux->Paciente_sig = nullptr;
				//fin = aux;
			}

			Paciente_leido = new Paciente;
		}
		archivoPaciente.close();
		delete Paciente_leido;
	}
	else {
		system("PAUSE");
	}
}
void Eliminar_Paciente(char nomPaciente[50]) {
	Paciente_aux = Paciente_inicio;

	if (Paciente_aux == nullptr)
	{
		MessageBox(0, "No hay Pacientes registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (Paciente_aux != nullptr && strcmp(Paciente_aux->Paciente_AP, nomPaciente) != 0) {

			Paciente_aux = Paciente_aux->Paciente_sig;
		}
		if (Paciente_aux == nullptr) {
			MessageBox(0, "Paciente no encontrado", "AVISO", MB_OK);
		}
		else if (Paciente_aux == Paciente_inicio) {	//El nodo es el primero 

			if (Paciente_aux->Paciente_sig == nullptr) {

				Paciente_inicio = nullptr;
				delete Paciente_aux;
				Paciente_aux = Paciente_inicio;
			}
			else {
				Paciente_inicio = Paciente_inicio->Paciente_sig;
				Paciente_aux->Paciente_sig->Paciente_ant = nullptr;
				delete Paciente_aux;
				Paciente_aux = Paciente_inicio;

			}

			MessageBox(0, "Paciente eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {

			if (Paciente_aux->Paciente_sig == nullptr) { //Si el nodo es el último
				Paciente_aux->Paciente_ant->Paciente_sig = nullptr;
				delete Paciente_aux;
				Paciente_aux = Paciente_inicio;
			}
			else {
				Paciente_aux->Paciente_sig->Paciente_ant = Paciente_aux->Paciente_ant;
				Paciente_aux->Paciente_ant->Paciente_sig = Paciente_aux->Paciente_sig;
				delete Paciente_aux;
				Paciente_aux = Paciente_inicio;
			}

			MessageBox(0, "Paciente eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);

		}
	}

}




void Agregar_Vacunas(Vacunas* nuevo) {


	if (Vacunas_inicio == nullptr) {
		Vacunas_inicio = new Vacunas;
		Vacunas_aux = Vacunas_inicio;

		Vacunas_aux->Vacunas_sig = nullptr;
		Vacunas_aux->Vacunas_ant = nullptr;
		/*char tipovacuna[50];
		char marca[30];
		char clavevacuna[30];
		char Descripcion[30];
		int Precio[99];
		int Numdosis[99];*/
		strcpy_s(Vacunas_aux->tipovacuna, nuevo->tipovacuna);
		strcpy_s(Vacunas_aux->marca, nuevo->marca);
		strcpy_s(Vacunas_aux->clavevacuna, nuevo->clavevacuna);
		strcpy_s(Vacunas_aux->Descripcion, nuevo->Descripcion);
		strcpy_s(Vacunas_aux->Precio, nuevo->Precio);
		strcpy_s(Vacunas_aux->Numdosis, nuevo->Numdosis);
		/*strcpy_s(Vacunas_aux->Promestatus, nuevo->Promestatus);*/

	/*	Vacunas_aux->Prommonto = nuevo->Prommonto;
		Vacunas_aux->Promdescuento = nuevo->Promdescuento;*/

	}
	else {
		Vacunas_aux = Vacunas_inicio;
		while (Vacunas_aux->Vacunas_sig != nullptr)
		{
			Vacunas_aux = Vacunas_aux->Vacunas_sig;
		}

		Vacunas_aux->Vacunas_sig = new Vacunas;

		Vacunas_aux->Vacunas_sig->Vacunas_sig = nullptr;
		Vacunas_aux->Vacunas_sig->Vacunas_ant = Vacunas_aux;

		Vacunas_aux = Vacunas_aux->Vacunas_sig;

		strcpy_s(Vacunas_aux->tipovacuna, nuevo->tipovacuna);
		strcpy_s(Vacunas_aux->marca, nuevo->marca);
		strcpy_s(Vacunas_aux->clavevacuna, nuevo->clavevacuna);
		strcpy_s(Vacunas_aux->Descripcion, nuevo->Descripcion);
		strcpy_s(Vacunas_aux->Precio, nuevo->Precio);
		strcpy_s(Vacunas_aux->Numdosis, nuevo->Numdosis);
		/*strcpy_s(Vacunas_aux->Promestatus, nuevo->Promestatus);*/

		/*Vacunas_aux->Prommonto = nuevo->Prommonto;
		Vacunas_aux->Promdescuento = nuevo->Promdescuento;*/
		Vacunas_aux->Vacunas_sig = nullptr;
	}
	MessageBox(0, "Vacunas registrada", "AVISO", MB_OK);
}
void Escribir_Binario_Vacunas()
{
	Vacunas_aux = Vacunas_inicio;

	ofstream escribirVacunas;
	escribirVacunas.open("C:\\Users\\karla\\source\\repos\\avance\\Vacunas.bin", ios::out | ios::binary | ios::trunc);

	if (escribirVacunas.is_open()) {
		while (Vacunas_aux != nullptr)
		{
			escribirVacunas.write((char*)Vacunas_aux, sizeof(Vacunas));
			Vacunas_aux = Vacunas_aux->Vacunas_sig;
		}

		escribirVacunas.close();
	}
	else
	{
		system("PAUSE");
	}
}
void Leer_Binario_Vacunas()
{
	ifstream archivoVacunas;
	archivoVacunas.open("C:\\Users\\karla\\source\\repos\\avance\\Vacunas.bin", ios::in | ios::binary);


	if (archivoVacunas.is_open()) {

		Vacunas* Vacunas_leido = new Vacunas;

		while (!archivoVacunas.read((char*)Vacunas_leido, sizeof(Vacunas)).eof()) {

			if (Vacunas_inicio == nullptr) {
				Vacunas_inicio = Vacunas_leido;
				Vacunas_inicio->Vacunas_sig = nullptr;
				Vacunas_inicio->Vacunas_ant = nullptr;
				Vacunas_aux = Vacunas_inicio;
			}
			else {
				Vacunas_aux->Vacunas_sig = Vacunas_leido;
				Vacunas_aux->Vacunas_sig->Vacunas_ant = Vacunas_aux;
				Vacunas_aux = Vacunas_aux->Vacunas_sig;
				Vacunas_aux->Vacunas_sig = nullptr;
				//fin = aux;
			}

			Vacunas_leido = new Vacunas;
		}
		archivoVacunas.close();
		delete Vacunas_leido;
	}
	else {
		system("PAUSE");
	}
}
void Eliminar_Vacunas(char nomVacunas[50]) {
	Vacunas_aux = Vacunas_inicio;

	if (Vacunas_aux == nullptr)
	{
		MessageBox(0, "No hay Vacunases registradas", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (Vacunas_aux != nullptr && strcmp(Vacunas_aux->tipovacuna, nomVacunas) != 0) {

			Vacunas_aux = Vacunas_aux->Vacunas_sig;
		}
		if (Vacunas_aux == nullptr) {
			MessageBox(0, "Vacunas no encontrada", "AVISO", MB_OK);
		}
		else if (Vacunas_aux == Vacunas_inicio) {	//El nodo es el primero 

			if (Vacunas_aux->Vacunas_sig == nullptr) {

				Vacunas_inicio = nullptr;
				delete Vacunas_aux;
				Vacunas_aux = Vacunas_inicio;
			}
			else {
				Vacunas_inicio = Vacunas_inicio->Vacunas_sig;
				Vacunas_aux->Vacunas_sig->Vacunas_ant = nullptr;
				delete Vacunas_aux;
				Vacunas_aux = Vacunas_inicio;

			}

			MessageBox(0, "Vacunas eliminada", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {

			if (Vacunas_aux->Vacunas_sig == nullptr) { //Si el nodo es el último
				Vacunas_aux->Vacunas_ant->Vacunas_sig = nullptr;
				delete Vacunas_aux;
				Vacunas_aux = Vacunas_inicio;
			}
			else {
				Vacunas_aux->Vacunas_sig->Vacunas_ant = Vacunas_aux->Vacunas_ant;
				Vacunas_aux->Vacunas_ant->Vacunas_sig = Vacunas_aux->Vacunas_sig;
				delete Vacunas_aux;
				Vacunas_aux = Vacunas_inicio;
			}

			MessageBox(0, "Promoción eliminada", "AVISO", MB_OK | MB_ICONINFORMATION);

		}
	}

}

