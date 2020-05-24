type CMouton1 = Record end; 
type CBonhomme = Record nom : string; end; 
type CObjNonAnime = Record nom : string; end; 
type CCamera = Record end; 

var mouton1 : CMouton1; 
var Camera : CCamera; 
var heros : CBonhomme; 

begin 
   heros.nom := "heros"; 
end; 


const alpha = "terrer";

const bas = 1;
      droite = 2;
      haut = 3;
      gauche = 4;

const relatif = 1;
      absolu = 2;


var Perso:string;
var nom_boss : string;
var nom_chaman :  string;
var pere_est_vivant : boolean;
var a_la_potion : boolean;
var a_vu_son_pere_mort : boolean;
var a_tue_boss: boolean;
var chaman_la: boolean;

begin
   nom_chaman := "Chaman";
   nom_boss := "Chouchou";
   Perso := "Occiseur-de-dragons"; //"Vladimir"; 
   pere_est_vivant := true;
   a_la_potion := false;
   a_vu_son_pere_mort := false;
   a_tue_boss := false;
   chaman_la := true;
end





procedure village_chargement();
begin

   //writeln('village_chargement'); 
   
   if a_tue_boss then 
   begin 
	 //{on prépare la fête}
      AjouterAnime("y", "y.anime");
      AjouterAnime("m", "m.anime");
      AjouterAnime("c", "c.anime");
      AjouterAnime("a", "a.anime");
      Camera -> solidariser();
      Camera -> Defaut();
   end;

end;


var y, m, c, a: CBonhomme; 
begin 
   y.nom := "y"; 
   m.nom := "m"; 
   c.nom := "c"; 
   a.nom := "a"; 
end; 

procedure ymca();
var i :  integer; 
begin
   //{on fait la fête}
   musique("ymca.mid");
   
   y -> setposition(15.0, 6.0, 1);
   m -> setposition(16.0, 6.0, 1);
   c -> setposition(17.0, 6.0, 1);
   a -> setposition(18.0, 6.0, 1);
   
   y -> setorientation(bas);
   m -> setorientation(bas);
   c -> setorientation(bas);
   a -> setorientation(bas);
   
   for i := 1 to 3 do
   begin
      y -> deplacer(0.0, -. 2.0, relatif);
      WaitFor(y);
      m -> deplacer(0.0, -. 2.0, relatif);
      WaitFor(m);
      c -> deplacer(0.0, -. 2.0, relatif);
      WaitFor(c);
      a -> deplacer(0.0, -. 2.0, relatif);
      WaitFor(a);
      
      Wait(50);
      
      y -> deplacer(0.0, 2.0, relatif);
      WaitFor(y);
      m -> deplacer(0.0, 2.0, relatif);
      WaitFor(m);
      c -> deplacer(0.0, 2.0, relatif);
      WaitFor(c);
      a -> deplacer(0.0, 2.0, relatif);
      WaitFor(a);
   end;

end;


procedure village_entree_carte();
  var i:integer;
begin
   //writeln('village_entree_carte'); 
   if a_tue_boss then ymca();
end;



procedure laver_table();
begin
  writeln('Oui, dans tes rêves, je lave des tables.')
end;


procedure prendre_avion();
begin

end;


var homme_g, homme_d, homme_rien, chaman, pere : CBonhomme; 
var bob, juliette, brigitte, prokofiev, pierre, squelette :  CBonhomme; 
var boss     : CBonhomme; 
var cercueil : CObjNonAnime; 

begin
   homme_g.nom := "homme_g"; 
   homme_d.nom := "homme_d"; 
   homme_rien.nom := "homme_rien"; 
   chaman.nom := "chaman"; 
   pere.nom := "pere"; 
   bob.nom:="bob"; 
   pierre.nom:="pierre"; 
   juliette.nom:="juliette"; 
   squelette.nom := "squelette"; 
   brigitte.nom:="brigitte"; 
   prokofiev.nom:="prokofiev"; 
   cercueil.nom:= "cercueil";
   boss.nom:= "boss";
end; 

procedure prendre_clef(); 
var i :  integer; 
begin 
   Writeln(Perso, " : Cool !! J'ai gagné une clef !!"); 
   Wait(5); 
   Camera->defaut(); 
   Camera->Zoom(0.75);
   
   Musique("secte.mid"); 
   
   AjouterAnime("homme_g"   , "homme_bizarre.anime"); 
   AjouterAnime("homme_d"   , "homme_bizarre.anime"); 
   AjouterAnime("homme_rien", "homme_bizarre.anime"); 
   
   homme_g    -> setposition(20.0, 15.0, 2); 
   homme_rien -> setposition(21.0, 15.0, 2); 
   homme_d    -> setposition(22.0, 15.0, 2); 
   
   homme_g    -> deplacer(20.0, 17.0, 2); 
   homme_rien -> deplacer(21.0, 17.0, 2); 
   homme_d    -> deplacer(22.0, 17.0, 2); 
   
   Waitfor(homme_g); 
   
   Writeln("Homme de droite : Polisson !!");

   heros -> deplacer(21.2, 18.2, 2); 
   Waitfor(heros); 
   heros -> deplacer(21.2, 17.9, 2); 
   Waitfor(heros); 
   
   Writeln("Homme de gauche : Sacripan !!");
   Writeln("Homme de rien : Rends nous les clefs de la cuisine !! On a faim !!");
   Writeln("Homme de droite : Ah oui c'est vrai... d'ailleurs... ");
   Writeln("Homme de gauche : voici ici de la viande fraaaîiche !!!");
   Writeln("Homme de droite : Je dirai même plus : de la viande fraîche !!!");
   Writeln("Homme de rien : Mais pas pour nous !!!! Elle l'est pour ", nom_boss, "...");
   
   heros -> deplacer(15.0, 20.0, 2);
   Waitfor(heros); 
   
   carte("niveau1_2.carte", 15.0, 20.0, 1);
   heros -> setpositionz(15.0, 20.0, 200.0, 2); 
   Wait(1); 
   for i := 0 to 10 do 
   begin 
      heros -> setpositionz(0.0, 0.0, -. 3.0, 1); 
      Wait(1); 
   end; 
   
   carte("niveau1_1.carte", 15.0, 25.0, 1);
   heros -> setpositionz(15.0, 25.0, 200.0, 2);
   Wait(1); 
   for i := 0 to 10 do
   begin
      heros -> setpositionz(0.0, 0.0, -. 3.0, 1);
      Wait(1);
   end;
   
   carte("niveau1_0.carte", 6.0, 6.0, 1);
   Musique("");
   AjouterAnime("boss", "dinotore.anime");
   //{  AjouterAnime(chaman, "chaman.nonanime"); }
   boss -> SetPosition(6.0, 10.0, 2);
   //{ chaman -> SetPosition(8.0, 10.0, 2);}
   
   heros -> setpositionz(6.0, 6.0, 200.0, 2);
   Wait(1); 
   for i := 0 to 10 do
   begin
      heros -> setpositionz(0.0, 0.0, -. 4.0, 1);
      Wait(1);
   end;
   
   Writeln(nom_boss, " : Tiens, tiens, mais qui voilà? Ah, tu dois être l'élu! Ecoute-moi! Il est encore temps de choisir la gloire; tu peux encore abandonner ta condition de misère et rallier notre cause.");
   Writeln(Perso, " : Tu veux dire abandonner mes amis, trahir mon père, faire le mal, répandre la terreur de par le monde, semer la panique, et tout et tout?");
   Writeln(nom_boss, " : Ouais!");
   Writeln(Perso, " : Ok.");
   Writeln(nom_boss, " : Bien joué petit, tu as fait le bon choix!");
   Writeln(Perso, " : Non mais je rêve, t'y as cru ?! HAHA, vilaine bête, viens par ici que je te botte les fesses pour venger la mort de mon père.");
   
   Musique("boss.mid");
   
   
end; 
  
procedure prendre_clef__X();
var i :  integer; 
begin
   //{chaman -> SupprimerObjet();}
  
end;




procedure faire_le_lit();
begin
  Writeln(Perso, " : Faire le lit !!");
  Writeln(Perso, " : FAIRE LE LIT !!");
  Writeln(Perso, " : Nan, mais je rêve... j'ai vraiment des idées bizarres des fois !!");
end;

procedure dormir_sur_lit();
begin
  Writeln(Perso, " : Dormir...");
  Writeln(Perso, " : Ch'suis pas Garfield.");
  Writeln(Perso, " : Et puis j'ai carrément pas que ça à faire.");
end;


procedure s_asseoir_chaise();
begin
  Writeln(Perso, " : Non, vraiment...");
  Writeln(Perso, " : Merci.");
end;

procedure prier();
begin
  Writeln(Perso, " : Je vous salue Thanatonautes...");
  Musique("prier.mid");
end;

procedure lire_inscription();
begin
   Writeln(Perso, " : Euh... Alors... il y a écrit...");
   Writeln(Perso, " : Nan mais en fait je sais pas lire.");
end;




procedure tue_boss();
//var b : -1..1;
//    c : -1..1;
//    d : -1..1;
var b,c,d : integer; 
begin 
   a_tue_boss := true;
   musique("gagne.mid");
   Wait(50);
   Writeln("Tu viens de tuer : LE DINOTORE !");
   Wait(50);
   AjouterAnime(chaman, "chaman.anime");
   chaman -> setposition(2.0, 10.0, 2);
   Writeln(nom_chaman, " : Waouh !!! Je te félicite !! Tu m'impressiones beaucoup.");
   
   heros -> deplacer(3.0, 10.0, 2);
   WaitFor(heros);
   
   Writeln(nom_chaman, " : J'ai appris ce qui est arrivé à ton père. De tels accidents n'arrivent pas souvent c'est terrible.");
   Writeln(Perso, "	 : Oui mais le dino a payé le prix fort.");
   Writeln(nom_chaman, " : Mais dis-moi, si tu t'occupais plutôt un peu de moi, maintenant! Je ne me sens pas très bien.");
   b := Menu("Tu n'aurais pas un petit remontant pour moi?")
	begin
	   item("Si bien sur, j'ai encore votre potion.");
	   item("Ah non, désolé.");
        end;
   
   if b == 1 then
     begin
       c := Menu("t'es sûr?") 
	   begin
	      item("Ah si, j'y pense, j'ai encore votre potion.");
	      item('Non, je ne vois pas.');
           end; 
	
       if c == 1 then 
         begin
           d := Menu("Allez, fais pas ton chacal !")
              begin
                 item("Ah si, j'y pense ! J'ai encore votre potion.");
		 item("Tu crois que je vais te payer un coup comme ça ? Tu rêves, allez dégage.");
              end;
	    
           if d == 1 then 
	      Writeln("WIN"); 
           else 
	     begin 
               Writeln("GAME OVER");
	       Writeln("Mais non, j'rigole le jeu n'est pas fini...");
               Writeln("...enfin si...");
	     end;
         end
       else 
        begin 
	  writeln("WIN"); 
	end;
     end
   else  
     begin 
       Writeln("WIN") 
     end;
   
   
   if false then 
   begin 
   Writeln("Comme tu as gagné, tu peux aller faire un tour en avion avec Saint-Exupéry !!");
   musique("avion.mid");
   carte("tore.carte", 10.0, 10.0, 2);
   end 
   else 
   begin 
      pere_est_vivant := false;
      a_la_potion := true;
      chaman_la := false;
      a_tue_boss := true;       
      carte("foret.carte", 50.0, 60.0, 1);
      writeln("Va au village!! Une surprise t'attendra...");
   end; 
   
   
end;




procedure conversation();
begin
//{  ******* Chez moi, mon papa est avec des méchants ********************************** Toute une cinématique à faire là }
    
   carte("chezmoi.carte", 6.0, 1.0, 1);
   Camera->Rotate(90.0,-. 10.0,0.0,absolu);
   AjouterAnime(homme_g, "homme_bizarre.anime");
   AjouterAnime(homme_d, "homme_bizarre.anime");
   AjouterAnime(homme_rien, "homme_bizarre.anime");
   AjouterAnime(pere,"heros.anime");
   
   homme_g -> SetPosition(2.0, 4.0, 2);
   homme_d -> SetPosition(9.0, 4.0, 2);
   homme_rien -> SetPosition (6.0, 6.0, 2);
   pere -> SetPosition (8.0, 5.0, 2);
   
   writeln("Homme de droite : On ne te le répétera pas deux fois... Tu sous-estimes les bénéfices de notre entreprise.");
   writeln("Homme de gauche : Camarade, si tu collabores pas, Isidore souffrira avec toi...");
end;

procedure conversationbis();
begin
//{  ******* Chez moi, mon papa est avec des méchants. On a refait une aute procédure car ça plantait!!!!}
    
   carte("chezmoi.carte", 6.0, 1.0, 1);
   Camera->Rotate(90.0,-. 10.0,0.0,absolu);
   AjouterAnime(homme_g, "homme_bizarre.anime");
   AjouterAnime(homme_d, "homme_bizarre.anime");
   AjouterAnime(homme_rien, "homme_bizarre.anime");
   AjouterAnime(pere,"heros.anime");
   
   homme_g -> SetPosition(2.0, 4.0, 2);
   homme_d -> SetPosition(9.0, 4.0, 2);
   homme_rien -> SetPosition (6.0, 6.0, 2);
   pere -> SetPosition (8.0, 5.0, 2);
   
   writeln("Homme de droite : On ne te le répétera pas deux fois... Tu sous-estimes les bénéfices de notre entreprise.");
   writeln("Homme de gauche : Camarade, si tu colabores pas, Isidore souffrira avec toi...");
end;

procedure chaman_donne_potion();
begin
   Camera->defaut();
   AjouterAnime(chaman, "chaman.anime");
   chaman -> setposition(52.0, 8.0, 2);
   heros -> deplacer(54.0, 8.0, 2);
   WaitFor(heros);
   
   writeln(Perso , ":  Chaman ! Chaman ! Mon père souffre, il me faut une potion.");
   writeln("chaman : Où sont localisées ses douleurs ?"); 
   writeln(Perso, " : Elles sont abdominales.");
   writeln("chaman : Comment sont elles ?");
   writeln(Perso, " : Elles sont abominables. la potion coûtera chère ?");
   writeln("chaman : Oh les potions sont abordables.");
   writeln("chaman : Mais ton père est un bon ami.");
   writeln("chaman : Vous êtes adorables.");
   writeln("chaman : Je vous file gratuitement cette potion abordable et admirable pour douleurs abdominales abominables.");
   writeln(Perso, " : Je vous en suis redevable.");
   a_la_potion := true;

   heros -> deplacer(60.0, 8.0, 2);
   Wait(50);
   
   pere_est_vivant := false;
   carte("village.carte", 16.0, 2.0, 2);
   
   bob -> setposition(14.0, 5.0, 2);
   juliette -> setposition(18.0, 5.0, 2);
   brigitte -> setposition(16.0, 6.0, 2);
   prokofiev -> setposition(15.0, 3.0, 2);
   Musique("excites.mid");
   
   writeln("Prokofiev : J'ai une nouvelle grave à t'annoncer...");
   writeln("Bob : Ton padre a passé l'arme à droite...enfin à gauche quoi ! ...");
   writeln("Bob : Tu vois ce que je veux dire quoi !");
   writeln("Bob : Ouais, enfin, you know what I mean quoi ! In english QUOI !");
   writeln("Brigitte : Je suis triste (enfin un peu).");
   writeln("Brigitte (à elle même) : Qu'est ce qu'il est relou ce type.");
   writeln("Juliette : Snif. Tu saurais pas où est Roméo ?");
   writeln(Perso, " : ..");
   writeln(Perso, " : ...");
   writeln(Perso, " : ....");
   Camera -> Desolidariser();
   heros -> Deplacer(16.0, 31.0, 2);
   writeln(Perso, " : NOOOOOOONNNNNNNNNN...");
   
   //{enterrement}
   carte("cimetiere.carte", 8.0, 1.0, 2);
   Camera -> Solidariser();
   Musique("prier.mid");
	
   //{ heros -> SupprimerObjet();}
    
   AjouterAnime(juliette, "juliette.anime");
   AjouterAnime(prokofiev, "prokofiev.anime");
   AjouterNonAnime("cercueil", "cercueil.nonanime");
   
   cercueil -> setposition (8.0, 4.0, 2);
   
   juliette -> setposition(7.0, 3.0, 2);
   prokofiev -> setposition(9.0, 3.0, 2);
   
   Camera -> Setposition(8.0, 5.0, 3.0, 2);
   Camera -> Rotate(45.0, 0.0, 0.0, relatif);
   juliette -> deplacer(7.0, 10.0, 1);
   prokofiev -> deplacer(9.0, 10.0, 1);
   
   WaitFor(juliette);
   
   Camera -> Defaut();
   //{il est chez lui, il se morfond près de son lit...}
   Camera -> Solidariser();
   
   Musique("");
   carte("", 6.0, 13.0, 2);
   Writeln("C'était... l'enterrement...");
   carte("chezmoi.carte", 6.0, 13.0, 2);
   Wait(100);
   
   writeln(Perso, " : c'est surement ce qui s'est passé hier soir ... il faut que tu te souviennes ...");
   //{rem : tout est fait dans conversation, en particulier le chgt de carte}
   Musique("glace.mid");
   conversationbis();
   Musique("");
   Camera -> Defaut();
   carte("chezmoi.carte", 6.0, 13.0, 2);
   writeln(Perso, " : Isidore .... Isisdore... mais oui bien sur! ce ne peut-être que le chaman, je dois aller lui parler");
   
end;



procedure chaman_enlevement();
  var i:integer;
begin
   musique("boss.mid");
   
   Camera->defaut();   
   AjouterAnime(chaman, "chaman.anime");
   AjouterAnime(homme_g, "homme_bizarre.anime");
   AjouterAnime(homme_d, "homme_bizarre.anime");
   AjouterAnime(homme_rien, "homme_bizarre.anime");
   
   
   chaman -> setposition(51.0, 8.0, 2);
   homme_g -> setposition(50.0, 8.0, 2);
   homme_g -> setorientation(1);
   homme_d -> setposition(51.0, 7.0, 2);
   homme_d -> setorientation(3);
   homme_rien -> setposition(52.0, 9.0, 2);
   homme_rien -> setorientation(1);
   
   writeln("Chef : Emparez-vous de lui... Plus vite que ça.");
   writeln("Chaman : Ah Lachez-moi cruels.");
   writeln("Le deuxième : Je n'arrive pas à attraper sa jambe gauche.");
   writeln("Gros bras : Coupons-la et laissons-la ici !");
   writeln("Le deuxième : Attends ! Je l'ai !");
   writeln("Chaman : Attendez, vous allez tâter de mon sceptre, vauriens... Merde mon bâton !");
   writeln("Gros bras : Allez viens par ici le vieux !");
   writeln("Chaman : Tiens prends ça misérable : Vigardium leviosa ! Coupdegenum burnas !");
   writeln("Le deuxième : Aie mes...");
   
   
   heros -> deplacer(62.0, 8.0, 2);
   camera -> desolidariser();
   camera -> setposition(56.0, 8.0, 0.0, 2);
   for i := 0 to 400 do
   begin
      chaman -> frapper(); 
      homme_g -> frapper();
      homme_d -> frapper();
      homme_rien -> frapper();
      chaman -> setorientation(1);
      //{chaman -> setorientation((i mod 4) + 1);}
      camera -> setposition(-. 0.02, 0.0, 0.0, 1);
      camera -> rotate(0.6, 0.0, 0.0, relatif);
      Wait(1);
   end;
   writeln("Gros bras : Eh Papy prends ça dans ta gueule !");
   for i := 0 to 100 do
   begin
      homme_g -> frapper();
      homme_d -> frapper();
      homme_rien -> frapper();
      chaman -> setorientation(1);
      //{chaman -> setorientation((i mod 4) + 1);}
      camera -> setposition(-. 0.02, 0.0, 0.0, 1);
      camera -> rotate(0.6, 0.0, 0.0, relatif);
      Wait(1);
   end;
   
   writeln("Chef : C'est bon on le tient. On l'embarque, les gars");
   WaitFor(heros);
   
   
   Camera->Setposition(51.0, 8.0, 0.0, 2);
   Camera->Zoom(2.0);
   Wait(50);
   Camera->Zoom(1.0);
   Camera->Solidariser();
   Camera->Zoom(2.0);
   Wait(50);
   Camera->Zoom(1.0);
   Camera->DeSolidariser();
   Camera->Setposition(51.0, 8.0, 0.0, 2);
   Wait(50);
   musique("enl.mid");
   chaman -> setorientation(2);
   homme_g -> deplacer(30.0, 8.0, 2);
   homme_d -> deplacer(32.0, 6.0, 2);
   homme_rien -> deplacer(32.0, 10.0, 2);

   for i := 0 to 100 do
   begin
      chaman -> setposition(-. 0.1, 0.0, 1);
      Wait(1);
   end;
   
   Wait(20);
   camera -> defaut();
   camera -> solidariser();
   chaman -> SupprimerObjet();
   homme_g -> SupprimerObjet();
   homme_d -> SupprimerObjet();
   homme_rien -> SupprimerObjet();
   
   chaman_la := false;
   

end;

procedure chaman_entree_carte();
begin
   if pere_est_vivant then
      chaman_donne_potion(); 
   else
     begin 
       if chaman_la then
         chaman_enlevement(); 
     end; 
end;


procedure CameraDemiTourPos();
   var i:integer;
begin
   for i := 0 to 90 do
   begin
      Camera->Rotate(-. 1.0,0.0,0.0,relatif);
      Wait(1);
   end;
end;


procedure CameraDemiTourNeg();
var i:integer;
begin
   for i := 0 to 90 do
   begin
      Camera->Rotate(1.0,0.0,0.0,relatif);
      Wait(1);
   end;
end;

const original = true;
   
procedure debut_donut();
  var i:integer;
begin
   //{Début du jeu : dehors ***********************************************************************************}
   writeln("Oh... tiens un donut...");
   writeln("C'est bon les donuts...");
   writeln("Approchons-nous...");
   writeln("Voilà un village...");
   writeln("(interruption)");
   writeln("Comme tout bon jeu de rôle, je vais te demander ton nom.");

   if original then
      readln(Perso);
   else
      Perso := "Vladimir"; 
   
   
   writeln("Hello ", Perso,"!", newline, newline, "Le jeu commence par une cinématique...");
end; 

procedure debut_cinematique();
  var i:integer;
begin
   carte("village.carte", 19.0, 11.0, 1); 
   Camera -> Desolidariser(); 
   Camera -> SetPosition(15.0, 20.0, 10.0, absolu); 
   Camera -> Rotate(180.0, -. 10.0, 0.0, absolu); 
   //{Camera -> Rotate(10.0, -. 0.0, 0.0, relatif);} 
   Camera -> Zoom(4.0); 
   //{writeln("Fuck 1");} 
   
   //writeln("Fuck 2"); 
   //writeln("Nom de la carte chargée: '", nomcarte(), "'"); 
   //writeln("Fuck 3"); 
end; 
   
procedure debut_drague();
  var i:integer;
begin
   Musique("amour.mid");
   
   bob -> SupprimerObjet();
   pierre -> SupprimerObjet();
   prokofiev -> SupprimerObjet();
   squelette -> SupprimerObjet();
   juliette -> SupprimerObjet();
   
   brigitte -> SetPosition(19.0, 12.0, 2);
   brigitte -> SetOrientation(1);
   heros -> SetOrientation(3);
   

   if original then
      for i := 0 to (15-5)*20 do
      begin
         Camera -> SetPosition(-. 0.05, 0.0 ,0.0, relatif);
         Wait(1);
      end;
   else
      for i := 0 to 50 do
      begin
         Camera -> SetPosition(-. 0.2, 0.0 ,0.0, relatif);
      end;

   CameraDemiTourNeg();
   
   for i := 0 to (20-15)*20 do
   begin
      Camera -> SetPosition(0.0, -. 0.05 ,0.0, relatif);
      Wait(1);
   end;
   
   CameraDemiTourNeg();
   
   //{8, 15}
   for i := 0 to (17-5)*20 do
   begin
      Camera -> SetPosition(0.05, 0.0 ,0.0, relatif);
      Wait(1);
   end;

   Writeln(Perso, " : Salut Brigitte. Ah, tu vois, aimer c'est ce qu'il y a de plus beau et tu sais");
   Writeln(", je ferai n'importe quoi, pour un flirt  avec ... une fille comme toi.");
   Writeln("Pour une fille que j'aime, comme un fou, comme un soldat, comme une star de cinéma.");
   Writeln("Brigitte : A d'autres, je ne suis pas une LOLITA!");
   
   CameraDemiTourPos();

   Writeln(Perso, " : Si tu ne m'aimes pas je t'aime et si je t'aime alors prends garde à toi.");
   Writeln("Je suis sur que tu peux, apprendre à aimer, aimer sans attendre, aimer à tout prendre...");
   Writeln("Brigitte : Mais je ne t'aime pas et l'amour n'a jamais jamais connu de loi.");
   
   for i := 0 to (15-11)*20 do
   begin
      Camera -> SetPosition(0.0, -. 0.05 , 0.0, 1);
      Wait(1);
   end;
   
   Writeln(Perso, " : C'est qu'il y a trop de gens qui t'aiment et tu ne me vois pas. Mais que je t'aime, que je t'aime, que je t'aime.");
   Writeln("Brigitte : Vous les hommes, sous vos airs innocents vous êtes de vrais brigands. Si c'est ça, moi je préfère rester toute seule.");
   
   CameraDemiTourNeg();

   Writeln(Perso, " : Ni brigand, ni pirate... Ah, y'a tant d'hommes que je ne suis pas. Mais je veux t'aimer comme on ne t'a jamais aimé.");
   Writeln("Où tu iras j'irai. Quoi que tu fasses l'amour est partout où tu regardes. Tu sais, je t'aimais, je t'aime et je t'aimerai.");
   Writeln("Brigitte : Moi aussi je t'aime mais pas d'amour mais quoi qu'il arrive, je resterai ta meilleure amie.");
   
   for i := 0 to 50 do
   begin
      Camera->Zoom(8.0);
      Wait(1);
   end;
   
   Writeln(Perso, " : Pfff, tu comprends rien ! ");
   
   Camera->Zoom(4.0);
   //{brigitte -> SetDirection}
   
   Wait(50);
   brigitte -> frapper();
   
   Wait(50);
   brigitte -> frapper();
   
   Wait(50);
   
   Camera->Solidariser();
   Camera->Zoom(1.0);
   
   heros -> Deplacer(7.0, 20.0, 2);
   
   Wait(200);
   Camera->Defaut();
   
end;




procedure debut_pere();
begin
   musique("glace.mid");
   conversation();
   writeln(Perso, " : Mais... mais.... qui êtes-vous ?");
   writeln("Père : Gamin, gam...ga... ... File dans ta chambre.");
   writeln(Perso, " : Mouais... ok c'est bon... j'vais dormir p'pa.");
   //{**le héros file dans sa chambre puis s'endort*** il faut faire la cinématique}
   Camera->Defaut();
   heros -> Deplacer(8.0,4.0,2);
   WaitFor(heros);
   heros -> Deplacer(8.0,13.0,2);
   WaitFor(heros);
   heros -> Deplacer(5.0,13.0,2);
   WaitFor(heros);
   
   musique("");
   //{il s'endort puis se réveille}
   carte("", 5.0, 13.0, 1);
   Wait(30);
end;

procedure debut_pere_reveil();
begin
   SetTemps(0.0);
   musique("mal.mid");
   carte("chezmoi.carte", 5.0, 13.0, 1);
   AjouterAnime(pere,"heros.anime");
   pere -> SetPosition (8.0, 5.0, 2);
   //{**t'y vas *****Cinématique}
   
   Camera->Defaut();
   writeln("AAAAAAAAHHHHHHH... OUILLLLLLLLLEEE......");
   heros -> Deplacer(8.0,13.0,2);
   WaitFor(heros);
   heros -> Deplacer(8.0,4.0,2);
   WaitFor(heros);
   writeln("Père : Fils... Je .... je souffre... j'agonise...");
   writeln("Père : Je suis malaaaa...deuh , complètement malaaaaa...deuh...");
   writeln(Perso, " : Comme quand ma mère sortait le soir ?");
   writeln("Père : Non, pire. J'ai des douleurs abdominales abominables...");
   writeln("Père : Mon fils... un service... j'ai à ... te ...demander... va voir ...");
   writeln("Père : Va voir le chaman.");
   writeln("Père : Demande lui ... m'apporter...potion.");
   writeln(Perso, " : Résiste, prouve que tu existes !");

end;



procedure debutvrai();
begin
   BloquerTemps(); 
   SetTemps(0.5); 
   //debut_donut(); 
   //debut_cinematique(); 
   //debut_drague(); 
   //debut_pere(); 
   debut_pere_reveil(); 
   DebloquerTemps(); 
   Camera->Solidariser();
   Camera->Zoom(1.0);
   Camera->Defaut();
end; 

procedure debutvrai_X();
begin
   BloquerTemps();
   SetTemps(0.5);
   debut_drague();
   debut_pere();
   DebloquerTemps();
end;



procedure debut();
   var b:integer;
begin
      
   //b := Menu("Bonjour! Choix des chapitres")
   b := Menu("Bonjour! :-) " + newline + "J'espère que vous portez bien. :-)" + newline + "Quel chapitre souhaitez-vous visiter?") 
	       begin
		      item("Début - Commencer au tout début"); 
		      item("Maladie"); 
		      item("Visite chez le chaman"); 
		      item("Enlèvement!"); 
		      item("Pyramide..."); 
		      item("Une aérothéière."); 
                      item("Générique de fin"); 
		      item("Annexe - Glace"); 
               end;

   
  //Writeln("La valeur de b est ", b);

  if b == -1 then
     begin 
	// RL: We do not anything as we're leaving the game. 
	writeln("Au revoir. Et à bientôt j'espère. :-)"); 
     end 

  else if b == 0 then
     begin 
       debutvrai();
     end 

  else if b == 1 then
     begin 
       debut_pere();
     end 

  else if b == 2 then 
     begin 
       //writeln("On va charger la carte."); 
       //{première fois qu'on voit le chaman}
       carte("foretverschaman.carte", 5.0, 10.0, 1);
     end 

  else if b == 3 then 
     //{deuxième fois ie l'enlèvement}
     begin 
       a_la_potion := true; 
       pere_est_vivant := false;
       carte("foretverschaman.carte", 5.0, 10.0, 1); 
     end 
   
  else if b == 4 then
//{devant la pyramide}
     begin      
      pere_est_vivant := false;
      a_la_potion := true;
      chaman_la := false;
      carte("pyramide.carte", 5.0, 10.0, 1); 
     end 

  else if b == 5 then
     begin 
      pere_est_vivant := false;
      a_la_potion := true;
      chaman_la := false;
      a_tue_boss := true;       
      carte("tore.carte", 20.0, 10.0, 1);
     end 

  else if b == 6 then
     begin 
      pere_est_vivant := false;
      a_la_potion := true;
      chaman_la := false;
      a_tue_boss := true;       
      carte("foret.carte", 50.0, 60.0, 1);
      writeln("Va au village!! Une surprise t'attendra...");
     end 

  else if b == 7 then 
     begin 
      carte("glace.carte", 10.0, 10.0, 2);    
     end 
  else
     begin 
       if false then
         begin 
	    Camera -> Desolidariser();
	    Camera -> SetPosition(15.0, 20.0 ,0.0, 2);
	    //{Camera -> Rotate(0.0, 0.0, 0.0, absolu);}
	    Camera -> Zoom(4.0);
	    carte("village.carte", 19.0, 11.0, 1);
	    Writeln("Yo ma poule!");
	    //{debutvrai();}
	 end 
       else
	 carte("village.carte", 19.0, 11.0, 1);
     end; 


end;














procedure brigitte_parler();
begin 
   if pere_est_vivant then 
      writeln("Coucou, c'est Brigitte !! ça va bien ?"); 
   else 
     if a_vu_son_pere_mort then 
	writeln("Coucou, c'est Brigitte !! ça va bien ?"); 
     else 
	writeln("Brigitte : Oh...ton père est décédé sur le divan c'est terrible."); 
end; //{ BrigitteParler }


procedure chercher_de_leau();
begin
   writeln("pfff... C'est trop lourd de chercher de l'eau."); 
end; 





procedure bob_parler();
   var i:integer;
   REPONSES : array[-1..2] of string;
begin
   REPONSES[-1]:='ERREUR';
   REPONSES[0]:="Ah ! Cela me rassure. Il n'avait pas l'air bien.";
   REPONSES[1]:="Et bien qu'est-ce que tu attends va voir le chaman";
   REPONSES[2]:="Non mais un peu de respect s'il te plaît !";

if false then 
begin 
   writeln('REPONSES[-1] = ', REPONSES[-1]); 
   writeln('REPONSES[ 0] = ', REPONSES[ 0]); 
   writeln('REPONSES[ 1] = ', REPONSES[ 1]); 
   writeln('REPONSES[ 2] = ', REPONSES[ 2]); 
end
else 
begin 
   if pere_est_vivant then
     begin 
       writeln("Boujour ",Perso, "!");
       writeln(REPONSES[Menu('Est-ce que ton père va bien ?')
                          begin
                            item('Oui');
                            item('Non');
                            item("Qu'est-ce que ça peut te faire?"); 
	                  end]);
     end;  

   else
     begin 
       if a_vu_son_pere_mort then
         begin 
           writeln("bob : Coucou, c'est bob!! ça va bien?");
           writeln("bob : Je crois que je vais bientôt déménager... Je sais pas... je ne le sens pas ce village.");
         end
       else
         begin 
	    writeln("Bob : On n'a rien pu faire, il est décédé. Quand on est arrivé, il était encore vivant. C'est terrible.");
	 end;
     end;
end; 
end;


procedure Puits_boss_parler();
  var REPONSES:array[-1..1] of string;
begin
REPONSES[-1]:='ERREUR';
REPONSES[0]:="As-tu seulement un seau pour la porter cette eau ? Gros malin.";
REPONSES[1]:="Reviens me voir quand tu veux.";
writeln("Boujour ",Perso, "! C'est moi qui m'occupe du puits.");
writeln(REPONSES[Menu("Tu veux de l'eau ?")
        begin
		item('Oui');
		item('Non');
		end]);
end;




procedure prokofiev_parler();
var REPONSES:array[-1..1] of string;
begin
    if pere_est_vivant then
     begin 
        REPONSES[-1]:='ERREUR';
        REPONSES[0]:="Lève le menton que je te massacre... Voilà ne bouge plus ça va partir...";
        REPONSES[1]:="Reviens me voir quand tu veux. Je suis toujours prêt pour te massacrer.";
        writeln("Boujour ",Perso, "! Je suis Prokofiev... Je sais pas quoi dire de plus.");
        writeln(REPONSES[Menu("Tu veux mon poing dans ta tronche ?")
            begin
		    item('Oui');
		    item('Non');
		    end]);
     end  
    else
      begin 
        if a_vu_son_pere_mort then
	  writeln("Prokofiev : Il se passe des choses étranges depuis que ton père est mort, les animaux de la forêt sont devenus aggressifs.");
        else
	  writeln("Prokofiev : Petit! Ivan le terrible a encore frappé : ton père est décédé.");
      end; 
end;


procedure pierre_parler();
var REPONSES:array[-1..1] of string;
begin
REPONSES[-1]:='ERREUR';
REPONSES[0]:="Tant mieux... Parce qu'en fait ça me saoule de te l'expliquer...";
REPONSES[1]:="Et bien c'est une montre... Plus la pierre est grosse, plus nous sommes proches de midi.";
writeln("Boujour ",Perso, "! Je suis le fils de Prokofiev...");
writeln(REPONSES[Menu("Sais-tu à quoi correspond la pierre en haut à droite ?")
        begin
		item('Oui');
		item('Non');
		end]);
end;

procedure juliette_parler();
var REPONSES:array[-1..1] of string;
begin
   REPONSES[-1]:='ERREUR';
   REPONSES[0]:="Non mais attends tu me prends pour qui ? Je vais appeller mon père. PAPA !!!";
   REPONSES[1]:="Reviens me voir quand tu veux. Je suis très ouverte comme fille.";
   
   if pere_est_vivant then 
     begin 
       writeln("Boujour ",Perso, "! Je suis la fille de Prokofiev...");
       writeln(REPONSES[Menu("Allons dans les fourrés ?")
              begin
              item('Oui');
              item('Non');
              end]);
   
     end  
   else
     begin 
       if a_vu_son_pere_mort then
         begin 
           writeln("Boujour ",Perso, "! Je suis la fille de Prokofiev...");
           writeln(REPONSES[Menu("Allons dans les fourrés ?")
                 begin
                 item('Oui');
                 item('Non');
                 end]);
         end  
       else
         writeln("Juliette : Mon dieu, ton père est mort, on l'a vu en arrivant, c'est terrible !");
     end; 
end;


procedure squelette_parler();
  var REPONSES:array[-1..1] of string;
      b : integer;
begin
   REPONSES[-1] := 'ERREUR';
   REPONSES[0]  := "Eh oh petit gars... T'as pas remarqué que j'avais pas de mains.";
   REPONSES[1]  := "Reviens me voir quand tu veux.";

   writeln("Boujour ", Perso, "! Je suis un squelette.");

   b := Menu("Un petit coup de main dans ta quête?")
        begin
           item('Oui');
           item('Non');
        end;

   writeln(REPONSES[b]);
   
end;





procedure heros_mort();
   var b : integer;
begin 
   Musique("mort.mid");
   //{Fondu(255);}
  
   b := Menu("Game over")
          begin
            item('Continuer');
            item('Quitter');
          end;
   
end;






