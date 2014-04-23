#include <glib.h>
#include <glib/giochannel.h>

typedef struct Count_s
{
	int val;	
}Count;

typedef struct Pair_s
{
	gchar * key;
	Count * val;
}Pair;

GSequence * seq;

//Compares two Pairs in the sequence allowing it to be sorted
gint cmp_func(Pair* a, Pair* b, gpointer user_data){
	return a->val->val - b->val->val;
}

//Function that takes a hash table entry and adds it to seq in a sorted order
void hash_func(gchar * key, Count * value, gpointer user_data){
	Pair * pair = (Pair *)g_malloc(sizeof(Pair));
	pair->key = key;
	pair->val = value;
	g_sequence_insert_sorted(seq,pair,(GCompareDataFunc)cmp_func,NULL);
	
}

//Fuction that prints each Pair in seq
void print_func(Pair * pair, gpointer user_data){
	g_printf("%s <-> %i\n", pair->key, pair->val->val);
}

//Removes all punctuation and returns the stripped string
gchar* punct_strip(gchar *to_strip){
	char *s = g_strdup(to_strip);
	int i;

	for (i = 0; s[i]; i++){
		if(g_ascii_ispunct(s[i])){
			g_stpcpy(&s[i],&s[i+1]);
			i--;
		}
	}
	return s;
}

int main(int argc, char** argv) {

	if (!g_file_test("TheSnowball", G_FILE_TEST_EXISTS)) {
	  g_print("file not found\n");
	} else {
	  g_print("file found\n");   
	}

	GError *error = NULL;
 	GIOChannel *channel = g_io_channel_new_file ("TheSnowball","r",&error);

 	gchar *line = NULL;
 	GHashTable *table = g_hash_table_new(g_str_hash,g_str_equal);

 	//Reads each line, splits into words, adds each word to hash table as needed
 	while(g_io_channel_read_line (channel, &line, NULL, NULL, &error) && line){
 		gchar **strings = g_strsplit(line," ",0);
 		int i;
 		char *s;
 		for(i=0; strings[i]; i++){
 			s = punct_strip(g_strstrip(strings[i]));
 			if(g_strcmp0(s,"")){
	 			if(g_hash_table_contains(table,s)){
	 				Count *current = (Count *)g_hash_table_lookup(table,s);
	 				current->val += 1;
	 				g_hash_table_insert(table,g_strdup(s),current);
	 			}else{
	 				Count *new_count = (Count*) g_malloc(sizeof(Count));
	 				new_count->val = 1;
	 				g_hash_table_insert(table,g_strdup(s),new_count);
	 			}
	 		}
 		}
 	}

 	seq = g_sequence_new(NULL);
 	//Add every hash to seq as a struct Pair
 	g_hash_table_foreach(table,(GHFunc)hash_func,NULL);
 	//Prints all sorted Pairs in seq
 	g_sequence_foreach(seq,(GFunc)print_func,NULL);

 }

