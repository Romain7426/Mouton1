{ Le langage ne connait le truc program ou unit ou debut.
Normal cela ne sert � rien.
S'il est mis, cela fera une erreur de parsing.}
{program pascal_ocaml_test;}


{ Ensuite, comme d'habitude, il y a un fichier de sortie de l'analyse lexicale. }
{ S'y rapporter en cas de soucis. }


{
Le langage est tr�s proche du pascal dans la forme.
N�anmoins, il est beaucoup plus typ�, dont on a pris l'exemple sur OCaml
( =, <, etc., polymorphe, mais pas +, +., etc.).
Aussi, pour les idents, on a pris l'exemple de Scheme,
qui reconnait vraiment un nombre impressionnant de machin.
Pour �tre s�r que nous reconnaissons tout bien,
on ne reconnait pas autant de chose, mais on reconnait n'importe quoi comme ident.
En fait, une erreur de lexing est impossible.
Par contre une erreur de parsing l'est tr�s nettement moins.
}

{
Un fichier Pascal OCaml Script de ZEmacs|Zeldacs,
est une suite de d�clarations :
des constantes,
des types,
des variables,
des proc�dures,
et des fonctions.
Par d�faut (seul mode), tous les �l�ments d'un fichier sont accessible de l'ext�rieur.
Le fichier est comme un module.
Seules les variables locales ne seront pas accessibles de l'ext�rieur.
}

{
Regardez c beau !
}

const
   N = 90;
   M = 3 * N + 2;
     
type
   TypeElement = integer;
   liste       = ^cellule;
   cellule     = record
		    contenu : TypeElement;
		    suivant : liste;
		 end;	    
   waza	       = array[1..N] of liste;
		 

procedure raz(var l : liste);
begin
   l := nil
end; { raz }


var l:liste;
function mp(a:TypeElement; l:liste):liste;
 var p:liste;
begin
   new(p);
   p^.contenu := a;
   p^.suivant := l;
   mp := p
end; { mp }

