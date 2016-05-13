var alreadyRun=false;

window.onload = function(){
  if(alreadyRun){
    return;
  }
  
  alreadyRun = true;
  
  init();
}

function init(){
  var language = "";
  language = window.navigator.language;
  language = language.substr(0, 2);
  
  if(language != "en"){
    switch(language){
      case "it":
	changeLanguage(lang_IT);
	break;
	
    }
  }
}

function changeLanguage(lan){
  document.getElementById("viewPrj").innerHTML = lan.viewPrj;
  
  document.getElementById("sub_title").innerHTML = lan.sub_title;
  document.getElementById("intro").innerHTML = lan.intro;
  
  document.getElementById("bugfix").innerHTML = lan.bugfix;
  document.getElementById("feature_1").innerHTML = lan.feature_1;
  document.getElementById("feature_2").innerHTML = lan.feature_2;
  document.getElementById("feature_3").innerHTML = lan.feature_3;
  document.getElementById("feature_4").innerHTML = lan.feature_4;
  
  document.getElementById("update_title").innerHTML = lan.update_title;
  document.getElementById("update").innerHTML = lan.update;
  
  document.getElementById("compile_title").innerHTML = lan.compile_title;
  document.getElementById("compile").innerHTML = lan.compile;
  
  document.getElementById("download_title").innerHTML = lan.download_title;
  document.getElementById("download").innerHTML = lan.download;
  
  document.getElementById("ppa_title").innerHTML = lan.ppa_title;
  document.getElementById("ppa").innerHTML = lan.ppa;
}

lang_IT = {
  viewPrj: "Guarda il progetto su",
  
  sub_title: "Scarica ora Series v1.2",
  intro: "Series 1.2 è ora disponibile per Linux!",
  
  bugfix: "Al momeno non sono presenti bug da risolvere.",
  feature_1: "Prima versione stabile",
  feature_2: "Aggiunti C preprocessor tag",
  feature_3: "Aggiunto dialog informativo",
  feature_4: "Aggiunto controllore di aggiornamenti con la libreria Fervor",
  
  update_title: "Come aggiornare",
  update: "Puoi aggiornare il programma in vari modi, dipende da che sistema operativo usi.",
  
  compile_title: "Compialre il codice sorgente",
  compile: "Se il tuo OS non è Debian (o una distro di Debian) o preferisci compilare il programma per conto tuo, puoi semplicemente scaricare <a href='https://github.com/Mani-GS/series/releases/latest' target='blank'>l'ultima release</a> e compilarla con queste istruzioni (vai alla <a href='index.html' target='blank'>pagina principale</a> per maggiori informazioni):",
  
  download_title: "Scaricare il pacchetto .deb",
  download: "Scarica il pacchetto .deb <strong>compilato su Debian 8 Jessie 64-bit</strong> ed eseguilo. Il sistema operativo aggiornerà automaticamente il programma.",
  
  ppa_title: "Aggiornare da PPA (solo per Ubuntu Trusty o più recente)",
  ppa: "Se stai usando Ubuntu Trusty o più recente e hai installato il progrmma dal PPA (ppa:mani-ddev/series) puoi aggiornarlo eseguendo:"
};
