var eseguito = false;

window.onload = function(){
	if(eseguito){
		return;
	}
	eseguito = true;
	
	init();
}

function init(){
	var language = "";
	language = window.navigator.language;
	language = language.substr(0,2);
	
	if(language != "en"){
		switch(language){
			
			case "it":
				changeLanguage(lang_IT);
				break;
		}
	}
}

function changeLanguage(language){
	document.getElementById("title").innerHTML = language.title;
	document.getElementById("viewPrj").innerHTML = language.viewPrj;
	document.getElementById("introduction").innerHTML = language.introduction;
	document.getElementById("install").innerHTML = language.install;
	document.getElementById("install_1").innerHTML = language.install_1;
	document.getElementById("install_1_1").innerHTML = language.install_1_1;
	document.getElementById("install_1_2").innerHTML = language.install_1_2;
	document.getElementById("install_1_3").innerHTML = language.install_1_3;
	document.getElementById("install_2").innerHTML = language.install_2;
	document.getElementById("install_2_1").innerHTML = language.install_2_1;
	document.getElementById("features_1").innerHTML = language.features_1;
	document.getElementById("features_2").innerHTML = language.features_2;
	document.getElementById("features_3").innerHTML = language.features_3;
	document.getElementById("todo_1").innerHTML = language.todo_1;
}

lang_IT={
	title: "Tieni traccia delle tue serie TV preferite",
	viewPrj: "Guarda il progetto su",
	introduction: "Tieni traccia delle tue serie TV preferite! Con questo semplice programma potrai creare un database sqlite e aggiungere l'ultima stagione/episodio visti. Puoi farlo per tutte le serie che vorrai! Non ti dimenticherai mai qual'era l'ultimo episodio visto. Questo programma utilizza Qt e le librerie sqlite.",
	install: "Installazione (Linux)",
	install_1: "Scarica il codice sorgente e compilalo da solo",
	install_1_1: "Per compilare questo programma assicurati di aver installato le seguenti librerie:",
	install_1_2: "Prima di tutto scarica l'ultima release, quindi estrai il codice sorgente in una cartella. Apri un terminale in quella cartella ed esegui:",
	install_1_3: "Creerà molti file, necessiti solamente di uno di essi: il file ELF, chiamato <strong>series</strong>. Premi due volte su di esso e il programma si avvierà!<br />Se vuoi creare un file .desktop puoi utilizzare l'immagine series_.png (128x128) come icona del file.",
	install_2: "Installazione su Ubuntu Trusty o più recente",
	install_2_1: "Puoi scaricare ed installare il pacchetto binario dal repository PPA <strong>ppa:mani-ddev/series</strong>. Apri un terminale ed esegui:",
	features_1: "Aggiungere nuove serie TV in un database sqlite;",
	features_2: "Tenere traccia dell'ultimo episodio e dell'ultima stagione visti, con un &quot;finish&quot; flag da utilizzare a piacere dell'utente;",
	features_3: "Rinominazione riordinamento e rimozione delle serie.",
	todo_1: "Implementare il servizio cloud per condividere il database con altri dispositivi."
};
