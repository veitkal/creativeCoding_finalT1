# creativeCoding_finalT1 Ascii Print Weave

Built by Jakob Jennerholm Hammar 
for IS71014B: Workshops In Creative Coding 1, 
Term 1 Final Project 
Goldsmiths University of London, 
January 2019

A projection mapping project developed for projecting a staircase. 
The piece is drawing from and is aspiring to highlight the historical and technical 
connection between digital and analogue pattern making.
One part is founded on ascii art and cli esthetics, 
the second takes of from the classic Commodor 64 basic program 'PRINT CHR$(205.5+RND(1)); : GOTO 10',
the third one is trying to emulate and animate two classic weaving pattern.

All files in /src goes to /src,
files in /data to /bin/data

the file stairsFront.png goes in bin/data and is used to simulate the eobject for mapping.


##Introduction

The initial thought behind this piece was to work with patterns and symbols, how these can be understood as an underlying current within art, design and the mind it self (as with perception, experience and understanding the world, meaning-making among others).          I wanted to trace this notion through time and see how this can be regarded from within a digital context (or a computational one), almost as a very, very limited historical and esthetic research. By splitting the piece up in three different but yet connected ideas (out of many possible ones), the project tracks some aspects of the digital medium to in some form try to reflect on the role of computers as a tool and means of creativity.

The staircase was a promising shape with its folding and cascading form, allowing to play with blocks of imagery, fields and repetitions as well as having silhouette with sharp edges, lines and cuts. It also has some interesting qualities (at least for me) alluding to movement, transportation, and liminality (as a place between places), that I find in a certain way can be woven into the project.

 
###Concept and background research

The three parts are inspired by very distinct practices and esthetics. They are different aspects of well know characteristics of computers and it's artistic and practical uses. They chosen for their almost archetypal properties more than trying to be all-encompassing of the subject. Even though they are still widely used, they are not bleeding edge computational art forms. But I hope they might catch something more generally referential of the medium.

###Ascii

The first part is drawing on Ascii art, the use of the textual qualities of computer terminals and consoles for creative ends. The scene starts with a black and white unruly animation based on simple symbols flickering over the object. Colour is then added followed by adding more symbols and the letters of the alphabet. Lines, waveforms and blimps and drawn by rapidly changing characters that flutter througout the scene

###Print

The next part is very closely linked to the first one but it is a very specific reference, hinting towards a language and technology that can be argued having played an imporatant part of forming and popularising the use of computers. At least it carries with it a legacy or and perhaps a feeling of a significant event in time. The reference is to a well known one line program called 10 PRINT CHR$(205.5+RND(1)); : GOTO 10 written in Basic for the Commodore 64. I am fascinated by this simple program, which manage to produce never ending complex maze like imagery with the use of two characters, randomness and a logical test.

###Weave

Following these two scenes is perhaps something very different, but what I hope will make some sort of sense. The part is inspired by weaving and weaving patterns, especially the draft patterns where the example pattern is drawn together with the technical instructions. I find the history, practice, materiality and symbology of weaving fascinating, something that is only augmented by weaving being one of the origins of computer technologies.

##Technical

The code is written in c++ with the help of OpenFrameworks and the ofxPiMapper add-on. The animations are often quite simple instances of geometric shapes, noise and pseudo-randomness and trigonometric functions.

For the first part the ascii-esque looks were created by an image filter reading the brightness and colours of pixels, substituting them with symbols and characters. Waves, lines and shapes where drawn to a frame buffer which in turn was rendered through the filter.

The print part is building on the same logic as the original 10 Print program but expanded to use different shapes and motions. The program is looping over the screen over a set distance and for each step doing a logical test of a random number to draw a specific shape. While the original program used '/' and '', this program uses different angled lines, triangles, boxes and more.

In the weave part two different patterns were drawn, one triangular and one striped/chequered. Both of these were based on very traditional patterns. As a way of trying to capture a resemblance to the draft
patterns I had in mind, a similar filter as for the ascii part was used but this time implemented as a pixel filter.

Some of the parts are black and white while others are not. The colours used are from a colour scheme I've been using for some years in my terminals and editors for years, namely Tomorrow Night by Chriskempson.


Self evaluation or how to move forward

I guess what I wanted to explore was some of the abstract aspects of computers and their esthetics within a wider notion of mark-, pattern- and art-making. Maybe to try find and capture a feeling or a sense of the role computers may have with the human engagement with the world. I'm pretty sure I didn't manage to do that but at least it made me think about some of these things and map out and connect different ideas and interesting threads. This together with gaining some very valuable experience in coding and laying out (and containing) a slightly larger project than usual. The work might have been able to convey some of the intensions but in a far to disrupted, shallow and incoherent maner. If I would have been able to do it again, and for future iterations, I would choose a narrower theme (perhaps one of the parts) and delved deeper and more extensive into that.

This work did play on several ideas I've been wanting to try out, and I'm certain parts of this will survive in other projects. Especially the weaving part (and the over arching theme, under which it lives) is something I've been thinking about for quite some time now and I I consider this as a small WIP part of a larger ongoing project. A test of tests of tests.

 
##References

###Inspirational code

- 10 PRINT CHR$(205.5+RND(1)); : GOTO 10 in PHP (or anything else, for
that matter),
https://codegolf.stackexchange.com/questions/9165/10-print-chr205-5rnd1-goto-10-in-php-or-anything-else-for-that-matter

- Shiffman, CC_076_10PRINT,
https://github.com/CodingTrain/website/tree/master/CodingChallenges/CC_076_10PRINT/P5

- Shiffman, Nature of Code, https://natureofcode.com/

- Shapes From Pixels, assignment for Workshops in Creative Coding
Week 6, Images and video.
https://learn.gold.ac.uk/mod/assign/view.php?id=720806

###Text, imagery and other inspirations

- 10 PRINT CHR$(205.5+RND(1)); : GOTO 10, https://10print.org/

- 10 PRINT "Hello 50 years of BASIC"; 20 GOTO 10, https://betanews.com/2014/05/01/10-print-hello-50-years-of-basic-20-goto-10/

- Basic Tablet Weaving,
http://sca.claypool.me/weaving/basictabletweaving.html

- Chriskempson / Tomorrow-theme,
- https://vimeo.com/klosterliv/review/388853387/c347518e1b

- Drafts from: Johann Georg Thaller Manuscript, Johann Georg Thaller and Others,
https://www.handweaving.net/collection-drafts/collection/58/johann-georg-thaller-manuscript-johann-georg-thaller-and-others?page=0&minshafts=0&maxshafts=0&maxtreadles=0&maxfloatlength=0
