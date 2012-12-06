<?php 
     include 'inc/define.inc.php';	
		
	   //À compléter
                                
	//Si la page est appelée suite à un clic sur le bouton Se connecter (index.php)
	if (isset($_POST["txtLogin"]) && isset($_POST["txtPassword"]))
	{
		//Si un login et un mot de passe ont été inscrits
		if ($_POST["txtLogin"] != "" && $_POST["txtPassword"] != "")
		{
			// Ouvre une connexion au serveur MySQL
			$connection = mysql_connect(NOM_SERVEUR, NOM_USAGER_BD, NOM_PASSWORD) ;
			if (!$connection) 
				die('Problème de connexion au serveur : ' . mysql_error());
			
	
			if (!mysql_select_db(NOM_BD))
				die('Problème de connexion à la base de données : ' . mysql_error());
			
			$sql = "SELECT U_ID, U_Login, U_Password, U_Nom, U_Prenom  FROM t_usagers WHERE U_Login = '" . addslashes($_POST["txtLogin"]) . "' AND U_Password = '" . addslashes($_POST["txtPassword"]) . "' ;";	
	
			$resultat = mysql_query($sql);
			
			//Si erreur SQL
			if (!$resultat)
				die('Problème avec la requète : '. $sql . '<br/>' . mysql_error());
	
			
			//--------------------------------------------------------	
			//Si l'usager existe
			if (mysql_num_rows($resultat) == 1)			
			{
				$tabUsager = mysql_fetch_assoc($resultat);			
					session_start();
					
					//mettre son Id dans la var Session
					$_SESSION['user_in'] =  $tabUsager['U_ID'];	
					
					
					mysql_close($connection);	
					header("Location: usager.php");	//Redirection avant toute balise HTML
	
			}
			//--------------------------------------------------------
			else
			{
				mysql_close($connection);	
				header("Location: index.php?message=UsagerInexistant");	
			}
		}
		//--------------------------------------------------------
		else
			header("Location: index.php?message=codeEtOuMotDePasseManquant");
	}
	//--------------------------------------------------------
	//Si la page est appelée sans passer par le bouton Se connecter (index.php)
	else
			header("Location: index.php?message=sessionfinie");	
	   
	   
?>