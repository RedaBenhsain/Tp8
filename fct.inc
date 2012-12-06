<?php
  
	//À compléter
	//Ce fichier contient toutes les fonctions appelées dans les autres pages
	//Vous devez au moins définir les 3 fonctions suivantes et les appeler aux moments opportuns dans usagers.php et/ou admin.php
	function connectionBD(){
		
		session_start();
		
		if (!isset($_SESSION['user_in']) )
				header("Location: index.php?erreur=TentativeAccesAUsager.phpAucunUtilisateurEnCours");
		else{
			//Ouvre une connexion au serveur MySQL
			$connection = mysql_connect(NOM_SERVEUR, NOM_USAGER_BD, NOM_PASSWORD) ;
			if (!$connection) {
				die('Problème de connexion au serveur : ' . mysql_error());
			}
			mysql_set_charset("utf8");
			
			if (!mysql_select_db(NOM_BD))
				die('Problème de connexion à la base de données : ' . mysql_error());
		
		}
	}
	
	
    //==============================================================================================
    function htmlListeTransactions($pIdUsager)  //Si vous appelez cette fonction pour la liste de toutes les transactions 
    {                                           //alors transmettez un id égal à zéro. Pour la liste des transactions d'un usager,
												//vous devez transmettre son u_id.
        
        
        //dernière instruction    
       // return $html;
    }

//determine et retourne le formulaire de payment=
    //==============================================================================================    
    function htmlFormPaiement()
    {
    	

		$sql = mysql_query("SELECT * FROM t_services");

		//Si la BD est vide
		if (!$sql)
			die('Problème avec la requête : '. $sql . '<br/>' . mysql_error());
			
		else{
			
			$html = '<form name="frmServices" action="' . $_SERVER['PHP_SELF'].'?operation=listetransactions" method="post">
						<input type="hidden" name="txtHidID" value="' . $_SESSION['user_in'] . '">
						<table border="1" cellspacing="0"><tbody>
							<tr>
								<th>Type</th>
								<th>Fournisseur</th>
								<th>Montant</th>
							</tr>';
			//parcoure le tableau 
			while($tabEnrCourant = mysql_fetch_assoc($sql)){
				$html .= '<tr>
								<td>' . $tabEnrCourant["S_Type"] . '</td>
								<td>' . $tabEnrCourant["S_Fournisseur"] . '</td>
								<td><input class="montant" type="text" name="txt' . $tabEnrCourant["S_ID"] . '"></td>
							</tr>';
			}
							
			$html .= '</tbody></table><input type="submit" value="Payer"/></form>';		
		}
     
        //dernière instruction    
        return $html;
    }
    
    
    //==============================================================================================
    function htmlListeUsagers()
    {
    	$sql = "SELECT U_ID, U_Nom, U_Prenom, T_ID, T_U_ID_FK, T_S_ID_FK, T_Date, T_Valeur, S_Type, S_Fournisseur FROM t_usagers,t_services,t_transactions ";
		$sql .= "WHERE T_U_ID_FK = U_ID AND T_S_ID_FK = S_ID AND U_ID = " . $_SESSION['user_in'] . " ORDER BY T_ID ASC";
        
        $tabTransactions = mysql_query($sql);	
		
		//Si la BDD ne contient pas de Services
		if (!$tabTransactions)
			die('Problème avec la requête : '. $sql . '<br/>' . mysql_error());
			
			$html = '<h1>ID ='.$_SESSION['user_in'].'</h1>';
			$html .= 	'<table border="1" cellspacing="0"><tbody>
							<tr>
								<th>Date</th>
								<th>Usager</th>
								<th>Type et fournisseur</th>
								<th>Montant</th>								
							</tr>';
				while($tabEnrCourant = mysql_fetch_assoc($tabTransactions)){
						$html .= '<tr>
							<td>' . $tabEnrCourant["T_Date"] . '</td>
							<td>' . $tabEnrCourant["U_Prenom"] . ' ' . $tabEnrCourant["U_Nom"] . '</td>
							<td>' . $tabEnrCourant["S_Type"] . ' : ' . $tabEnrCourant["S_Fournisseur"] . '</td>
							<td>' . $tabEnrCourant["T_Valeur"] . ' $</td>
						</tr>';
				}
        //dernière instruction    
        return $html;
    } 
    
    
	// menu de Gauche
	function menuListeServices(){	
		
			if(isset($_GET['operation']) && $_GET["operation"]== "listetransactions"){
					$html = '<div class="lien"><a href="' . $_SERVER['PHP_SELF'] . '?operation=listeusagers">Payer services</a></div>';
					$html .= '<div class="lienSel"><a href="' . $_SERVER['PHP_SELF'] . '?operation=listetransactions">Liste des transactions</a></div>';
					$html .= '<div class="lien"><a href="quitter.php">Se déconnecter</a></div>';
				}
			else
				{
					$html = '<div class="lienSel"><a href="' . $_SERVER['PHP_SELF'] . '?operation=listeusagers">Payer services</a></div>';
					$html .= '<div class="lien"><a href="' . $_SERVER['PHP_SELF'] . '?operation=listetransactions">Liste des transactions</a></div>';
					$html .= '<div class="lien"><a href="quitter.php">Se déconnecter</a></div>';
				}
		
		return $html;
	}
    
          
?>
