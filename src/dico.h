/*un dictionnaire permet de stocker de manière efficace une table 
 clé (char*) -valeur (type T quelconque)*/

#if 0
 
//typedef long char * LPSTR;  // Putain François tu avais oublié la déclaration de ce type de merde !!!!
typedef char * LPSTR;

template <class T> struct TDicoCellule
{
	char ch;
	T* obj;
	TDicoCellule<T> *suite, *autre;

};



template <class T> class CDico
{
private:
	TDicoCellule<T>* rac;

public:
	CDico();
	~CDico();
	void Set(const char* s, T* o); //associe la liste l à son libellé s
	T* Get(const char* s); //renvoit la liste du nom s, si elle n'est pas, renvoit NULL

};


template <class T> TDicoCellule<T>* CreerBrancheDico(const char* s,int i, T* o)
{
	TDicoCellule<T>* Cell = new TDicoCellule<T>;
	
	Cell->ch = s[i];
	Cell->autre = NULL;
	

	if(s[i+1]==0)
	{
		Cell->obj = o;
		Cell->suite = NULL;
	}
	else
	{
		Cell->obj = NULL;
		Cell->suite = CreerBrancheDico<T>(s, i+1, o);

	}

	return Cell;

}


template <class T> CDico<T>::CDico() : rac(NULL) {printf("CDico::CDico()\n");}


template <class T> void CDico<T>::Set(const char* s, T* o)
//parcourt le dictionnaire pour pour rajouter la liste de pts
{
    printf("CDico::Set(%s, %p)\n", s, o);         
	if(rac == NULL)
		rac = CreerBrancheDico<T>(s,0,o);

	else
	{

		int i = 0;

		TDicoCellule<T>* p = rac;

		int ya = 0; //qd ya vaut 1, on a inséré la liste dans le dico et on peut quitter


		while(ya==0)
		{
			if(p->ch == s[i])
			{
				if(s[i+1] == 0) //la case était déjà préparé : (si une liste du ^m nom était déjà rentré, on écrase)
				{
					// CHOISIR !! Politique de remplacement d'objet
					// ON NE DETRUIT PAS L'OBJET
					
					p->obj = o;
					ya = 1;
				}
				else
				{
					i++;
					if(p->suite == NULL)
					{
						p->suite = CreerBrancheDico<T>(s,i,o);
						ya = 1;
					}

					p = p->suite;
				}
			}
			else
			{
				if(p->autre == NULL)
				{
					p->autre = CreerBrancheDico<T>(s,i,o);
					ya = 1;
				}

				p = p->autre;

			}


		}
	}

}



template <class T> T* CDico<T>::Get(const char* s)
/*parcourt dans le dictionnaire pour trouver l'objet de type T
  (il faut qu'elle y soit, sinon renvoit NULL)*/
  
{
    printf("CDico::Get(%s)\n", s);
	int i = 0;

	TDicoCellule<T>* p = rac;
	T* res=NULL;


	while((res==NULL) && (p!=NULL))
	{
		if(p->ch == s[i])
		{
			if(s[i+1] == 0)
				res = p->obj;
			else
			{
				i++;
				p = p->suite;
			}
		}
		else
			p = p->autre;


	}

    if(p == NULL)
         printf("   ERREUR : L'objet de nom %s n'a pas été trouvé dans le dictionnaire.\n", s);
         //rem : si il n'a pas été trouvé, res = NULL...
    
    if(res == NULL)
         printf("    ERREUR : Aucun objet de nom %s n'a été trouvé dans le dictionnaire.\n",s);
	
	printf("    get renvoie l'objet %p.\n", res);
    return res;
	
	

}



template <class T> void detruireDicoCell(TDicoCellule<T>* c)
{
	if(c!=NULL)
	{
		//politique de destruction
		detruireDicoCell<T>(c->suite);
		detruireDicoCell<T>(c->autre);
		delete c;
	}

}


template <class T> CDico<T>::~CDico()
{
    printf("CDico::~CDico()\n");     
	detruireDicoCell<T>(rac);
}



#endif
