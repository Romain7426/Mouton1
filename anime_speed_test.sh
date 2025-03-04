#!/bin/sh


for i in "saintexupery.anime" "pere.anime" "bob.anime" "heros.anime" "brigitte.anime" "juliette.anime" "mouton.anime" "chaman.anime" "dinotore.anime" "heros.anime" "pecu.anime" "prokofiev.anime" "sang.anime" "chapinmechant.anime" "fantome.anime" "moutonmechant.anime" "pierre.anime" "y.anime" "m.anime" "c.anime" "a.anime" "bizarre1.anime" "bizarre2.anime" "bucheron.anime" "chapin.anime" "eclaboussures.anime" "homme_bizarre.anime" "puit_boss.anime" "squelette.anime" ; do 
    ./libs/anime/destroot/bin/anime data/animes/$i 
#    ./libs/anime/destroot/bin/anime data/animes/$i --stdlog log/$i.log
done;

