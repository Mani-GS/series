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

	document.getElementById("features_1").innerHTML = language.features_1;
	document.getElementById("features_2").innerHTML = language.features_2;
	document.getElementById("features_3").innerHTML = language.features_3;

	document.getElementById("todo_1").innerHTML = language.todo_1;

	document.getElementById("install").innerHTML = language.install;
	document.getElementById("install_intro").innerHTML = language.install_intro;

	document.getElementById("linux_intro").innerHTML = language.linux_intro;
	document.getElementById("linux_install_1").innerHTML = language.linux_install_1;
	document.getElementById("linux_install_1_1").innerHTML = language.linux_install_1_1;
	document.getElementById("linux_install_1_2").innerHTML = language.linux_install_1_2;
	document.getElementById("linux_install_1_3").innerHTML = language.linux_install_1_3;	

	document.getElementById("linux_install_2").innerHTML = language.linux_install_2;
	document.getElementById("linux_install_2_1").innerHTML = language.linux_install_2_1;

	document.getElementById("mac_intro").innerHTML = language.mac_intro;
	document.getElementById("mac_install_1").innerHTML = language.mac_install_1;
	document.getElementById("mac_install_2").innerHTML = language.mac_install_2;
	document.getElementById("mac_install_3").innerHTML = language.mac_install_3;
	document.getElementById("mac_install_4").innerHTML = language.mac_install_4;

	document.getElementById("windows_intro").innerHTML = language.windows_intro;
	document.getElementById("windows_install_1").innerHTML = language.windows_install_1;
	document.getElementById("windows_install_2").innerHTML = language.windows_install_2;
	document.getElementById("windows_install_3").innerHTML = language.windows_install_3;
	document.getElementById("windows_install_4").innerHTML = language.windows_install_4;
}

lang_IT={
	title: "Tieni traccia delle tue serie TV preferite",
	viewPrj: "Guarda il progetto su",
	introduction: "Tieni traccia delle tue serie TV preferite! Con questo semplice programma potrai creare un database sqlite e aggiungere l'ultima stagione/episodio visti. Puoi farlo per tutte le serie che vorrai! Non ti dimenticherai mai qual'era l'ultimo episodio visto. Questo programma utilizza Qt e le librerie sqlite. <br /> È disponibile per <strong>Linux</strong> (Debian distro), <strong>Windows</strong> e <strong>Mac OS X</strong>. Puoi scaricare il codice sorgente e compilarlo per conto tuo o, più semplicemente, scaricare il binario pre-compilato per il tuo sistema.",
	
	features_1: "Aggiungere nuove serie TV in un database sqlite;",
	features_2: "Tenere traccia dell'ultimo episodio e dell'ultima stagione visti, con un &quot;finish&quot; flag da utilizzare a piacere dell'utente;",
	features_3: "Rinominazione riordinamento e rimozione delle serie.",

	todo_1: "Implementare il servizio cloud per condividere il database con altri dispositivi.",

	install: "Installazione",
	install_intro: "Come installare il programma nel tuo sistema operativo.",

	linux_intro: "Binario pre-compilato disponibile. Il pacchetto .deb è stato compilato su <strong>Debian 8 Jessie 64-bit</strong>.",
	linux_install_1: "Scarica il codice sorgente e compilalo per conto tuo",
	linux_install_1_1: "Per compilare questo programma assicurati di aver installato le seguenti librerie:",
	linux_install_1_2: "Prima di tutto scarica l'ultima release, quindi estrai il codice sorgente in una cartella. Apri un terminale in quella cartella ed esegui:",
	linux_install_1_3: "Fai doppio click sul file ELF, chiamato <strong>series</strong>, e il programma si avvierà!<br />Se vuoi creare un file .desktop puoi utilizzare l'immagine series_.png (128x128) come icona del file.",

	linux_install_2: "Installazione su Ubuntu Trusty o più recente",
	linux_install_2_1: "Puoi scaricare ed installare il pacchetto binario dal repository PPA <strong>ppa:mani-ddev/series</strong>. Apri un terminale ed esegui:",

	mac_intro: "Binario pre-compilato disponibile. Il file .dmg è stato compilato su <strong>Mac OS X 10.11 El Capitan 64-bit</strong>.",
	mac_install_1: "Per compilare questo programma assicurati di aver installato tutte le librerie <strong>Qt</strong>; se stai usando una versione di OS X precedente alla 10.5 (Leopard), dovrai installare anche le librerie <strong>sqlite3</strong>.<br />Inoltre assicurati di esportare la <strong><u>qmake path</u></strong> in questo modo:",
	mac_install_2: "Prima di tutto scarica l'ultima release, quindi estrai il codice sorgente in una cartella. Apri un terminale in quella cartella ed esegui:",
	mac_install_3: "Se vuoi farlo funzionare in un altro MAC (un MAC senza librerie Qt) dovrai eseguire il seguente comando:",
	mac_install_4: "Fai doppio click sul file APP, chiamato <strong>series</strong>, e il programma si avvierà!",

	windows_intro: "Binario pre-compilato disponibile. Il file .exe è stato compilato su <strong>Windows 10 64-bit</strong> (funziona anche su versioni a 32-bit).",
	windows_install_1: "Per iniziare,  <a href='http://www.qt.io/download/' target='blank'>scarica Qt Creator</a>.<br />Quindi, una volta che avrai scaricato l'ultima release, apri il file <strong>series.pro</strong> con il tuo editor di testo preferito per includere i file sqlite3.c e sqlite3.h:",
	windows_install_2: "Devi solamente rimuovere il carattere # all'inizio delle due righe che lo presentano (prima di sqlite3.c e di sqlite3.h). Quindi apri il progetto con Qt Creator, seleziona Build -> Release e compilalo.<br />Per farlo funzionare (sul tuo PC, con le librerie Qt già installate) avrai bisogno delle seguenti dll nella cartella del file .exe:",
	windows_install_3: "Se vuoi farlo funzionare in altro PC (un PC senza librerie Qt) dovrai creare una cartella come questa:",
	windows_install_4: "Ora, fai doppio click sul file EXE, chiamato <strong>series</strong>, e il programma si avvierà!"
};
