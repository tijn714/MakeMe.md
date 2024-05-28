## MakeMe.md

MakeMe.md is een Markdown-editor gebouwd met behulp van het wxWidgets-framework. Deze software stelt gebruikers in staat om Markdown-bestanden te maken, bewerken en op te slaan met behulp van een gebruiksvriendelijke grafische interface.

### Functies

- **Opmaakopties:** Maak gebruik van knoppen voor het vet maken, cursief maken, maken van een checklist, invoegen van links, maken van blockquotes, codeblokken en kopteksten.
- **Bestandsbewerking:** Open bestaande Markdown-bestanden, bewerk ze en sla ze op.
- **Gebruiksvriendelijke interface:** Eenvoudig te begrijpen interface voor het bewerken van Markdown-bestanden.
- **Cross-platform:** Beschikbaar voor Windows, macOS en Linux dankzij het gebruik van het wxWidgets-framework.

### Hoe te gebruiken

1. **Openen van bestanden:** Klik op "Bestand" in het menu en kies "Openen..." om een Markdown-bestand te openen.
2. **Opslaan van bestanden:** Klik op "Bestand" in het menu en kies "Opslaan..." om het huidige bestand op te slaan als een Markdown-bestand.
3. **Opmaakopties:** Gebruik de knoppen voor vet maken, cursief maken, maken van een checklist, invoegen van links, maken van blockquotes, codeblokken en kopteksten om de opmaak van de tekst te wijzigen.

 
***Meer opties zullen snel worden toegevoegd!***

### Bouwen van de broncode

Om MakeMe.md vanuit de broncode te bouwen, volg deze stappen:

1. **Installeer wxWidgets:** Zorg ervoor dat wxWidgets geïnstalleerd is op uw systeem. Raadpleeg de documentatie van wxWidgets voor instructies over hoe u dit kunt doen.
2. **Installer CMake:** Zorg ervoor dat CMake geïnstalleerd is op uw systeem. 
3. **Bouwen van de app:**
- Maak de folder ```build``` aan met het commando ```mkdir -p build```
- Ga in de folder ```build```
- Genereer de makefile met CMake, voer het commando ```cmake ..``` uit om dat te doen.
- bouw MakeMe.md door het command ```make``` uit te voeren.

### Auteurs

MakeMe.md is geschreven door Tijn Rodrigo.

### Licentie

Dit project is gelicentieerd onder de MIT-licentie. Zie het bestand LICENSE voor meer informatie.