#include <iostream>
#include <string.h>
#include<fstream>
#include<algorithm>
#include<cctype>
#include<bits/stdc++.h>
using namespace std;



//Structure de l'arbre binaire de recherche (Marche)
struct Arbre{
    string mot;
    int positions[20], i=0;
    Arbre *fg, *fd;
};

//Fonction pour supprimer espaces dans un mot (Marche)
string removeSpaces(string str){
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}


//Cr�er un nouveau fichier txt (Marche)
ofstream creationFichier(string NOM){
string ligne;
ofstream F(NOM);
cout << "\nEcrivez vos phrases et finissez les par un point. Tapez 0 pour vous arreter." << endl;
    while(F){
        getline(cin, ligne);
    if(ligne=="0")
        {
            break;
        }
    F << ligne << endl;
}
return F;
}

//Affichier le contenu d'un fichier txt existant ligne par ligne (Marche)
void afficherFichier(string NOM){
cout << "\nVotre fichier contient les phrases suivantes:" << endl;
ifstream fin;
string ligne;
fin.open(NOM);
while(getline(fin, ligne))
{
    cout << ligne << endl;
}
fin.close();
exit;
}

//Fonction pour cr�er nouveau arbre binaire de recherche (ordre ALPHABETIQUE) (Marche)
struct Arbre* newArbre(string MOT, int position)
{
    Arbre* temp = new Arbre;
    temp->mot = MOT;
    temp->positions[temp->i]=position;
    (temp->i)++;
    temp->fg = temp->fd = NULL;
    return temp;
}

//Fonction pour afficher l'arbre en traversant dans l'ordre infix� (Marche)
void inorder(Arbre* root)
{
    int i=0;
    if (root != NULL) {
        inorder(root->fg);
        cout << "\n'" << root->mot << "'" << " est present dans les phrases suivantes:" << endl;
        while(root->positions[i]){
            cout << "[" << root->positions[i] << "]";
            i++;
        }
        cout << endl << endl;
        inorder(root->fd);
    }
}

//Fonction pour ins�rer un mot dans l'arbre binaire de  (Marche)
struct Arbre* insert(Arbre* root, string MOT, int phrase)
{
    //Sous-fonction pour extraire les ponctuations du mot avant de l'ins�rer
    for(int j=0,len=MOT.size();j<len;j++){
        if(ispunct(MOT[j]))
        {
            MOT.erase(j--, 1);
            len = MOT.size();
        }
        }

    MOT=removeSpaces(MOT);
    if (root == NULL)
        return newArbre(MOT, phrase);
    if (root->mot==MOT){
        if(root->positions[root->i-1]==phrase){
            exit;
        }else{
        root->positions[root->i]=phrase;
        (root->i)++;
        }
        return root;}
    if (MOT < root->mot)
        root->fg = insert(root->fg, MOT, phrase);
    else if (MOT > root->mot)
        root->fd = insert(root->fd, MOT, phrase);
    return root;
}

//Fonction pour savoir si un mot existe dans l'arbre binaire de recherche (Marche)
bool existe(Arbre* root, string exi){
 if (root != NULL) {
        if(root->mot==exi){
            return true;
        }
        if(root->mot>exi)
        {
            return existe(root->fg, exi);
        }if(root->mot<exi)
        {
            return existe(root->fd, exi);
        }
 }
        return false;
 }

 //Fonction pour retourner un arbre binaire sp�cifique � partir du mot (Marche)
Arbre* rech(Arbre* root, string exi){
 if (root != NULL) {
        if(root->mot==exi || root==NULL){
            return root;
        }
        if(root->mot>exi)
        {
            return rech(root->fg, exi);
        }if(root->mot<exi)
        {
            return rech(root->fd, exi);
        }
 }
 }

//Transposer fichier texte dans arbre binaire de recherche. Ensuite le choix entre afficher les r�sultats de l'arbre binaire ou chercher une phrase. (MARCHE LETS FUCKING GOOO)
void InsertionFichier(string NOM, Arbre* root){
    Arbre *tempo;
    char limite='.';
    fstream fichier;
    string mot, recherche, mot1, phrase;
    int i=1, ab;
    fichier.open(NOM);
    while(fichier >> mot)
    {
        root=insert(root, mot, i);
        if(find(mot.begin(), mot.end(), limite)!=mot.end())
        {
            i++;
        }
    }
    cout << "\nVoulez-vous afficher les resultats du traitement, ou chercher une mot dans le fichier ?" << endl << "[0] - Afficher resultats du traitement." << endl << "[1] - Chercher une phrase." << endl;
    cin >> ab;
    if(ab==0){
        inorder(root);
    }
    //Fonction recherche de phrase dans le fichier en faisant l'intersection des positions
    if(ab==1){
        cout << "Tapez la phrase que vous voulez rechercher (Attention aux majuscules): ";
        getline(cin, phrase);
        getline(cin, phrase);
        int posi[20], posi2[20], posi3[20];
        int j;
        int k=0;
        int CONF=0;
        string mot2;
        istringstream s(phrase); //contient la phrase tapp�e par l'utilisateur
        while(s){ //pour chaque mot de la phrase
                s >> mot2;
                for(int j=0,len=mot2.size();j<len;j++){ //On retire la ponctuation
                    if(ispunct(mot2[j])){
                        mot2.erase(j--, 1);
                        len = mot2.size();
                    }
                }
                removeSpaces(mot2); //On retire les espaces
            if (existe(root, mot2)){ //On cherche si le mot existe dans l'arbre, et si oui, on d�roule l'algorithme qui permet de faire les intersections
            struct Arbre *tempura=rech(root, mot2);
            int i, j, k=0;
            if(CONF==0){ //On initialise le vecteur positions pour le premier mot
                for(i=0;i<tempura->i;i++){
                    posi[i]=tempura->positions[i];
                }
                CONF=1;
            }
            for(i=0;i<20;i++){
                for(j=0;j<tempura->i;j++){
                    if(posi[i]==tempura->positions[j]){
                        posi2[k]=posi[i];
                        k++;
                        break;
                    }
                }
            }
            if(posi2[k])
            for(i=0;i<20;i++){
                posi[i]=posi2[i];
            }
                       }else{ //si un des mots de la phrase n'existe pas, on sort directement de la fonction
                       cout << "\nCette phrase n'existe pas.";
                        return;
                        }
        }
        if(CONF==1){ //si tous les mots existent dans les m�mes phrases, alors on d�file
            cout<< "\nLa phrase existe dans les phrases:";
            for(i=0;i<20;i++){
            if(posi2[i]==0){
                break;
            }
            cout << "["<< posi2[i] << "] ";
                }
            exit;
            }
        }
    }

int main(){
ofstream F;
string nom, NOM, ligne;
int conf, conf2=1;
struct Arbre *root=NULL;
while(conf2){
cout << "\nVoulez-vous creer un fichier, ou en traiter un?\n" << "[0] - Creer un fichier\n[1] - Traiter un fichier existant\n\n";
cin >> conf;
if(conf!=0&&conf!=1)
{
cout << "\nErreur. Tapez un chiffre valable.\n";
cout << "Voulez-vous creer un fichier, ou en traiter un?\n" << "[0] - Cr�er un fichier\n[1] - Traiter un fichier existant\n\n";
cin >> conf;
}
if(conf==0)
{
cout << "\nVous avez decide de creer un fichier.\nEntrez le nom du fichier (sans espaces et sans accents).\n" << endl;
cin >> nom;
NOM=nom+".txt";
F=creationFichier(NOM);
}else{
cout << "\nVous avez decide de traiter un fichier.\nTapez le nom du fichier que voulez traiter(Sans le .txt)\n\n";
cin >> nom;
NOM=nom+".txt";
InsertionFichier(NOM, root);
}
cout << endl << endl;
cout << "\nVoulez-vous revenir au debut du programme?\n\n" << "[0] - Non\n[1] - Oui\n\n";
cin >> conf2;
}
cout << "\nFin du programme.\n";
return 0;
}
