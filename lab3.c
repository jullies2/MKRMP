#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h> // подключаем заголовочный файл библиотеки
int main(){
// Инициализируем DLL
WSADATA wsaData; // объявляем переменную для инициализации библиотеки
WSAStartup(MAKEWORD(2, 2), &wsaData); // инициализируем библиотеку, передаем в
//функцию версию библиотеки и созданную переменную
printf ( "\Init Winsock..." );
if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
{
printf ( "We cant error : %d" ,WSAGetLastError()); // WSAGetLastError()
//возвращает код ошибки инициализации библиотеки
return 1;
}
printf ( "Cool!" );
//Для того, чтоб скомпилировать приложение добавим завершающий штрих
//Объявляем структуру для хранения сокета:
SOCKET s;
//после инициализации библиотеки добавляем:
if ((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
{
printf ( "can't create socket : %d" , WSAGetLastError());
}
printf ( "Good Job! Socket is working now.\n" );
return 0; }