
//      $$$$$$\   $$$$$$\  $$$$$$$\      $$$$$$$\                                               $$$$$$\       $$$$$$\                  $$\
//     $$ ___$$\ $$  __$$\ $$  ____|     $$  __$$\                                             $$  __$$\     $$  __$$\                 $$ |
//     \_/   $$ |$$ /  \__|$$ |          $$ |  $$ | $$$$$$\  $$\   $$\  $$$$$$$\      $$$$$$\  $$ /  \__|    $$ /  \__| $$$$$$\   $$$$$$$ | $$$$$$\
//        $$$$$ / $$$$$$$\  $$$$$$$\     $$ |  $$ | \____$$\ $$ |  $$ |$$  _____|    $$  __$$\ $$$$\         $$ |      $$  __$$\ $$  __$$ |$$  __$$\
//       \___$$\ $$  __$$\ \_____$$\     $$ |  $$ | $$$$$$$ |$$ |  $$ |\$$$$$$\      $$ /  $$ |$$  _|        $$ |      $$ /  $$ |$$ /  $$ |$$$$$$$$ |
//     $$\   $$ |$$ /  $$ |$$\   $$      $$ |  $$ |$$  __$$ |$$ |  $$ | \____$$\     $$ |  $$ |$$ |          $$ |  $$\ $$ |  $$ |$$ |  $$ |$$   ____|
//     \$$$$$$  | $$$$$$  |\$$$$$$  |    $$$$$$$  |\$$$$$$$ |\$$$$$$$ |$$$$$$$  |    \$$$$$$  |$$ |          \$$$$$$  |\$$$$$$  |\$$$$$$$ |\$$$$$$$\
//      \______/  \______/  \______/     \_______/  \_______| \____$$ |\_______/      \______/ \__|           \______/  \______/  \_______| \_______|
//                                                             $$\   $$ |
//                                                             \$$$$$$  |
//                                                              \______/
// Author : Saihaj Law
// Date : January 5th
// Project : TOP Simplified Version
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <libproc.h>
#include <Security/Authorization.h>

int main() {
  while (1) {
    // Use "ps" to list the current processes
    char *arguments[] = {"ps", "-ax", NULL};
    FILE *output = NULL;
    OSStatus status = AuthorizationExecuteWithPrivileges(
      NULL, "/bin/ps", kAuthorizationFlagDefaults, arguments, &output);
    if (status != errAuthorizationSuccess) {
      fprintf(stderr, "AuthorizationExecuteWithPrivileges failed: %d\n", status);
      exit(1);
    }

    // Read the output of the "ps" command
    char line[1024];
    while (fgets(line, sizeof(line), output)) {
      printf("%s", line);
    }

    // Sleep for 5 seconds before updating the list
    sleep(5);
  }

  return 0;
}
