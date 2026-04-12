/**
 * Cross-platform compatibility shim for conio.h (Windows) on POSIX systems.
 *
 * Provides getch() using termios on Linux/macOS, and maps system("CLS")
 * to system("clear") on non-Windows platforms.
 */

#ifndef COMPAT_H
#define COMPAT_H

#ifdef _WIN32
  #include <conio.h>
  #define CLEAR_SCREEN() system("cls")
#else
  #include <termios.h>
  #include <unistd.h>
  #include <cstdlib>

  inline int getch() {
      struct termios oldt, newt;
      int ch;
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      ch = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      return ch;
  }

  #define CLEAR_SCREEN() system("clear")
#endif

#endif // COMPAT_H
