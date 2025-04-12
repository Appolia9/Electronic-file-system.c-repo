**Electronic file system**\
**struct MUSIC - song**\
Structure for describing a music element with fields:\
int id: element\
ID char* name_of_the_song: song name\
char* performer: artist\
char* name_of_the_album: album name\
int numer_in_top: place in the top of songs\
double profit: profit\
double rating: song rating\
char** feet: array of song co-performers\
struct MUSIC* prev: link to the previous element\
struct MUSIC* next: link to the next element\
\
**struct first_sh – head**\
Head structure of a doubly linked list\
int cnt: number of items in the file cabinet\
song* first: link to the first item in the file cabinet\
song* last: link to the last item in the file cabinet\
\
