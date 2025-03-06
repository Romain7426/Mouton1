
FRANCAIS: [README.fra.md](README.fra.md)
GLOBISH: [README.eng.md](README.eng.md)


---------------------------------------------------------------------------

COMMENTAIRE de mars 2025

Ici, il s'agit d'un commentaire en complément de la description ci-dessous (datant de mars 2024).
 - Tout d'abord, j'en ai marre du globish. Je suis français et vous me saoulez. 
 - Ensuite, j'en ai marre du langage [*C*](https://en.wikipedia.org/wiki/C_(programming_language)). 
   À mon avis, le principe du langage C est bon: faire abstraction du processeur sous-jacent, 
   et opérer sur la mémoire. Opérant sur la mémoire, le langage C est appelé le langage de pointeurs.
   De ce fait, le langage C serait un bon intermédiaire entre un langage processeur et un 
   langage utilisateur. D'ailleurs, d'aucuns le considère comme un méta-assembleur.
 - Cependant, l'implémentation actuelle est infâme. (Moins pire que le C++ cependant.) 
 - À propos du C++, rappelons ces propos de son créateur, Bjarne Stroustrup: ["I did it for you all"]([*C*](http://harmful.cat-v.org/software/c++/I_did_it_for_you_all)
 - Un programme ne compile jamais de la même facon. Ca dépend du systeme et de l'année.
   Quelque chose qui compile sur un systeme ne compilera pas sur le voisin.
   Quelque chose qui compilait l'année dernière ne compilera plus cette année.
 - Quand on écrit une erreur, le compilateur essaye de trouver une semantique puis continue. 
   Pour corriger un tel comportement, il faut activer moult options du compilateur. 
 - On a beau lui dire de désactiver les optimisations, le compilateur optimise quand même.
   Et quand on se retrouve dans le débuggueur, celui-ci ne sait pas où on est.
   Et quand on lui demande d'afficher une variable, il répond que il ne la trouve pas. 
 - Et ceci, quand gdb fonctionne. La plupart du temps, gdb plante.
   Et quand il ne plante pas, il n'affiche que des points d'interrogation dans la backtrace. 
   Donc on se retrouve à débugguer en mettant des printf partout. 
 - De fait, les compilateurs C sont des programmes bloated, qui doivent savoir faire le café.
 - Les préprocesseur bizarre. 
 - L'absence de modules!!!!! (collision des noms) (et portée des nom)
 - une libc bizarre
 - libkernelcall (unistd.h) et la libc devrait être séparées. On voudrait pouvoir ne pas utiliser la libc. 
   En revanche, on ne veut pas savoir comment techniquement réalisé un kernel call (int 80? syscall? On s'en fout.) 
   On devrait pouvoir utiliser la libC qui nous plait. 
 - De fait, il existe un concours du code le plus obscur en C. 
 - Les bibliothèques tierces qui ne compilent jamais ("Tient! Cette bibliothèque a l'air de résoudre notre problème." Puis make échoue.). 
 - GitHub est pénible. (Le côté réseau social pour geek est néanmoins sympa.)
    - Il nous casse les couilles avec son token que il fait expirer régulièrement.
    - Et là, ce connard vient de me refuser un commit pour des raisons obscures. 
    - Putain! Même commiter est un putain de problèmes. 
    - Poubelle!
 - Accessoirement, git est bloated et est une usine à gaz. 
   De fait, il existe des générateurs de manpage pour Git: [https://git-man-page-generator.lokaltog.net/](https://git-man-page-generator.lokaltog.net/)
 - Dans les faits, je suis improductif en C. Je perds la quasi-totalité de mon temps 
   en futilités et en points techniques qui n'ont aucun intérêt. Vraiment en putain de conneries. 
   Alors que je devrais programmer le jeu sur un plan projectif! 
   J'en ai putain de marre. Ca me saoule. 
   Tout ça est une perte de temps. 
   Donc j'arrête. Terminé. Je ne veux plus en entendre parler. 
   J'ai le jeu. Il possède une beauté. Mais je ne retouche plus au C.
   Pour ma part, par le passé, le langage où je fus productif fut le Pascal (Turbo/Delphi). 
   J'arrête. 
   Il n'y aura aucune amélioration à l'avenir. Ni aucun correctif.
   J'arrête. 


À toute cette instabilité et ce chaos, je préfère les consoles de jeux:
 - le matériel ne change jamais 
 - le compilateur ne change jamais

Sept ans plus tard, le même programme compile et fonctionne de la même facon!


Ceci étant dit, je suis admiratif de [Fabrice Bellard](http://fr.wikipedia.org/Fabrice_Bellard) qui, lui, arrive à coder C et produire de puissants logiciels: [FFmpag](http://fr.wikipedia.org/FFmpeg), [QEmu](http://fr.wikipedia.org/QEmu), et [TinyCC](http://fr.wikipedia.org/TinyCC). 
 
Nous sommes tous différents.

J'arrête. 


Au lieu de créer, je perdais mon temps empêtré dans des putains de conneries techniques.

Plus jamais.

Je perdis trop de temps de ma vie. Je voulais créer - pas geeker. 


En l'état, le jeu compile à peu près. Et il fonctionne couci-couça. Et surtout, il est lent. Alors que, vingt ans auparavant, pas de souci. 
 
Je déteste tout ça. 

---------------------------------------------------------------------------

VERSION de décembre 2021

---------------------------------------------------------------------------

# *Dessine-moi un mouton!* :relaxed: 

Bonjour tout le monde! :relaxed: 

***Dessine-moi un mouton!*** est un jeu que nous conçûmes pendant notre licence 3. C'était il y a longtemps. (Vingt ans! Et pourtant c'était hier.) 

Nous, les concepteurs, sommes des joueurs de [*The Legend of Zelda*](https://en.wikipedia.org/wiki/The_Legend_of_Zelda) et de [*Secret of Mana*](https://en.wikipedia.org/wiki/Secret_of_Mana). Nous sommes également des mathématiciens, notamment en informatique théorique (laquelle fait partie des mathématiques), ce qui explique que notre jeu soit hors des clous. À ce sujet, un mathématicien en informatique théorique n'est pas ingénieur logiciel. Nous n'eûmes aucun cours de programmation, et surtout de conception de logiciel. Nous apprîmes donc par nous-mêmes, en procédant par [essais et erreurs](https://en.wikipedia.org/wiki/Trial_and_error) (et [backtracking](https://en.wikipedia.org/wiki/Backtracking)); cependant le jeu ne fut pas architecturé. Celui-ci était notre premier projet conséquent, ayant même une équipe d'artistes (!), et nous avions trop d'idées. À la fin de l'année, le jeu était jouable, mais nous avions passés trop de temps dans les détails techniques, au lieu de les passer dans la création. Et le jeu avait de nombreux bugs incompréhensibles. (Et il avait été codé en C++ - un enfer.)
Retrospectivement, le résultat n'est pas si mauvais - j'en suis même fier (dans la mesure où celui-ci serait présentement jouable, ce qui n'est pas le cas). 
Le but était de présente les jeux aux ['InterENS culturelles'](https://interq.ens.fr/) ("Cultural InterENS"), ce que nous fîmes fièrement. À l'époque, nous avions publié le résultat ici (les codes de connexion ont été hémas perdus): <br> 
&nbsp;&nbsp;&nbsp; [http://dessine.moi.mouton.free.fr/](http://dessine.moi.mouton.free.fr/)
 
  
## Auteurs 
 
Auteurss: 
 - [François](https://github.com/francoisschwarzentruber) <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Musiques, moteur du jeu, création des cartes <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://people.irisa.fr/Francois.Schwarzentruber/
 - Ludovic <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; concepteur des objets 3DS <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://goudenege.perso.math.cnrs.fr/output/
 - Pierre <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; concepteur des personnsages <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; https://www.facebook.com/pierre.carcaud?_fb_noscript=1 
 - Mathilde <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; conceptrice des personnages <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://??? 
 - Clément <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; textes <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://??? 
 - [Romain](https://github.com/Romain7426) (moi-même)  <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; langages de Description <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://??? 
  

## Compilation & Installation

<pre>
$ echo "clang" > ./CC        # Ou votre compilateur préféré. 
$ sh ./configure.sh          # Génération des outils puis du Makefile. 
$ make 
$ make install 
</pre>
 
Personnalisations
 - [Compilateur](https://fr.wikipedia.org/wiki/Compilateur) — Le compilateur utilisé par défaut est 'cc'. Vous pouvez utiliser votre compilateur préféré à travers le fichier ['./CC'](CC). 
    - $ echo "cc" > ./CC 
    - $ echo "clang" > ./CC 
    - $ echo "/usr/local/bin/x86_64-unknown-openbsd7.0-gcc-11.2.0" > ./CC 
    - $ echo "pcc -L /usr/lib " > ./CC 
    - $ echo "tcc" > ./CC 
 - Le répertoire d'installation — Par défaut, l'installation se fait dans le sous-répertoire './destroot'. Ensuite, il suffit de copier ce répertoire où vous voulez. 
 - Aucune autre personnalisation. 
 
Configuration
 - La système de onfiguration n'est pas basé sur [GNU Autohell](https://en.wikipedia.org/wiki/Autohell). 
 - À la place, nous avons conçu notre propre système. Celui-ci est basé sur [GNU Make](https://en.wikipedia.org/wiki/GNU_make). 
 - Le [Makefile](https://en.wikipedia.org/wiki/Make_(software)#Makefile) est générer par GMake à partir du fichier ['./Makefile-gen.mkf'](Makefile-gen.mkf). 
 - Le script ['./Makefile-gen.mkf'](Makefile-gen.mkf) nécessite des outils qui doivent être compilés en amont. Ceux-ci sont localisés dans le sous-répertoire ['./tools'](tools). Pour les compiler, il faut lancer le script sell ['./tools-compile.sh'](tools-compile.sh): «sh ./tools-compile.sh» 
 - Et c'est fini. 
 - En une seule étape, il est possible d'utiliser le script [shell](https://en.wikipedia.org/wiki/Bourne_shell) ['./configure.sh'](configure.sh): «sh ./congigure.sh» 
 - Le script shell ['./configure.sh'](configure.sh) aura besoin de savoir comment invoquer GMake: 
    - $ echo "gmake" > GMAKE
 
Testé avec les [compilateurs](https://fr.wikipedia.org/wiki/Compilateur): 
 - [clang](https://fr.wikipedia.org/wiki/Clang) - 2,6Mo 
 - [gcc11](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection) - 5,5Mo
 - [tcc](https://fr.wikipedia.org/wiki/Tiny_C_Compiler) - 37,4 Mo
 - [pcc](https://fr.wikipedia.org/wiki/Portable_C_Compiler) - Echoue. Son préprocesseur meurt. 
 

Testé sur les systèmes suivants: 
 - [OpenBSD](https://en.wikipedia.org/wiki/OpenBSD) 
 - Les autres [BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution) - Pas testé mais ne devrait pas poser de problèmes. 
 - [MacOSX](https://en.wikipedia.org/wiki/MacOS) - Pas testé mais ne devrait pas poser de problèmes. 
 - [Unix](https://en.wikipedia.org/wiki/Unix)-compatible - Pas testé mais ne devrait pas poser de problèmes. 
 - [Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) - Il y a vingt ans, il y fonctionnait. Hui, je ne sais pas. ([Cygwin](https://en.wikipedia.org/wiki/Cygwin)? [MinGW](https://en.wikipedia.org/wiki/MinGW)? Autre?)
 
Dépendances: 
 - Le code source est écrit en [C99](https://en.wikipedia.org/wiki/C99). 
 - [GNU Make](https://fr.wikipedia.org/wiki/GNU_make). 


   
## [Propriété intellectuelle](https://fr.wikipedia.org/wiki/Propriete_intellectuelle) 

On s'en fout. Faites-en ce que vous en voulez. 
 
Ce travail aurait pu être publié dans le [domaine publique](https://en.wikipedia.org/wiki/Public_domain). Cependant, il semblerait que il existe des moyens s'approprier respectivement des droits. Et donc nous désapproprier ce travail. Pour empêcher ce cas, ce travail est publiée sous une version allégée de la [licence ISC](https://en.wikipedia.org/wiki/ISC_license). Vous pouvez consulter [COPYING](COPYING)
 

## Notes techniques

Hui, le jeu compile couci-couça - hélas. Et le jeu est lent (il ne l'était pas il y a vingt ans). 

Aucune aide ne vous sera apporté pour le faire compiler. Pour nous, c'est terminé. Il s'agit d'une publication post-mortem. Le jeu ne sera plus mis à jour ni corrigé. 

Pour compiler, le jeu repose sur les bibliothèques suivantes:
 - [SDL](http://www.libsdl.org)
 - [SDL_image](http://www.libsdl.org/projects/SDL_image/release-1.2.html)
 - [SDL_mixer](http://www.libsdl.org/projects/SDL_mixer/release-1.2.html). If these libraries do not work on your computer, then it just can't work. But that's its only library depencies, so it's not that bad

En sus, SDL_image & SDL_mixer dépendent d'autres librairies: libjpeg, libpng, libvorbis, libogg, etc.
 
Egalement, le jeu a besoin des analyseurs de DSL: 
 - https://github.com/Romain7426/Mouton1-anime 
 - https://github.com/Romain7426/Mouton1-nonanime 
 - https://github.com/Romain7426/Mouton1-carte 
 - https://github.com/Romain7426/Mouton1-pscript 

Pour le moment, le sous-système des objets [3DS objects](https://en.wikipedia.org/wiki/.3ds) fonctionne pour les architectures little-endian. Je ne sais pas pour les autres. 

Aussi, le jeu avait d'abord été écrit en [*C++*](https://fr.wikipedia.org/wiki/C%2B%2B): (i) il compile quoiqu'il arrive; (ii) la sémantique est obscure; (iii) les erreurs de compilation sont hermétiques («Voyons, je je commente ces lignes, peut-être que ça compilera»); (iv) avant de produire une erreur, le compilateur essaye toujours une sémantique); (v) le débogage est impossible; (vi) trèslent à compiler (voir [Turbo Pascal](https://fr.wikipedia.org/wiki/Turbo_Pascal) en comparaison: immédiat); (vii) bien entendu, après quelques années, le jeu cessa de compiler; (viii) aucun compilataur [*C++*](https://en.wikipedia.org/wiki/C%2B%2B) ne se comportent de la même façon. <br> 
De cette expérience, nous réalisons notre second jeu en [*C*](https://en.wikipedia.org/wiki/C_(programming_language)); ce fut bien mieux - nous ne le regreattâmes pas. 

Le fait que le jeu ne fonctionne plus et notre bonne expériene en C fut le point de départ de cette publication: le réécrire en C et faire que il fonctionne et compile. (Ce qui me pris beaucoup trop de temps. Plus jamais.)
 
  
## Architecture 
 
Nous divisâmes le jeu en sous-projet afin de pouvoir travailler en équipe: la description des personnsages, la description des éléments du décoer, la description des cartes, la description des éléments de la narration, et le moteur du jeu. 

 
### Les DSLs spatiales

Pour la descriptions des éléments spatiaux, nous conçûmes des petits et rapides langages de descriptions. 

À propos des DSL, vous pouvez visionner la vidéo: [«Functional MzScheme DSLs in Game Development»](https://www.youtube.com/watch?v=Z8Xamkb-J2k

Nous avons rencontrés les problèmes suivants: 
 - (i) *Lex* & *Yacc* - En pratique, on ne sait jamais si les expressions rgulières sont correctement écrites (dans les faits, il y a toujours des problèmes). Ils sont lents. Ils sont conçus bizarrement. Ils ne sont ni thread-safe ni reentrant. Et la gestion des erreurs de syntaxe est nulle: *yacc* returns "syntax error" et c'est tout. <br> 
       Dans les faits, un analyseur LALR(0) produit par yacc fonctionne bien quand la syntaxe est déjà correcte. Un tel analyseur permet alors de produire un arbre (ou du code) (ou d'interpréter). Mais alors, il faut d'abord vérifier la syntaxe (sans quoi yacc nous dit le laconique "syntax error"). 
 - (ii) *Typage* - En tant que mathématiciens en informatique théorique, on nous parla de [*OCaml*](https://en.wikipedia.org/wiki/OCaml) et de son inférene de type. Je fus influencé par ça. Et j'en présente mes excuses à ceux qui écrivaient les descriptions. En fait, le typage, on s'en fout. Les langages de descriptions ne doivent pas être typés. Ca doit fonctionner, un point c'est tout. <br> 
   
 
 
### Les DSL-s temporelles

Une DSL temporelle décrit les évènements, les interrations, et la narration. 

Dans notre cas, nous réalisâmes rapidement que nous avions besoin d'un langage de script
 - Autant que faire se pouvait, il fallait se séparer le moteur du jeu du reste. Toute la description du jeu devait être séparée. 
 - En l'espèece, il fallait pouvoir décrire les interractions. 
 - En l'espèece, il fallait pouvoir décrire les évènements. 
 - Et surtout, nous voulions pouvoir diriger le jeu comme si c'était un film. Le script dirigeait le moteur de jeu. 
 - Plus encore, afin que le script et le jeu puisse coopérer, il fallait que chacun ait sa propre stack. 
 - Peoblème, un tel langage de description était une tâche énorme. 
 - Le résultat est que le langage fonctionne, mais le code interne est laid. 
 - Pire, comme chacun n'avait pas sa propre stack, pour les faire coopérer, j'ai dû écrire un byte-code. Galère. Mauvais souvenirs. 

Notre langqge de description temporelle s'appelle «PScript» for «Pascal Scripting Language». 

Dans cette réécriture:
 - J'ai effectivement séparé la stack de chacun. Ca a changé la vie. Les interactiosn entre les deux sont beaucoup plus simples. 
 - Dans les faits, ce que nous avons implémentés sont des [threads coopératifs](https://en.wikipedia.org/wiki/Non-preemptive_multitasking) (ou encore des [«co-routines»](https://en.wikipedia.org/wiki/Coroutine), ou encore des[«fibers»](https://en.wikipedia.org/wiki/Fiber_(computer_science)) - [libco](https://byuu.org/projects/libco)). 
 - Ces coop-threads furent bons. Ils permirent de réécrire le jeu, et de le linéariser. Car, auparavant, pour faire coopérer le moteur de jeu et le moteur de jeu, il s'agissait de fonctions imbriquées et mutuellement récursives et de variables globales. C'était incompréhensible. 
 - Une autre conséquence des coop-threads est que le DSL temporel peut être en n'importe quel langage. Et, de fait, en l'espèce, j'ai testé en C. (Ce qui nous aurait permis de ne pas perdre de temps à développer PScript.)
  
  
 
### Eléménts non standards 

Dans l'ensemble, le jeu n'utilise rien de compliquer. Deux exceptions:
 - (a) Les coop-threads - Pour les créer, nous utiliser des signaux. Pour basculer, nous utilisons des long-jmp. 
 - (b) stdlog et stderr
      - Afin de débugger le jeu, nous écrivons verbeusement. Nous avons donc un gros (très gros) fichier de log. Pour l'écrire, nous redirigeâmes stdout vers ce fichier de log. (Techniquement, c'est un reopen.)
      - Problème: le jeu passe beaucoup de temps à écrire ces logs, au point que ça le ralentisse. Nous dûmes donc mettre entre les deux un tampon. Et mettre ce tampon nécessite d'utiliser un pipe et SIGIO (ce qui est pénible). 
      - Pire. Nous écrivions les erreurs sur stderr. Malheureusement, nous avions besoin du contexte au sein des logs. Donc il fallait dupliquer cette écriture vers stdlog. Idem, pour ceci, pipe & SIGIO (pénible). 
      - Dans les fais, il semblerait que, une fois dans un handler suite à signal, le programme ne puisse plus attraper lui-même de nouveaux signaux (sans quoi une attente mutuelle se produit: attente que le précédent handler se termine pour prendre la main). 


### Critiques

J'ai une critique à émettre par rapport à notre organisation: il aurait fallu un unique chef. Notre méthode était trop consensuelle (un comité). Ce qui fait que certaines décisions ne plaisaient à personne. 

Non. Il faut une unique vision. Et implémenter une unique vision. Afin que le jeu ait une cohérence et une personnalité. Un truc mou, consensuel, fade, sans personnalité, est pire. 

Et le fait d'avoir un chef est vrai pour la division du travail: 
 - un unique chef pour la conception du moteur de jeu, 
 - un unique chef pour la eonception des DSL, 
 - un unique chef pour la conception des cartes, 
 - et un unique pour la vision du jeu.


## Agenda
 
Avant toute chose, le jeu est abandonné. Aucune aide ne sera fourni. Et plus aucun développement n'aura lieu. Ni aucun correctif. Malheureusement, le jeu ne fonctionne pas bien (contrairement à il y a vingt ans), mais c'est ainsi. 
 
Les éventuelles choses à faires: 
 - (i) Projeter le jeu sur un plan projectif. 
 - (ii) Réécrire le moteur de jeu. (Plein de fonctions imbriquées et mutuellement récursives.) 
 - (iii) Portabliité.
 - (iv) Nettoyer les DSL. 
 - (v) Faire fonctionner la théière. 
 - (vi) Faire fonctionner la carte de la glace. 
 - (vii) Ecrire des outils de développement (maps design, 3DS, etc.) (en FLTK)
 - (viii) Développer le jeu. 
 - (ix) Ajouter un type 'world' (la variété riemannienne, et le nombre de cartes sur icelle). 
 - (x) Ajouter [GLFW](http://fr.wikipedia.org/GLFW). 
 - (xi) Ajouter [TinyGL](http://bellarg.org/TinyGL).
 - (xii) Ajouter [Small3Dlib](https://gitlab.com/drummyfish/small3dlib).
 - (xiii) Ajouter Mesa pour avoir un OpenGL purement software (ce qui permettrait de faire des captures d'écran). 
 - (xiv) Ajouter FFmpeg (ce qui permettrait d'afficher des vidés (ce qui était initialement prévu) et d'enregistrer une partie). 
 - (xv) Ajouter un mode VESA. (Voire le faire fonctionner sous DosBox tel Theme Hospital.)
 - (xvi) Porter le jeu sur WebGL. 
 - (xvii) Porter le jeu sur Nintendo 64. 
 - (xviii) Porter le jeu [RetroArch](http://fr.wikipedia.org/RetroArch). 
 - (xix) Pouvoir redimensionner le jeu. (Par exemple, 960x720. Hui, il ne supporte que le 800x600.)
 - (xx) En fait, le jeu devrait être entièrement écrit en DSL. Et le deux aurait deux parties: le code qui précède la DSL, et le code qui suit la DSL. 
          Le moteur et la bibliothèque. 
          Le code qui suit la DSL serait une bibliothèque fournie à la DSL (donc ffi) pour réaliser ses opérations. Par exemple,
          bonhomme.c est une bibliothèque pour la DSL. 
          La partie créative elle-même devrait être en DSL. 
          Par exemple, pour la page de titre, on pourrait avoir quelque chose comme:
             begin
               mode2D();
               image_de_fonds("mouton.png");
               menu := menu(/*pos_x en %*/40, /*y*/40, /*largeur en %*/66.6);
               menu -> ajouter("Jeu rapide");
	       menu -> ajouter("Mode histoire");
               menu -> ajouter("Restaurer une sauvegarde");
               menu -> afficher();
             end
 - (xxi) Pour continuer cette idée, en sus, les FFI de la bibliothèques appelées ne devraient pas être appelées mais empilées sur une pile FIFO
           et ensuite être exécutée par le moteur du jeu. 
 - (xxii) Idéalement, pour éviter tous ces problèmes insupportables dus au C, il serait bon de développer un langage spécifique 
         pour le moteur de jeu. Ainsi, seul ce langage serait écrit en C, et devrait supporter les affres et les instablités du C. 
 - (xxxiii) Se débarrasser de GitHub.
 - (xxiv) Pour publier des versions compilées, les mettre dans une img en fat32. (À défaut de les monter, ils sont extractibles par 7z.) (Hélas, pas par bsdtar.)  


Ceci étant dit, rien de tout ça ne sera développé. C'est fini. 

 
Merci!! :smile: 

Et nous vous aimons tous. :kissing_heart: 
