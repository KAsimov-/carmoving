#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include <Windows.h>
#include "rs232.h"
#pragma warning(disable:4996)
 //ahead atop back turnright turnleft

void ahead(char* name,int cport_nr)
{
  unsigned char buf[50]="\rat+remote=";
  strcat((char*)buf,name);
   strcat((char*)buf,",at+dio=1000001000000\r");
   RS232_SendBuf(cport_nr,(unsigned char*)buf,50);

}
void stop(char* name,int cport_nr)
{
  unsigned char buf[50]="\rat+remote=";
   strcat((char*)buf,name);
  strcat((char*)buf,",at+dio=0000000000000\r");
   RS232_SendBuf(cport_nr,(unsigned char*)buf,50);

}
void back(char* name,int cport_nr)
{
  unsigned char buf[50]="\rat+remote=";
  strcat((char*)buf,name);
  strcat((char*)buf,",at+dio=0100100000000\r");
   RS232_SendBuf(cport_nr,(unsigned char*)buf,50);
}
void turnright(char* name,int cport_nr)
{
  unsigned char buf[50]="\rat+remote=";
  strcat((char*)buf,name);
  strcat((char*)buf,",at+dio=0000001000000\r");
   RS232_SendBuf(cport_nr,(unsigned char*)buf,50);
}
void turnleft(char* name,int cport_nr)
{
  unsigned char buf[50]="\rat+remote=";
  strcat((char*)buf,name);
  strcat((char*)buf,",at+dio=1000000000000\r");
   RS232_SendBuf(cport_nr,(unsigned char*)buf,50);
}
