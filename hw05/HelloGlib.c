#include <glib.h>
int main(int argc, char** argv) {
 	GString* hello = g_string_new("Hello Glib!");
 	g_printf("%s\n",hello->str);
}