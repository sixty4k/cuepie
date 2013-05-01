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

int mkeycodes[12] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
 
void handler (int sig)
{
  fprintf (stderr, "\nexiting...(%d)\n", sig);
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
    fprintf (stderr, "You are not root! This may not work...\n");
 
  if (argc > 1)
    device = argv[1];
 
  //Open Device
  if ((fd = open (device, O_RDONLY)) == -1)
    fprintf (stderr, "%s is not a vaild device.\n", device);
 
  while (1){
      if ((rd = read (fd, ev, size * 64)) < size)
          perror_exit ("read()");
 
      value = ev[0].value;
 
      if (value != ' ' && ev[1].value == 1 && ev[1].type == 1 ){ // Only read the key press event
  	      if (ev[1].code != 28 ){
              fprintf (stdout, "%d", (mkeycodes[(ev[1].code)]));
          } else  {
              fprintf (stdout, "\n");
              fflush (stdout);
          }
      }
  }
 
  return 0;
}
