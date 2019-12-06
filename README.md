# Project-Cluster

Υλοποιηση 2ης Εργασιας για το μαθημα Αναπτυξη Λογισμικού για Αλγοριθμικα Προβληματα
Χειμερινο Εξαμηνο 2019/20 .

# Αρχεια
Ο κωδικας χωριζεται στα αρχεια που βρισκονται στο φακελο src/ και στον φακελο test/ .
Στο φακελο src/ βρισκονται τα αρχεια υλοποιησης , ενω στον φακελο test η βιβλιοθηκη
catch και τα unit tests.

1. CMDParser.cpp/.hpp , ConfParser.cpp/.hpp Parser.hpp/Parser.cpp
Υλοποιηση του parsing των ζητουμενων αρχειων . Με σειρα
 1. Parsing cmd-line arguments
 2. .conf file parser
 3. .dat file parser

2. Item.cpp/.hpp , Curve.hpp/.cpp , Vector.cpp/.hpp
Η abstract κλαση Item αντιπροσωπευει τα αντικειμενα που ζητειται να υλοποιηθει
το clustering . (Διανυσματα,Καμπυλες) . Οριζεται η pure virtual συναρτηση distance
για τον υπολογισμο της αποστασης μεταξυ 2 αντικειμενων. Αντιστοιχα τα αντικειμενα
Curve,Vector κληρονομουν απο την κλαση Item και υλοποιουν τις pure virtual συναρτησεις.

3. Database.cpp
Υλοποιηση κλασης για την αποθηκευση και ανακτηση των δεδομενων . Η ανακτηση δεδομενων
γινεται μεσω string(id) και int(index). Στην ΒΔ αποθηκεουονται αντικειμενα της
abstract class Item.

4. Clustering.cpp/.hpp
Υλοποιηση της λειτουργικοτητας των αλγοριθμων που ζητουνται . Η επιλογη των αλγοριθμων
για το init , assign , update γινεται μεσω του constructor . Δηλαδη , οριζονται τα
flags init_f , assign_f, update_f . Αν το init_f ειναι 0 τοτε επιλεγεται ο random selection
αλγοριθμος για το initialization , ενω αν το init_f ειναι 1 τοτε επιλεγεται ο kmeans++. κ.ο.κ.
π.χ
Clustering(..,0,0,0) επιλεγονται οι [random select ,lloyd assign,pam a'la lloyd update]
Clustering(..,1,0,0) επιλεγονται οι [kmeans++ ,lloyd assign,pam a'la lloyd update]

#Αποτελεσματα

Οι συγκρισεις βασιζονται στην εισοδο DataVectors_5_500x100

## Kmeans init vs Random Init

Στα αποτελεσματα μας φαινεται η αισθητη βελτιωση που προσφερει η kmeans init σε
σχεση με την random init στα αποτελεσματα . Απο σ = 0.5 , παμε στο 0.9 με την kmeans
init . Ενω και ο χρονος υπολογισμου μειωνεται .

## Reverse Assignment vs Lloyd

Το reverse assignment δεν προσφερει καποια βελτιωση στα αποτελεσματα . Ενω πρoσθετει
χρονο , που οφειλετε στην αρχικοποιηση των hashtable

## PAM update vs Mean Vector

Η mean vector βελτιωνει τα αποτελεσματα σε θεμα ακριβειας αλλα προσθετει χρονο
στον υπολογισμο . Κατι που θα περιμεναμε να δουμε λογω του χρονου που παιρνει ο
υπολογισμος μεσου διανυσματος / καμπυλης .

#Compile

Στον φακελο src/

    $ make cluster

Για την δημιουργια των unit test

    $ make test

# Run

Στον φακελο src

    $ ./cluster -i [input file] -c [config file] -o [output file]

Για τα test . Στον φακελο test/

    $ ./test

Περιλαμβανονται και δοκιμαστικα test data

#Unit Testing

Το unit testing γινεται με χρηση της βιβλιοθηκης catch2(https://github.com/catchorg/Catch2).
Η βιβλιοθηκη επιλεχτηκε λογω της ευκολης χρησης της . Ειναι header only οποτε δεν χρειαζεται
η εγκατσταση καποιου πακετου.

#Version Control

Εγινε χρηση του git

#Συμμετεχοντες

sdi1600036 - Γιατρακος Γεωργιος

sdi1400134 - Παμποριδης Στεφανος
