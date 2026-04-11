#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
#define BOLD_RED "\033[1;31m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_CYAN "\033[1;36m"
#define ERROR(msg) printf(BOLD_RED "error: " RESET msg "\n")
#define NOTE(msg)  printf(BOLD_CYAN "note: " RESET msg "\n")
