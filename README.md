# *Dessine-moi un mouton!* 

Hello everyone! :relaxed: 

***Dessine-moi un mouton!*** is a game that we wrote during our university second year. That was a fairly long time ago (time flies, guys). 
We're french, so the game is in french. 

The main spirit underlying the game is that we were (still are) great fans of [*The Legend of Zelda*](https://en.wikipedia.org/wiki/The_Legend_of_Zelda) and [*Secret of Mana*](https://en.wikipedia.org/wiki/Secret_of_Mana). We also happened to be mathematicians & computer scientists, meaning that this software a bit wild & crazy. However, 'computer scientists' does not mean 'software engineers', and we did not have any lecture on software designing (seems like it's still an academic issue though); so, we learnt through our [trials and our errors](https://en.wikipedia.org/wiki/Trial_and_error), but the game was not thought nor designed. It was our first large project, with a team of artists (!), and we had too many ideas that we did not know were too big for the project. And our software lectures being quite scarce & poor, we rushed into it without knowing the dragons that we would meet nor how to properly & simply defeat them. Retrospectively, the result is not that bad considering the context (we also had to play *World of Warcraft*, exams to pass, academic projects, eating crêpes, drinking apple cider, working on internship essays, and so forth). <br> 
The goal was to be able to present the game at the ['InterENS culturelles'](https://interq.ens.fr/) ("Cultural InterENS"), which we proudly (& brokenly) did. The result can (still!) be seen here (incl. screenshots): <br> 
&nbsp;&nbsp;&nbsp; http://dessine.moi.mouton.free.fr/
 
  
## Authors  
 
Authors: 
 - Mathilde <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Characters design <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://??? 
 - Pierre <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Characters design <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; https://www.facebook.com/pierre.carcaud?_fb_noscript=1 
 - Clément <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Texts & words <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://??? 
 - Ludovic <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Scenery items design <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://goudenege.perso.math.cnrs.fr/output/
 - François <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Music, Game engine, Level design <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://people.irisa.fr/Francois.Schwarzentruber/
 - Romain (myself)  <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Description languages <br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; http://??? 
  
   
## Intellectual Property 
 
Basically, we do not care about intellectual property. You can do whatever you like with anything in that project. 
 
However, as it seems that backward copyrighting could exist, we do have a license to prevent that case - for uninteresting law related stuffs, please see [COPYING](COPYING) (it's an [ISC license](https://en.wikipedia.org/wiki/ISC_license), the most liberal license we found out: do whatever you like with it, as long as you do not prevent ourselves or others to use it). 
 

   
## Technicalities 

First, likely, the game won't compile right off the bat on your computer: too many things to make it work. And as the saying goes, 'libtool is hell'. I might look into that in twenty years. It used to compile and work on Windows & MacOSX. Currently, it compiled & works on BSD. 
 
Then, the game depends on [SDL](http://www.libsdl.org), [SDL_image](http://www.libsdl.org/projects/SDL_image/release-1.2.html), [SDL_mixer](http://www.libsdl.org/projects/SDL_mixer/release-1.2.html). If these libraries do not work on your computer, then it's just can't work. But that's its only library depencies, so it's not that bad (to be fair, SDL_image & SDL_mixer depend on sub-libraries, like libjpeg, libpng, libvorbis, libogg, etc.). 
 
Then, the game was compiled with gcc and clang. It might work with other compilers, but we can't know for sure. 
 
Then, this repository is the main repository - there are small sub-projects that need to be compiled first: 
 - https://github.com/Romain7426/Mouton1-anime 
 - https://github.com/Romain7426/Mouton1-nonanime 
 - https://github.com/Romain7426/Mouton1-carte 
 - https://github.com/Romain7426/Mouton1-pscript 
  
I do not know how to integrate all of them in a single GitHub repository. So, in a user-unfriendly spirit, these have to be downloaded and compiled first. However, the idea was that these sub-projects were separate from the main project, and should be able to compile & run on their own. 
 
Then, as of now, loading of 3DS object work on little-endian system, but cannot properly work on non-little-endian system as non-little-endian endian-ness is not properly handled (bytes have to be swapped while reading 3DS files). 
 
All that being said, after downloading the project, type 'gmake -f Makefile-gen.mkf' and then 'make' and, supposedly, it should work. I would not bet my bottom dollar on it though. 
 
Also, the game used to be first developed in *C++*. Along with many critics, we ran into *C++* confusedness: (i) it always compiles whatever one writes; (ii) nobody has any idea about the actual semantic; (iii) compiling errors, when the compiler fails to somehow find a random semantic, are cryptic (to solve compiling errors, we were «hmm, if we comment out these lines, perhaps that gonna compile» - insane & shameful for a compiler); (iv) output results are weird and very tough to debug; (v) very slow to compile (we were used to [Turbo Pascal](https://en.wikipedia.org/wiki/Turbo_Pascal), whose compilation was immediate); (vi) with the years, the game just stopped from compiling; (vii) no two *C++* compilers behave the same way. <br> 
For our second game, we switched to old & boring *C*, and it was so much better - we did not regret it. 
 
That was the starting point of the currently published project: *C++* is an unstable language, the game did not compile any longer, and the game deserved to be published - so I decided to clean it up and to switch it to *C*, to make it work, and then to publish it to GitHub (for the record, as usual, it took way longer than initially planned). Here we are.  
 
  
## Architecture & Structuring ideas 
 
Despite our lack of training in software design, we naturally wanted to divide & conquer that big dragon: cut that one big problem into smaller manageable problems. We still knew that the core, the game engine, would be big though. But we separated the character description, the music, the scenery items description, the level description, the narrative description, from the game engine. That way we could also divide the work among team members. 
 
### Spatial DSLs

First, for the game stuffs descriptions, we designed small & quick purposed description languages (about that subject, one can check out that video [«Functional MzScheme DSLs in Game Development»](https://www.youtube.com/watch?v=Z8Xamkb-J2k), wherein they talk about «DSL» («data specific language») (very bad audio sadly)). We ran into two issues: 
 - (i) *Lex* & *Yacc* - In the very scarce software engineering lessons we had, we were advised to use *Lex* & *Yacc*. Well well well. *Lex* & *Yacc* are nice theoretical objects, but should not be used in real life. First, one never knows whether the regular expressions are the right ones (and for some reasons, there are always weird issues). They are slow. They are weirdly designed. They are not thread-safe nor reentrant. And the syntax error management is terrible: *yacc* returns "syntax error" and that's it - you're stuck - it's very frustrating. And during these lectures, you're told about intricate weird issues. Great. In real life, description languages are trivial LL(1) languages. We're using a [BFG](https://en.wikipedia.org/wiki/BFG_(weapon)) to kill an ant; and worse, that [BFG](https://en.wikipedia.org/wiki/BFG_(weapon)) is broken and can't even do properly the job. <br> 
   So, one should not use *Lex* & *Yacc* ever. One should study them to understand the underlying issues of tokenizing & parsing, but one should not use these broken & useless tools. First, regarding tokenizing, it's way simpler to directly write the automata; automata are simple, and they simply do what you think they do. And do not write these automata as data arrays - for each token, just write a function that takes the current state, the being-read character, and returns the next state - that's it. It works perfectly, it's simple, and it's very fast. <br> 
   For parsing, LL(1) languages are trivial. So just do it. Basically it's a big automaton. The only location where it could be trickier is expression-parsing: infix expressions ("1 + 2") are why LALR(0) stuffs were developed; they can still be parsed, but a side stack is needed. That's it. It's very simple, and it works very well. And syntax errors can be understood and more explanatory than the hellish "syntax error". <br> 
   So, please, *Lex* & *Yacc* are nice curiosities, proofs of concept, but should not be used. Even for our very simple description languages, they poorly failed. 
 - (ii) *Typing* - As computer scientists, we were introduced to *OCaml*, typing inference, and program correctness-proof giving. Typing is seen as a way to automatically prove, at least partially, the correctness of a program. Duh... Academically speaking, I do understand the attractiveness of such concepts, and *OCaml* is a very nice language (*pattern-matching* is still really great), but in real life, what one actually wants, it's something like *Visual Basic*: proofs do not matter, the program should work - that's it - the team member who wants to describe the object he is working on does not care about typing - it should just work - typing does not even make sense to him. Unfortunately, we learnt it the hard way. <br> 
   Regarding typing, we then met [Scheme](https://en.wikipedia.org/wiki/Scheme_(programming_language)), and we had a cognitive dissonance: this language is amazing, but does not care about typing at all. From the user point of view, there's no type (of course, in-memory data are typed). And the language was so powerful and easy. With very few lines of code, we could run quite powerful programs. In spirit, [Scheme](https://en.wikipedia.org/wiki/Scheme_(programming_language)) was the opposite of [OCaml](https://en.wikipedia.org/wiki/OCaml), and it was way easier & simple to use. (A quick note about so-called "functional programming" & "first-order functions": it does not matter, nobody cares. An actual full-fledged functional language is very complex, for nothing; the issue is to remember the current stack of lexical environments; *OCaml* & *Scheme* cope with that complexity in removing variables and substituting them with "bindings", and so-called *let-bindings*. Such choices are definitely understandable, but are not user-friendly; variables are the way to go; let-bindings are a creepy work-around in spirit, and slow in facts. Having both, variables & lexical stacked environment remembered means that the whole call-stack must be remembered at & for each *lambda*, which is huge - basically, it means that the call-stack is duplicated each time - and obviously, implementing 'call/cc' is trivial with such a feature. If in-line anymous functions are handy, remembering lexical environment does not worth it - just provide the global the environment to such functions. Or one can do the *Pascal* way: local functions cannot be objects (which is not convenient at all).) <br> 
   So, please, type as less as possible your description languages. In spirit, description languages should be like [Scheme](https://en.wikipedia.org/wiki/Scheme_(programming_language)). And description languages implies that they are no variables (nor let-bindings). 
   
 
 
### Temporal DSL 

Then, after spatial descriptions (the «objects»), we wanted temporal description (the «narrative»). Well well well. Now we can tell you that this is a very very very big dragon. 
 - (a) We quickly realized that a «scripting» language was needed: variables & procedures were needed. Better, at some point, we wanted the game to be driven from the narrative (makes sense, right). Duh... So a full-fledged scripting language was developed. <br> 
       Such a choice is definitely understandable. But one should keep in mind that this is a very large & complex task, and that the scripting language should be kept as feature-less as possible - it should not make coffee & toasts. And it will already be very complicated. 
 - (b) That task was started without any actual lecture on such a subject, which could have been very very useful. In the end, the dragon got defeated, the narrative description language did work, but it was ugly. 
 - (c) Language design issues aside, the main issue is that, actually, they are two competiting sub-programs in one program: the script engine & the game engine. Technological speaking, what we needed were «cooperative threads» («non-preempting threads», «co-routines», «fibers»), but we did not know that. With «cooperative threads», one can have the two engines running in their own environments, and then would just have to write some in-between communication stuffs. The advantage of that is both engines can be black boxes; especially, the scripting language can be taken from any where, and it could be run without knowing anything about it. Same thing for the game engine. <br> 
   We were not aware of that useful technology. Instead, we flattened and linearized both engines, and we had kernel which ran one step of the first engine and then one step of the second engine. We did not conceptually thought about that. We were looking for a way to defeat that dragon, and that's the bottom-up solution we came up with - we did not realize what we were doing, we implemented these features because we needed them. <br> 
   A good consequence was that the game engine was rewritten - it was still not good, but before that it was just a hell bunch of global variables and mutually recursive functions, where no-one could infer any semantic except the main developer. So that was definitely an improvement. <br> 
   On the other hand, scripting language are easier when recursively interpreted. But the linearization & step-wise design implied to break that down. What should have been was to take the full step and develop a bytecode. We did not know that, but, in facts, bytecode is not very complicated - so that step could have been taken. Instead, a halfway solution was designed, the worst of the two worlds: stepped interpretation (it's an oxymoron; by definition, interpretation is a recursive process). Never do «stepped interpretation» - it's complicated as hell - bytecode is simpler. 
 - (d) As of now, I rewrote that whole part. It generates bytecode. It's easier, more powerfull, less buggy, and simpler. The narrative description language is called «PScript» for «Pascal Scripting Language». I tried to make as simple as possible, with variables, type-less as Scheme, no *lex* and no *yacc*. There are many things to be improved, to be tested, but the core works, and works pretty well. 
 - (e) The program now has an explicit kernel part, and two explicit cooperative threads: script & game. It makes much more sense. 
 - (f) A good consequence of cooperative threads is that the temporal DSL can be in any language, including plain *C*. As a proof of concept, I did implement some scripts in plain *C*. Meaning that it is not even necessary to develop to dedicated languages to do that. (Geez - Had we known that...!) 
  
  
 

## Future & TODOs  
 
First, that game is ***NOT*** maintained. Patches are welcome, but the program is not actively developed. The point of that GiHub repository is to show off the work that we did - and it's still not a bad piece of software. 
 
Regarding the future & TODOs, there are many things: 
 - (i) Being able to walk a negative-curvature manifold (projective plan) would be great. 
 - (ii) Refactor the game engine which still a bunch functions bypassing each other, and breaking assertions and invariants. A lot of work here. 
 - (iii) Make it compile and work on every arch & OS. A lot of uninteresting work here. 
 - (iv) Refine the DSLs. 
 - (v) Make the airteapot work. 
 - (vi) Make the ice map work. 
 - (vii) Develop many side tools (maps design, 3DS, etc.) 
 - (viii) Fix & improve the current narrative (when the game engine won't be based on a jenga-tower design, it should be easier to expand the narrative). 
 - (ix) There are obviously many bugs everywhere. 
 - (x) There are many useless files & lines of code. 
 
That said, once again, the game is not being currently developed. Do not expect any improvement for the upcoming twenty years.  
 
For information, when we presented the game at the InterENS, the game was a broken buggy jenga-tower. It's so much better now. 
 
Thanks!! :smile: 

And we all love you. :kissing_heart: 

 

