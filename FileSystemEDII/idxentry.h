#ifndef IDXENTRY_H
#define IDXENTRY_H


class IdxEntry
{
public:
    IdxEntry();
    void setNombre(char * nom);
    void setNumBloque(int num);
    void setNumEntry(int numE);
    void setCantIdxEntries(int cant);

    char * getNombre();
    int getNumBloque();
    int getNumEntry();
    int getCantIdxEntries();

    char * nombre;
    int numBloque;
    int numEntry;
    int cantIdxEntries;
};

#endif // IDXENTRY_H