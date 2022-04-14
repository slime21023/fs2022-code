/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"

#include "synchconsole.h"


void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysCreate(char *filename)
{
	// return value
	// 1: success
	// 0: failed
	return kernel->interrupt->CreateFile(filename);
}

int SysOpen(char *filename)
{
	return OpenForReadWrite(filename, false);
}

int SysRead(char *buffer, int size, int fid)
{
	OpenFile *file =  new OpenFile(fid);
	int count = file->Read(buffer, size);
	return (count == size) ? size : -1;
}

int SysWrite(char *buffer, int size, int fid)
{
	OpenFile *file =  new OpenFile(fid);
	int count = file->WriteAt(buffer, size, file->Length());
	return (count == size) ? size : -1;
}

int SysClose(int fid)
{
	return (Close(val) == 0) ? 1 : 0;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
