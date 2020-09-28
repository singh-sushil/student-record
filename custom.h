/*for implementation of getch() function on linux platform*/
#ifndef CUSTOM_HEADER_H
#define CUSTOM_HEADER_H
struct termios termios_p, termios_p1, p;
void normalizeTerminal()
{
    tcgetattr(STDIN_FILENO, &termios_p);
    termios_p1 = termios_p;
    termios_p.c_lflag &= ~(ICANON | ECHO);
    termios_p.c_cc[VMIN] = 1;
    termios_p.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}
void denormalizeTerminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_p1);
}
char getch(){
    normalizeTerminal();
    char ch =  getchar();
    denormalizeTerminal();
    return ch;
}
#endif