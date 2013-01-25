#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

int keyLookupArray[58]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Q','W','E','R','T','Y','U','I','O','P',0,0,0,0,'A','S','D','F','G','H','J','K','L',0,0,0,0,0,'Z','X','C','V','B','N','M',0,0,0,0,0,0,' '};
 
void handler (int sig)
{
  printf ("nexiting...(%d)n", sig);
  exit (0);
}
 
void perror_exit (char *error)
{
  perror (error);
  handler (9);
}
 
int main (int argc, char *argv[])
{
  struct input_event ev[64];
  int fd, rd, value, size = sizeof (struct input_event);
  char name[256] = "Unknown";
  char *device = NULL;
 
  //Setup check
  if (argv[1] == NULL){
    device = "/dev/input/event0";
    }
 
  if ((getuid ()) != 0)
    printf ("You are not root! This may not work...n");
 
  if (argc > 1)
    device = argv[1];
 
  //Open Device
  if ((fd = open (device, O_RDONLY)) == -1)
    printf ("%s is not a vaild device.n", device);
 
  while (1){
      if ((rd = read (fd, ev, size * 64)) < size)
          perror_exit ("read()");
 
      value = ev[0].value;
 
      if (value != ' ' && ev[1].value == 1 && ev[1].type == 1){ // Only read the key press event
    	    printf ("%d", (ev[1].code));
      } else if (ev[1].code == 28 ) {
          printf ("\n");
      }
  }
 
  return 0;
}
