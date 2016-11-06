#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// clib deps
#include <serial.h>
#include <commander.h>
#include <color-sh.h>

struct opts {
  const char* port;
  long baud;
};

static void port(command_t *self){
  struct opts *opts = (struct opts *) self->data;
  opts->port = self->arg;
}

static long parse_baud(const char* input){
  long baud = atol(input);
  if (baud > 0){
    return baud;
  }
  color_red("Error: Baud must be a non-zero number\n");
  exit(1);
  return 0;
}

static void baud(command_t *self){
  struct opts *opts = (struct opts *) self->data;
  opts->baud = parse_baud(self->arg);
}

static struct opts get_opts(int argc, const char **argv){
  struct opts o = {.baud=115200, .port = NULL};

  command_t cmd;
  cmd.data = &o;
  int no_more_args = 0;

  command_init(&cmd, argv[0], "0.0.1");

  // add positional arguments
  /*cmd.usage = "[options] <Port> <Baud>";*/
  command_option(&cmd, "-p", "--port <arg>", "Serial port to log", port);
  command_option(&cmd, "-b", "--baud <arg>", "Baud rate of serial port (default: 115200)", baud);
  command_parse(&cmd, argc, (char**)argv);
  
  for (int i = 0; i < cmd.argc; ++i) {
      /*printf("(%s,%ld) - %s\n", o.port, o.baud, cmd.argv[i]);*/
    if (o.port == NULL){
      o.port = strdup(cmd.argv[i]);
    } else if (!no_more_args){
      o.baud = parse_baud(cmd.argv[i]);
    } else {
      color_red("Error: Too many arguments.\n");
      command_help(&cmd);
      exit(1);
    }
  }

  if (o.port == NULL || strlen(o.port) == 0){
    color_red("You must specify a port\n");
    command_help(&cmd);
    exit(1);
  }
  command_free(&cmd);

  return o;
}


int main(int argc, const char **argv){
  struct opts opts = get_opts(argc, argv);

  int sp = serialOpen(opts.port, opts.baud);
  if (sp == -1){
    /*color_red("%s\n", strerror(errno));*/
    exit(1);
  }

  color_yellow("=========== %s at %ld baud ===========\033[0m\n",opts.port, opts.baud);

  char buffer[1024];
  while(1){
    int length = read(sp, buffer, 1024);
    write(1, buffer, length);
  }
}
