# Petites reflexions

## Bonus editeur de map ? :
- affichage 2d simple (vulgaires blocs carrés colorés)
- touches 1,2,3,4,5... pour choisir les blocs
- sauvegarde vers fichier serialisé (mot compliqué pour un truc hyper simple)
- binaire brute (serialisation du pauvre)
- sauvegarde au format texte ? la serialisation est plus simple

## Les casts C sont interdits en C++, utilisez les casts modernes
    int     monInt = ...;
	Player *monPlayer = new ...;
	
	// Avant :
	  
    (float)monInt;
    (Entity*)monPlayer;
    
	// Apres :
    
	static_cast<float>(monInt);
	static_cast<Entity*>(monPlayer);

## Gestion d'erreur
- Attention au thread-safety :
 - rajouter des mutex a toutes les ressources susceptibles d'etre utilisé par plusieur thread
 - voire les encapsuler dans un objet singleton global qui se chargera lui du thread-safety (grosse artillerie)
 - regardez le pattern "singleton de meyer"

- ### getline()
  - verifier les valeurs de retour

## Nettoyer le depot ?
- fichiers inutiles, fichiers temporaires

## Header 42  
- enlever les headers 42 parce qu'il est juste hyper mal conçu.
- le nom du fichier ecrit en haut ? pourquoi ? au cas ou t'aurai oublié ?
- le nom de l'auteur apparait deux fois (au cas ou t'aurai oublié en lisant la ligne d'apres)
- si le nom du fichier change (mv), le nom dans le header ne se met pas forcment a jour
- le plugin header-42 atom modifie a la fois le nom de premier nom d'auteur et nom de modificateur sans toucher au deuxieme nom d'auteur, donc paternité du fichier ambigu en plus de compliquer le merge Git puisque la modification est en deux parties
- le simple fait de sauvegarder le fichier sans le modifier change la date de modification, pratique pour engendrer des merge conflicts a la chaines

## Les headers sont OBSELETES
Avec git, il est totalement inutile d'avoir un header puisque git connait l'auteur et modificateur de chaque LIGNE a chaque NANOSECONDES

Si vraiment on veut utiliser un header alors banissons celui de 42, il est trop mal conçu,du moins, les benefice sont inferieur a tout les problemes quils crée
je trouve deja aberrant qu'un vulgaire header me fasse ecrire un pavé

Utilisons plutot un header à la javadoc :
  
    /**
     * @author jdupont
     * @description parser
     */

Ou bien comme ceci : http://stackoverflow.com/a/134211
facilement parsable en XML avec une vulgaire lib qui parse le XML ( on strip le "///" et hop) :

    /// <summary>
    ///   truc qui sert a parser
    /// </summary>
    /// <author>
    ///   jdupont
    /// </author>
	
	void someCode() {
		/// <tag-xml-facilement-parsable>
		///   commentaire de porc
		/// </tag-xml-facilement-parsable>
		...
		codeDePorc(variableDeFou);
		...
		return ;
	}

